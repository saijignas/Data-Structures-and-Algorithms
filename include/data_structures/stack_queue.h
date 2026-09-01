// Stack and Queue, each backed by a linked list of nodes (not
// std::deque). Also a Queue built entirely out of two Stacks, to make
// the classic "amortized O(1) even though a single dequeue can be O(n)"
// argument an explicit, tested behavior.
#pragma once

#include <stdexcept>

template <typename T>
class Stack {
public:
    Stack() : top_(nullptr), size_(0) {}
    ~Stack() { while (!empty()) pop(); }
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    bool empty() const { return top_ == nullptr; }
    std::size_t size() const { return size_; }

    void push(const T& value) {
        top_ = new Node{value, top_};
        ++size_;
    }

    T pop() {
        if (empty()) throw std::out_of_range("pop from empty stack");
        Node* node = top_;
        T value = node->value;
        top_ = node->next;
        delete node;
        --size_;
        return value;
    }

    T& peek() {
        if (empty()) throw std::out_of_range("peek on empty stack");
        return top_->value;
    }

private:
    struct Node {
        T value;
        Node* next;
    };
    Node* top_;
    std::size_t size_;
};

template <typename T>
class Queue {
public:
    Queue() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~Queue() { while (!empty()) dequeue(); }
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    bool empty() const { return head_ == nullptr; }
    std::size_t size() const { return size_; }

    void enqueue(const T& value) {
        Node* node = new Node{value, nullptr};
        if (!head_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    T dequeue() {
        if (empty()) throw std::out_of_range("dequeue from empty queue");
        Node* node = head_;
        T value = node->value;
        head_ = node->next;
        if (!head_) tail_ = nullptr;
        delete node;
        --size_;
        return value;
    }

private:
    struct Node {
        T value;
        Node* next;
    };
    Node* head_;
    Node* tail_;
    std::size_t size_;
};

// Queue implemented with two stacks: enqueue pushes onto `in_`; dequeue
// pops from `out_`, refilling `out_` from `in_` (reversing order) only
// when `out_` runs dry. A single dequeue can be O(n) when it triggers a
// refill, but each element is moved between stacks at most once, so the
// amortized cost per operation is still O(1).
template <typename T>
class QueueFromStacks {
public:
    void enqueue(const T& value) { in_.push(value); }

    T dequeue() {
        if (out_.empty()) {
            while (!in_.empty()) out_.push(in_.pop());
        }
        return out_.pop();
    }

    bool empty() const { return in_.empty() && out_.empty(); }
    std::size_t size() const { return in_.size() + out_.size(); }

private:
    Stack<T> in_;
    Stack<T> out_;
};
