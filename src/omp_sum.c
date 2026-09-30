/**
 * @file omp_sum.c
 * @brief OpenMP Parallel Loop Work-Sharing and Reduction Directive
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 8

int array[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80};

int main(void) {
    int total_sum = 0;

    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int thread_id = omp_get_thread_num();
        printf("Thread %d processing array[%d] = %d\n", thread_id, i, array[i]);
        total_sum += array[i];
    }

    printf("Total sum = %d\n", total_sum);
    return EXIT_SUCCESS;
}
