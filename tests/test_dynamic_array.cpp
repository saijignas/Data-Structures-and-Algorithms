#include "../include/data_structures/dynamic_array.h"
#include "../include/test_framework.h"

TEST_CASE("dynamic array: append and get") {
    DynamicArray<int> arr;
    arr.append(10);
    arr.append(20);
    arr.append(30);
    CHECK(arr.size() == 3);
    CHECK(arr.get(0) == 10);
    CHECK(arr.get(1) == 20);
    CHECK(arr.get(2) == 30);
}

TEST_CASE("dynamic array: append triggers growth past initial capacity") {
    DynamicArray<int> arr;
    std::size_t initial_capacity = arr.capacity();
    for (int i = 0; i < 100; ++i) arr.append(i);
    CHECK(arr.size() == 100);
    CHECK(arr.capacity() > initial_capacity);
    for (int i = 0; i < 100; ++i) CHECK(arr.get(static_cast<std::size_t>(i)) == i);
}

TEST_CASE("dynamic array: insert in the middle shifts later elements") {
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(3);
    arr.insert(1, 2);
    CHECK(arr.size() == 3);
    CHECK(arr.get(0) == 1);
    CHECK(arr.get(1) == 2);
    CHECK(arr.get(2) == 3);
}

TEST_CASE("dynamic array: remove_at shifts later elements left") {
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(2);
    arr.append(3);
    arr.remove_at(1);
    CHECK(arr.size() == 2);
    CHECK(arr.get(0) == 1);
    CHECK(arr.get(1) == 3);
}

TEST_CASE("dynamic array: get/insert/remove out of range throws") {
    DynamicArray<int> arr;
    arr.append(1);
    bool threw = false;
    try {
        arr.get(5);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    CHECK(threw);

    threw = false;
    try {
        arr.remove_at(5);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    CHECK(threw);
}

TEST_CASE("dynamic array: empty array has size 0") {
    DynamicArray<int> arr;
    CHECK(arr.empty());
    CHECK(arr.size() == 0);
}

TEST_CASE("dynamic array: set overwrites existing element") {
    DynamicArray<int> arr;
    arr.append(1);
    arr.set(0, 99);
    CHECK(arr.get(0) == 99);
}
