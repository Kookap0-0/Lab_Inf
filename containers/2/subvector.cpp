#include "subvector.hpp"

Subvector::Subvector() : data(nullptr), top(0), capacity(0) {}

Subvector::~Subvector() {
    delete[] data;
}

void Subvector::resize(std::size_t new_capacity) {
    if (new_capacity == 0) {
        delete[] data;
        data = nullptr;
        top = 0;
        capacity = 0;
        return;
    }

    int* new_data = new int[new_capacity];

    std::size_t limit = (top < new_capacity) ? top : new_capacity;
    for (std::size_t i = 0; i < limit; ++i) {
        new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
    capacity = new_capacity;
    top = limit;
}

void Subvector::push_back(int value) {
    if (top == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);;
    }
    data[top] = value;
    ++top;
}

int Subvector::pop_back() {
    if (top == 0) {
        return 0;
    }
    --top;
    return data[top];
}

void Subvector::insert(std::size_t pos, int value) {
    if (pos > top) {
        return;
    }

    if (top == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);;
    }

    for (std::size_t i = top; i > pos; --i) {
        data[i] = data[i - 1];
    }

    data[pos] = value;
    ++top;
}

std::size_t Subvector::size() const {
    return top;
}

void Subvector::reserve(std::size_t new_capacity) {
    if (new_capacity > capacity) {
        resize(new_capacity);
    }
}

void Subvector::erase(std::size_t pos) {
    if (pos >= top) {
        return;
    }

    for (std::size_t i = pos; i + 1 < top; ++i) {
        data[i] = data[i + 1];
    }

    --top;
}