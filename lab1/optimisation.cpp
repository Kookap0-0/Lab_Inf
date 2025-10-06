#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>

constexpr int MAX_SIZE = 100000;
constexpr int NUM_ARRAYS = 1;

int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

// O(n^2) Algorithms
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void copy_array(int source[], int destination[], int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

// Function to measure average time
long long measure_average_time(void (*sort_func)(int[], int), int test_arrays[][MAX_SIZE], int n, int num_arrays) {
    long long total_time = 0;
    int copy_arr[MAX_SIZE];
    
    for (int a = 0; a < num_arrays; a++) {
        copy_array(test_arrays[a], copy_arr, n);
        
        auto start = std::chrono::high_resolution_clock::now();
        sort_func(copy_arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        
        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    
    return total_time / num_arrays;
}

int main() {
    std::ofstream csv_file("bubble_optimisationO0.csv", std::ios::out);
    csv_file << "algorithm,array_size,time_ns" << std::endl;

    int test_arrays[NUM_ARRAYS][MAX_SIZE];
    
    int sizes[] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
    int num_sizes = 10;
    
    std::cout << "Starting sorting tests..." << std::endl;
    
    // Array of sorting algorithms to test
    struct Algorithm {
        std::string name;
        void (*function)(int[], int);
    }; 
    Algorithm algorithms[] = {
        {"bubble_sort", bubble_sort}
    };
    int num_algorithms = 1;


    for (int s = 0; s < num_sizes; s++) {
        int current_size = sizes[s];
        for (int a = 0; a < NUM_ARRAYS; a++) {
            for (int i = 0; i < current_size; i++) {
                test_arrays[a][i] = rand_uns(1, 10000);
            }
        }
    }
    for (int s = 0; s < num_sizes; s++) {
        int current_size = sizes[s];
        for (int a = 0; a < NUM_ARRAYS; a++) {
            for (int i = 0; i < current_size; i++) {
                test_arrays[a][i] = rand_uns(1, 10000);
            }
        }
        
        std::cout << "Testing size " << current_size << ":" << std::endl;
        
        
        for (int a = 0; a < num_algorithms; a++) {
            long long avg_time = measure_average_time(algorithms[a].function, test_arrays, current_size, NUM_ARRAYS);
            csv_file << algorithms[a].name << "," << current_size << "," << avg_time << std::endl;
            std::cout << "  " << algorithms[a].name << ": " << avg_time << " ns" << std::endl;
        }
        
        std::cout << "---" << std::endl;
    }
    
    csv_file.close();
    std::cout << "All results saved to sorting_times.csv" << std::endl;
    
    return 0;
}