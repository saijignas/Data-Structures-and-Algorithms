#include <algorithm>
#include <random>
#include <vector>

#include "../include/data_structures/heap.h"
#include "../include/test_framework.h"

TEST_CASE("heap: pop_min always returns the smallest remaining element") {
    MinHeap<int> heap;
    for (int v : {5, 3, 8, 1, 9, 2}) heap.push(v);
    std::vector<int> popped;
    while (!heap.empty()) popped.push_back(heap.pop_min());
    std::vector<int> expected = {1, 2, 3, 5, 8, 9};
    CHECK(popped == expected);
}

TEST_CASE("heap: peek_min does not remove the element") {
    MinHeap<int> heap;
    heap.push(5);
    heap.push(1);
    CHECK(heap.peek_min() == 1);
    CHECK(heap.size() == 2);
}

TEST_CASE("heap: pop_min on empty heap throws") {
    MinHeap<int> heap;
    bool threw = false;
    try {
        heap.pop_min();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    CHECK(threw);
}

TEST_CASE("heap: single element push/pop") {
    MinHeap<int> heap;
    heap.push(42);
    CHECK(heap.pop_min() == 42);
    CHECK(heap.empty());
}

TEST_CASE("heap: randomized stress test against std::sort as the oracle") {
    std::mt19937 rng(12345);  // fixed seed: reproducible, not flaky
    for (int trial = 0; trial < 50; ++trial) {
        std::uniform_int_distribution<int> size_dist(0, 100);
        std::uniform_int_distribution<int> value_dist(-1000, 1000);
        int n = size_dist(rng);

        std::vector<int> values;
        for (int i = 0; i < n; ++i) values.push_back(value_dist(rng));

        MinHeap<int> heap;
        for (int v : values) heap.push(v);

        std::vector<int> popped;
        while (!heap.empty()) popped.push_back(heap.pop_min());

        std::vector<int> expected = values;
        std::sort(expected.begin(), expected.end());

        CHECK(popped == expected);
    }
}
