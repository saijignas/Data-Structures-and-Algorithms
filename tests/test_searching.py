from algorithms.searching import binary_search, binary_search_recursive


def test_binary_search_found_and_not_found():
    items = [1, 3, 5, 7, 9, 11, 13]
    for target in items:
        assert binary_search(items, target) == items.index(target)
    assert binary_search(items, 4) == -1
    assert binary_search(items, 0) == -1
    assert binary_search(items, 100) == -1


def test_binary_search_empty_list():
    assert binary_search([], 5) == -1


def test_binary_search_recursive_matches_iterative():
    items = list(range(0, 100, 2))
    for target in [0, 2, 50, 98]:
        assert binary_search_recursive(items, target) == binary_search(items, target)
    assert binary_search_recursive(items, 3) == -1
