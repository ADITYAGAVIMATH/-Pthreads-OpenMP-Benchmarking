# Comprehensive Technical Report
## Experiment 02: Multithreaded Programming Using Pthreads and OpenMP

### 1. Abstract
Multithreading provides concurrent execution paths within a single process address space, enabling applications to exploit modern multi-core processor architectures. This laboratory experiment investigates two primary shared-memory multithreading standards: the explicit, POSIX Threads (Pthreads) API, and the compiler-directed OpenMP framework. Through progressive implementations, we analyze thread creation, work distribution, shared memory contention, race conditions, synchronization mechanisms (mutexes vs. critical sections), barrier coordination, and empirical performance scalability across thread counts ranging from 1 to 16 on a compute workload of $10^9$ floating-point operations.

---

### 2. Theoretical Foundations

#### 2.1 Thread Architecture and Address Space
A thread is an independent execution context consisting of a program counter, registers, and a private stack. Unlike processes, threads share heap memory, global variables, and operating system file descriptors.

#### 2.2 Work Partitioning Strategy
For an array or loop of size $N$ partitioned across $P$ threads:
- Contiguous block decomposition assigns chunk size $S = \lfloor N / P \rfloor$.
- Thread $t \in [0, P-1]$ computes indices $[t \cdot S, (t+1) \cdot S)$, with thread $P-1$ handling remainder indices up to $N$.

#### 2.3 Race Conditions and Critical Sections
When multiple concurrent threads execute read-modify-write instructions (such as `counter++`) on shared variables without atomic isolation, instructions interleave unpredictably across CPU pipeline stages, resulting in lost updates. Mutual exclusion primitives enforce that at most one thread enters a critical section at any given moment.

---

### 3. Progressive Implementation Hierarchy

1. **Explicit Thread Life Cycle (Pthreads)**:
   - Creation via `pthread_create()`, synchronization via `pthread_join()`.
   - Work partitioning with structure parameter passing (`ThreadData`).
   - Mutual exclusion via `pthread_mutex_lock()` and `pthread_mutex_unlock()`.

2. **Directive-Based Parallelism (OpenMP)**:
   - Implicit thread team creation via `#pragma omp parallel`.
   - Automatic static loop iteration scheduling via `#pragma omp parallel for`.
   - Safe multi-threaded reduction accumulation via `reduction(+:sum)`.
   - Mutual exclusion via `#pragma omp critical`.
   - Rendezvous synchronization via `#pragma omp barrier`.

3. **Empirical Scalability (1 Billion Term Summation)**:
   - Computational Workload: $\sum_{i=0}^{N-1} (i \times 10^{-6}) = 499999999500.00$.
   - Tested configurations: Sequential baseline, 1, 2, 4, 6, and 16 threads for both frameworks.

---

### 4. Consolidated Performance Benchmark

| Thread Count ($P$) | Pthreads Time (s) | Pthreads Speedup | Pthreads Efficiency | OpenMP Time (s) | OpenMP Speedup | OpenMP Efficiency |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Sequential (Baseline)** | 1.353219 | $1.000\times$ | $100.00\%$ | 1.353219 | $1.000\times$ | $100.00\%$ |
| **1 Thread** | 1.348142 | $1.004\times$ | $100.38\%$ | 1.409294 | $0.960\times$ | $96.02\%$ |
| **2 Threads** | 0.680737 | $1.988\times$ | $99.39\%$ | 0.715560 | $1.891\times$ | $94.56\%$ |
| **4 Threads** | 0.358872 | $3.771\times$ | $94.27\%$ | 0.360803 | $3.751\times$ | $93.76\%$ |
| **6 Threads** | 0.241345 | $5.608\times$ | $93.45\%$ | 0.241608 | $5.601\times$ | $93.35\%$ |
| **16 Threads** | 0.144812 | $9.345\times$ | $58.40\%$ | 0.140692 | $9.618\times$ | $60.11\%$ |

---

### 5. Discussion & Critical Findings

1. **Framework Parity**: Pthreads and OpenMP exhibited nearly identical execution profiles across all thread counts, differing by less than $2\%$ at 4, 6, and 16 threads. OpenMP directives achieve performance equal to hand-crafted Pthreads while drastically reducing code complexity and boilerplate.
2. **Sub-linear Scaling at High Thread Counts**: Moving from 6 threads ($93.4\%$ efficiency) to 16 threads ($58.4-60.1\%$ efficiency) illustrates hardware resource constraints. As thread counts approach the physical core limit, memory bandwidth saturation and thread scheduling contention prevent ideal linear scaling.
3. **Synchronization Necessity**: Unsynchronized parallel access resulted in over $50\%$ to $70\%$ lost increments, proving that synchronization is mathematically imperative for shared data integrity.
