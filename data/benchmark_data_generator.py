#!/usr/bin/env python3
"""
Workload Verification and Chunk Partitioner
Course: Parallel and Graphical Computing (PCG)
"""

import sys

def verify_theoretical_sum(n: int) -> float:
    # Sum of i from 0 to N-1 = (N-1)*N / 2
    sum_int = (n - 1) * n // 2
    scaled = sum_int * 1e-6
    print(f"Elements (N)       : {n}")
    print(f"Exact Integer Sum  : {sum_int}")
    print(f"Scaled Sum (* 1e-6): {scaled:.2f}")
    return scaled

def print_chunks(n: int, num_threads: int):
    chunk = n // num_threads
    print(f"\nChunk distribution for {n} items across {num_threads} threads:")
    for t in range(num_threads):
        start = t * chunk
        end = n if t == num_threads - 1 else (t + 1) * chunk
        print(f"Thread {t:2d}: [{start:10d} to {end:10d}) -> {end - start:10d} items")

if __name__ == "__main__":
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 1000000000
    threads = int(sys.argv[2]) if len(sys.argv) > 2 else 4
    verify_theoretical_sum(n)
    print_chunks(n, threads)
