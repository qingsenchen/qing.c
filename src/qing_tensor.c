#include <stdbool.h>

#include "qing_tensor.h"

#include <string.h>

#include "qing_object.h"

static const DTypeTraits dtype_traits[QING_DTYPE_COUNT] = {
    [QING_DTYPE_F32] = {
        .type_name                = "f32",
        .blck_size                = 1,
        .type_size                = sizeof(float),
        .is_quantized             = false,
    }
};

#define QING_DTYPE_SIZE(dtype) \
    (dtype_traits[dtype].type_size)

#define QING_DTYPE_NAME(dtype) \
    (dtype_traits[dtype].type_name)

#define QING_ROW_SIZE(dtype, size) \
    (QING_DTYPE_SIZE(dtype) * (size))

#define QING_TENSOR_NROWS(tensor) \
    (tensor->stride[1]*tensor->stride[2]*tensor->stride[3])

#define QING_TENSOR_NATOM(tensor) \
    (tensor->stride[0]*QING_TENSOR_NROWS(tensor))

static QingTensor* qingNewTensorImpl(DType dtype, int n_dims, const int64_t *stride) {

    QING_ASSERT(n_dims >= 1 && n_dims <= QING_MAX_DIMS, "n_dims out of range");

    size_t head_size = sizeof(QingTensor);
    size_t data_size = QING_ROW_SIZE(QING_DTYPE_F32, stride[0]);

    for (int i = 1; i < n_dims; i++) {
        data_size *= stride[i];
    }

    QingTensor* tensor = (QingTensor*)qingAllocateObject(head_size + data_size, QING_OBJ_TENSOR);

    *tensor = (QingTensor) {
        .type   = dtype,
        .op     = QING_OP_NONE,
        .stride = { 1, 1, 1, 1 },
        .bytes  = { 0, 0, 0, 0 },
        .data   = data_size > 0 ? (void *)(tensor + 1) : NULL
    };

    for (int i = 0; i < n_dims; i++) {
        tensor->stride[i] = stride[i];
    }

    tensor->bytes[0] = QING_DTYPE_SIZE(dtype);
    tensor->bytes[1] = QING_ROW_SIZE(QING_DTYPE_F32, stride[0]);
    for (int i = 2; i < QING_MAX_DIMS; i++) {
        tensor->bytes[i] = tensor->bytes[i - 1]*tensor->stride[i - 1];
    }

    //printf("diff:%lu\n", (void*)tensor->data - (void*)tensor);
    return tensor;
}

void qingPrintTensor(const QingTensor* tensor) {
    printf("QingTensor(");
    const float* data = (float*)tensor->data;
    const int n_dims = qingTensorDims(tensor);
    size_t n_atom = QING_TENSOR_NATOM(tensor);

    printf("[");
    for (int i = 0; i < n_atom; i++) {
        size_t span = 1;
        for (int j = n_dims - 1; j >= 1; --j) {
            span *= tensor->stride[j];
            if (i % span == 0) {
                printf("[");
            }
        }

        printf("%.2f", data[i]);
        if ( (i+1) % tensor->stride[n_dims-1] > 0 && i+1 < n_atom) {
            printf(",");
        }

        if ( i+1 < tensor->stride[n_dims-1]) continue;

        span = 1;
        bool is_comma = false;
        for (int j = n_dims - 1; j >= 1; --j) {
            span *= tensor->stride[j];
            if ( (i+1) % span == 0 ) {
                printf("]");
                if (i+1 < n_atom) {
                    is_comma = true;
                }
            }
        }

        if (is_comma) {
            printf(",");
        }
    }
    printf("] ");
    printf("stride=(");
    for (int i = 0; i < QING_MAX_DIMS; i++) {
        if (tensor->stride[i] == 1) break;
        printf("%ld,", tensor->stride[i]);
    }
    printf(") dtype=%s)\n", QING_DTYPE_NAME(tensor->type));
}

QingTensor* qingNewTensor(DType dtype, int n_dims, const int64_t *stride) {
    return qingNewTensorImpl(dtype, n_dims, stride);
}

QingTensor* qingTensorSet(QingTensor* tensor, const float value) {

    float* data = tensor->data;
    for (int i = 0; i < QING_TENSOR_NATOM(tensor); i++) {
        data[i] = value;
    }
    return tensor;
}

int qingTensorDims(const QingTensor * tensor) {
    for (int i = QING_MAX_DIMS - 1; i >= 1; --i) {
        if (tensor->stride[i] > 1) {
            return i + 1;
        }
    }
    return 1;
}
