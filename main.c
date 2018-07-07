#include <stdio.h>

#include "lab4.h"




int main() {
    test_all_mat_vec_mul_simple();
    //test_all_mat_mul_unrolled();
    test_all_mat_vec_mul_sse();
    //test_all_mat_mul_simple();
    return 0;
}

