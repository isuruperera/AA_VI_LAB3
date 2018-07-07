//
// Created by isurutee on 7/7/18.
//
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <bits/time.h>
#include <time.h>

void matmul_simple(int n, float *mat_c[n],
                          const float *mat_a[n], const float *mat_b[n])
{
    for(int i=0;i<n;i+=4)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
        }
    }
}

// Tests simple matrix matrix multiplication, and returns the average time
// taken for a given number of iterations
void test_mat_mul_simple(int n, float *mat_c[n],
                          const float *mat_a[n], const float *mat_b[n], int iterations){
    double totalTime = 0;
    for(int i=0; i<iterations ;i++)
    {
        struct timespec tstart={0,0}, tend={0,0};
        clock_gettime(CLOCK_MONOTONIC, &tstart);
        matmul_simple(n,mat_c,mat_a,mat_b);
        clock_gettime(CLOCK_MONOTONIC, &tend);
        totalTime += ((double)tend.tv_sec*1000 + tend.tv_nsec/1000) - ((double)tstart.tv_sec*1000 + tstart.tv_nsec/1000);
    }
    printf("FN: MAT_MUL_SIMPLE\n");
    printf("MAT_SIZE: [%d],[%d] \n",n,n);
    printf("VEC_SIZE: [%d],[%d] \n",n,n);
    printf("TEST_ITERATIONS: %d \n",iterations);
    printf("AVG_TIME: %Lf \n",totalTime/(long double)iterations);
    printf("-----------------------------------------\n");
}

void test_all_mat_mul_simple(){
    for(int n=100; n<=1600 ;n*=2)
    {
        srand((unsigned int) n);
        float *mat_a[n];
        float *mat_b[n];
        float *mat_c[n];
        // Allocate memory for 2d array from the heap instead of stack
        for(int j=0;j<n;j++){
            mat_a[j] = malloc(n* sizeof(float));
            mat_b[j] = malloc(n* sizeof(float));
            mat_c[j] = malloc(n* sizeof(float));
        }

        for (int j = 0; j<n ; j++) {
            for (int k = 0; k <n ; k++) {
                mat_a[j][k] = (float)random()/(float)(RAND_MAX);
                mat_b[j][k] = (float)random()/(float)(RAND_MAX);
            }
        }
        test_mat_mul_simple(n, mat_c, (const float **) mat_a, (const float **) mat_b, 10);
        for(int j=0;j<n;j++){
            free(mat_a[j]);
            free(mat_b[j]);
            free(mat_c[j]);
        }
    }
}