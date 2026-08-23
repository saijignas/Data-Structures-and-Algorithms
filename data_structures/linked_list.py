"""Singly linked list with the classic interview-relevant operations:
reversal and Floyd's cycle detection.

Time complexity:
    append/prepend: O(1)
    get(i)/insert(i): O(n)
    reverse:        O(n)
    has_cycle:       O(n) time, O(1) space (Floyd's tortoise and hare)
Space complexity: O(n)
"""


class Node:
    __slots__ = ("value", "next")

    def __init__(self, value, next=None):
        self.value = value
        self.next = next


class LinkedList:
    def __init__(self):
        self.head = None
        self._size = 0

    def __len__(self) -> int:
        return self._size

    def __iter__(self):
        node = self.head
        while node is not None:
            yield node.value
            node = node.next

    def append(self, value) -> None:
        node = Node(value)
        if self.head is None:
            self.head = node
        else:
            cur = self.head
            while cur.next is not None:
                cur = cur.next
            cur.next = node
        self._size += 1

    def prepend(self, value) -> None:
        self.head = Node(value, self.head)
        self._size += 1

    def get(self, index: int):
        if not 0 <= index < self._size:
            raise IndexError("index out of range")
        cur = self.head
        for _ in range(index):
            cur = cur.next
        return cur.value

    def delete(self, value) -> bool:
        """Remove the first node with a matching value. Returns True if removed."""
        prev, cur = None, self.head
        while cur is not None:
            if cur.value == value:
                if prev is None:
                    self.head = cur.next
                else:
                    prev.next = cur.next
                self._size -= 1
                return True
            prev, cur = cur, cur.next
        return False

    def reverse(self) -> None:
        """In-place reversal using the standard three-pointer technique."""
        prev = None
        cur = self.head
        while cur is not None:
            nxt = cur.next
            cur.next = prev
            prev = cur
            cur = nxt
        self.head = prev

    def has_cycle(self) -> bool:
        """Floyd's tortoise-and-hare cycle detection."""
        slow = fast = self.head
        while fast is not None and fast.next is not None:
            slow = slow.next
            fast = fast.next.next
            if slow is fast:
                return True
        return False

    def to_list(self) -> list:
        return list(self)
