#include <vector>

#include "../include/algorithms/searching.h"
#include "../include/test_framework.h"

TEST_CASE("binary_search_iterative: finds present values at correct index") {
    std::vector<int> sorted = {1, 3, 5, 7, 9, 11};
    CHECK(binary_search_iterative(sorted, 1) == 0);
    CHECK(binary_search_iterative(sorted, 7) == 3);
    CHECK(binary_search_iterative(sorted, 11) == 5);
}

TEST_CASE("binary_search_iterative: returns -1 for a missing value") {
    std::vector<int> sorted = {1, 3, 5, 7, 9};
    CHECK(binary_search_iterative(sorted, 4) == -1);
    CHECK(binary_search_iterative(sorted, 0) == -1);
    CHECK(binary_search_iterative(sorted, 100) == -1);
}

TEST_CASE("binary_search_iterative: empty input always returns -1") {
    std::vector<int> empty;
    CHECK(binary_search_iterative(empty, 5) == -1);
}

TEST_CASE("binary_search_recursive: finds present values at correct index") {
    std::vector<int> sorted = {1, 3, 5, 7, 9, 11};
    CHECK(binary_search_recursive(sorted, 1) == 0);
    CHECK(binary_search_recursive(sorted, 7) == 3);
    CHECK(binary_search_recursive(sorted, 11) == 5);
}

TEST_CASE("binary_search_recursive: returns -1 for a missing value") {
    std::vector<int> sorted = {1, 3, 5, 7, 9};
    CHECK(binary_search_recursive(sorted, 4) == -1);
}

TEST_CASE("binary_search_recursive: empty input always returns -1") {
    std::vector<int> empty;
    CHECK(binary_search_recursive(empty, 5) == -1);
}

TEST_CASE("binary_search: single-element input, present and absent") {
    std::vector<int> single = {42};
    CHECK(binary_search_iterative(single, 42) == 0);
    CHECK(binary_search_iterative(single, 1) == -1);
    CHECK(binary_search_recursive(single, 42) == 0);
    CHECK(binary_search_recursive(single, 1) == -1);
}
