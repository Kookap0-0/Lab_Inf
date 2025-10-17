import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

def f(df,s):
    x = df['array_size']
    y = df['time_ns']
    plt.plot(x,y, marker='o', ms=1, label=s, linewidth=1)

# Read the CSV file
df0 = pd.read_csv('bubble_optimisationO0.csv')
df1 = pd.read_csv('bubble_optimisationO1.csv')
df2 = pd.read_csv('bubble_optimisationO2.csv')
df3 = pd.read_csv('bubble_optimisationO3.csv')


# df0 = np.array(pd.read_csv('bubble_sort_csv0.csv',header = None))
# df1 = np.array(pd.read_csv('bubble_sort_csv1.csv',header = None))
# df2 = np.array(pd.read_csv('bubble_sort_csv2.csv',header = None))
# df3 = np.array(pd.read_csv('bubble_sort_csv3.csv',header = None))

# Create the plots
plt.figure(figsize=(12, 5))

f(df0,'O0')
f(df1,'O1')
f(df2,'O2')
f(df3,'O3')

plt.xlabel('N')
plt.ylabel('t, ns')
plt.title('Bubble sort')
plt.legend(fontsize=8)
plt.grid(which='major', linestyle='-')
plt.minorticks_on() 
plt.grid(which='minor', linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.savefig("optimisation_plot.png", dpi = 300)
plt.show()