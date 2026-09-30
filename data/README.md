# Dataset and Workload Characterization

## Problem Definition
Experiment 02 analyzes multithreading across two distinct computational regimes:

1. **Discrete Demonstration Workload (Part A & Part B)**:
   - Fixed array of 8 integers: `[10, 20, 30, 40, 50, 60, 70, 80]`
   - Sum: $10 + 20 + 30 + 40 + 50 + 60 + 70 + 80 = 360$
   - Race condition stress loop: 4 threads executing $100,000$ increment operations ($400,000$ expected total).

2. **Compute-Bound Scaling Benchmark (Part C)**:
   - Single precision summation loop traversing $N = 1,000,000,000$ ($10^9$) iterations:
     $$\text{Total Sum} = \sum_{i=0}^{N-1} (i \times 10^{-6}) = 499999999500.00$$
   - Arithmetic progression:
     $$\sum_{i=0}^{N-1} i = \frac{(N-1)N}{2} = \frac{999,999,999 \times 1,000,000,000}{2} = 4.999999995 \times 10^{17}$$
     $$\text{Scaled Result} = 4.999999995 \times 10^{17} \times 10^{-6} = 499999999500.00$$

## Verification Tool
- `benchmark_data_generator.py`: Generates custom test arrays for verifying chunk-based partition boundaries across arbitrary thread counts.
