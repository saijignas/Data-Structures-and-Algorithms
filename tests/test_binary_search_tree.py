from data_structures.binary_search_tree import BinarySearchTree


def build_tree(values):
    tree = BinarySearchTree()
    for v in values:
        tree.insert(v)
    return tree


def test_insert_and_search():
    tree = build_tree([5, 3, 8, 1, 4, 7, 9])
    for v in [5, 3, 8, 1, 4, 7, 9]:
        assert tree.search(v) is True
    assert tree.search(100) is False


def test_duplicate_insert_ignored():
    tree = build_tree([5, 3, 5, 3])
    assert len(tree) == 2


def test_in_order_is_sorted():
    values = [5, 3, 8, 1, 4, 7, 9, 2, 6]
    tree = build_tree(values)
    assert tree.in_order() == sorted(values)


def test_delete_leaf():
    tree = build_tree([5, 3, 8])
    tree.delete(3)
    assert tree.search(3) is False
    assert tree.in_order() == [5, 8]
    assert len(tree) == 2


def test_delete_node_with_one_child():
    tree = build_tree([5, 3, 8, 1])
    tree.delete(3)
    assert tree.search(3) is False
    assert tree.in_order() == [1, 5, 8]


def test_delete_node_with_two_children():
    tree = build_tree([5, 3, 8, 1, 4, 7, 9])
    tree.delete(3)
    assert tree.search(3) is False
    assert tree.in_order() == [1, 4, 5, 7, 8, 9]
    assert len(tree) == 6


def test_delete_root():
    tree = build_tree([5, 3, 8, 1, 4, 7, 9])
    tree.delete(5)
    assert tree.search(5) is False
    assert tree.in_order() == [1, 3, 4, 7, 8, 9]
    assert len(tree) == 6


def test_height_reflects_shape():
    empty = BinarySearchTree()
    assert empty.height() == -1

    single = build_tree([1])
    assert single.height() == 0

    # A sorted-order insertion degenerates into a linked list -- worth
    # asserting explicitly, since it's the whole reason balanced trees exist.
    degenerate = build_tree([1, 2, 3, 4, 5])
    assert degenerate.height() == 4
