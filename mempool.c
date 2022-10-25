#include <stdio.h>
#include <stdlib.h>

#include "mempool.h"

VOS_UINT32 queue_init(s_mempool_queue* queue_info) {

    queue_info->queue_total_len = MEMPOOL_MAX_LEN;
    queue_info->queue_curr_len  = MEMPOOL_MAX_LEN;
    queue_info->queue_head_pos  = 0;
    queue_info->queue_tail_pos  = MEMPOOL_MAX_LEN;



    return VOS_OK;

}

/***********************************************
 * mempool_init
 * function:
 *     initialise the mempool and the control info
 * input:
 *     ctrl_info: control info
 * output:
 *     ctrl_info: intialised control info
 * return:
 *     VOS_OK if successfully initialised
 *     VOS_ERR if failed to malloc memory
 ***********************************************/
VOS_UINT32 mempool_init(s_mempool_ctrl* ctrl_info) {

    // init queue

    ctrl_info->mempool_base = (VOS_VOID*)malloc(MEMPOOL_TOTAL_SIZE);

    for (int i = 0; i < MEMPOOL_MAX_LEN; i++) {
        // enqueue memset
    }
    
    if (ctrl_info->mempool_base == VOS_NULL_PTR) {
        return VOS_ERR;
    }

    ctrl_info->mempool_curr_usage = 0;
    ctrl_info->mempool_remain     = MEMPOOL_MAX_SIZE;
    ctrl_info->error_count        = 0;
    ctrl_info->alloc_free_diff    = 0;

    return VOS_OK;

}

/***********************************************
 * mempool_alloc
 * function:
 *     allocate memory as asked
 * input:
 *     ctrl_info: control info
 *     size:      size of memory needed
 * output:
 *     ctrl_info: intialised control info
 ***********************************************/
VOS_VOID* mempool_alloc(s_mempool_ctrl* ctrl_info, VOS_UINT32 size) {



    return VOS_NULL_PTR;

}

/***********************************************
 * mempool_free
 * function:
 *     free the memory given from mempool
 * input:
 *     ctrl_info: control info
 *     addr:      address of the memory to be freed
 * output:
 *     pointer of freed memory, null if failed
 ***********************************************/
VOS_VOID* mempool_free(s_mempool_ctrl* ctrl_info, VOS_VOID* addr) {

    return VOS_NULL_PTR;

}