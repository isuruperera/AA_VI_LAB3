//
// Created by isurutee on 7/7/18.
//
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

void matvec_unrolled(int n, float vec_c[n],
                            float *mat_a[n], const float vec_b[n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j+=4)
        {
            vec_c[i] += mat_a[i][j+0] * vec_b[j+0]
                       +mat_a[i][j+1] * vec_b[j+1]
                       +mat_a[i][j+2] * vec_b[j+2]
                       +mat_a[i][j+3] * vec_b[j+3];
        }
    }
}

void test_mat_vec_mul_unrolled(int n, float vec_c[n],
                               const float *mat_a[n], const float vec_b[n], int iterations){
    long long totalTime = 0;
    for(int i=0; i<iterations ;i++)
    {
        struct timeval stop, start;
        gettimeofday(&start, NULL);
        matvec_unrolled(n,vec_c,mat_a,vec_b);
        gettimeofday(&stop, NULL);
        totalTime += stop.tv_usec - start.tv_usec;
    }
    printf("FN: MAT_VEC_MUL_UNROLLED\n");
    printf("MAT_SIZE: [%d],[%d] \n",n,n);
    printf("VEC_SIZE: [%d],[1] \n",n);
    printf("TEST_ITERATIONS: %d \n",iterations);
    printf("AVG_TIME: %f \n",(double)totalTime/(double)iterations);
    printf("-----------------------------------------\n");
}

void test_all_mat_mul_unrolled(){
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
        test_mat_vec_mul_unrolled(n, vec_c, (const float **) mat_a, vec_b, 10);
        free(vec_b);
        free(vec_c);
        for(int j=0;j<n;j++){
            free(mat_a[j]);
        }
    }
}