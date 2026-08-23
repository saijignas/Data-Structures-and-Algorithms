"""Binary min-heap on top of a plain Python list, implemented directly
(not via heapq) to make the array-index-arithmetic and sift up/down logic
explicit.

Time complexity:
    push:      O(log n)  (sift-up)
    pop_min:   O(log n)  (sift-down)
    peek_min:  O(1)
    build from n items: O(n log n) here (n pushes); a true heapify from an
        unordered array can do this in O(n), which is noted but not the
        approach taken -- pushing one at a time is the simpler, more
        common interview-relevant version.
Space complexity: O(n)
"""


class MinHeap:
    def __init__(self):
        self._data = []

    def __len__(self) -> int:
        return len(self._data)

    def is_empty(self) -> bool:
        return len(self._data) == 0

    def peek_min(self):
        if self.is_empty():
            raise IndexError("peek from empty heap")
        return self._data[0]

    def push(self, value) -> None:
        self._data.append(value)
        self._sift_up(len(self._data) - 1)

    def pop_min(self):
        if self.is_empty():
            raise IndexError("pop from empty heap")
        last_index = len(self._data) - 1
        self._data[0], self._data[last_index] = self._data[last_index], self._data[0]
        min_value = self._data.pop()
        if self._data:
            self._sift_down(0)
        return min_value

    def _sift_up(self, index: int) -> None:
        while index > 0:
            parent = (index - 1) // 2
            if self._data[index] < self._data[parent]:
                self._data[index], self._data[parent] = self._data[parent], self._data[index]
                index = parent
            else:
                break

    def _sift_down(self, index: int) -> None:
        n = len(self._data)
        while True:
            left, right = 2 * index + 1, 2 * index + 2
            smallest = index
            if left < n and self._data[left] < self._data[smallest]:
                smallest = left
            if right < n and self._data[right] < self._data[smallest]:
                smallest = right
            if smallest == index:
                break
            self._data[index], self._data[smallest] = self._data[smallest], self._data[index]
            index = smallest
