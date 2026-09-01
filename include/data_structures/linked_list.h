// Singly linked list.
// append:          O(n) -- walks to the tail (no tail pointer kept, to
//                  keep reverse() and cycle detection the interesting
//                  parts rather than the append bookkeeping).
// reverse:         O(n) time, O(1) space -- iterative pointer rewiring.
// has_cycle:       O(n) time, O(1) space -- Floyd's cycle detection
//                  (slow/fast pointers), not a visited-set.
#pragma once

#include <stdexcept>

template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList() : head_(nullptr), size_(0) {}
    ~SinglyLinkedList() { clear(); }

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    std::size_t size() const { return size_; }
    bool empty() const { return head_ == nullptr; }

    void append(const T& value) {
        Node* node = new Node{value, nullptr};
        if (!head_) {
            head_ = node;
        } else {
            Node* cur = head_;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
        ++size_;
    }

    T& at(std::size_t index) {
        Node* cur = head_;
        for (std::size_t i = 0; i < index; ++i) {
            if (!cur) throw std::out_of_range("index out of range");
            cur = cur->next;
        }
        if (!cur) throw std::out_of_range("index out of range");
        return cur->value;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head_ = prev;
    }

    // Introduces a cycle for testing: the tail's next pointer is made to
    // point back to the node at `to_index`. Test-only helper -- a real
    // linked list wouldn't expose this.
    void introduce_cycle_for_testing(std::size_t to_index) {
        if (!head_) return;
        Node* target = head_;
        for (std::size_t i = 0; i < to_index && target; ++i) target = target->next;
        Node* tail = head_;
        while (tail->next) tail = tail->next;
        tail->next = target;
    }

    bool has_cycle() const {
        Node* slow = head_;
        Node* fast = head_;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

private:
    struct Node {
        T value;
        Node* next;
    };

    void clear() {
        // Only safe to walk-and-delete when there's no cycle; tests that
        // introduce a cycle don't rely on destruction afterward.
        Node* cur = head_;
        std::size_t guard = 0;
        while (cur && guard <= size_) {
            Node* next = cur->next;
            delete cur;
            cur = next;
            ++guard;
        }
        head_ = nullptr;
    }

    Node* head_;
    std::size_t size_;
};
