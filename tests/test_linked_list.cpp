#include "../include/data_structures/linked_list.h"
#include "../include/test_framework.h"

TEST_CASE("linked list: append builds correct order") {
    SinglyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    CHECK(list.size() == 3);
    CHECK(list.at(0) == 1);
    CHECK(list.at(1) == 2);
    CHECK(list.at(2) == 3);
}

TEST_CASE("linked list: empty list has size 0") {
    SinglyLinkedList<int> list;
    CHECK(list.empty());
    CHECK(list.size() == 0);
}

TEST_CASE("linked list: reverse a multi-element list") {
    SinglyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.reverse();
    CHECK(list.at(0) == 3);
    CHECK(list.at(1) == 2);
    CHECK(list.at(2) == 1);
}

TEST_CASE("linked list: reverse a single-element list is a no-op") {
    SinglyLinkedList<int> list;
    list.append(42);
    list.reverse();
    CHECK(list.at(0) == 42);
    CHECK(list.size() == 1);
}

TEST_CASE("linked list: no cycle in a normal list") {
    SinglyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    CHECK(!list.has_cycle());
}

TEST_CASE("linked list: cycle detection finds a cycle back to the head") {
    SinglyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.introduce_cycle_for_testing(0);
    CHECK(list.has_cycle());
}

TEST_CASE("linked list: cycle detection finds a cycle into the middle") {
    SinglyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.introduce_cycle_for_testing(1);
    CHECK(list.has_cycle());
}
