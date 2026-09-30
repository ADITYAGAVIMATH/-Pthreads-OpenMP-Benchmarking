# Thread Synchronization and Scalability Analysis

## 1. Mechanisms of Race Conditions
In modern symmetric multiprocessing (SMP) architectures, threads share physical memory. When multiple threads perform a non-atomic read-modify-write operation concurrently:
```
Thread A: Read counter (value = 10)
Thread B: Read counter (value = 10)
Thread A: Increment (value = 11)
Thread B: Increment (value = 11)
Thread A: Write counter = 11
Thread B: Write counter = 11
```
Two arithmetic operations occurred, but the final stored value only incremented by 1. One update was silently overwritten and lost.

In empirical testing:
- **Pthreads (`race.c`)**: With 4 threads and $100,000$ iterations each, the expected count was $400,000$. The actual recorded count was $197,937$ ($50.5\%$ loss).
- **OpenMP (`omp_race.c`)**: With 4 threads and $100,000$ iterations each, the recorded count was $119,127$ ($70.2\%$ loss).

## 2. Mutual Exclusion Primitives Comparison

| Characteristic | Pthreads (`pthread_mutex_t`) | OpenMP (`#pragma omp critical`) |
| :--- | :--- | :--- |
| **Control Model** | Explicit manual lock/unlock calls | Compiler-directed block scoping |
| **Initialization** | `pthread_mutex_init(&mutex, NULL)` | Automatic at parallel runtime init |
| **Destruction** | `pthread_mutex_destroy(&mutex)` | Automatic at block exit |
| **Performance Overhead** | Kernel/futex fast path | Runtime team lock table lookup |
| **Safety** | High risk of deadlocks if unlock is missed | Structurally enclosed by lexical block |

Both mechanisms successfully eliminated data corruption, recording exactly `400000 / 400000`.

## 3. Parallel Scalability & Amdahl's Law Limitations
While increasing thread count from 1 to 6 threads maintains $>93\%$ parallel efficiency, moving to 16 threads causes efficiency to drop to $\approx 58-60\%$:
- **Memory Bus Contention**: 16 concurrent threads reading and accumulating double-precision values saturate the L3 cache bus and memory controllers.
- **Operating System Thread Scheduling**: WSL2 virtualizes thread context switching across host hardware logical threads.
- **Diminishing Returns**: Synchronization barriers (`pthread_join` and OpenMP reduction combining phase) scale with $O(\log P)$ or $O(P)$, placing an upper bound on speedup as predicted by Amdahl's Law.
