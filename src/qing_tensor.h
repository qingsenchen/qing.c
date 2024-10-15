#ifndef QING_TENSOR_H
#define QING_TENSOR_H

#include <stdlib.h>
#include "qing_common.h"

typedef enum {
    QING_DTYPE_F32     = 0,
    QING_DTYPE_F16     = 1,
} DType;

typedef enum {
    QING_OP_NONE = 0,
    QING_OP_ADD,
} OpType;

typedef struct sQingTensor QingTensor;
struct sQingTensor {
    DType   type;
    OpType  op;

    int64_t     stride[QING_MAX_DIMS];
    size_t      offs[QING_MAX_DIMS];

    void        *data;
};

#endif //QING_TENSOR_H
