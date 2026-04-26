import csv
import matplotlib.pyplot as plt


def read_csv(filename):
    sizes = []
    list_times = []
    forward_list_times = []
    subforward_list_times = []

    with open(filename, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            sizes.append(int(row["size"]))
            list_times.append(float(row["list"]))
            forward_list_times.append(float(row["forward_list"]))
            subforward_list_times.append(float(row["subforward_list"]))

    return sizes, list_times, forward_list_times, subforward_list_times


def plot_graph(sizes, list_times, forward_list_times, subforward_list_times, output_png):

    plt.figure(figsize=(10, 6))

    plt.plot(sizes, list_times, marker="o", label="std::list")
    plt.plot(sizes, forward_list_times, marker="o", label="std::forward_list")
    plt.plot(sizes, subforward_list_times, marker="o", label="SubforwardList")

    plt.xlabel("Размер контейнера n")
    plt.ylabel("Среднее время t, нс")
    plt.title("Добавление элемента в начало списка (O(1))")

    plt.grid(True, which="major", linestyle="-", alpha=0.7)
    plt.grid(True, which="minor", linestyle="--", alpha=0.3)
    plt.minorticks_on()

    plt.legend()
    plt.tight_layout()

    plt.savefig(output_png, dpi=300, bbox_inches="tight")

    plt.show()


def main():
    input_csv = "3/push_front_benchmark.csv"
    output_png = "3/push_front_benchmark.png"

    sizes, list_times, forward_list_times, subforward_list_times = read_csv(input_csv)
    plot_graph(sizes, list_times, forward_list_times, subforward_list_times, output_png)


if __name__ == "__main__":
    main()