#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <ctype.h>

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

typedef struct mempool_queue {
    /* data */
} s_mempool_queue;

typedef struct mempool_ctrl {
    VOS_VOID*  mempool_base;        // first memory in mempool
    VOS_UINT32 mempool_curr_usage;  // size_t, amount of mempool used
    VOS_UINT32 mempool_remain;      // size_t, amount of mempool left
    VOS_UINT32 error_count;         // times where memory failed to alloc
    VOS_UINT32 free_alloc_diff;     // alloc: +1; free: -1;
} s_mempool_ctrl;

VOS_UINT32 mempool_init(s_mempool_ctrl* ctrl_info);
VOS_VOID*  mempool_alloc(s_mempool_ctrl* ctrl_info, VOS_UINT32 size);
VOS_VOID*  mempool_free(s_mempool_ctrl* ctrl_info, VOS_VOID* addr);

#endif