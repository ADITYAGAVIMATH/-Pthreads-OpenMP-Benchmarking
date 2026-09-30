/**
 * @file thread2.c
 * @brief Creating and Managing Multiple Concurrent POSIX Threads
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    printf("Hello from Thread %d\n", thread_id);
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Launch multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Thread creation error");
            return EXIT_FAILURE;
        }
    }

    // Await all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished.\n");
    return EXIT_SUCCESS;
}
