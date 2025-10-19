import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams.update({
    'text.usetex': True,
    'font.family': 'serif',
    'text.latex.preamble': r'\usepackage[utf8]{inputenc} \usepackage[russian]{babel}',
})

df = pd.read_csv('lab2_float/numerical_integration.csv')

fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(14, 12), dpi=100)
manager = plt.get_current_fig_manager()
manager.window.wm_geometry("+50+50")
fig.suptitle('Численное интегрирование: сравнение методов и типов данных', 
             fontsize=18, fontweight='bold')


colors = ['#1f77b4', '#ff7f0e', '#2ca02c']
markers = ['v', '^', 'o']
cases = ['Left', 'Right', 'Mid']
data_types = ['float', 'double']

# Float plot
ax1.set_xlabel(r'Количество разбиений $n$', fontsize=14, fontweight='light', labelpad=10)
ax1.set_ylabel(r'Разность $\int$', fontsize=14, fontweight='light', labelpad=10)
ax1.set_title(r'Тип данных $float$, $n \sim 1000$', fontsize=16, fontweight='semibold', pad=20)
ax1.grid(which='major', linestyle='-')
ax1.minorticks_on() 
ax1.grid(which='minor', linestyle='--', linewidth=0.5)

ax3.set_xlabel(r'Количество разбиений $n$', fontsize=14, fontweight='light', labelpad=10)
ax3.set_ylabel(r'Разность $\int$', fontsize=14, fontweight='light', labelpad=10)
ax3.set_title(r'Тип данных $float$, $n >> 1000$', fontsize=16, fontweight='semibold', pad=20)
ax3.grid(which='major', linestyle='-')
ax3.minorticks_on() 
ax3.grid(which='minor', linestyle='--', linewidth=0.5)

# Double plot
ax2.set_xlabel(r'Количество разбиений $n$', fontsize=14, fontweight='light', labelpad=10)
ax2.set_ylabel(r'Разность $\int$', fontsize=14, fontweight='light', labelpad=10)
ax2.set_title(r'Тип данных $double$, $n \sim 1000$', fontsize=16, fontweight='semibold', pad=20)
ax2.grid(which='major', linestyle='-')
ax2.minorticks_on() 
ax2.grid(which='minor', linestyle='--', linewidth=0.5)

ax4.set_xlabel(r'Количество разбиений $n$', fontsize=14, fontweight='light', labelpad=10)
ax4.set_ylabel(r'Разность $\int$', fontsize=14, fontweight='light', labelpad=10)
ax4.set_title(r'Тип данных $double$, $n >> 1000$', fontsize=16, fontweight='semibold', pad=20)
ax4.grid(which='major', linestyle='-')
ax4.minorticks_on() 
ax4.grid(which='minor', linestyle='--', linewidth=0.5)

for data_type, ax in zip(data_types, (ax1, ax2)):
    for i, case in enumerate(cases):
        new_color = colors[i]
        new_marker = markers[i]
        data = df[df['data_type'] == data_type]
        x = data['n'][:55]
        y = data[case][:55]
        ax.plot(x, y, color=new_color, marker=new_marker, ms=3, linewidth=1, 
                label=f'{case} ({data_type})')
for data_type, ax in zip(data_types, (ax3, ax4)):
    for i, case in enumerate(cases):
        new_color = colors[i]
        new_marker = markers[i]
        data = df[df['data_type'] == data_type]
        x = data['n'][55:]
        y = data[case][55:]
        ax.plot(x, y, color=new_color, marker=new_marker, ms=3, linewidth=1, 
                label=f'{case} ({data_type})')

ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()

# plt.tight_layout()
plt.subplots_adjust(
    left=0.08,
    right=0.95,
    bottom=0.08, 
    top=0.90,   
    wspace=0.3,   
    hspace=0.4   
)

fig.savefig('lab2_float/plot.png', dpi = 300)
# plt.show()