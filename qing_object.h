#ifndef QING_OBJECT_H
#define QING_OBJECT_H

typedef enum {
    QING_OBJ_TENSOR,
} ObjType;

typedef struct sQingObj QingObj;

struct sQingObj {
    ObjType type;
    struct sQingObj* next;   /* 指向下一个对象，用于虚拟机垃圾回收 */
};

#endif //QING_OBJECT_H
