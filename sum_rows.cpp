//lets keep the same loop structure
void sum(int N, int A[], int Y[]) {
    #pragma omp parallel for
    for int i = 0; i < N; i++ {
        Y[i] = 0;
        for int j = 0; j <= i; j++ {
            Y[i] += A[j];
        }
    }
}

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("--- This run is using %d thread(s) ---\n", omp_get_num_threads());
        }
    } 
    //set matrix size
    const int N = 1000;

    int *A = new int[N * N];
    int *Y = new int[N];

    for (int i = 0; i < N * N; i++) {
        A[i] = 1;
    }

    printf("Processing a %d x %d matrix (all 1s)...\n", N, N);

    double start_time = omp_get_wtime();
    
    sum(N, A, Y);
    
    double end_time = omp_get_wtime();
    printf("Calculation finished in %f seconds.\n", end_time - start_time);


    bool success = true;
    for (int i = 0; i < N; i++) {
        if (Y[i] != N) {
            success = false;
        }
    }

    printf("Verification check: ");
    if (success) {
        printf("PASSED (All row sums = %d)\n", N);
    } else {
        printf("FAILED\n");
        printf("Y[0] = %d (expected %d)\n", Y[0], N);
        printf("Y[%d] = %d (expected %d)\n", N - 1, Y[N - 1], N);
    }

    delete[] A;
    delete[] Y;

    return 0;
}