//
// Created by isurutee on 7/7/18.
//
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static float **mat_a;
static float **mat_b;
static float **mat_c;

void matmul_simple_av(int n)
 {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            for(int k=0;k<n;k++) {
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
        }
    }
}

// Tests simple matrix matrix multiplication, and returns the average time
// taken for a given number of iterations
void test_mat_mul_simple_av(int n, int iterations){
    double totalTime = 0;
    for(int i=0; i<iterations ;i++)
    {
        clock_t start = clock();
        matmul_simple_av(n);
        clock_t end = clock();
        totalTime += (((double)(end-start))/CLOCKS_PER_SEC);
    }
    printf("FN: MAT_MUL_SIMPLE_AUTO_V\n");
    printf("MAT_SIZE: [%d],[%d] \n",n,n);
    printf("VEC_SIZE: [%d],[%d] \n",n,n);
    printf("TEST_ITERATIONS: %d \n",iterations);
    printf("AVG_TIME: %f \n",totalTime/iterations);
    printf("-----------------------------------------\n");
}

void test_all_mat_mul_simple_av(){
    for(int n=100; n<=1600 ;n*=2)
    {
        srand((unsigned int) n);

        static float *mat_aI;
        static float *mat_bI;
        static float *mat_cI;
        mat_a = malloc(n* sizeof(*mat_a));
        mat_b = malloc(n* sizeof(*mat_b));
        mat_c = malloc(n* sizeof(*mat_c));

        // Allocate memory for 2d array from the heap instead of stack
        for(int j=0;j<n;j++){
            mat_a[j] = malloc(n* sizeof(*mat_aI));
            mat_b[j] = malloc(n* sizeof(*mat_bI));
            mat_c[j] = malloc(n* sizeof(*mat_cI));
        }

        for (int j = 0; j<n ; j++) {
            for (int k = 0; k <n ; k++) {
                mat_a[j][k] = (float)random()/(float)(RAND_MAX);
                mat_b[j][k] = (float)random()/(float)(RAND_MAX);
                mat_c[j][k] = 0.0;
            }
        }
        test_mat_mul_simple_av(n, 10);
        for(int j=0;j<n;j++){
            free(mat_a[j]);
            free(mat_b[j]);
            free(mat_c[j]);
        }
    }
}