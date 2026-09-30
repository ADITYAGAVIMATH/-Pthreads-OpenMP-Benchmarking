/**
 * @file omp_barrier.c
 * @brief Thread Coordination and Synchronization via OpenMP Barrier
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d completed Stage 1\n", thread_id);

        #pragma omp barrier

        printf("Thread %d started Stage 2\n", thread_id);
    }

    return EXIT_SUCCESS;
}
