#include <stdlib.h>
#include <stdbool.h>

#include "qing_object.h"
#include "qing_memory.h"
#include "qing_vm.h"

QingObj* qingAllocateObject(size_t size, ObjType type) {
    QingObj* object = (QingObj*)reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;

#ifdef DEBUG_LOG_GC
    printf("%p allocate %zu for %d\n", (void*)object, size, type);
#endif
    return object;
}

