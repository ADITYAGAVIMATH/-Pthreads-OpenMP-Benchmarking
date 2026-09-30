/**
 * @file pthread_perf.c
 * @brief Scalable Benchmark of Multi-Threaded Summation using Pthreads
 * 
 * Part of Laboratory Experiment 02: Multithreaded Programming
 * Course: Parallel and Graphical Computing (PCG)
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000000000L
#define MAX_THREADS 32

double partial_sum[MAX_THREADS];

typedef struct {
    int thread_id;
    long start;
    long end;
} ThreadData;

static inline double get_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

void *calculate(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    double sum = 0.0;
    for (long i = data->start; i < data->end; i++) {
        sum += (double)i * 0.000001;
    }
    partial_sum[data->thread_id] = sum;
    return NULL;
}

int main(int argc, char *argv[]) {
    int num_threads = 1;
    if (argc > 1) {
        num_threads = atoi(argv[1]);
    } else {
        printf("Enter number of threads: ");
        if (scanf("%d", &num_threads) != 1) {
            num_threads = 1;
        }
    }

    if (num_threads < 1 || num_threads > MAX_THREADS) {
        printf("Please enter a value between 1 and %d.\n", MAX_THREADS);
        return EXIT_FAILURE;
    }

    pthread_t threads[num_threads];
    ThreadData data[num_threads];
    long chunk = N / num_threads;

    double start_time = get_time();

    for (int i = 0; i < num_threads; i++) {
        data[i].thread_id = i;
        data[i].start = i * chunk;
        data[i].end = (i == num_threads - 1) ? N : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, calculate, &data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    double total_sum = 0.0;
    for (int i = 0; i < num_threads; i++) {
        total_sum += partial_sum[i];
    }

    double end_time = get_time();

    printf("Result = %.2f\n", total_sum);
    printf("Execution time = %.6f seconds\n", end_time - start_time);

    return EXIT_SUCCESS;
}
