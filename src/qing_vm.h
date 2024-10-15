#ifndef QING_VM_H
#define QING_VM_H

#include <stdlib.h>
#include "qing_object.h"


typedef struct sQingVM {
    QingObj* objects;                       /* 记录虚拟机分配的对象列表，用于垃圾回收。 */
    size_t bytesAllocated;
} QingVM;

extern QingVM vm;

#endif //QING_VM_H
