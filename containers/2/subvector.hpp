#pragma once

#include <cstddef>

#include <cstddef>

class Subvector {
private:
    int* data;
    std::size_t top;
    std::size_t capacity;

    void resize(std::size_t new_capacity);

public:
    Subvector();
    ~Subvector();

    void push_back(int value);
    int pop_back();

    void reserve(std::size_t new_capacity);
    void erase(std::size_t pos);

    void insert(std::size_t pos, int value);

    std::size_t size() const;
};