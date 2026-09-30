/**
 * @file omp_perf.c
 * @brief Scalable Benchmark of Multi-Threaded Summation using OpenMP
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000000L

static inline double get_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

int main(int argc, char *argv[]) {
    double sum = 0.0;
    int num_threads = 1;

    if (argc > 1) {
        num_threads = atoi(argv[1]);
    } else {
        printf("Enter number of threads: ");
        if (scanf("%d", &num_threads) != 1) {
            num_threads = 1;
        }
    }

    if (num_threads < 1 || num_threads > 64) {
        printf("Please enter a value between 1 and 64.\n");
        return EXIT_FAILURE;
    }

    omp_set_num_threads(num_threads);

    double start_time = get_time();

    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (long i = 0; i < N; i++) {
        sum += (double)i * 0.000001;
    }

    double end_time = get_time();
    double elapsed = end_time - start_time;

    printf("Result = %.2f\n", sum);
    printf("Execution time = %.6f seconds\n", elapsed);

    return EXIT_SUCCESS;
}
