#include <stdio.h>
#include <stdbool.h>

#include "qing_tensor.h"
#include "qing_common.h"


int main() {
    printf("Hello, World!\n");
    printf("Tensor Size: %lu\n", sizeof(QingTensor));
    QING_ASSERT(1!=1, "test");
    return 0;
}