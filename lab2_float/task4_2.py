import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams.update({
    'text.usetex': True,
    'font.family': 'serif',
    'text.latex.preamble': r'\usepackage[utf8]{inputenc} \usepackage[russian]{babel}',
})

df = pd.read_csv('lab2_float/function_data.csv')

fig, ax = plt.subplots(figsize=(12, 8), dpi=100)
manager = plt.get_current_fig_manager()
manager.window.wm_geometry("+50+50")


colors = ['#1f77b4', '#ff7f0e', '#2ca02c']
markers = ['v', '^', 'o']
cases = ['f(x)', 'derivative', 'antiderivative']
legend = [r'$f(x)$', r'$\frac{df}{dx}$', r'$\int f(x)dx$']

ax.set_xlabel(r'$x$', fontsize=14, fontweight='light', labelpad=10)
ax.grid(which='major', linestyle='-')
ax.minorticks_on() 
ax.grid(which='minor', linestyle='--', linewidth=0.5)

for i, case in enumerate(cases):
    new_color = colors[i]
    new_marker = markers[i]
    x = df['x']
    y = df[case]
    ax.plot(x, y, color=new_color, marker=new_marker, ms=3, linewidth=1, 
            label=legend[i])

ax.legend()

plt.tight_layout()
fig.savefig('lab2_float/function_data.png', dpi = 300)
# plt.show()