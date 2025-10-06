import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

# Read the CSV file
df = pd.read_csv('sort_algorithms.csv')

# Separate algorithms into O(n^2) and O(n log n) groups
n2_algorithms = ['bubble_sort', 'insertion_sort', 'selection_sort']
nlogn_algorithms = ['merge_sort', 'quick_sort', 'heap_sort']

# Create the plots
plt.figure(plt.figure(figsize=(12,8)))
manager = plt.get_current_fig_manager()
manager.window.wm_geometry("+50+50")

# Plot 1: O(n^2) algorithms
plt.subplot(2, 2, 1)
for algo in n2_algorithms:
    algo_data = df[df['algorithm'] == algo]
    x = np.log(algo_data['array_size'])
    y = np.log(algo_data['time_ns'])
    plt.plot(x, y, marker='o', ms=1, label=algo, linewidth=1)
    
    # Add LSM line
    slope, intercept, r_value, p_value, std_err = stats.linregress(x, y)
    lsm_line = slope * x + intercept
    plt.plot(x, lsm_line, '--', linewidth=0.8, alpha=0.7, label=f'{algo} LSM (slope={slope:.7f})')

plt.xlabel('ln(N)')
plt.ylabel('ln(t/ns)')
plt.title('O(n²)')
plt.legend(fontsize=8)
plt.grid(which='major', linestyle='-')
plt.minorticks_on() 
plt.grid(which='minor', linestyle='--', linewidth=0.5)

# Plot 2: O(n log n) algorithms
plt.subplot(2, 2, 2)
for algo in nlogn_algorithms:
    algo_data = df[df['algorithm'] == algo]
    x = algo_data['array_size']
    y = algo_data['time_ns'] / (algo_data['array_size'] * np.log(algo_data['array_size']))
    plt.plot(x, y, marker='o', ms=1, label=algo, linewidth=1)
    
    # Add LSM line
    slope, intercept, r_value, p_value, std_err = stats.linregress(x[6:], y[6:]) #First 6 points have small N
    lsm_line = slope * x + intercept
    plt.plot(x, lsm_line, '--', linewidth=0.8, alpha=0.7, label=f'{algo} LSM (intercept={intercept:.2f})')

plt.xlabel('N')
plt.ylabel('t/NlogN (ns)')
plt.title('O(n log n)')
plt.legend(fontsize=8)
plt.grid(which='major', linestyle='-')
plt.minorticks_on() 
plt.grid(which='minor', linestyle='--', linewidth=0.5)

plt.subplot(2, 2, (3,4))
for algo in (nlogn_algorithms + n2_algorithms):
    algo_data = df[df['algorithm'] == algo]
    x = algo_data['array_size']
    y = algo_data['time_ns']
    plt.plot(x, y, marker='o', ms=1, label=algo, linewidth=1)
    
plt.xlabel('N')
plt.ylabel('t (ns)')
plt.title('O(n²) and O(n log n)')
plt.legend(fontsize=8)
plt.grid(which='major', linestyle='-')
plt.minorticks_on() 
plt.grid(which='minor', linestyle='--', linewidth=0.5)


plt.tight_layout()
plt.savefig("sort_algorithms_plots.png", dpi = 300)
plt.show()