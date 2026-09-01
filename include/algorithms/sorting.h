// merge_sort: O(n log n), stable (equal elements keep their relative
//             order -- the merge step always takes from the left half
//             on ties).
// quicksort:  O(n log n) average, O(n^2) worst case. Uses a randomized
//             pivot to make the worst case vanishingly unlikely rather
//             than eliminating it structurally. Not in-place -- builds
//             a new vector per partition, trading memory for clarity
//             (an in-place version with the same pivot strategy is a
//             reasonable follow-up, not a correctness issue with this
//             one).
#pragma once

#include <random>
#include <vector>

template <typename T>
std::vector<T> merge_sort(const std::vector<T>& input) {
    if (input.size() <= 1) return input;
    std::size_t mid = input.size() / 2;
    std::vector<T> left(input.begin(), input.begin() + mid);
    std::vector<T> right(input.begin() + mid, input.end());
    left = merge_sort(left);
    right = merge_sort(right);

    std::vector<T> merged;
    merged.reserve(input.size());
    std::size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i++]);
        } else {
            merged.push_back(right[j++]);
        }
    }
    while (i < left.size()) merged.push_back(left[i++]);
    while (j < right.size()) merged.push_back(right[j++]);
    return merged;
}

template <typename T>
std::vector<T> quicksort(const std::vector<T>& input) {
    if (input.size() <= 1) return input;

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, input.size() - 1);
    T pivot = input[dist(rng)];

    std::vector<T> less, equal, greater;
    for (const auto& item : input) {
        if (item < pivot) less.push_back(item);
        else if (item > pivot) greater.push_back(item);
        else equal.push_back(item);
    }

    std::vector<T> sorted_less = quicksort(less);
    std::vector<T> sorted_greater = quicksort(greater);

    std::vector<T> result;
    result.reserve(input.size());
    result.insert(result.end(), sorted_less.begin(), sorted_less.end());
    result.insert(result.end(), equal.begin(), equal.end());
    result.insert(result.end(), sorted_greater.begin(), sorted_greater.end());
    return result;
}
