import csv
import matplotlib.pyplot as plt


def read_csv(filename):
    sizes = []
    vec_times = []
    subvec_times = []

    with open(filename, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            sizes.append(int(row["size"]))
            vec_times.append(float(row["vector"]))
            subvec_times.append(float(row["subvector"]))

    return sizes, vec_times, subvec_times


def plot_graph(sizes, vec_times, subvec_times, output_png):

    fig, axes = plt.subplots(1, 2, figsize=(16, 6))

    axes[0].plot(sizes, vec_times, marker="o", label="std::vector", color = 'darkcyan')
    axes[0].plot(sizes, subvec_times, marker="o", label="Subvector", color = 'crimson')

    axes[0].set_xlabel("Размер контейнера n")
    axes[0].set_ylabel("Среднее время insert (мкс)")
    axes[0].set_title("Вставка в случайную позицию")

    axes[0].grid(True, which="major", linestyle="-", alpha=0.7)
    axes[0].grid(True, which="minor", linestyle="--", alpha=0.3)
    axes[0].minorticks_on()
    axes[0].legend()

    vec_norm = [t / n for t, n in zip(vec_times, sizes)]
    subvec_norm = [t / n for t, n in zip(subvec_times, sizes)]

    axes[1].plot(sizes, vec_norm, marker="o", label="std::vector", color = 'darkcyan')
    axes[1].plot(sizes, subvec_norm, marker="o", label="Subvector", color = 'crimson')

    axes[1].set_xlabel("Размер контейнера n")
    axes[1].set_ylabel("t/n, мкс")
    axes[1].set_title("Асимптотика O(n)")

    axes[1].grid(True, which="major", linestyle="-", alpha=0.7)
    axes[1].grid(True, which="minor", linestyle="--", alpha=0.3)
    axes[1].minorticks_on()
    axes[1].legend()

    fig.tight_layout()

    plt.savefig(output_png, dpi=300, bbox_inches="tight")
    plt.show()


def main():
    input_csv = "1/insert_benchmark.csv"
    output_png = "1/insert_benchmark.png"

    sizes, vec_times, subvec_times = read_csv(input_csv)
    plot_graph(sizes, vec_times, subvec_times, output_png)


if __name__ == "__main__":
    main()