// Dynamic array built from a raw fixed-size buffer, not std::vector.
// append:        O(1) amortized -- doubles capacity when full, so the
//                total cost of n appends is O(n), not O(n^2).
// insert/delete: O(n) -- shifts every element after the target index.
// get/set:       O(1) -- direct index into the buffer.
#pragma once

#include <algorithm>
#include <stdexcept>

template <typename T>
class DynamicArray {
public:
    DynamicArray() : size_(0), capacity_(4), data_(new T[capacity_]) {}
    ~DynamicArray() { delete[] data_; }

    DynamicArray(const DynamicArray& other) : size_(other.size_), capacity_(other.capacity_),
                                               data_(new T[capacity_]) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        T* new_data = new T[other.capacity_];
        std::copy(other.data_, other.data_ + other.size_, new_data);
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    void append(const T& value) {
        if (size_ == capacity_) grow();
        data_[size_++] = value;
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) throw std::out_of_range("insert index out of range");
        if (size_ == capacity_) grow();
        for (std::size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++size_;
    }

    void remove_at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("remove index out of range");
        for (std::size_t i = index; i + 1 < size_; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    T& get(std::size_t index) {
        if (index >= size_) throw std::out_of_range("get index out of range");
        return data_[index];
    }

    const T& get(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("get index out of range");
        return data_[index];
    }

    void set(std::size_t index, const T& value) {
        if (index >= size_) throw std::out_of_range("set index out of range");
        data_[index] = value;
    }

    std::size_t capacity() const { return capacity_; }

private:
    void grow() {
        capacity_ *= 2;
        T* new_data = new T[capacity_];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
    }

    std::size_t size_;
    std::size_t capacity_;
    T* data_;
};
