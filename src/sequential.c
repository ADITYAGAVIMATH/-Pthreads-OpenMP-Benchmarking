/**
 * @file sequential.c
 * @brief Baseline Sequential Summation Benchmark (1 Billion Elements)
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000L

static inline double get_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

int main(void) {
    double sum = 0.0;
    double start = get_time();

    for (long i = 0; i < N; i++) {
        sum += (double)i * 0.000001;
    }

    double end = get_time();
    double elapsed = end - start;

    printf("========================================\n");
    printf("Sequential Baseline Summation\n");
    printf("========================================\n");
    printf("Workload Size  : %ld elements\n", N);
    printf("Result         : %.2f\n", sum);
    printf("Execution time : %.6f seconds\n", elapsed);
    printf("========================================\n");

    return EXIT_SUCCESS;
}
