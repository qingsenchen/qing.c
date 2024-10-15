#include <stdlib.h>
#include <stdbool.h>

#include "qing_object.h"
#include "qing_memory.h"
#include "qing_tensor.h"
#include "qing_vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)qingAllocateObject(sizeof(type), objectType)

static QingObj* qingAllocateObject(size_t size, ObjType type) {
    QingObj* object = (QingObj*)reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;

#ifdef DEBUG_LOG_GC
    printf("%p allocate %zu for %d\n", (void*)object, size, type);
#endif
    return object;
}

static QingTensor* qingNewTensorImpl(int n_dims, DType dtype) {

    QING_ASSERT(n_dims >= 1 && n_dims <= QING_MAX_DIMS, "n_dims out of range");

    QingTensor* tensor = ALLOCATE_OBJ(QingTensor, QING_OBJ_TENSOR);
    tensor->type = dtype;




    return tensor;
}