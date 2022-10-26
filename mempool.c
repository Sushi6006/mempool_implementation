/***********************************************
 * mempool.c
 * basic memory pool implementation with queue
 * - each block shares the same size
 * - initiate and free return memory to the queue (enqueue)
 * - alloc get memory from the queue (dequeue)
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

#include "mempool.h"

VOS_UINT32 mempool_init_queue(s_mempool_queue* queue_info) {

    queue_info->queue_head_pos = 0;
    queue_info->queue_tail_pos = 0;
    queue_info->queue_curr_len = 0;
    queue_info->p_queue = (VOS_VOID*)malloc(sizeof(VOS_VOID*) * MEMPOOL_MAX_LEN);

    if (queue_info->p_queue == VOS_NULL_PTR) {
        return ERR_QUEUE_MALLOC_FAIL;
    }

    return VOS_OK;

}

/***********************************************
 * mempool_enqueue
 * function:
 *     add data to queue, used when initialising mempool and free
 ***********************************************/
VOS_UINT32 mempool_enqueue(s_mempool_queue* queue_info, VOS_VOID* data) {

    // check failures
    if (queue_info->queue_curr_len == MEMPOOL_MAX_LEN) {
        // head == 0 and tail == max len
        // OR head - 1 == tail (wrapped around)
        return ERR_QUEUE_IS_FULL;
    }
    if (data == VOS_NULL_PTR) {
        return ERR_QUEUE_INVALID_DATA;
    }

    // enqueue
    queue_info->p_queue[queue_info->queue_tail_pos] = data;
    
    // update ctrl info
    if (queue_info->queue_tail_pos >= MEMPOOL_MAX_LEN - 1) {
        queue_info->queue_tail_pos = 0;
    } else {
        queue_info->queue_tail_pos++;
    }
    queue_info->queue_curr_len++;
    
    return VOS_OK;

}

/***********************************************
 * mempool_dequeue
 * function:
 *     get data from queue, used when alloc
 ***********************************************/
VOS_UINT32 mempool_dequeue(s_mempool_queue* queue_info, VOS_VOID** data) {

    // check failures
    if (queue_info->queue_curr_len == 0) {
        // head == tail == 0
        return ERR_QUEUE_IS_EMPTY;
    }

    // dequeue
    *data = queue_info->p_queue[queue_info->queue_head_pos];

    // update ctrl info
    if (queue_info->queue_head_pos >= MEMPOOL_MAX_LEN - 1) {
        queue_info->queue_head_pos = 0;
    } else {
        queue_info->queue_head_pos++;
    }
    queue_info->queue_curr_len--;
    
    return VOS_OK;

}

/***********************************************
 * mempool_print_queue
 * function:
 *     get data from queue, used when alloc
 ***********************************************/
VOS_VOID mempool_print_queue(s_mempool_queue* queue_info) {
    
    printf("%-20s%-20s%-20s\n",
           "queue_curr_len", "queue_head_pos", "queue_tail_pos");
    printf("%-20u%-20u%-20u\n\n",
           queue_info->queue_curr_len,
           queue_info->queue_head_pos,
           queue_info->queue_tail_pos);
    printf("QUEUE CONTENT:\n");
    for (int i = 0; i < MEMPOOL_MAX_LEN; i++) {
        VOS_UINT32 head_pos = queue_info->queue_head_pos;
        VOS_UINT32 tail_pos = queue_info->queue_tail_pos;
        if (head_pos < tail_pos) {
            if ((head_pos <= i) && (i < tail_pos)) {
                printf("%-15p", queue_info->p_queue[i]);
            } else {
                printf("%-15s", "0");
            }
        } else if (head_pos > tail_pos) {
            if ((tail_pos <= i) && (i < head_pos)) {
                printf("%-15s", "0");
            } else {
                printf("%-15p", queue_info->p_queue[i]);
            }
        } else {
            if (queue_info->queue_curr_len == 0) {
                printf("%-15s", "0");
            } else {
                printf("%-15p", queue_info->p_queue[i]);
            }
        }
    }

    printf("\n");

}

/***********************************************
 * mempool_init
 * function:
 *     initialise the mempool and the control info
 ***********************************************/
VOS_UINT32 mempool_init(s_mempool_ctrl* ctrl_info) {

    VOS_UINT32 ret;

    // init queue
    ctrl_info->mempool_base = (VOS_VOID*)malloc(MEMPOOL_TOTAL_SIZE);
    if (ctrl_info->mempool_base == VOS_NULL_PTR) {
        return VOS_ERR;
    }
    memset(ctrl_info->mempool_base, 0, MEMPOOL_TOTAL_SIZE);
    ret = mempool_init_queue(&(ctrl_info->ctrl_queue));
    if (ret != VOS_OK) {
        return ret;
    }

    for (int i = 0; i < MEMPOOL_MAX_LEN; i++) {
        ret = mempool_enqueue(&(ctrl_info->ctrl_queue),
                              ctrl_info->mempool_base + i * MEMPOOL_MAX_SIZE);
        if (ret != VOS_OK) {
            return ret;
        }
    }

    ctrl_info->error_count        = 0;
    ctrl_info->alloc_free_diff    = 0;

    return VOS_OK;

}

/***********************************************
 * mempool_alloc
 * function:
 *     allocate memory as asked
 ***********************************************/
VOS_VOID* mempool_alloc(s_mempool_ctrl* ctrl_info, VOS_UINT32 size) {

    VOS_VOID* p_ret = VOS_NULL_PTR;
    VOS_UINT32 ret;

    if (size > MEMPOOL_MAX_SIZE) {
        ctrl_info->error_count++;
        return VOS_NULL_PTR;
    }

    ret = mempool_dequeue(&(ctrl_info->ctrl_queue), &p_ret);
    
    if (ret != VOS_OK) {
        ctrl_info->error_count++;
        return VOS_NULL_PTR;
    }

    ctrl_info->alloc_free_diff++;
    return p_ret;

}

/***********************************************
 * mempool_free
 * function:
 *     free the memory given from mempool
 ***********************************************/
VOS_UINT32 mempool_free(s_mempool_ctrl* ctrl_info, VOS_VOID* addr) {

    // if (addr == VOS_NULL_PTR) {
    //     // tries to free a null pointer
    //     return ERR_POOL_FREE_NULL;
    // }

    VOS_UINT32 ret;
    memset(addr, 0, MEMPOOL_MAX_SIZE);
    ret = mempool_enqueue(&(ctrl_info->ctrl_queue), addr);
    if (ret == VOS_OK) {
        ctrl_info->alloc_free_diff--;
    }
    return ret;

}

VOS_VOID mempool_print(s_mempool_ctrl* ctrl_info) {

    printf("================== MEMPOOL DEBUG INFO ==================\n");

    printf("%-20s%-20s%-20s\n",
           "mempool_base", "error_count", "alloc_free_diff");
    printf("%-20p%-20u%-20u\n",
           ctrl_info->mempool_base,
           ctrl_info->error_count,
           ctrl_info->alloc_free_diff);

    mempool_print_queue(&(ctrl_info->ctrl_queue));

    printf("================== MEMPOOL DEBUG INFO ==================\n\n");

}
