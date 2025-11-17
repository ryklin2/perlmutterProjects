#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 
#include <time.h>
#include <iostream>
#include <stdio.h>
void dgemv(int M, int N, double* A, double* x, double* y) {
    

    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        

        double sum = 0.0;
        

        for (int j = 0; j < N; j++) {

            sum += A[i + j*M] * x[j];
        }

        y[i] += sum;
    }
}

int main() {
    const int M = 128;
    const int N = 64;

    double* A = (double*) malloc(M * N * sizeof(double));
    double* x = (double*) malloc(N * sizeof(double));
    double* y = (double*) malloc(M * sizeof(double));

    if (!A || !x || !y) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    dgemv(M, N, A, x, y);

    // Clean up
    free(A);
    free(x);
    free(y);

    return 0;
}


