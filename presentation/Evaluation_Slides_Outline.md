# Evaluation Presentation: Multithreaded Programming
## Pthreads vs. OpenMP Lab Evaluation Slide Deck Structure

### Slide 1: Title and Overview
- **Title**: Multithreaded Programming: Thread Lifecycle, Synchronization, and Scalability
- **Course**: Parallel and Graphical Computing (5th Semester B.Tech CSE)
- **Student**: Aditya Gavimath
- **Frameworks Evaluated**: POSIX Threads (Pthreads) and OpenMP

### Slide 2: Core Concepts and Architectural Foundations
- **Definition**: Thread as an execution path sharing heap and global segments within a process.
- **Pthreads Paradigm**: Explicit low-level API (`pthread_create`, `pthread_join`, `pthread_mutex_t`).
- **OpenMP Paradigm**: High-level compiler directives (`#pragma omp parallel`, `parallel for`, `critical`, `barrier`, `reduction`).

### Slide 3: Race Conditions and Mutual Exclusion
- **Mechanism**: Concurrent, unsynchronized read-modify-write on shared variable (`counter++`).
- **Empirical Demonstration**:
  - Pthreads: $197,937$ recorded vs. $400,000$ expected ($50.5\%$ loss).
  - OpenMP: $119,127$ recorded vs. $400,000$ expected ($70.2\%$ loss).
- **Resolution**:
  - Pthreads `pthread_mutex_lock/unlock`: Restores $400,000 / 400,000$ accuracy.
  - OpenMP `#pragma omp critical`: Restores $400,000 / 400,000$ accuracy.

### Slide 4: Coordination and Work Sharing
- **Array Work Sharing ($N=8$)**: Block partitioning $[0, 2), [2, 4), [4, 6), [6, 8) \implies \text{Total} = 360$.
- **Barrier Coordination**: `#pragma omp barrier` guarantees all threads finish Stage 1 before any thread initiates Stage 2.

### Slide 5: Performance Scalability Benchmark ($N = 10^9$ terms)
- Sequential Baseline: $1.353\text{ s}$.
- Scaling Summary:
  - 1 Thread: Pthreads $1.348\text{ s}$ ($1.00\times$) vs. OpenMP $1.409\text{ s}$ ($0.96\times$)
  - 4 Threads: Pthreads $0.359\text{ s}$ ($3.77\times$) vs. OpenMP $0.361\text{ s}$ ($3.75\times$)
  - 6 Threads: Pthreads $0.241\text{ s}$ ($5.61\times$) vs. OpenMP $0.242\text{ s}$ ($5.60\times$)
  - 16 Threads: Pthreads $0.145\text{ s}$ ($9.35\times$) vs. OpenMP $0.141\text{ s}$ ($9.62\times$)

### Slide 6: Key Takeaways & Amdahl's Law
- High efficiency ($>93\%$) through 6 threads; efficiency tapers to $58-60\%$ at 16 threads due to memory bus saturation and OS thread scheduling.
- OpenMP achieves performance parity with manual Pthreads with greater code brevity and reduced likelihood of synchronization bugs.
