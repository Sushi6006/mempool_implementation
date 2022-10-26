#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <ctype.h>
#include <stdint.h>
#include <string.h>

/***************** VOS TYPEDEFS *****************/
// #define VOS_VOID     void
#define VOS_OK       (0)
#define VOS_ERR      (1)
#define VOS_TRUE     (1)
#define VOS_FALSE    (0)
#define VOS_NULL     (0)
#define VOS_NULL_PTR (0L)

typedef void     VOS_VOID;
typedef uint8_t  VOS_BOOL;
typedef uint8_t  VOS_UINT8;
typedef uint16_t VOS_UINT16;
typedef uint32_t VOS_UINT32;

/***************** MEMPOOL DEFINES *****************/
#define MEMPOOL_MAX_LEN  10   // alloc max 32 times before freed: TODO:
#define MEMPOOL_MAX_SIZE 512  // max size of each malloc
#define MEMPOOL_TOTAL_SIZE (MEMPOOL_MAX_LEN * MEMPOOL_MAX_SIZE)

/***************** MEMPOOL TYPEDEFS *****************/
typedef enum {
    ERR_QUEUE_NOT_EXIST=8,
    ERR_QUEUE_MALLOC_FAIL,    // 9
    ERR_QUEUE_IS_FULL,        // 10
    ERR_QUEUE_IS_EMPTY,       // 11
    ERR_QUEUE_INVALID_DATA,   // 12
    ERR_POOL_MALLOC,          // 13
    ERR_POOL_NULL_IN_QUEUE,   // 14
    ERR_POOL_SIZE_TOO_LARGE,  // 15
    ERR_POOL_FREE_NULL,       // 16
} mempool_err_list;

typedef struct mempool_queue {
    VOS_UINT32 queue_curr_len;
    VOS_UINT32 queue_head_pos;
    VOS_UINT32 queue_tail_pos;
    VOS_VOID** p_queue;
} s_mempool_queue;

typedef struct mempool_ctrl {
    VOS_VOID*  mempool_base;     // first memory in mempool
    VOS_UINT32 error_count;      // times where memory failed to alloc
    VOS_UINT32 alloc_free_diff;  // alloc: +1; free: -1;
    s_mempool_queue ctrl_queue;  // queue to manage the pool, indicates memory available
} s_mempool_ctrl;

/***************** FUNCTION DECLARATIONS *****************/\

VOS_UINT32 mempool_init_queue(s_mempool_queue* queue_info);
VOS_UINT32 mempool_enqueue(s_mempool_queue* queue_info, VOS_VOID* data);
VOS_UINT32 mempool_dequeue(s_mempool_queue* queue_info, VOS_VOID** data);
VOS_VOID   mempool_print_queue(s_mempool_queue* queue_info);

VOS_UINT32 mempool_init(s_mempool_ctrl* ctrl_info);
VOS_VOID*  mempool_alloc(s_mempool_ctrl* ctrl_info, VOS_UINT32 size);
VOS_UINT32 mempool_free(s_mempool_ctrl* ctrl_info, VOS_VOID* addr);
VOS_VOID   mempool_print(s_mempool_ctrl* ctrl_info);

#endif  // __MEMPOOL_H__
