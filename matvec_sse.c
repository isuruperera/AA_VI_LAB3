//
// Created by isurutee on 7/7/18.
//
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
void matvec_sse(int n, float vec_c[n],
                          const float *mat_a[n], const float vec_b[n])
{
    float *temp1;
    temp1 = malloc(4* sizeof(float));
    for(int i=0;i<n;i+=4)
    {
        for(int j=0;j<n;j++)
        {
            __m128 vector1 = _mm_set_ps(mat_a[i+0][j], mat_a[i+1][j], mat_a[i+2][j], mat_a[i+3][j]);
            __m128 vector2 = _mm_set_ps(vec_b[j], vec_b[j], vec_b[j], vec_b[j]);
            __m128 result1 = _mm_mul_ps(vector1, vector2);
            _mm_store_ps(temp1,result1);

            vec_c[i+0] += temp1[0];
            vec_c[i+1] += temp1[1];
            vec_c[i+2] += temp1[2];
            vec_c[i+3] += temp1[3];
        }
    }
    free(temp1);
}

// Tests simple matrix vector multiplication, and returns the average time
// taken for a given number of iterations
void test_mat_vec_mul_sse(int n, float vec_c[n],
                               const float *mat_a[n], const float vec_b[n], int iterations){
    long long totalTime = 0;
    for(int i=0; i<iterations ;i++)
    {
        struct timeval stop, start;
        gettimeofday(&start, NULL);
        matvec_sse(n,vec_c,mat_a,vec_b);
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
        float *vec_b;
        float *vec_c;
        float *mat_a[n];
        // Allocate memory for vectors from heap instead of stack
        vec_b = malloc(n* sizeof(float));
        vec_c = malloc(n* sizeof(float));
        // Allocate memory for 2d array from the heap instead of stack
        for(int j=0;j<n;j++){
            mat_a[j] = malloc(n* sizeof(float));
        }
        for (int j = 0; j<n ; j++) {

        }
        for (int j = 0; j<n ; j++) {
            vec_b[j] = (float)random()/(float)(RAND_MAX);
            for (int k = 0; k <n ; k++) {
                mat_a[j][k] = (float)random()/(float)(RAND_MAX);
            }
        }
        test_mat_vec_mul_sse(n, vec_c, (const float **) mat_a, vec_b, 10);
        free(vec_b);
        free(vec_c);
        for(int j=0;j<n;j++){
            free(mat_a[j]);
        }
    }
}