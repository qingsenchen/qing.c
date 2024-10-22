#include <stdio.h>
#include <stdbool.h>

#include "qing_tensor.h"
#include "qing_common.h"


int main() {
    printf("Hello, World!\n");

    const int64_t stride[2] = {2, 3};
    const int64_t stride2[2] = {3, 2};

    QingTensor* one = qingNewTensor(QING_DTYPE_F32, 2, stride);
    qingTensorSetName(one, "conv1d");
    QingTensor* two = qingTensorView(one, 2, stride2);
    printf("Tensor Size: %lu\n", sizeof(*one));

    qingTensorSetValue(one, 0.21);


    qingPrintTensor(one);
    qingTensorSetValue(one, 0.1);
    qingPrintTensor(two);

    printf("Tensor Dims: %d\n", qingTensorDims(one));



    return 0;
}
