import random

from algorithms.sorting import merge_sort, quicksort


def test_merge_sort_basic():
    assert merge_sort([5, 3, 8, 1, 9, 2]) == [1, 2, 3, 5, 8, 9]


def test_merge_sort_empty_and_single():
    assert merge_sort([]) == []
    assert merge_sort([1]) == [1]


class _TaggedByKey:
    """Compares only on `key`, so two instances with equal keys but
    different tags are "equal" for sorting purposes -- exactly the setup
    needed to actually observe whether a sort preserves original order
    among equal elements (stability), rather than just re-deriving the
    same order tuple comparison would already produce."""

    def __init__(self, key, tag):
        self.key = key
        self.tag = tag

    def __le__(self, other):
        return self.key <= other.key

    def __lt__(self, other):
        return self.key < other.key


def test_merge_sort_stability():
    items = [
        _TaggedByKey(1, "a"),
        _TaggedByKey(0, "b"),
        _TaggedByKey(1, "c"),
        _TaggedByKey(0, "d"),
    ]
    result = merge_sort(items)
    assert [(x.key, x.tag) for x in result] == [(0, "b"), (0, "d"), (1, "a"), (1, "c")]


def test_quicksort_basic():
    assert quicksort([5, 3, 8, 1, 9, 2]) == [1, 2, 3, 5, 8, 9]


def test_quicksort_empty_and_single():
    assert quicksort([]) == []
    assert quicksort([1]) == [1]


def test_quicksort_handles_duplicates():
    assert quicksort([4, 2, 4, 1, 2, 4]) == [1, 2, 2, 4, 4, 4]


def test_both_sorts_match_builtin_on_random_input():
    random.seed(7)
    for _ in range(20):
        data = [random.randint(-100, 100) for _ in range(random.randint(0, 50))]
        expected = sorted(data)
        assert merge_sort(data) == expected
        assert quicksort(data) == expected
