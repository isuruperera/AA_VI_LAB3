#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include "matvec_simple.h"
#include "matvec_unrolled.h"
#include "matvec_sse.h"

/* Print usage text */
void usage(){
    printf("CS4342 Advanced Computer Architecture\n");
    printf("Lab 2\n");
    printf("Name: P.D. I. T. S. K. Perera\n");
    printf("Index: 140462E \n");
    printf("\n");
    printf(" Global options:\n");
    printf("  -h        Help - Print this text\n");
    printf("\n");
    printf(" Predictor type:\n");
    printf("  -p <PREDICTOR> Predictor to run\n");
    printf("            -p 1 : 8,192 BHT\n");
    printf("            -p 2 : 2-bit 4,096 BHT\n");
    printf("            -p 3 : (2, 2) 1024 BHT\n");
    printf("            -p 4 : Custom\n");
    printf("\n");
}


int main() {
    test_all_mat_mul_simple();
    test_all_mat_mul_unrolled();
    test_all_mat_mul_sse();
    return 0;
}

