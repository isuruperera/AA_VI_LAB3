//
// Created by isurutee on 7/7/18.
//
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
void matmul_sse(int n, float *mat_c[n],
                const float *mat_a[n], const float *mat_b[n])
{
    float *temp1;
    temp1 = malloc(4* sizeof(float));
    for(int i=0;i<n;i+=4)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                __m128 vector1 = _mm_set_ps(mat_a[i+0][k], mat_a[i+1][k], mat_a[i+2][k], mat_a[i+3][k]);
                __m128 vector2 = _mm_set1_ps(mat_b[k][j]);
                __m128 result1 = _mm_mul_ps(vector1,vector2);
                _mm_store_ps(temp1,result1);

                mat_c[i+0][j] += temp1[0];
                mat_c[i+1][j] += temp1[1];
                mat_c[i+2][j] += temp1[2];
                mat_c[i+3][j] += temp1[3];
            }
        }
    }
    free(temp1);
}

// Tests simple matrix matrix multiplication, and returns the average time
// taken for a given number of iterations
void test_mat_mul_sse(int n, float *mat_c[n],
                          const float *mat_a[n], const float *mat_b[n], int iterations){
    long long totalTime = 0;
    for(int i=0; i<iterations ;i++)
    {
        struct timeval stop, start;
        gettimeofday(&start, NULL);
        matmul_sse(n,mat_c,mat_a,mat_b);
        gettimeofday(&stop, NULL);
        totalTime += stop.tv_usec - start.tv_usec;
    }
    printf("FN: MAT_VEC_MUL_SSE\n");
    printf("MAT_SIZE: [%d],[%d] \n",n,n);
    printf("VEC_SIZE: [%d],[1] \n",n);
    printf("TEST_ITERATIONS: %d \n",iterations);
    printf("AVG_TIME: %f \n",(double)totalTime/(double)iterations);
    printf("-----------------------------------------\n");
}

void test_all_mat_mul_sse(){
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
                mat_a[j][k] = (float)rand()/(float)(RAND_MAX);
                mat_b[j][k] = (float)rand()/(float)(RAND_MAX);
            }
        }
        test_mat_mul_sse(n, mat_c, mat_a, mat_b, 10);
        free(mat_b);
        free(mat_c);
        for(int j=0;j<n;j++){
            free(mat_a[j]);
        }
    }
}