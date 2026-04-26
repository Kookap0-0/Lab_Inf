import csv
import os
import math
import matplotlib.pyplot as plt


def read_csv(filename):
    sizes = []
    set_times = []
    map_times = []
    multiset_times = []
    multimap_times = []

    with open(filename, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            sizes.append(int(row["size"]))
            set_times.append(float(row["set"]))
            map_times.append(float(row["map"]))
            multiset_times.append(float(row["multiset"]))
            multimap_times.append(float(row["multimap"]))

    return sizes, set_times, map_times, multiset_times, multimap_times


def plot_graph(sizes, set_times, map_times, multiset_times, multimap_times, output_png):

    fig, axes = plt.subplots(1, 2, figsize=(16, 6))

    axes[0].plot(sizes, set_times, marker="o", label="std::set")
    axes[0].plot(sizes, map_times, marker="o", label="std::map")
    axes[0].plot(sizes, multiset_times, marker="o", label="std::multiset")
    axes[0].plot(sizes, multimap_times, marker="o", label="std::multimap")

    axes[0].set_xlabel("Размер контейнера n")
    axes[0].set_ylabel("Среднее время вставки t, нс")
    axes[0].set_title("Время вставки элементов")

    axes[0].grid(True, which="major", linestyle="-", alpha=0.7)
    axes[0].grid(True, which="minor", linestyle="--", alpha=0.3)
    axes[0].minorticks_on()
    axes[0].legend()

    log_sizes = [math.log(n) for n in sizes]

    axes[1].plot(log_sizes, set_times, marker="o", label="std::set")
    axes[1].plot(log_sizes, map_times, marker="o", label="std::map")
    axes[1].plot(log_sizes, multiset_times, marker="o", label="std::multiset")
    axes[1].plot(log_sizes, multimap_times, marker="o", label="std::multimap")

    axes[1].set_xlabel("log(n)")
    axes[1].set_ylabel("Среднее время вставки t, нс")
    axes[1].set_title("Асимптотика вставки O(log(n))")

    axes[1].grid(True, which="major", linestyle="-", alpha=0.7)
    axes[1].grid(True, which="minor", linestyle="--", alpha=0.3)
    axes[1].minorticks_on()
    axes[1].legend()

    fig.tight_layout()

    fig.savefig(output_png, dpi=300, bbox_inches="tight")
    plt.show()


def main():
    input_csv = "5/insert_benchmark.csv"
    output_png = os.path.splitext(input_csv)[0] + ".png"

    sizes, set_times, map_times, multiset_times, multimap_times = read_csv(input_csv)
    plot_graph(sizes, set_times, map_times, multiset_times, multimap_times, output_png)


if __name__ == "__main__":
    main()