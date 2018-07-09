//
// Created by isurutee on 7/7/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <smmintrin.h>
#include <time.h>

void matvec_sse_un(int n, float vec_c[n],
                          const float *mat_a[n], const float vec_b[n])
{
    float *temp;
    temp = malloc(4* sizeof(float));
    for(int i=0;i<n;i+=4)
    {
        for(int j=0;j<n;j+=4)
        {
            __m128 vectorA1 = _mm_set_ps(mat_a[i+0][j+0], mat_a[i+1][j+0], mat_a[i+2][j+0], mat_a[i+3][j+0]);
            __m128 vectorA2 = _mm_set1_ps(vec_b[j+0]);
            __m128 resultA1 = _mm_mul_ps(vectorA1, vectorA2);

            __m128 vectorB1 = _mm_set_ps(mat_a[i+0][j+1], mat_a[i+1][j+1], mat_a[i+2][j+1], mat_a[i+3][j+1]);
            __m128 vectorB2 = _mm_set1_ps(vec_b[j+1]);
            __m128 resultB1 = _mm_mul_ps(vectorB1, vectorB2);

            __m128 vectorC1 = _mm_set_ps(mat_a[i+0][j+2], mat_a[i+1][j+2], mat_a[i+2][j+2], mat_a[i+3][j+2]);
            __m128 vectorC2 = _mm_set1_ps(vec_b[j+2]);
            __m128 resultC1 = _mm_mul_ps(vectorC1, vectorC2);

            __m128 vectorD1 = _mm_set_ps(mat_a[i+0][j+3], mat_a[i+1][j+3], mat_a[i+2][j+3], mat_a[i+3][j+3]);
            __m128 vectorD2 = _mm_set1_ps(vec_b[j+3]);
            __m128 resultD1 = _mm_mul_ps(vectorD1, vectorD2);

            __m128 resultFinal = _mm_add_ps(_mm_add_ps(resultA1,resultB1),_mm_add_ps(resultC1,resultD1));
            _mm_store_ps(temp,resultFinal);

            vec_c[i+0] += temp[0];
            vec_c[i+1] += temp[1];
            vec_c[i+2] += temp[2];
            vec_c[i+3] += temp[3];
        }
    }
    free(temp);
}

// Tests simple matrix vector multiplication, and returns the average time
// taken for a given number of iterations
void test_mat_vec_mul_sse_un(int n, float vec_c[n],
                               const float *mat_a[n], const float vec_b[n], int iterations){
    double totalTime = 0;
    for(int i=0; i<iterations ;i++)
    {
        clock_t start = clock();
        matvec_sse_un(n,vec_c,mat_a,vec_b);
        clock_t end = clock();
        totalTime += (((double)(end-start))/CLOCKS_PER_SEC);

    }
    printf("FN: MAT_VEC_MUL_SSE_UN\n");
    printf("MAT_SIZE: [%d],[%d] \n",n,n);
    printf("VEC_SIZE: [%d],[1] \n",n);
    printf("TEST_ITERATIONS: %d \n",iterations);
    printf("AVG_TIME: %f \n",totalTime/iterations);
    printf("-----------------------------------------\n");
}

void test_all_mat_vec_mul_sse_un(){
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
        test_mat_vec_mul_sse_un(n, vec_c, (const float **) mat_a, vec_b, 10);
        free(vec_b);
        free(vec_c);
        for(int j=0;j<n;j++){
            free(mat_a[j]);
        }
    }
}