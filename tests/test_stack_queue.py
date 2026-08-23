import pytest

from data_structures.stack_queue import Queue, QueueFromStacks, Stack


def test_stack_lifo_order():
    s = Stack()
    s.push(1)
    s.push(2)
    s.push(3)
    assert s.peek() == 3
    assert s.pop() == 3
    assert s.pop() == 2
    assert len(s) == 1


def test_stack_empty_raises():
    s = Stack()
    with pytest.raises(IndexError):
        s.pop()
    with pytest.raises(IndexError):
        s.peek()


def test_queue_fifo_order():
    q = Queue()
    q.enqueue("a")
    q.enqueue("b")
    q.enqueue("c")
    assert q.peek() == "a"
    assert q.dequeue() == "a"
    assert q.dequeue() == "b"
    assert len(q) == 1


def test_queue_empty_raises():
    q = Queue()
    with pytest.raises(IndexError):
        q.dequeue()


def test_queue_from_stacks_matches_fifo_semantics():
    q = QueueFromStacks()
    for v in [1, 2, 3, 4]:
        q.enqueue(v)
    assert q.dequeue() == 1
    q.enqueue(5)
    assert q.dequeue() == 2
    assert q.dequeue() == 3
    assert q.dequeue() == 4
    assert q.dequeue() == 5
    with pytest.raises(IndexError):
        q.dequeue()
