#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>

// Структура для хранения одной точки измерения
struct DataPoint {
    size_t iteration;
    size_t size;
    size_t capacity;
};

// Генерация случайного числа
int getRandomNumber(std::mt19937& gen) {
    static std::uniform_int_distribution<int> dist(0, 1000000);
    return dist(gen);
}

// Запись в CSV
void writeToCSV(const std::string& filename, const std::vector<DataPoint>& data) {
    std::ofstream out(filename);

    out << "i,size,capacity\n";

    for (const auto& point : data) {
        out << point.iteration << ","
            << point.size << ","
            << point.capacity << "\n";
    }
}

// Эксперимент: push_back для vector
std::vector<DataPoint> runVectorPushBackExperiment(size_t maxElements) {
    std::vector<DataPoint> results;

    std::vector<int> v;
    std::mt19937 gen(42);

    size_t lastCapacity = v.capacity();

    for (size_t i = 0; i < maxElements; ++i) {
        v.push_back(getRandomNumber(gen));

        // записываем ТОЛЬКО если capacity изменился
        if (i % 1000 == 0 || v.capacity() != lastCapacity) {
            results.push_back({
                i,
                v.size(),
                v.capacity()
            });

            lastCapacity = v.capacity();
        }
    }

    return results;
}


int main() {
    const size_t maxBytes = 10ull * 1024 * 1024; // ~10MB
    const size_t maxElements = maxBytes / sizeof(int);

    auto data = runVectorPushBackExperiment(maxElements);

    writeToCSV("vector_push_back.csv", data);

    std::cout << "Done!\n";
    return 0;
}