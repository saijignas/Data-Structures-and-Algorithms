#include "../include/data_structures/binary_search_tree.h"
#include "../include/test_framework.h"

TEST_CASE("bst: insert then in_order returns sorted values") {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(1);
    tree.insert(4);
    auto order = tree.in_order();
    std::vector<int> expected = {1, 3, 4, 5, 8};
    CHECK(order == expected);
}

TEST_CASE("bst: contains finds inserted values and rejects missing ones") {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    CHECK(tree.contains(5));
    CHECK(tree.contains(3));
    CHECK(!tree.contains(99));
}

TEST_CASE("bst: duplicate insert is a no-op (set semantics)") {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(5);
    CHECK(tree.size() == 1);
}

TEST_CASE("bst: remove a leaf node") {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.remove(3);
    CHECK(!tree.contains(3));
    std::vector<int> expected = {5, 8};
    CHECK(tree.in_order() == expected);
}

TEST_CASE("bst: remove a node with two children preserves BST order") {
    BinarySearchTree<int> tree;
    for (int v : {5, 3, 8, 1, 4, 7, 9}) tree.insert(v);
    tree.remove(5);
    CHECK(!tree.contains(5));
    std::vector<int> expected = {1, 3, 4, 7, 8, 9};
    CHECK(tree.in_order() == expected);
}

TEST_CASE("bst: empty tree has height 0") {
    BinarySearchTree<int> tree;
    CHECK(tree.height() == 0);
    CHECK(tree.empty());
}

TEST_CASE("bst: height reflects shape -- sorted-order insertion degenerates to a line") {
    BinarySearchTree<int> degenerate;
    for (int v = 1; v <= 7; ++v) degenerate.insert(v);  // sorted order: degenerates
    CHECK(degenerate.height() == 7);  // O(n), the unbalanced worst case

    BinarySearchTree<int> balanced;
    for (int v : {4, 2, 6, 1, 3, 5, 7}) balanced.insert(v);  // level order: stays balanced
    CHECK(balanced.height() == 3);  // O(log n)
}
