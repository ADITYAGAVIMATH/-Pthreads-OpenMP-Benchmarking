/**
 * @file omp1.c
 * @brief OpenMP Basic Parallel Region and Thread Querying
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hello from Thread %d of %d\n", thread_id, total_threads);
    }
    return EXIT_SUCCESS;
}
