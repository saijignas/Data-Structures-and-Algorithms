// Binary search tree -- deliberately unbalanced (no AVL/red-black
// rebalancing). insert/search/delete are all O(h): O(log n) average on
// random data, but O(n) worst case when inserted in sorted order and
// the tree degenerates into a linked list. That degenerate case is a
// tested, explicit behavior here (see test_height_reflects_shape),
// not a hidden gotcha.
#pragma once

#include <algorithm>
#include <vector>

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree() : root_(nullptr), size_(0) {}
    ~BinarySearchTree() { clear(root_); }
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    std::size_t size() const { return size_; }
    bool empty() const { return root_ == nullptr; }

    void insert(const T& value) {
        root_ = insert_node(root_, value);
    }

    bool contains(const T& value) const {
        return find_node(root_, value) != nullptr;
    }

    void remove(const T& value) {
        bool removed = false;
        root_ = remove_node(root_, value, removed);
        if (removed) --size_;
    }

    std::vector<T> in_order() const {
        std::vector<T> out;
        in_order_walk(root_, out);
        return out;
    }

    // Height of an empty tree is 0; a single node has height 1. Used to
    // make the "unbalanced tree can degenerate to O(n)" tradeoff visible
    // and testable rather than asserted in a comment.
    int height() const { return height_of(root_); }

private:
    struct Node {
        T value;
        Node* left;
        Node* right;
    };

    Node* insert_node(Node* node, const T& value) {
        if (!node) {
            ++size_;
            return new Node{value, nullptr, nullptr};
        }
        if (value < node->value) {
            node->left = insert_node(node->left, value);
        } else if (value > node->value) {
            node->right = insert_node(node->right, value);
        }
        // Equal values are ignored (set semantics), matching the Python
        // version's behavior.
        return node;
    }

    const Node* find_node(const Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->value) return node;
        return value < node->value ? find_node(node->left, value) : find_node(node->right, value);
    }

    Node* remove_node(Node* node, const T& value, bool& removed) {
        if (!node) return nullptr;
        if (value < node->value) {
            node->left = remove_node(node->left, value, removed);
        } else if (value > node->value) {
            node->right = remove_node(node->right, value, removed);
        } else {
            removed = true;
            if (!node->left) {
                Node* right = node->right;
                delete node;
                return right;
            }
            if (!node->right) {
                Node* left = node->left;
                delete node;
                return left;
            }
            // Two children: replace with the in-order successor (the
            // smallest value in the right subtree), then delete that
            // successor from the right subtree.
            Node* successor = node->right;
            while (successor->left) successor = successor->left;
            node->value = successor->value;
            bool unused = false;
            node->right = remove_node(node->right, successor->value, unused);
        }
        return node;
    }

    void in_order_walk(const Node* node, std::vector<T>& out) const {
        if (!node) return;
        in_order_walk(node->left, out);
        out.push_back(node->value);
        in_order_walk(node->right, out);
    }

    int height_of(const Node* node) const {
        if (!node) return 0;
        return 1 + std::max(height_of(node->left), height_of(node->right));
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* root_;
    std::size_t size_;
};
