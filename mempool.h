#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <ctype.h>
#include <stdint.h>

/***************** VOS TYPEDEFS *****************/
#define VOS_VOID     void
#define VOS_OK       (0)
#define VOS_ERR      (1)
#define VOS_TRUE     (1)
#define VOS_FALSE    (0)
#define VOS_NULL     (0)
#define VOS_NULL_PTR (0L)

typedef uint8_t  VOS_BOOL;
typedef uint8_t  VOS_UINT8;
typedef uint16_t VOS_UINT16;
typedef uint32_t VOS_UINT32;

/***************** MEMPOOL DEFINES *****************/
#define MEMPOOL_MAX_LEN  32   // alloc max 32 times before freed
#define MEMPOOL_MAX_SIZE 512  // max size of each malloc
#define MEMPOOL_TOTAL_SIZE (MEMPOOL_MAX_LEN * MEMPOOL_MAX_SIZE)

/***************** MEMPOOL TYPEDEFS *****************/
typedef struct mempool_queue {
    VOS_UINT32 queue_total_len;
    VOS_UINT32 queue_curr_len;
    VOS_UINT32 queue_head_pos;
    VOS_UINT32 queue_tail_pos;
    VOS_VOID** p_queue;
} s_mempool_queue;

typedef struct mempool_ctrl {
    VOS_VOID*  mempool_base;        // first memory in mempool
    VOS_UINT32 mempool_curr_usage;  // size_t, amount of mempool used
    VOS_UINT32 mempool_remain;      // size_t, amount of mempool left
    VOS_UINT32 error_count;         // times where memory failed to alloc
    VOS_UINT32 alloc_free_diff;     // alloc: +1; free: -1;
} s_mempool_ctrl;

/***************** FUNCTION DECLARATIONS *****************/
VOS_UINT32 queue_init(s_mempool_queue* queue_info);
VOS_UINT32 queue_enqueue(s_mempool_queue* queue_info, VOS_VOID* data);
VOS_UINT32 queue_dequeue(s_mempool_queue* queue_info, VOS_VOID* data);


VOS_UINT32 mempool_init(s_mempool_ctrl* ctrl_info);
VOS_VOID*  mempool_alloc(s_mempool_ctrl* ctrl_info, VOS_UINT32 size);
VOS_VOID*  mempool_free(s_mempool_ctrl* ctrl_info, VOS_VOID* addr);

#endif