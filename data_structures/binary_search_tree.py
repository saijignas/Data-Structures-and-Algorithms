"""Unbalanced binary search tree (deliberately not self-balancing, to keep
the invariant simple: everything in a node's left subtree is smaller,
everything in its right subtree is larger).

Time complexity:
    insert/search/delete: O(h), where h is tree height.
        - O(log n) average case for random insertion order.
        - O(n) worst case (e.g. inserting a sorted sequence degenerates the
          tree into a linked list) -- this is exactly why balanced trees
          (AVL/Red-Black) exist, and worth stating rather than glossing over.
    in-order traversal: O(n), and always yields values in sorted order.
Space complexity: O(n)
"""


class TreeNode:
    __slots__ = ("value", "left", "right")

    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self):
        self.root = None
        self._size = 0

    def __len__(self) -> int:
        return self._size

    def insert(self, value) -> None:
        if self.root is None:
            self.root = TreeNode(value)
            self._size += 1
            return
        node = self.root
        while True:
            if value == node.value:
                return  # no duplicates
            elif value < node.value:
                if node.left is None:
                    node.left = TreeNode(value)
                    self._size += 1
                    return
                node = node.left
            else:
                if node.right is None:
                    node.right = TreeNode(value)
                    self._size += 1
                    return
                node = node.right

    def search(self, value) -> bool:
        node = self.root
        while node is not None:
            if value == node.value:
                return True
            node = node.left if value < node.value else node.right
        return False

    def _min_node(self, node: TreeNode) -> TreeNode:
        while node.left is not None:
            node = node.left
        return node

    def delete(self, value) -> None:
        self.root = self._delete(self.root, value)

    def _delete(self, node, value):
        if node is None:
            return None
        if value < node.value:
            node.left = self._delete(node.left, value)
        elif value > node.value:
            node.right = self._delete(node.right, value)
        else:
            self._size -= 1
            if node.left is None:
                return node.right
            if node.right is None:
                return node.left
            # Two children: replace with in-order successor (smallest in
            # the right subtree), then delete that successor from there.
            successor = self._min_node(node.right)
            node.value = successor.value
            self._size += 1  # undo the decrement; the real delete happens below
            node.right = self._delete(node.right, successor.value)
        return node

    def in_order(self) -> list:
        result = []

        def walk(node):
            if node is None:
                return
            walk(node.left)
            result.append(node.value)
            walk(node.right)

        walk(self.root)
        return result

    def height(self) -> int:
        def h(node):
            if node is None:
                return -1
            return 1 + max(h(node.left), h(node.right))

        return h(self.root)
