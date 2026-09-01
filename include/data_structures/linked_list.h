// Singly linked list.
// append:          O(n) -- walks to the tail (no tail pointer kept, to
//                  keep reverse() and cycle detection the interesting
//                  parts rather than the append bookkeeping).
// reverse:         O(n) time, O(1) space -- iterative pointer rewiring.
// has_cycle:       O(n) time, O(1) space -- Floyd's cycle detection
//                  (slow/fast pointers), not a visited-set.
#pragma once

#include <stdexcept>
#include <unordered_set>
#include <vector>

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
        // Bounding the walk by size_ does NOT make this cycle-safe: a
        // short cycle revisits an already-freed node well within that
        // bound, which is a double-free. (Found by CI on a Linux glibc
        // runner, which aborts on double-free; the old MinGW/Windows CRT
        // allocator used for local testing silently tolerated it instead
        // -- a real lesson in not trusting one platform's allocator to
        // catch memory bugs.) Tracking visited addresses and stopping the
        // moment a node would be revisited is correct for any cycle
        // shape (self-loop, tail-to-head, tail-to-middle), and collecting
        // every node before deleting any of them means the traversal
        // itself never dereferences freed memory either.
        std::unordered_set<Node*> seen;
        std::vector<Node*> to_delete;
        Node* cur = head_;
        while (cur && seen.find(cur) == seen.end()) {
            seen.insert(cur);
            to_delete.push_back(cur);
            cur = cur->next;
        }
        for (Node* n : to_delete) delete n;
        head_ = nullptr;
    }

    Node* head_;
    std::size_t size_;
};
