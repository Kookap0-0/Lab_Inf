#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <set>
#include <random>
#include <chrono>
#include <fstream>

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

template <typename Container, typename Func>
double benchmark_traverse(const Container& container, std::size_t trials, Func operation) {
    double total_ns = 0.0;
    volatile long long sink = 0;

    for (std::size_t t = 0; t < trials; ++t) {
        auto start = Clock::now();
        for (const auto& x : container) {operation(x, sink);}
        auto end = Clock::now();

        total_ns += std::chrono::duration<double, std::nano>(end - start).count();
    }

    // защита от оптимизации
    if (sink == -1) {std::cout << "";}

    return total_ns/trials;
}

void write_csv(const std::string& filename,
               const std::vector<std::size_t>& sizes,
               const std::vector<double>& vector_times,
               const std::vector<double>& forward_list_times,
               const std::vector<double>& list_times,
               const std::vector<double>& map_times,
               const std::vector<double>& set_times) {
    std::ofstream out(filename);
    out << "size,vector,forward_list,list,map,set\n";

    for (std::size_t i = 0; i < sizes.size(); ++i) {
        out << sizes[i] << ","
            << vector_times[i] << ","
            << forward_list_times[i] << ","
            << list_times[i] << ","
            << map_times[i] << ","
            << set_times[i] << "\n";
    }
}

int main() {
    std::vector<std::size_t> sizes;
    for (std::size_t n = 1000; n <= 200000; n *= 1.4) {
        sizes.push_back(n);
    }

    const std::size_t trials = 1000;

    std::vector<double> vector_times;
    std::vector<double> forward_list_times;
    std::vector<double> list_times;
    std::vector<double> map_times;
    std::vector<double> set_times;

    for (std::size_t n : sizes) {
        std::cout << "n = " << n << std::endl;

        auto values = generate_values(n, 42);
        std::vector<int> vec = values;
        vector_times.push_back(
            benchmark_traverse(vec, trials, [](const auto& x, volatile long long& sink) {sink += x;})
        );

        std::forward_list<int> flst;
        for (auto it = values.rbegin(); it != values.rend(); ++it) {flst.push_front(*it);}
        forward_list_times.push_back(
            benchmark_traverse(flst, trials, [](const auto& x, volatile long long& sink) {sink += x;})
        );

        std::list<int> lst;
        for (int x : values) {lst.push_back(x);}
        list_times.push_back(
            benchmark_traverse(lst, trials, [](const auto& x, volatile long long& sink) {sink += x;})
        );

        std::map<int, int> m;
        for (int x : values) {m.insert({x, x});}
        map_times.push_back(
            benchmark_traverse(m, trials, [](const auto& x, volatile long long& sink) {sink += x.first + x.second;})
        );

        std::set<int> s;
        for (int x : values) {s.insert(x);}
        set_times.push_back(
            benchmark_traverse(s, trials, [](const auto& x, volatile long long& sink) {sink += x;})
        );
    }

    write_csv("traverse_benchmark.csv",
              sizes,
              vector_times,
              forward_list_times,
              list_times,
              map_times,
              set_times);

    std::cout << "Done!\n";
    return 0;
}