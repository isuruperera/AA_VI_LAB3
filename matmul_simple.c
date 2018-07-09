//
// Created by isurutee on 7/7/18.
//
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matmul_simple(int n, int m, float *mat_c[n],
                          const float *mat_a[n], const float *mat_b[n]) //n is the size of square matrix mat_A, m is the number of columns in mat_B
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
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
void test_mat_mul_simple(int n, int m, float *mat_c[n],
                          const float *mat_a[n], const float *mat_b[n], int iterations){
    double totalTime = 0;
    for(int i=0; i<iterations ;i++)
    {
        clock_t start = clock();
        matmul_simple(n, m, mat_c,mat_a,mat_b);
        clock_t end = clock();
        totalTime += (((double)(end-start))/CLOCKS_PER_SEC);
    }
    printf("FN: MAT_MUL_SIMPLE\n");
    printf("MAT_SIZE: [%d],[%d] \n",n,n);
    printf("VEC_SIZE: [%d],[%d] \n",n,n);
    printf("TEST_ITERATIONS: %d \n",iterations);
    printf("AVG_TIME: %f \n",totalTime/iterations);
    printf("-----------------------------------------\n");
}

void test_all_mat_mul_simple(){
    const int m = 200;
    for(int n=100; n<=1600 ;n*=2)
    {
        srand((unsigned int) n);
        float *mat_a[n];
        float *mat_b[m];
        float *mat_c[m];
        // Allocate memory for 2d array from the heap instead of stack
        for(int j=0;j<n;j++){
            mat_a[j] = malloc(n* sizeof(float));
            if(j>=m)
                continue;
            mat_b[j] = malloc(n* sizeof(float));
            mat_c[j] = malloc(n* sizeof(float));
        }

        for (int j = 0; j<n ; j++) {
            for (int k = 0; k <n ; k++) {
                mat_a[j][k] = (float)rand()/(float)(RAND_MAX);
            }
        }
        for (int j = 0; j<m ; j++) {
            for (int k = 0; k <n ; k++) {
                mat_b[j][k] = (float)rand()/(float)(RAND_MAX);
            }
        }

        test_mat_mul_simple(n,m,mat_c, (const float **) mat_a, (const float **) mat_b, 10);
        for(int j=0;j<n;j++){
            free(mat_a[j]);
            free(mat_b[j]);
            free(mat_c[j]);
        }
    }
}