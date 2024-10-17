#ifndef QING_TENSOR_H
#define QING_TENSOR_H

#include <stdlib.h>
#include "qing_common.h"
#include "qing_object.h"


typedef enum {
    QING_DTYPE_F32     = 0,
    QING_DTYPE_COUNT
} DType;

typedef struct sDTypeTraits {
    const char             * type_name;
    int64_t                  blck_size;
    size_t                   type_size;
    bool                     is_quantized;
} DTypeTraits;

typedef enum {
    QING_OP_NONE = 0,
    QING_OP_ADD,
} OpType;

typedef struct sQingTensor QingTensor;
struct sQingTensor {
    QingObj     obj;
    DType       type;
    OpType      op;

    int64_t     stride[QING_MAX_DIMS];
    size_t      bytes[QING_MAX_DIMS];

    char        name[QING_MAX_NAME];
    void        *data;
};

QingTensor* qingNewTensor(DType dtype, int n_dims, const int64_t *stride);
int qingTensorDims(const QingTensor * tensor);

void printTensor(const QingTensor* tensor);
QingTensor* qingTensorSet(QingTensor* tensor, const float value);


#endif //QING_TENSOR_H
