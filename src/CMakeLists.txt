cmake_minimum_required(VERSION 3.27)
project(qing_c C)

set(CMAKE_C_STANDARD 11)
option(DEBUG ON)

add_executable(qing_c main.c
        qing_vm.c
        qing_vm.h
        qing_object.c
        qing_object.h
        qing_memory.c
        qing_memory.h
        qing_tensor.c
        qing_tensor.h
        qing_common.h)
