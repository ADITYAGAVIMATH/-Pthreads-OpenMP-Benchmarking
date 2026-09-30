# Makefile for Experiment 02: Multithreaded Programming (Pthreads & OpenMP)
CC      = gcc
CFLAGS  = -O2 -Wall
PTHFLAGS = -pthread
OMPFLAGS = -fopenmp

PTHREAD_TARGETS = thread1 thread2 thread_sum race mutex pthread_perf
OPENMP_TARGETS  = omp1 omp_sum omp_race omp_critical omp_barrier omp_perf
PERF_TARGETS    = sequential

ALL_TARGETS = $(PTHREAD_TARGETS) $(OPENMP_TARGETS) $(PERF_TARGETS)

all: $(ALL_TARGETS)

# Pthreads Programs
thread1: thread1.c
	$(CC) $(CFLAGS) thread1.c -o thread1 $(PTHFLAGS)

thread2: thread2.c
	$(CC) $(CFLAGS) thread2.c -o thread2 $(PTHFLAGS)

thread_sum: thread_sum.c
	$(CC) $(CFLAGS) thread_sum.c -o thread_sum $(PTHFLAGS)

race: race.c
	$(CC) $(CFLAGS) race.c -o race $(PTHFLAGS)

mutex: mutex.c
	$(CC) $(CFLAGS) mutex.c -o mutex $(PTHFLAGS)

pthread_perf: pthread_perf.c
	$(CC) $(CFLAGS) pthread_perf.c -o pthread_perf $(PTHFLAGS)

# OpenMP Programs
omp1: omp1.c
	$(CC) $(CFLAGS) omp1.c -o omp1 $(OMPFLAGS)

omp_sum: omp_sum.c
	$(CC) $(CFLAGS) omp_sum.c -o omp_sum $(OMPFLAGS)

omp_race: omp_race.c
	$(CC) $(CFLAGS) omp_race.c -o omp_race $(OMPFLAGS)

omp_critical: omp_critical.c
	$(CC) $(CFLAGS) omp_critical.c -o omp_critical $(OMPFLAGS)

omp_barrier: omp_barrier.c
	$(CC) $(CFLAGS) omp_barrier.c -o omp_barrier $(OMPFLAGS)

omp_perf: omp_perf.c
	$(CC) $(CFLAGS) omp_perf.c -o omp_perf $(OMPFLAGS)

# Sequential Baseline
sequential: sequential.c
	$(CC) $(CFLAGS) sequential.c -o sequential

clean:
	rm -f $(ALL_TARGETS) *.o *.exe
