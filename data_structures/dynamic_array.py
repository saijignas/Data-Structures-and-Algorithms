"""Dynamic array (like a simplified Python list / C++ vector) built on a
fixed-size backing array, to make the amortized-O(1) append argument concrete
rather than relying on the built-in list.

Time complexity:
    append:      O(1) amortized (occasional O(n) resize, doubling strategy)
    pop:         O(1) amortized
    get/set:     O(1)
    insert(i):   O(n)
    delete(i):   O(n)
Space complexity: O(n)
"""


class DynamicArray:
    def __init__(self, capacity: int = 4):
        self._capacity = max(1, capacity)
        self._size = 0
        self._data = [None] * self._capacity

    def __len__(self) -> int:
        return self._size

    def __getitem__(self, index: int):
        if not 0 <= index < self._size:
            raise IndexError("index out of range")
        return self._data[index]

    def __setitem__(self, index: int, value) -> None:
        if not 0 <= index < self._size:
            raise IndexError("index out of range")
        self._data[index] = value

    def __iter__(self):
        for i in range(self._size):
            yield self._data[i]

    def _resize(self, new_capacity: int) -> None:
        new_data = [None] * new_capacity
        for i in range(self._size):
            new_data[i] = self._data[i]
        self._data = new_data
        self._capacity = new_capacity

    def append(self, value) -> None:
        if self._size == self._capacity:
            self._resize(self._capacity * 2)
        self._data[self._size] = value
        self._size += 1

    def pop(self):
        if self._size == 0:
            raise IndexError("pop from empty array")
        self._size -= 1
        value = self._data[self._size]
        self._data[self._size] = None
        # Shrink to avoid unbounded memory retention after many pops.
        if self._capacity > 4 and self._size <= self._capacity // 4:
            self._resize(max(4, self._capacity // 2))
        return value

    def insert(self, index: int, value) -> None:
        if not 0 <= index <= self._size:
            raise IndexError("index out of range")
        if self._size == self._capacity:
            self._resize(self._capacity * 2)
        for i in range(self._size, index, -1):
            self._data[i] = self._data[i - 1]
        self._data[index] = value
        self._size += 1

    def delete(self, index: int):
        if not 0 <= index < self._size:
            raise IndexError("index out of range")
        value = self._data[index]
        for i in range(index, self._size - 1):
            self._data[i] = self._data[i + 1]
        self._size -= 1
        self._data[self._size] = None
        return value

    def to_list(self) -> list:
        return [self._data[i] for i in range(self._size)]
