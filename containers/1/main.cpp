#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include "subvector.hpp"

int getRandom(std::mt19937& gen) {
    static std::uniform_int_distribution<int> dist(0, 1000000);
    return dist(gen);
}

std::vector<std::size_t> generate_positions(std::size_t n, std::size_t trials) {
    std::vector<std::size_t> positions;
    positions.reserve(trials);

    std::mt19937 gen(42);
    std::uniform_int_distribution<std::size_t> dist(0, n - 1);

    for (std::size_t i = 0; i < trials; ++i) {
        positions.push_back(dist(gen));
    }

    return positions;
}

double test_vector(std::size_t n, std::size_t trials) {
    std::mt19937 gen(42);

    std::vector<int> v;
    v.reserve(n + 1);

    for (std::size_t i = 0; i < n; ++i) {
        v.push_back(getRandom(gen));
    }

    std::vector<std::size_t> positions = generate_positions(n, trials);

    double total_microseconds = 0.0;

    for (std::size_t pos : positions) {
        auto start = std::chrono::steady_clock::now();

        v.insert(v.begin() + pos, 999);


        auto end = std::chrono::steady_clock::now();
        total_microseconds += std::chrono::duration<double, std::micro>(end - start).count();

        v.erase(v.begin() + pos);
    }

    return total_microseconds / trials;
}
 
double test_subvector(std::size_t n, std::size_t trials) {
    std::mt19937 gen(42);

    Subvector v;
    v.reserve(n + 1);

    for (std::size_t i = 0; i < n; ++i) {
        v.push_back(getRandom(gen));
    }

    std::vector<std::size_t> positions = generate_positions(n, trials);

    double total_microseconds = 0.0;

    for (std::size_t pos : positions) {
        auto start = std::chrono::steady_clock::now();

        v.insert(pos, 999);

        auto end = std::chrono::steady_clock::now();
        total_microseconds += std::chrono::duration<double, std::micro>(end - start).count();

        v.erase(pos);
    }

    return total_microseconds / trials;
}

void write_csv(const std::string& filename,
               const std::vector<std::size_t>& sizes,
               const std::vector<double>& vec_times,
               const std::vector<double>& subvec_times) {
    std::ofstream out(filename);
    out << "size,vector,subvector\n";

    for (std::size_t i = 0; i < sizes.size(); ++i) {
        out << sizes[i] << "," << vec_times[i] << "," << subvec_times[i] << "\n";
    }
}

int main() {
    std::vector<std::size_t> sizes;
    std::vector<double> vec_times;
    std::vector<double> subvec_times;

    for (std::size_t n = 1000; n <= 2000000; n *= 1.2) {
        sizes.push_back(n);
    }

    const std::size_t trials = 1000;

    for (std::size_t n : sizes) {
        std::cout << "n = " << n << std::endl;
        vec_times.push_back(test_vector(n, trials));
        subvec_times.push_back(test_subvector(n, trials));
    }

    write_csv("insert_benchmark.csv", sizes, vec_times, subvec_times);

    std::cout << "Done!\n";
    return 0;
}