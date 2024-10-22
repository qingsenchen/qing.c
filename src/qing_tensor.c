#include <stdbool.h>
#include <stdarg.h>

#include "qing_tensor.h"
#include "qing_object.h"
#include "qing_memory.h"

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
    (tensor->sizes[1]*tensor->sizes[2]*tensor->sizes[3])

#define QING_TENSOR_NATOM(tensor) \
    (tensor->sizes[0]*QING_TENSOR_NROWS(tensor))

static QingTensor* qingNewTensorImpl(DType dtype, int n_dims, const int64_t *sizes, void *storage) {

    QING_ASSERT(n_dims >= 1 && n_dims <= QING_MAX_DIMS, "n_dims out of range");

    size_t data_size = QING_ROW_SIZE(QING_DTYPE_F32, sizes[0]);

    for (int i = 1; i < n_dims; i++) {
        data_size *= sizes[i];
    }

    QingTensor* tensor = ALLOCATE_OBJ(QingTensor, QING_OBJ_TENSOR);

    if (storage == NULL) {
        storage = ALLOCATE_ANY(data_size);
    }

    *tensor = (QingTensor) {
        .type   = dtype,
        .op     = QING_OP_NONE,
        .sizes = { 1, 1, 1, 1 },
        .stride  = { 0, 0, 0, 0 },
        .storage   = storage
    };

    for (int i = 0; i < n_dims; i++) {
        tensor->sizes[i] = sizes[i];
        tensor->stride[i] = 1;
    }

    for (int i = n_dims - 2; i >= 0; --i) {
        tensor->stride[i] = tensor->sizes[i + 1] * tensor->stride[i + 1];
    }

    //printf("diff:%lu\n", (void*)tensor->data - (void*)tensor);
    return tensor;
}

QingTensor* qing_format(QingTensor* tensor, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(tensor->name, sizeof(tensor->name), fmt, args);
    va_end(args);
    return tensor;
}

static QingTensor* qingTensorViewImpl(QingTensor* src, int n_dims, const int64_t *stride) {
    QingTensor* view = qingNewTensorImpl(src->type, n_dims, stride, src->storage);
    qing_format(view, "%s (view)", src->name);
    view->op = QING_OP_NONE;
    return view;
}

QingTensor* qingNewTensor(DType dtype, int n_dims, const int64_t *stride) {
    return qingNewTensorImpl(dtype, n_dims, stride, NULL);
}

QingTensor* qingAddImpl(OpType op, QingTensor* x, QingTensor* y) {
    int n_dims = qingTensorDims(x);

    QingTensor * z = qingNewTensorImpl(x->type, n_dims, x->sizes, NULL);
    z->op = QING_OP_ADD;
    z->input[0] = x;
    z->input[1] = y;

    return z;
}

QingTensor* qingTensorView(QingTensor* src, int n_dims, const int64_t *stride) {
    return qingTensorViewImpl(src, n_dims, stride);
}

QingTensor* qingTensorTranspose(QingTensor* src) {
    int n_dims = qingTensorDims(src);
    QING_ASSERT(n_dims == 2, "transpose only supports the 2d tensor");

    QingTensor * result = qingNewTensorImpl(src->type, n_dims, src->sizes, src->storage);
    qing_format(result, "%s (transpose)", src->name);
    result->op = QING_OP_TRANSPOSE;

    result->sizes[0] = src->sizes[1];
    result->sizes[1] = src->sizes[0];

    result->stride[0] = src->stride[1];
    result->stride[1] = src->stride[0];

    result->input[0] = src;

    return result;
}

bool qingTensorIsContiguous(QingTensor* tensor) {

    int n_dims = qingTensorDims(tensor);
    for (int i = n_dims - 2; i >= 0; --i) {
        if (tensor->stride[i] != tensor->sizes[i + 1] * tensor->stride[i + 1]) {
            return false;
        }
    }
    return true;
}

void qingPrintTensor(const QingTensor* tensor) {
    printf("QingTensor(");
    const float* data = (float*)tensor->storage;
    const int n_dims = qingTensorDims(tensor);
    size_t n_atom = QING_TENSOR_NATOM(tensor);

    printf("[");
    for (int i = 0; i < n_atom; i++) {
        size_t span = 1;
        for (int j = n_dims - 1; j >= 1; --j) {
            span *= tensor->sizes[j];
            if (i % span == 0) {
                printf("[");
            }
        }

        printf("%.2f", data[i]);
        if ( (i+1) % tensor->sizes[n_dims-1] > 0 && i+1 < n_atom) {
            printf(",");
        }

        if ( i+1 < tensor->sizes[n_dims-1]) continue;

        span = 1;
        bool is_comma = false;
        for (int j = n_dims - 1; j >= 1; --j) {
            span *= tensor->sizes[j];
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

    printf("sizes=(");
    for (int i = 0; i < n_dims; i++) {
        printf("%ld,", tensor->sizes[i]);
    }
    printf(") ");
    printf("stride=(");
    for (int i = 0; i < n_dims; i++) {
        printf("%ld,", tensor->stride[i]);
    }
    printf(") dtype=%s name=\'%s\')\n", QING_DTYPE_NAME(tensor->type), tensor->name);
}

const char* qingTensorGetName(const QingTensor* tensor) {
    return tensor->name;
}

QingTensor* qingTensorSetName(QingTensor* tensor, const char * name) {
    size_t i;
    for (i = 0; i < sizeof(tensor->name) - 1 && name[i] != '\0'; i++) {
        tensor->name[i] = name[i];
    }
    tensor->name[i] = '\0';
    return tensor;
}

QingTensor* qingTensorSetValue(QingTensor* tensor, const float value) {

    float* data = tensor->storage;
    for (int i = 0; i < QING_TENSOR_NATOM(tensor); i++) {
        data[i] = value;
    }
    return tensor;
}

int qingTensorDims(const QingTensor * tensor) {
    for (int i = QING_MAX_DIMS - 1; i >= 1; --i) {
        if (tensor->sizes[i] > 1) {
            return i + 1;
        }
    }
    return 1;
}
