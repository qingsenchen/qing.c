#include <stdio.h>
#include <stdbool.h>

#include "qing_tensor.h"
#include "qing_common.h"


int main() {
    printf("Hello, World!\n");

    const int64_t stride[2] = {3, 3};
    const int64_t stride2[2] = {3, 2};

    QingTensor* one = qingNewTensor(QING_DTYPE_F32, 2, stride);
    qingTensorSetName(one, "conv1d");

    qingTensorSetValue(one, 0.21);

    qingPrintTensor(one);


    printf("one IsContiguous: %d\n", qingTensorIsContiguous(one));

    QingTensor* two = qingTensorTranspose(one);
    qingPrintTensor(two);
    printf("two IsContiguous: %d\n", qingTensorIsContiguous(two));

    printf("Tensor Dims: %d\n", qingTensorDims(one));



    return 0;
}
