import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

#Additional function
def new_plot(x,y,case,color,algo):
    new_marker = 'o'
    if case==cases[0]:
        new_marker = '^'
    elif case ==cases[2]:
        new_marker = 'v'
    plt.plot(x, y, marker=new_marker, ms=3, label=algo+ " " + case, linewidth=1,color =color)
    if algo in n2_algorithms:
        plt.xlabel('ln(N)')
        plt.ylabel('ln(t/ns)')
    else:
        plt.xlabel('N')
        plt.ylabel('t/NlogN (ns)')
    plt.title(algo)
    plt.legend(fontsize=8)
    plt.grid(which='major', linestyle='-')
    plt.minorticks_on() 
    plt.grid(which='minor', linestyle='--', linewidth=0.5)


# Read the CSV file
df = pd.read_csv('dependence_on_initial_data.csv')

# Separate algorithms into O(n^2) and O(n log n) groups
n2_algorithms = ['bubble_sort', 'insertion_sort', 'selection_sort']
nlogn_algorithms = ['merge_sort', 'quick_sort', 'heap_sort']
cases = ['best', 'average', 'worst']
colors = ['#1f77b4', '#ff7f0e', '#2ca02c']

# Create the plots
plt.figure(plt.figure(figsize=(14,8)))
manager = plt.get_current_fig_manager()
manager.window.wm_geometry("+50+50")

# Plot 1: O(n^2) algorithms

for i, algo in enumerate(n2_algorithms):
    plt.subplot(2, 3, i+1)
    color = colors[i]
    for case in cases:
        algo_data = df[(df['algorithm'] == algo) & (df['initial_data'] == case)]
        x = np.log(algo_data['array_size'])
        y = np.log(algo_data['time_ns'])
        new_plot(x,y,case,color,algo)


# Plot 2: O(n log n) algorithms
for i, algo in enumerate(nlogn_algorithms):
    plt.subplot(2, 3, i+4)
    color = colors[i]
    for case in cases:
        algo_data = df[(df['algorithm'] == algo) & (df['initial_data'] == case)]
        x = algo_data['array_size']
        y = algo_data['time_ns'] / (algo_data['array_size'] * np.log(algo_data['array_size']))
        new_plot(x,y,case,color,algo)

plt.tight_layout()
plt.savefig("dependence_on_initial_data.png", dpi = 300)
plt.show()