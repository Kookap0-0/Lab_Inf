#pragma once

#include <cstddef>

class SubforwardList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value, Node* next_node = nullptr)
            : data(value), next(next_node) {}
    };

    Node* head_;
    std::size_t size_;

    Node* node_at(std::size_t index) const;

public:
    SubforwardList();
    ~SubforwardList();

    SubforwardList(const SubforwardList&) = delete;
    SubforwardList& operator=(const SubforwardList&) = delete;

    void push_front(int value);
    int pop_front();

    void push_back(int value);
    int pop_back();

    bool push_where(std::size_t where, int value);
    int erase_where(std::size_t where);

    void clear();
    std::size_t size() const;
    bool empty() const;
};