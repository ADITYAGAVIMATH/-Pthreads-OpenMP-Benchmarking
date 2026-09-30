/**
 * @file race.c
 * @brief Demonstration of Race Condition on Unsynchronized Shared Data
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS 100000

int counter = 0;

void *increment_counter(void *arg) {
    (void)arg;
    for (int i = 0; i < INCREMENTS; i++) {
        counter++;
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter = %d\n", NUM_THREADS * INCREMENTS);
    printf("Actual counter   = %d\n", counter);

    return EXIT_SUCCESS;
}
