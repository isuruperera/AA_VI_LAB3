cmake_minimum_required(VERSION 3.9)
project(Lab3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab3 main.c matvec_simple.c matvec_unrolled.c matvec_sse.c
        matmul_simple.c matmul_sse.c lab4.h)