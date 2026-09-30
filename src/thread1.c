/**
 * @file thread1.c
 * @brief Creating and Joining a Single POSIX Thread
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    (void)arg;
    printf("Hello from the thread!\n");
    return NULL;
}

int main(void) {
    pthread_t thread;

    // Create a new thread executing thread_function
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    // Wait for thread termination
    if (pthread_join(thread, NULL) != 0) {
        perror("Failed to join thread");
        return EXIT_FAILURE;
    }

    printf("Main thread finished.\n");
    return EXIT_SUCCESS;
}
