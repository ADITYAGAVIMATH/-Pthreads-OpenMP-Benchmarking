# Experiment 02: Multithreaded Programming Using Pthreads and OpenMP
## Thread Lifecycle, Work Partitioning, Synchronization, and Performance Scalability

[![Parallel Computing](https://img.shields.io/badge/Course-Parallel%20and%20Graphical%20Computing-0052CC?style=for-the-badge&logo=cplusplus&logoColor=white)](https://github.com)
[![Pthreads](https://img.shields.io/badge/Threading%20Model-POSIX%20Threads%20(Pthreads)-607078?style=for-the-badge&logo=c&logoColor=white)](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html)
[![OpenMP](https://img.shields.io/badge/Directive%20Model-OpenMP-E57000?style=for-the-badge&logo=c&logoColor=white)](https://www.openmp.org)
[![Compiler](https://img.shields.io/badge/Compiler-GCC%2015.2.0-2ea44f?style=for-the-badge&logo=gnu&logoColor=white)](https://gcc.gnu.org)
[![Environment](https://img.shields.io/badge/Platform-WSL2%20Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)](https://ubuntu.com)

---

## Table of Contents
- [1. Overview and Core Objectives](#1-overview-and-core-objectives)
- [2. System and Hardware Specifications](#2-system-and-hardware-specifications)
- [3. Repository Structure](#3-repository-structure)
- [4. Step-by-Step Hands-on Guide](#4-step-by-step-hands-on-guide)
  - [Part A: POSIX Threads (Pthreads)](#part-a-posix-threads-pthreads)
  - [Part B: OpenMP Compiler Directives](#part-b-openmp-compiler-directives)
  - [Part C: Scalability Benchmark (1 Billion Workload)](#part-c-scalability-benchmark-1-billion-workload)
- [5. Performance Benchmark Results](#5-performance-benchmark-results)
- [6. Comparative Performance and Synchronization Analysis](#6-comparative-performance-and-synchronization-analysis)
- [7. Quick Build and Execution Instructions](#7-quick-build-and-execution-instructions)
- [8. Author Information](#8-author-information)

---

## 1. Overview and Core Objectives

### Objective
To implement, execute, and analyze multithreaded applications in C using both low-level explicit POSIX Threads (Pthreads) and high-level compiler directives (OpenMP), examining:
- Explicit thread creation, argument passing, and lifecycle coordination.
- Work distribution over discrete array slices.
- Shared-memory race conditions arising from non-atomic read-modify-write operations.
- Mutual exclusion primitives (`pthread_mutex_t` vs. `#pragma omp critical`).
- Rendezvous barrier synchronization (`#pragma omp barrier`).
- Scalability and parallel efficiency across 1, 2, 4, 6, and 16 threads for a 1-billion element numerical workload ($N = 10^9$).

```mermaid
flowchart TD
    subgraph P["POSIX Threads (Explicit Model)"]
        P_Create["pthread_create()"] --> P_Exec["Thread Function Execution"]
        P_Exec --> P_Sync["pthread_mutex_lock() / unlock()"]
        P_Sync --> P_Join["pthread_join()"]
    end

    subgraph O["OpenMP (Directive-Based Model)"]
        O_Region["#pragma omp parallel"] --> O_Work["#pragma omp parallel for reduction"]
        O_Work --> O_Crit["#pragma omp critical"]
        O_Crit --> O_Barr["#pragma omp barrier"]
    end

    subgraph B["Performance Benchmarking (N = 10^9)"]
        B_Seq["Sequential Baseline (1.353s)"]
        B_Pth["Pthreads (1 to 16 Threads)"]
        B_Omp["OpenMP (1 to 16 Threads)"]
    end
```

---

## 2. System and Hardware Specifications

| Component / Layer | Specification / Version | Role in Benchmark |
| :--- | :--- | :--- |
| **Host Operating System** | Microsoft Windows 11 (64-bit) | Workstation OS and virtualization layer |
| **Linux Subsystem** | WSL2 (Ubuntu Linux) | Execution runtime for Pthreads and OpenMP |
| **Compiler** | GCC 15.2.0 (`build-essential`) | C compiler supporting `-pthread` and `-fopenmp` |
| **Processor Architecture** | Multi-Core x86_64 CPU (16 Logical Threads) | Parallel compute execution units |
| **Memory Allocation** | Unified Symmetric Multi-Processing RAM | Shared address space for thread communication |
| **Benchmark Problem Size** | $N = 1,000,000,000$ iterations | High-intensity CPU compute benchmark |

---

## 3. Repository Structure

```text
EXP2/
├── README.md                          # Master documentation and empirical performance analysis
├── src/                               # Complete C source code for all experimental stages
│   ├── Makefile                       # Unified build script with targets for all stages
│   ├── thread1.c                      # Single thread creation and joining
│   ├── thread2.c                      # Multiple concurrent thread management
│   ├── thread_sum.c                   # Pthreads array work partitioning
│   ├── race.c                         # Unsynchronized Pthreads race condition demo
│   ├── mutex.c                        # Pthreads race condition resolution via mutex
│   ├── pthread_perf.c                 # Scalable Pthreads performance benchmark
│   ├── omp1.c                         # OpenMP basic parallel region and thread IDs
│   ├── omp_sum.c                      # OpenMP work-sharing and reduction directive
│   ├── omp_race.c                     # Unsynchronized OpenMP race condition demo
│   ├── omp_critical.c                 # OpenMP critical section synchronization
│   ├── omp_barrier.c                  # OpenMP rendezvous barrier synchronization
│   ├── sequential.c                   # Single-threaded 1-billion term baseline
│   └── omp_perf.c                     # Scalable OpenMP performance benchmark
├── data/                              # Workload characterization and partition tools
│   ├── README.md                      # Mathematical summation proof and chunk equations
│   └── benchmark_data_generator.py    # Analytical verification and chunk boundary script
├── results/                           # Raw console logs, metrics tables, and timing outputs
│   ├── performance_metrics.csv        # Tabulated execution time, speedup, and efficiency
│   ├── execution_timings.txt          # Verbatim terminal benchmark transcripts
│   └── synchronization_analysis.md    # Detailed lock mechanics and contention analysis
├── graphs/                            # High-resolution benchmark comparison charts (300 DPI)
│   ├── generate_graphs.py             # Matplotlib visualization script
│   ├── execution_time_vs_threads.png  # Execution time curve across thread counts
│   ├── speedup_vs_threads.png         # Speedup curve vs. ideal linear scaling
│   └── efficiency_vs_threads.png      # Parallel efficiency curve vs. 100% ideal
├── screenshots/                       # High-resolution console verification images
│   ├── pthreads/                      # 11 screenshots covering Pthreads lifecycle & mutex
│   ├── openmp/                        # 10 screenshots covering OpenMP directives & barriers
│   └── performance/                   # 6 screenshots covering scaling runs (1 to 16 threads)
├── report/                            # Comprehensive technical laboratory report
│   └── Multithreaded_Programming_Comprehensive_Report.md
└── presentation/                      # Evaluation defense presentation slide deck outline
    └── Evaluation_Slides_Outline.md
```

---

## 4. Step-by-Step Hands-on Guide

---

### Part A: POSIX Threads (Pthreads)

#### Step 1: Environment Preparation and Toolchain Check
Confirm compiler capabilities and OpenMP support inside WSL2 Ubuntu:
```bash
mkdir -p ~/parallel_lab
cd ~/parallel_lab
gcc --version
gcc -fopenmp --version
```

<div align="center">
  <img src="screenshots/pthreads/01-env-setup-gcc.png" alt="Compiler Verification" width="850"/>
  <p><strong>Figure 1.1:</strong> Verification of GCC 15.2.0 compiler installation and OpenMP capabilities.</p>
</div>

#### Step 2: Single Thread Creation and Joining (`thread1.c`)
Instantiate an additional worker thread using `pthread_create()` and coordinate termination with `pthread_join()`:
```bash
nano thread1.c
gcc thread1.c -o thread1 -pthread
./thread1
```

<div align="center">
  <img src="screenshots/pthreads/02-thread1-code.png" alt="thread1.c Source Code" width="850"/>
  <p><strong>Figure 1.2:</strong> Source code of thread1.c in Nano editor demonstrating pthread_create and pthread_join.</p>
</div>

<div align="center">
  <img src="screenshots/pthreads/03-thread1-run.png" alt="thread1.c Execution" width="850"/>
  <p><strong>Figure 1.3:</strong> Successful compilation and execution of thread1.</p>
</div>

#### Step 3: Multiple Concurrent Threads (`thread2.c`)
Launch 4 concurrent worker threads, passing unique thread IDs by address:
```bash
nano thread2.c
gcc thread2.c -o thread2 -pthread
./thread2
```

<div align="center">
  <img src="screenshots/pthreads/04-thread2-code.png" alt="thread2.c Source Code" width="850"/>
  <p><strong>Figure 1.4:</strong> Source code of thread2.c spawning 4 concurrent worker threads.</p>
</div>

<div align="center">
  <img src="screenshots/pthreads/05-thread2-run.png" alt="thread2.c Execution" width="850"/>
  <p><strong>Figure 1.5:</strong> Execution of thread2 demonstrating non-deterministic thread scheduling.</p>
</div>

#### Step 4: Work Partitioning across Threads (`thread_sum.c`)
Divide an 8-element integer array across 4 worker threads, computing partial sums:
```bash
nano thread_sum.c
gcc thread_sum.c -o thread_sum -pthread
./thread_sum
```

<div align="center">
  <img src="screenshots/pthreads/06-thread-sum-worksharing-code.png" alt="thread_sum.c Source Code" width="850"/>
  <p><strong>Figure 1.6:</strong> Source code of thread_sum.c partitioning array boundaries per thread ID.</p>
</div>

<div align="center">
  <img src="screenshots/pthreads/07-thread-sum-worksharing-run.png" alt="thread_sum.c Execution" width="850"/>
  <p><strong>Figure 1.7:</strong> Partial sums computed by threads and reassembled to produce total sum = 360.</p>
</div>

#### Step 5: Unsynchronized Race Condition (`race.c`)
Concurrently increment a shared counter across 4 threads without synchronization:
```bash
nano race.c
gcc race.c -o race -pthread
./race
```

<div align="center">
  <img src="screenshots/pthreads/08-race-condition-code.png" alt="race.c Source Code" width="850"/>
  <p><strong>Figure 1.8:</strong> Source code of race.c demonstrating unprotected shared variable updates.</p>
</div>

<div align="center">
  <img src="screenshots/pthreads/09-race-condition-run.png" alt="race.c Execution" width="850"/>
  <p><strong>Figure 1.9:</strong> Race condition execution: Expected 400000, Actual 197937 (over 50% data loss).</p>
</div>

#### Step 6: Mutual Exclusion Synchronization (`mutex.c`)
Protect the critical section with `pthread_mutex_lock()` and `pthread_mutex_unlock()`:
```bash
nano mutex.c
gcc mutex.c -o mutex -pthread
./mutex
```

<div align="center">
  <img src="screenshots/pthreads/10-mutex-synchronization-code.png" alt="mutex.c Source Code" width="850"/>
  <p><strong>Figure 1.10:</strong> Source code of mutex.c enclosing increment operations within mutual exclusion locks.</p>
</div>

<div align="center">
  <img src="screenshots/pthreads/11-mutex-synchronization-run.png" alt="mutex.c Execution" width="850"/>
  <p><strong>Figure 1.11:</strong> Execution of mutex.c confirming exact arithmetic correctness (400000 / 400000).</p>
</div>

---

### Part B: OpenMP Compiler Directives

#### Step 7: Basic Parallel Region (`omp1.c`)
Instantiate a team of OpenMP threads and query runtime IDs:
```bash
nano omp1.c
gcc omp1.c -o omp1 -fopenmp
./omp1
```

<div align="center">
  <img src="screenshots/openmp/01-omp-basic-parallel-region-code.png" alt="omp1.c Source Code" width="850"/>
  <p><strong>Figure 2.1:</strong> OpenMP parallel region pragma and runtime query functions.</p>
</div>

<div align="center">
  <img src="screenshots/openmp/02-omp-basic-parallel-region-run.png" alt="omp1.c Execution" width="850"/>
  <p><strong>Figure 2.2:</strong> Execution showing parallel team of 16 threads greeting concurrently.</p>
</div>

#### Step 8: Work Sharing and Reduction (`omp_sum.c`)
Partition loop iterations automatically and combine partial sums via `reduction(+:total_sum)`:
```bash
nano omp_sum.c
gcc omp_sum.c -o omp_sum -fopenmp
./omp_sum
```

<div align="center">
  <img src="screenshots/openmp/03-omp-worksharing-reduction-code.png" alt="omp_sum.c Source Code" width="850"/>
  <p><strong>Figure 2.3:</strong> Source code of omp_sum.c using parallel for with reduction clause.</p>
</div>

<div align="center">
  <img src="screenshots/openmp/04-omp-worksharing-reduction-run.png" alt="omp_sum.c Execution" width="850"/>
  <p><strong>Figure 2.4:</strong> Execution showing iteration distribution across threads and correct final sum (360).</p>
</div>

#### Step 9: OpenMP Race Condition (`omp_race.c`)
Demonstrate that compiler-managed threads still corrupt shared memory without explicit protection:
```bash
nano omp_race.c
gcc omp_race.c -o omp_race -fopenmp
./omp_race
```

<div align="center">
  <img src="screenshots/openmp/05-omp-race-condition-code.png" alt="omp_race.c Source Code" width="850"/>
  <p><strong>Figure 2.5:</strong> Unprotected OpenMP parallel block modifying shared variable.</p>
</div>

<div align="center">
  <img src="screenshots/openmp/06-omp-race-condition-run.png" alt="omp_race.c Execution" width="850"/>
  <p><strong>Figure 2.6:</strong> OpenMP race condition: Expected 400000, Actual 119127 (70% data loss).</p>
</div>

#### Step 10: Critical Section Mutual Exclusion (`omp_critical.c`)
Enforce atomic serialized access using `#pragma omp critical`:
```bash
nano omp_critical.c
gcc omp_critical.c -o omp_critical -fopenmp
./omp_critical
```

<div align="center">
  <img src="screenshots/openmp/07-omp-critical-section-code.png" alt="omp_critical.c Source Code" width="850"/>
  <p><strong>Figure 2.7:</strong> Source code incorporating OpenMP critical directive.</p>
</div>

<div align="center">
  <img src="screenshots/openmp/08-omp-critical-section-run.png" alt="omp_critical.c Execution" width="850"/>
  <p><strong>Figure 2.8:</strong> Execution confirming data integrity: Expected 400000, Actual 400000.</p>
</div>

#### Step 11: Rendezvous Barrier Coordination (`omp_barrier.c`)
Synchronize execution phases using `#pragma omp barrier`:
```bash
nano omp_barrier.c
gcc omp_barrier.c -o omp_barrier -fopenmp
./omp_barrier
```

<div align="center">
  <img src="screenshots/openmp/09-omp-barrier-coordination-code.png" alt="omp_barrier.c Source Code" width="850"/>
  <p><strong>Figure 2.9:</strong> Source code implementing barrier synchronization between Stage 1 and Stage 2.</p>
</div>

<div align="center">
  <img src="screenshots/openmp/10-omp-barrier-coordination-run.png" alt="omp_barrier.c Execution" width="850"/>
  <p><strong>Figure 2.10:</strong> Execution proving that all Stage 1 prints finish before any Stage 2 prints begin.</p>
</div>

---

### Part C: Scalability Benchmark (1 Billion Workload)

#### Step 12: Sequential Baseline Benchmark (`sequential.c`)
Establish baseline execution time summing $N = 10^9$ terms on a single thread:
```bash
nano sequential.c
gcc sequential.c -o sequential
./sequential
```

<div align="center">
  <img src="screenshots/performance/01-sequential-benchmark-code.png" alt="sequential.c Source Code" width="850"/>
  <p><strong>Figure 3.1:</strong> Sequential benchmark source code computing 1-billion term progression.</p>
</div>

<div align="center">
  <img src="screenshots/performance/02-sequential-benchmark-run.png" alt="sequential.c Execution" width="850"/>
  <p><strong>Figure 3.2:</strong> Execution of sequential baseline recording elapsed time (1.788s local / 1.353s reference).</p>
</div>

#### Step 13: Pthreads Scalability Evaluation (`pthread_perf.c`)
Execute Pthreads implementation across 1, 2, 4, 6, and 16 worker threads:
```bash
nano pthread_perf.c
gcc pthread_perf.c -o pthread_perf -pthread
./pthread_perf
```

<div align="center">
  <img src="screenshots/performance/03-pthreads-perf-benchmark-code.png" alt="pthread_perf.c Source Code" width="850"/>
  <p><strong>Figure 3.3:</strong> Pthreads benchmark source code with dynamic thread creation and chunking.</p>
</div>

<div align="center">
  <img src="screenshots/performance/04-pthreads-perf-benchmark-run.png" alt="pthread_perf.c Execution" width="850"/>
  <p><strong>Figure 3.4:</strong> Multi-run execution recording execution timings across thread counts.</p>
</div>

#### Step 14: OpenMP Scalability Evaluation (`omp_perf.c`)
Execute OpenMP implementation across matching thread counts:
```bash
nano omp_perf.c
gcc omp_perf.c -o omp_perf -fopenmp
./omp_perf
```

<div align="center">
  <img src="screenshots/performance/05-openmp-perf-benchmark-code.png" alt="omp_perf.c Source Code" width="850"/>
  <p><strong>Figure 3.5:</strong> OpenMP performance benchmark source code using parallel for reduction.</p>
</div>

<div align="center">
  <img src="screenshots/performance/06-openmp-perf-benchmark-run.png" alt="omp_perf.c Execution" width="850"/>
  <p><strong>Figure 3.6:</strong> OpenMP multi-run execution measuring elapsed timings from 1 to 16 threads.</p>
</div>

---

## 5. Performance Benchmark Results

### Tabulated Empirical Results ($N = 10^9$)

| Threads ($P$) | Pthreads Time (s) | Pthreads Speedup | Pthreads Efficiency | OpenMP Time (s) | OpenMP Speedup | OpenMP Efficiency |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Sequential** | 1.353219 | $1.000\times$ | $100.00\%$ | 1.353219 | $1.000\times$ | $100.00\%$ |
| **1** | 1.348142 | $1.004\times$ | $100.38\%$ | 1.409294 | $0.960\times$ | $96.02\%$ |
| **2** | 0.680737 | $1.988\times$ | $99.39\%$ | 0.715560 | $1.891\times$ | $94.56\%$ |
| **4** | 0.358872 | $3.771\times$ | $94.27\%$ | 0.360803 | $3.751\times$ | $93.76\%$ |
| **6** | 0.241345 | $5.608\times$ | $93.45\%$ | 0.241608 | $5.601\times$ | $93.35\%$ |
| **16** | 0.144812 | $9.345\times$ | $58.40\%$ | 0.140692 | $9.618\times$ | $60.11\%$ |

### Graphical Performance Visualizations

<div align="center">
  <img src="graphs/execution_time_vs_threads.png" alt="Execution Time vs Threads" width="850"/>
  <p><strong>Figure 5.1:</strong> Execution time comparison between Pthreads and OpenMP relative to sequential baseline.</p>
</div>

<div align="center">
  <img src="graphs/speedup_vs_threads.png" alt="Speedup vs Threads" width="850"/>
  <p><strong>Figure 5.2:</strong> Measured speedup curves plotted against ideal linear scaling ($S = P$).</p>
</div>

<div align="center">
  <img src="graphs/efficiency_vs_threads.png" alt="Efficiency vs Threads" width="850"/>
  <p><strong>Figure 5.3:</strong> Parallel efficiency curves illustrating high utilization up to 6 threads and contention drop at 16 threads.</p>
</div>

---

## 6. Comparative Performance and Synchronization Analysis

### 1. Framework Comparison: Pthreads vs. OpenMP
- **Execution Parity**: Pthreads and OpenMP show virtually identical runtime performance (differing by less than $2\%$ at 4, 6, and 16 threads).
- **Productivity**: OpenMP replaces $\approx 40$ lines of thread management, struct definitions, and join loops with a single `#pragma omp parallel for reduction(+:sum)` directive.

### 2. Scalability Limits and Amdahl's Law
- **Near-Linear Regime ($P \le 6$)**: Both frameworks achieve $>93\%$ parallel efficiency from 1 to 6 threads.
- **Saturation Regime ($P = 16$)**: Efficiency drops to $\approx 58-60\%$. Adding more threads introduces:
  1. Memory bus contention during arithmetic reduction.
  2. Operating system scheduler context-switching latency.
  3. Non-parallel overhead in thread spawning and reduction combination.

---

## 7. Quick Build and Execution Instructions

### Unified Build using Makefile
```bash
cd src

# Build all programs
make all

# Build individual suites
make pthreads
make openmp

# Clean executables
make clean
```

### Manual Compilation Commands
```bash
# Pthreads programs
gcc -O2 src/thread1.c -o thread1 -pthread
gcc -O2 src/thread2.c -o thread2 -pthread
gcc -O2 src/thread_sum.c -o thread_sum -pthread
gcc -O2 src/race.c -o race -pthread
gcc -O2 src/mutex.c -o mutex -pthread
gcc -O2 src/pthread_perf.c -o pthread_perf -pthread

# OpenMP programs
gcc -O2 -fopenmp src/omp1.c -o omp1
gcc -O2 -fopenmp src/omp_sum.c -o omp_sum
gcc -O2 -fopenmp src/omp_race.c -o omp_race
gcc -O2 -fopenmp src/omp_critical.c -o omp_critical
gcc -O2 -fopenmp src/omp_barrier.c -o omp_barrier
gcc -O2 -fopenmp src/omp_perf.c -o omp_perf

# Sequential baseline
gcc -O2 src/sequential.c -o sequential
```

---

## 8. Author Information

| Attribute | Details |
| :--- | :--- |
| **Author** | Aditya Gavimath |
| **Course** | Parallel and Graphical Computing (PCG) |
| **Semester** | 5th Semester B.Tech CSE |
| **Repository** | [EXP2 - Multithreaded Pthreads & OpenMP](https://github.com/ADITYAGAVIMATH) |
| **Reference Format** | [Hypervisor-Analysis Baseline](https://github.com/ADITYAGAVIMATH/Hypervisor-Analysis) |
