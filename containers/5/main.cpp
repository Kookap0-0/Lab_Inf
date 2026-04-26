#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <chrono>
#include <fstream>

using Clock = std::chrono::steady_clock;

std::vector<int> generate_values(std::size_t count, unsigned seed) {
    std::vector<int> values;
    values.reserve(count);

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 1000000000);

    for (std::size_t i = 0; i < count; ++i) {
        values.push_back(dist(gen));
    }

    return values;
}

double benchmark_set_insert(std::size_t n, const std::vector<int>& trial_values) {
    std::set<int> s;
    std::vector<int> initial_values = generate_values(n, 42);

    for (int x : initial_values) {
        s.insert(x);
    }

    double total_ns = 0.0;

    for (int x : trial_values) {
        auto start = Clock::now();
        auto it = s.insert(x);
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();

        if (it.second) {
            s.erase(it.first);
        }
    }

    return total_ns / trial_values.size();
}

double benchmark_map_insert(std::size_t n, const std::vector<int>& trial_values) {
    std::map<int, int> m;
    std::vector<int> initial_values = generate_values(n, 42);

    for (int x : initial_values) {
        m.insert({x, x});
    }

    double total_ns = 0.0;

    for (int x : trial_values) {
        auto start = Clock::now();
        auto it = m.insert({x, x});
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();

        if (it.second) {
            m.erase(it.first);
        }
    }

    return total_ns / trial_values.size();
}

double benchmark_multiset_insert(std::size_t n, const std::vector<int>& trial_values) {
    std::multiset<int> ms;
    std::vector<int> initial_values = generate_values(n, 42);

    for (int x : initial_values) {
        ms.insert(x);
    }

    double total_ns = 0.0;

    for (int x : trial_values) {
        auto start = Clock::now();
        auto it = ms.insert(x);
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();

        ms.erase(it);
    }

    return total_ns / trial_values.size();
}

double benchmark_multimap_insert(std::size_t n, const std::vector<int>& trial_values) {
    std::multimap<int, int> mm;
    std::vector<int> initial_values = generate_values(n, 42);

    for (int x : initial_values) {
        mm.insert({x, x});
    }

    double total_ns = 0.0;

    for (int x : trial_values) {
        auto start = Clock::now();
        auto it = mm.insert({x, x});
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();

        mm.erase(it);
    }

    return total_ns / trial_values.size();
}

void write_csv(const std::string& filename,
               const std::vector<std::size_t>& sizes,
               const std::vector<double>& set_times,
               const std::vector<double>& map_times,
               const std::vector<double>& multiset_times,
               const std::vector<double>& multimap_times) {
    std::ofstream out(filename);
    out << "size,set,map,multiset,multimap\n";

    for (std::size_t i = 0; i < sizes.size(); ++i) {
        out << sizes[i] << ","
            << set_times[i] << ","
            << map_times[i] << ","
            << multiset_times[i] << ","
            << multimap_times[i] << "\n";
    }
}

int main() {
    std::vector<std::size_t> sizes;
    for (std::size_t n = 1000; n <= 200000; n *= 1.4) {
        sizes.push_back(n);
    }

    const std::size_t trials = 100000;
    std::vector<int> trial_values = generate_values(trials, 42);

    std::vector<double> set_times;
    std::vector<double> map_times;
    std::vector<double> multiset_times;
    std::vector<double> multimap_times;

    for (std::size_t n : sizes) {
        std::cout << "n = " << n << std::endl;

        set_times.push_back(benchmark_set_insert(n, trial_values));
        map_times.push_back(benchmark_map_insert(n, trial_values));
        multiset_times.push_back(benchmark_multiset_insert(n, trial_values));
        multimap_times.push_back(benchmark_multimap_insert(n, trial_values));
    }

    write_csv("insert_benchmark.csv",
              sizes,
              set_times,
              map_times,
              multiset_times,
              multimap_times);

    std::cout << "Done!\n";
    return 0;
}