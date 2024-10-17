#include <stdio.h>
#include <stdbool.h>

#include "qing_tensor.h"
#include "qing_common.h"


int main() {
    printf("Hello, World!\n");

    const int64_t stride[4] = {2,2,2,2};
    QingTensor* one = qingNewTensor(QING_DTYPE_F32, 4, stride);
    QingTensor* two = qingNewTensor(QING_DTYPE_F32, 4, stride);
    printf("Tensor Size: %lu\n", sizeof(*one));

    qingTensorSet(one, 0.21);

    qingPrintTensor(one);

    printf("Tensor Dims: %d\n", qingTensorDims(one));



    return 0;
}
