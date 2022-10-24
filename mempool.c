#include <stdio.h>
#include <stdlib.h>

#include "mempool.h"

/***********************************************
 * mempool_init
 * function:
 *     initialise the mempool and the control info
 * input:
 *     ctrl_info: control info
 * output:
 *     ctrl_info: intialised control info
 ***********************************************/
VOS_UINT32 mempool_init(s_mempool_ctrl* ctrl_info) {

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

}