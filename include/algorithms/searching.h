// Binary search, iterative and recursive -- both O(log n), on a sorted
// input. Returns the index of `target`, or -1 if not present.
#pragma once

#include <vector>

template <typename T>
int binary_search_iterative(const std::vector<T>& sorted, const T& target) {
    int lo = 0;
    int hi = static_cast<int>(sorted.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (sorted[mid] == target) return mid;
        if (sorted[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

template <typename T>
int binary_search_recursive_impl(const std::vector<T>& sorted, const T& target, int lo, int hi) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (sorted[mid] == target) return mid;
    if (sorted[mid] < target) return binary_search_recursive_impl(sorted, target, mid + 1, hi);
    return binary_search_recursive_impl(sorted, target, lo, mid - 1);
}

template <typename T>
int binary_search_recursive(const std::vector<T>& sorted, const T& target) {
    return binary_search_recursive_impl(sorted, target, 0, static_cast<int>(sorted.size()) - 1);
}
