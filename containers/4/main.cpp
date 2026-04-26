#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <random>
#include <chrono>
#include <fstream>
#include "subforward_list.hpp"

using Clock = std::chrono::steady_clock;

std::vector<int> generate_values(std::size_t count, unsigned seed) {
    std::vector<int> values;
    values.reserve(count);

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 1000000);

    for (std::size_t i = 0; i < count; ++i) {
        values.push_back(dist(gen));
    }

    return values;
}

double benchmark_list_push_front(std::size_t n, const std::vector<int>& trial_values) {
    std::list<int> lst;
    std::vector<int> initial_values = generate_values(n, 42);

    for (int x : initial_values) {
        lst.push_front(x);
    }

    double total_ns = 0.0;

    for (int x : trial_values) {
        lst.push_front(x);
        auto start = Clock::now();
        lst.pop_front();
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();
    }

    return total_ns / trial_values.size();
}

double benchmark_forward_list_push_front(std::size_t n, const std::vector<int>& trial_values) {
    std::forward_list<int> flst;
    std::vector<int> initial_values = generate_values(n, 42);

    for (int x : initial_values) {
        flst.push_front(x);
    }

    double total_ns = 0.0;

    for (int x : trial_values) {
        flst.push_front(x);
        auto start = Clock::now();
        flst.pop_front();
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();
    }

    return total_ns / trial_values.size();
}

double benchmark_subforward_list_push_front(std::size_t n, const std::vector<int>& trial_values) {
    SubforwardList sfl;
    std::vector<int> initial_values = generate_values(n, 42);

    for (int x : initial_values) {
        sfl.push_front(x);
    }

    double total_ns = 0.0;

    for (int x : trial_values) {
        auto start = Clock::now();
        sfl.push_front(x);
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();
        sfl.pop_front();
    }

    return total_ns / trial_values.size();
}

void write_csv(const std::string& filename,
               const std::vector<std::size_t>& sizes,
               const std::vector<double>& list_times,
               const std::vector<double>& forward_list_times,
               const std::vector<double>& subforward_list_times) {
    std::ofstream out(filename);
    out << "size,list,forward_list,subforward_list\n";

    for (std::size_t i = 0; i < sizes.size(); ++i) {
        out << sizes[i] << ","
            << list_times[i] << ","
            << forward_list_times[i] << ","
            << subforward_list_times[i] << "\n";
    }
}

int main() {
    std::vector<std::size_t> sizes;
    for (std::size_t n = 1000; n <= 200000; n *= 1.2) {
        sizes.push_back(n);
    }

    const std::size_t trials = 1000000;
    std::vector<int> trial_values = generate_values(trials, 42);

    std::vector<double> list_times;
    std::vector<double> forward_list_times;
    std::vector<double> subforward_list_times;

    for (std::size_t n : sizes) {
        std::cout << "n = " << n << std::endl;

        list_times.push_back(benchmark_list_push_front(n, trial_values));
        forward_list_times.push_back(benchmark_forward_list_push_front(n, trial_values));
        subforward_list_times.push_back(benchmark_subforward_list_push_front(n, trial_values));
    }

    write_csv("pop_front_benchmark.csv",
              sizes,
              list_times,
              forward_list_times,
              subforward_list_times);

    std::cout << "Done!\n";
    return 0;
}