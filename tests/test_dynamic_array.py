import pytest

from data_structures.dynamic_array import DynamicArray


def test_append_and_index():
    arr = DynamicArray()
    for i in range(20):
        arr.append(i)
    assert len(arr) == 20
    assert arr.to_list() == list(range(20))


def test_resize_triggers_correctly():
    arr = DynamicArray(capacity=2)
    for i in range(10):
        arr.append(i)
    assert arr.to_list() == list(range(10))


def test_pop():
    arr = DynamicArray()
    for i in range(5):
        arr.append(i)
    assert arr.pop() == 4
    assert arr.pop() == 3
    assert len(arr) == 3


def test_pop_empty_raises():
    arr = DynamicArray()
    with pytest.raises(IndexError):
        arr.pop()


def test_insert_and_delete_middle():
    arr = DynamicArray()
    for i in [1, 2, 4, 5]:
        arr.append(i)
    arr.insert(2, 3)
    assert arr.to_list() == [1, 2, 3, 4, 5]
    deleted = arr.delete(0)
    assert deleted == 1
    assert arr.to_list() == [2, 3, 4, 5]


def test_get_set_bounds():
    arr = DynamicArray()
    arr.append(10)
    arr[0] = 99
    assert arr[0] == 99
    with pytest.raises(IndexError):
        arr[5]
    with pytest.raises(IndexError):
        arr[-1]
