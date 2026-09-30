#!/usr/bin/env python3
"""
Performance Visualization Generator for Experiment 02
Generates publication-quality charts for Execution Time, Speedup, and Efficiency.
"""

import os
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')
plt.rcParams['font.sans-serif'] = 'Arial'
plt.rcParams['font.family'] = 'sans-serif'
plt.rcParams['figure.dpi'] = 300

threads = np.array([1, 2, 4, 6, 16])
seq_baseline = 1.353219

pth_times = np.array([1.348142, 0.680737, 0.358872, 0.241345, 0.144812])
omp_times = np.array([1.409294, 0.715560, 0.360803, 0.241608, 0.140692])

pth_speedup = np.array([1.004, 1.988, 3.771, 5.608, 9.345])
omp_speedup = np.array([0.960, 1.891, 3.751, 5.601, 9.618])

pth_eff = np.array([100.38, 99.39, 94.27, 93.45, 58.40])
omp_eff = np.array([96.02, 94.56, 93.76, 93.35, 60.11])

output_dir = os.path.dirname(os.path.abspath(__file__))

# 1. Execution Time vs. Threads
fig, ax = plt.subplots(figsize=(8.5, 5))
ax.axhline(y=seq_baseline, color='#C53030', linestyle='--', linewidth=1.5, label=f'Sequential Baseline ({seq_baseline:.3f}s)')
ax.plot(threads, pth_times, marker='o', linewidth=2.2, color='#2B6CB0', label='Pthreads Execution Time')
ax.plot(threads, omp_times, marker='s', linewidth=2.2, color='#2F855A', label='OpenMP Execution Time')

for t, pt, ot in zip(threads, pth_times, omp_times):
    ax.annotate(f"{pt:.3f}s", (t, pt), textcoords="offset points", xytext=(0, 8), ha='center', fontsize=9, fontweight='bold', color='#2B6CB0')
    ax.annotate(f"{ot:.3f}s", (t, ot), textcoords="offset points", xytext=(0, -14), ha='center', fontsize=9, fontweight='bold', color='#2F855A')

ax.set_xlabel('Number of Threads', fontsize=12, fontweight='bold')
ax.set_ylabel('Execution Time (seconds)', fontsize=12, fontweight='bold')
ax.set_title('Experiment 02: Execution Time vs. Number of Threads (N = 10^9)', fontsize=13, fontweight='bold', pad=15)
ax.set_xticks(threads)
ax.legend(frameon=True, facecolor='white', framealpha=0.9, fontsize=10)
ax.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'execution_time_vs_threads.png'), dpi=300)
plt.close()

# 2. Speedup vs. Threads
fig, ax = plt.subplots(figsize=(8.5, 5))
ax.plot(threads, threads, color='#A0AEC0', linestyle=':', linewidth=1.8, label='Ideal Linear Speedup (S = P)')
ax.plot(threads, pth_speedup, marker='o', linewidth=2.2, color='#2B6CB0', label='Pthreads Measured Speedup')
ax.plot(threads, omp_speedup, marker='s', linewidth=2.2, color='#2F855A', label='OpenMP Measured Speedup')

for t, ps, os_val in zip(threads, pth_speedup, omp_speedup):
    ax.annotate(f"{ps:.2f}x", (t, ps), textcoords="offset points", xytext=(-10, 8), ha='right', fontsize=9, fontweight='bold', color='#2B6CB0')
    ax.annotate(f"{os_val:.2f}x", (t, os_val), textcoords="offset points", xytext=(10, -12), ha='left', fontsize=9, fontweight='bold', color='#2F855A')

ax.set_xlabel('Number of Threads', fontsize=12, fontweight='bold')
ax.set_ylabel('Speedup Relative to Sequential', fontsize=12, fontweight='bold')
ax.set_title('Experiment 02: Speedup vs. Number of Threads', fontsize=13, fontweight='bold', pad=15)
ax.set_xticks(threads)
ax.legend(frameon=True, facecolor='white', framealpha=0.9, fontsize=10)
ax.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'speedup_vs_threads.png'), dpi=300)
plt.close()

# 3. Efficiency vs. Threads
fig, ax = plt.subplots(figsize=(8.5, 5))
ax.axhline(y=100.0, color='#A0AEC0', linestyle=':', linewidth=1.8, label='Ideal 100% Efficiency')
ax.plot(threads, pth_eff, marker='o', linewidth=2.2, color='#2B6CB0', label='Pthreads Parallel Efficiency (%)')
ax.plot(threads, omp_eff, marker='s', linewidth=2.2, color='#2F855A', label='OpenMP Parallel Efficiency (%)')

for t, pe, oe in zip(threads, pth_eff, omp_eff):
    ax.annotate(f"{pe:.1f}%", (t, pe), textcoords="offset points", xytext=(-10, 8), ha='right', fontsize=9, fontweight='bold', color='#2B6CB0')
    ax.annotate(f"{oe:.1f}%", (t, oe), textcoords="offset points", xytext=(10, -12), ha='left', fontsize=9, fontweight='bold', color='#2F855A')

ax.set_xlabel('Number of Threads', fontsize=12, fontweight='bold')
ax.set_ylabel('Parallel Efficiency (%)', fontsize=12, fontweight='bold')
ax.set_title('Experiment 02: Parallel Efficiency vs. Number of Threads', fontsize=13, fontweight='bold', pad=15)
ax.set_xticks(threads)
ax.set_ylim(40, 115)
ax.legend(frameon=True, facecolor='white', framealpha=0.9, fontsize=10)
ax.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'efficiency_vs_threads.png'), dpi=300)
plt.close()

print("EXP2 Graphs generated successfully in:", output_dir)
