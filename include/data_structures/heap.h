// Binary min-heap on top of a plain vector (array-backed, not
// std::priority_queue). push/pop_min are each O(log n): a new element
// bubbles up at most height-of-tree swaps; removing the root pulls the
// last element to the top and sifts it down the same distance.
#pragma once

#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class MinHeap {
public:
    std::size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }

    void push(const T& value) {
        data_.push_back(value);
        sift_up(data_.size() - 1);
    }

    const T& peek_min() const {
        if (empty()) throw std::out_of_range("peek_min on empty heap");
        return data_[0];
    }

    T pop_min() {
        if (empty()) throw std::out_of_range("pop_min on empty heap");
        T min_value = data_[0];
        data_[0] = data_.back();
        data_.pop_back();
        if (!data_.empty()) sift_down(0);
        return min_value;
    }

private:
    void sift_up(std::size_t idx) {
        while (idx > 0) {
            std::size_t parent = (idx - 1) / 2;
            if (data_[idx] < data_[parent]) {
                std::swap(data_[idx], data_[parent]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    void sift_down(std::size_t idx) {
        std::size_t n = data_.size();
        while (true) {
            std::size_t left = 2 * idx + 1;
            std::size_t right = 2 * idx + 2;
            std::size_t smallest = idx;
            if (left < n && data_[left] < data_[smallest]) smallest = left;
            if (right < n && data_[right] < data_[smallest]) smallest = right;
            if (smallest == idx) break;
            std::swap(data_[idx], data_[smallest]);
            idx = smallest;
        }
    }

    std::vector<T> data_;
};
