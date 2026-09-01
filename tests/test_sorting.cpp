#include <algorithm>
#include <random>
#include <vector>

#include "../include/algorithms/sorting.h"
#include "../include/test_framework.h"

TEST_CASE("merge_sort: sorts an unsorted vector") {
    std::vector<int> input = {5, 3, 8, 1, 9, 2};
    std::vector<int> expected = {1, 2, 3, 5, 8, 9};
    CHECK(merge_sort(input) == expected);
}

TEST_CASE("merge_sort: empty and single-element inputs") {
    CHECK(merge_sort(std::vector<int>{}).empty());
    CHECK(merge_sort(std::vector<int>{42}) == std::vector<int>{42});
}

namespace {
// A type whose ordering depends only on `key`, so a stability test can
// tell apart "sorted correctly" from "happened to also end up in the
// right order" -- comparing by the whole struct (key + original_index)
// the way the pair-of-ints version of this test accidentally did would
// pass even for an unstable sort whenever the input's tie-break order
// already matched index order, which defeats the point of the test.
struct KeyedValue {
    int key;
    int original_index;
    bool operator<(const KeyedValue& other) const { return key < other.key; }
    bool operator<=(const KeyedValue& other) const { return key <= other.key; }
};
}  // namespace

TEST_CASE("merge_sort: is stable -- equal keys keep relative input order") {
    // Deliberately out of index order within the key==1 group (3 before 1
    // before 0) -- an unstable sort has no reason to preserve this,
    // while a stable one always will.
    std::vector<KeyedValue> input = {{1, 3}, {0, 4}, {1, 1}, {1, 0}};
    auto sorted = merge_sort(input);

    std::vector<int> key1_indices;
    for (const auto& kv : sorted) {
        if (kv.key == 1) key1_indices.push_back(kv.original_index);
    }
    std::vector<int> expected_order = {3, 1, 0};  // same order they appeared in the input
    CHECK(key1_indices == expected_order);
}

TEST_CASE("quicksort: sorts an unsorted vector") {
    std::vector<int> input = {5, 3, 8, 1, 9, 2};
    std::vector<int> expected = {1, 2, 3, 5, 8, 9};
    CHECK(quicksort(input) == expected);
}

TEST_CASE("quicksort: empty and single-element inputs") {
    CHECK(quicksort(std::vector<int>{}).empty());
    CHECK(quicksort(std::vector<int>{42}) == std::vector<int>{42});
}

TEST_CASE("quicksort: handles duplicate values correctly") {
    std::vector<int> input = {4, 2, 4, 1, 2, 4};
    std::vector<int> expected = {1, 2, 2, 4, 4, 4};
    CHECK(quicksort(input) == expected);
}

TEST_CASE("sorting: randomized stress test against std::sort as the oracle") {
    std::mt19937 rng(54321);  // fixed seed: reproducible, not flaky
    for (int trial = 0; trial < 50; ++trial) {
        std::uniform_int_distribution<int> size_dist(0, 200);
        std::uniform_int_distribution<int> value_dist(-1000, 1000);
        int n = size_dist(rng);

        std::vector<int> values;
        for (int i = 0; i < n; ++i) values.push_back(value_dist(rng));

        std::vector<int> expected = values;
        std::sort(expected.begin(), expected.end());

        CHECK(merge_sort(values) == expected);
        CHECK(quicksort(values) == expected);
    }
}
