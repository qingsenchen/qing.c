cmake_minimum_required(VERSION 3.27)
project(yolo_c C)

set(CMAKE_C_STANDARD 11)
set(DEBUG 1)

add_executable(yolo_c main.c
        qing_vm.c
        qing_vm.h
        qing_object.c
        qing_object.h
        qing_memory.c
        qing_memory.h
        qing_tensor.c
        qing_tensor.h
        qing_common.h)
