import csv
import os
import matplotlib.pyplot as plt


def read_csv(filename):
    sizes = []
    vector_times = []
    forward_list_times = []
    list_times = []
    map_times = []
    set_times = []

    with open(filename, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            sizes.append(int(row["size"]))
            vector_times.append(float(row["vector"]))
            forward_list_times.append(float(row["forward_list"]))
            list_times.append(float(row["list"]))
            map_times.append(float(row["map"]))
            set_times.append(float(row["set"]))

    return sizes, vector_times, forward_list_times, list_times, map_times, set_times


def plot_graph(sizes, vector_times, forward_list_times, list_times, map_times, set_times, output_png):
    vector_norm = [t / s for t, s in zip(vector_times, sizes)]
    forward_list_norm = [t / s for t, s in zip(forward_list_times, sizes)]
    list_norm = [t / s for t, s in zip(list_times, sizes)]
    map_norm = [t / s for t, s in zip(map_times, sizes)]
    set_norm = [t / s for t, s in zip(set_times, sizes)]

    fig, axes = plt.subplots(1, 2, figsize=(16, 6))

    axes[0].plot(sizes, vector_times, marker="o", label="std::vector")
    axes[0].plot(sizes, forward_list_times, marker="o", label="std::forward_list")
    axes[0].plot(sizes, list_times, marker="o", label="std::list")
    axes[0].plot(sizes, map_times, marker="o", label="std::map")
    axes[0].plot(sizes, set_times, marker="o", label="std::set")
    axes[0].set_xlabel("Размер контейнера n")
    axes[0].set_ylabel("Среднее время, нс")
    axes[0].set_title("Среднее время обхода")
    axes[0].grid(True, which="major", linestyle="-", alpha=0.7)
    axes[0].grid(True, which="minor", linestyle="--", alpha=0.3)
    axes[0].minorticks_on()
    axes[0].legend()

    axes[1].plot(sizes, vector_norm, marker="o", label="std::vector")
    axes[1].plot(sizes, forward_list_norm, marker="o", label="std::forward_list")
    axes[1].plot(sizes, list_norm, marker="o", label="std::list")
    axes[1].plot(sizes, map_norm, marker="o", label="std::map")
    axes[1].plot(sizes, set_norm, marker="o", label="std::set")
    axes[1].set_xlabel("Размер контейнера n")
    axes[1].set_ylabel("t/n, нс")
    axes[1].set_title("Асимптотика времени обхода O(n)")
    axes[1].grid(True, which="major", linestyle="-", alpha=0.7)
    axes[1].grid(True, which="minor", linestyle="--", alpha=0.3)
    axes[1].minorticks_on()
    axes[1].legend()

    fig.tight_layout()
    fig.savefig(output_png, dpi=300, bbox_inches="tight")
    plt.show()


def main():
    input_csv = "6/traverse_benchmark.csv"
    output_png = os.path.splitext(input_csv)[0] + ".png"

    sizes, vector_times, forward_list_times, list_times, map_times, set_times = read_csv(input_csv)
    plot_graph(sizes, vector_times, forward_list_times, list_times, map_times, set_times, output_png)


if __name__ == "__main__":
    main()