#include "subforward_list.hpp"

SubforwardList::SubforwardList() : head_(nullptr), size_(0) {}

SubforwardList::~SubforwardList() {
    clear();
}

SubforwardList::Node* SubforwardList::node_at(std::size_t index) const {
    Node* cur = head_;
    while (cur && index > 0) {
        cur = cur->next;
        --index;
    }
    return cur;
}

void SubforwardList::push_front(int value) {
    head_ = new Node(value, head_);
    ++size_;
}

int SubforwardList::pop_front() {
    if (head_ == nullptr) {
        return 0;
    }

    Node* old = head_;
    int value = old->data;
    head_ = old->next;
    delete old;
    --size_;
    return value;
}

void SubforwardList::push_back(int value) {
    if (head_ == nullptr) {
        push_front(value);
        return;
    }

    Node* cur = head_;
    while (cur->next != nullptr) {
        cur = cur->next;
    }

    cur->next = new Node(value);
    ++size_;
}

int SubforwardList::pop_back() {
    if (head_ == nullptr) {
        return 0;
    }

    if (head_->next == nullptr) {
        int value = head_->data;
        delete head_;
        head_ = nullptr;
        size_ = 0;
        return value;
    }

    Node* cur = head_;
    while (cur->next->next != nullptr) {
        cur = cur->next;
    }

    int value = cur->next->data;
    delete cur->next;
    cur->next = nullptr;
    --size_;
    return value;
}

bool SubforwardList::push_where(std::size_t where, int value) {
    if (where == 0) {
        push_front(value);
        return true;
    }

    if (where > size_) {
        return false;
    }

    Node* prev = node_at(where - 1);
    if (prev == nullptr) {
        return false;
    }

    prev->next = new Node(value, prev->next);
    ++size_;
    return true;
}

int SubforwardList::erase_where(std::size_t where) {
    if (head_ == nullptr || where >= size_) {
        return 0;
    }

    if (where == 0) {
        return pop_front();
    }

    Node* prev = node_at(where - 1);
    if (prev == nullptr || prev->next == nullptr) {
        return 0;
    }

    Node* victim = prev->next;
    int value = victim->data;
    prev->next = victim->next;
    delete victim;
    --size_;
    return value;
}

void SubforwardList::clear() {
    while (head_ != nullptr) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }
    size_ = 0;
}

std::size_t SubforwardList::size() const {
    return size_;
}

bool SubforwardList::empty() const {
    return head_ == nullptr;
}