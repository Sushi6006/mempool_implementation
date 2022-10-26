#include <stdio.h>
#include <stdlib.h>

#include "mempool.h"

int main(void) {

    s_mempool_ctrl g_mempool_ctrl_info;
    mempool_init(&g_mempool_ctrl_info);
    mempool_print(&g_mempool_ctrl_info);
    VOS_VOID* memory_allocated[20];

    // try to allocate to max and more
    printf("ALLOCATING 20 BLOCKS OF MEMORY...\n");
    for (int i = 0; i < 20; i++) {
        VOS_VOID* p_ret = mempool_alloc(&g_mempool_ctrl_info, 20);
        memory_allocated[i] = p_ret;
        printf("memory allocated #%02d: %p\n", i, p_ret);
    }
    printf("\n\n");

    mempool_print(&g_mempool_ctrl_info);

    // free some of the memory
    printf("FREEING 5 BLOCKS OF MEMORY...\n\n");
    for (int i = 0; i < 5; i++) {
        mempool_free(&(g_mempool_ctrl_info), memory_allocated[i]);
    }

    mempool_print(&g_mempool_ctrl_info);

    return 0;

}
