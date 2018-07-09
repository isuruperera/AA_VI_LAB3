cmake_minimum_required(VERSION 3.9)
project(Lab3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab3 main.c matvec_simple.c matvec_unrolled.c matvec_sse.c
        matmul_simple.c matmul_sse.c matvec_sse_unrolled.c matmul_simple_av_optimized.c lab4.h)