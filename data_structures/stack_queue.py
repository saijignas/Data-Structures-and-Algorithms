"""Stack (LIFO) and Queue (FIFO), plus a queue implemented from two stacks --
a classic exercise showing how the operations one gets "for free" on top of
a simpler primitive still cost something (amortized O(1), not O(1) worst case).

Stack (list-backed):
    push/pop/peek: O(1)

Queue (collections.deque-backed):
    enqueue/dequeue/peek: O(1)

QueueFromStacks (two Stack instances only, no deque):
    enqueue: O(1)
    dequeue: O(1) amortized -- worst case O(n) when the "in" stack has to be
             drained into the "out" stack, but each element only ever makes
             that trip once, so it amortizes to O(1) per operation.
"""

from collections import deque


class Stack:
    def __init__(self):
        self._data = []

    def __len__(self) -> int:
        return len(self._data)

    def is_empty(self) -> bool:
        return len(self._data) == 0

    def push(self, value) -> None:
        self._data.append(value)

    def pop(self):
        if self.is_empty():
            raise IndexError("pop from empty stack")
        return self._data.pop()

    def peek(self):
        if self.is_empty():
            raise IndexError("peek from empty stack")
        return self._data[-1]


class Queue:
    def __init__(self):
        self._data = deque()

    def __len__(self) -> int:
        return len(self._data)

    def is_empty(self) -> bool:
        return len(self._data) == 0

    def enqueue(self, value) -> None:
        self._data.append(value)

    def dequeue(self):
        if self.is_empty():
            raise IndexError("dequeue from empty queue")
        return self._data.popleft()

    def peek(self):
        if self.is_empty():
            raise IndexError("peek from empty queue")
        return self._data[0]


class QueueFromStacks:
    """FIFO queue built only from two Stack instances (no deque)."""

    def __init__(self):
        self._in = Stack()
        self._out = Stack()

    def __len__(self) -> int:
        return len(self._in) + len(self._out)

    def enqueue(self, value) -> None:
        self._in.push(value)

    def dequeue(self):
        if self._out.is_empty():
            while not self._in.is_empty():
                self._out.push(self._in.pop())
        if self._out.is_empty():
            raise IndexError("dequeue from empty queue")
        return self._out.pop()
