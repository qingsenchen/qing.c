#ifndef QING_TENSOR_H
#define QING_TENSOR_H

#include <stdlib.h>
#include <stdbool.h>
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

    QING_OP_VIEW,
    QING_OP_TRANSPOSE,
} OpType;

typedef struct sQingTensor QingTensor;

struct sQingTensor {
    QingObj     obj;
    DType       type;
    OpType      op;

    int64_t     sizes[QING_MAX_DIMS];
    size_t      stride[QING_MAX_DIMS];

    char        name[QING_MAX_NAME];
    QingTensor  *grad;
    QingTensor  *input[QING_MAX_INPUT];
    void        *storage;
};

QingTensor* qingNewTensor(DType dtype, int n_dims, const int64_t *sizes);
QingTensor* qingTensorView(QingTensor* src, int n_dims, const int64_t *sizes);
QingTensor* qingTensorTranspose(QingTensor* src);
int qingTensorDims(const QingTensor * tensor);

void qingPrintTensor(const QingTensor* tensor);
QingTensor* qingTensorSetName(QingTensor* tensor, const char * name);
QingTensor* qingTensorSetValue(QingTensor* tensor, const float value);

bool qingTensorIsContiguous(QingTensor* tensor);

#endif //QING_TENSOR_H
