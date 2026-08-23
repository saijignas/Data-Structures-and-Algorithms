import random

import pytest

from data_structures.heap import MinHeap


def test_pop_min_returns_ascending_order():
    heap = MinHeap()
    values = [5, 3, 8, 1, 9, 2, 7]
    for v in values:
        heap.push(v)
    result = [heap.pop_min() for _ in range(len(values))]
    assert result == sorted(values)


def test_peek_does_not_remove():
    heap = MinHeap()
    heap.push(4)
    heap.push(1)
    assert heap.peek_min() == 1
    assert len(heap) == 2


def test_empty_heap_raises():
    heap = MinHeap()
    with pytest.raises(IndexError):
        heap.pop_min()
    with pytest.raises(IndexError):
        heap.peek_min()


def test_randomized_stress_matches_sorted():
    random.seed(42)
    values = [random.randint(-1000, 1000) for _ in range(500)]
    heap = MinHeap()
    for v in values:
        heap.push(v)
    result = [heap.pop_min() for _ in range(len(values))]
    assert result == sorted(values)
