#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>

constexpr int MAX_SIZE = 50000;

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
void bubble_sort_reverse(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_index = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}

// O(n log n) Algorithms

// MERGE SORT (using fixed-size temporary array)
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    
    // Copy back from temp to original array
    for (int x = left; x <= right; x++) {
        arr[x] = temp[x];
    }
}
void merge_sort_helper(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(arr, temp, left, mid);
        merge_sort_helper(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
    }
}
void merge_sort(int arr[], int n) {
    int temp[MAX_SIZE];  // Fixed-size temporary array
    merge_sort_helper(arr, temp, 0, n - 1);
}

// QUICK SORT (no dynamic arrays needed)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}
void quick_sort_helper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}
void quick_sort(int arr[], int n) {
    quick_sort_helper(arr, 0, n - 1);
}

// HEAP SORT (no dynamic arrays needed)
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}
void heap_sort(int arr[], int n) {
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}


void copy_array(int source[], int destination[], int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

// Function to measure average time
long long measure_average_time(void (*sort_func)(int[], int), int test_array[], int n, int repetitions) {
    long long total_time = 0;
    int copy_arr[MAX_SIZE];  // Fixed-size copy array
    
    for (int r = 0; r < repetitions; r++) {
        copy_array(test_array, copy_arr, n);
        auto start = std::chrono::high_resolution_clock::now();
        sort_func(copy_arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    } 
    return total_time / repetitions;
}

int main() {
    std::ofstream csv_file("dependence_on_initial_data.csv", std::ios::out);
    csv_file << "algorithm,initial_data,array_size,time_ns" << std::endl;

    int test_array1[MAX_SIZE];
    int test_array2[MAX_SIZE];
    int test_array3[MAX_SIZE];
    int repetitions = 1;
    
    int sizes[] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,12000,13000,14000,15000};
    int num_sizes = 15;
    
    std::cout << "Starting sorting tests..." << std::endl;
    
    // Array of sorting algorithms to test
    struct Algorithm {
        std::string name;
        void (*function)(int[], int);
    }; 
    Algorithm algorithms[] = {
        {"bubble_sort", bubble_sort},
        {"insertion_sort", insertion_sort},
        {"selection_sort", selection_sort},
        {"merge_sort", merge_sort},
        {"quick_sort", quick_sort},
        {"heap_sort", heap_sort}
    };
    int num_algorithms = 6;
    
    // Test each array size
    for (int s = 0; s < num_sizes; s++) {
        int current_size = sizes[s];
        
        // Fill arrays
        for (int i = 0; i < current_size; i++) {
            int temp = rand_uns(1, 10000);
            test_array1[i] = temp;
            test_array2[i] = temp;
            test_array3[i] = temp;
        }
        heap_sort(test_array1, current_size);
        bubble_sort_reverse(test_array3, current_size);
        std::cout << "Testing size " << current_size << ":" << std::endl;
        
        // Test each algorithm
        for (int a = 0; a < num_algorithms; a++) {
            long long avg_time1 = measure_average_time(algorithms[a].function, test_array1, current_size, repetitions);
            csv_file << algorithms[a].name << "," <<"best"<<","<< current_size << "," << avg_time1 << std::endl;
            std::cout << "  " << algorithms[a].name << ": " << avg_time1 << " ns" << std::endl;

            long long avg_time2 = measure_average_time(algorithms[a].function, test_array2, current_size, repetitions);
            csv_file << algorithms[a].name << "," <<"average"<<","<< current_size << "," << avg_time2 << std::endl;
            std::cout << "  " << algorithms[a].name << ": " << avg_time2 << " ns" << std::endl;
            
            long long avg_time3 = measure_average_time(algorithms[a].function, test_array3, current_size, repetitions);
            csv_file << algorithms[a].name << "," <<"worst"<<","<< current_size << "," << avg_time3 << std::endl;
            std::cout << "  " << algorithms[a].name << ": " << avg_time3 << " ns" << std::endl;
        }
        
        std::cout << "---" << std::endl;
    }
    
    csv_file.close();
    std::cout << "All results saved to sorting_times.csv" << std::endl;
    
    return 0;
}