#include <stdio.h>
#include <stdlib.h>

#include "mempool.h"

int main(void) {

    s_mempool_ctrl g_mempool_ctrl_info;

    // TODO: testings: using the mempool
    mempool_init(&g_mempool_ctrl_info);

    return 0;

}