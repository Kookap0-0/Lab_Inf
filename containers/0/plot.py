import csv
import matplotlib.pyplot as plt


def read_csv(filename):
    i_vals = []
    sizes = []
    capacities = []

    with open(filename, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            i_vals.append(int(row["i"]))
            sizes.append(int(row["size"]))
            capacities.append(int(row["capacity"]))

    return i_vals, sizes, capacities


def plot_vector_growth(i_vals, sizes, capacities, output_png):

    plt.figure(figsize=(10, 6))

    plt.plot(i_vals, sizes, label="size", color = 'darkcyan')
    plt.plot(i_vals, capacities, label="capacity", color = 'crimson')

    plt.xlabel("Итерация")
    plt.ylabel("Количество элементов")
    plt.title("Рост std::vector при push_back")

    plt.grid(True, which="major", linestyle="-", alpha=0.7)
    plt.grid(True, which="minor", linestyle="--", alpha=0.3)
    plt.minorticks_on()

    plt.legend()
    plt.tight_layout()

    plt.savefig(output_png, dpi=300, bbox_inches="tight")

    plt.show()


def main():
    input_csv = "0/vector_push_back.csv"
    output_png = "0/vector_growth.png"

    i_vals, sizes, capacities = read_csv(input_csv)
    plot_vector_growth(i_vals, sizes, capacities, output_png)


if __name__ == "__main__":
    main()