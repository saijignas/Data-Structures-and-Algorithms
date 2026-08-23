from data_structures.linked_list import LinkedList


def test_append_prepend():
    ll = LinkedList()
    ll.append(2)
    ll.append(3)
    ll.prepend(1)
    assert ll.to_list() == [1, 2, 3]
    assert len(ll) == 3


def test_get():
    ll = LinkedList()
    for v in [10, 20, 30]:
        ll.append(v)
    assert ll.get(0) == 10
    assert ll.get(2) == 30


def test_delete_head_middle_tail():
    ll = LinkedList()
    for v in [1, 2, 3, 4]:
        ll.append(v)
    assert ll.delete(1) is True  # head
    assert ll.to_list() == [2, 3, 4]
    assert ll.delete(3) is True  # middle
    assert ll.to_list() == [2, 4]
    assert ll.delete(4) is True  # tail
    assert ll.to_list() == [2]
    assert ll.delete(99) is False  # not present


def test_reverse():
    ll = LinkedList()
    for v in [1, 2, 3, 4, 5]:
        ll.append(v)
    ll.reverse()
    assert ll.to_list() == [5, 4, 3, 2, 1]


def test_reverse_empty_and_single():
    empty = LinkedList()
    empty.reverse()
    assert empty.to_list() == []

    single = LinkedList()
    single.append(1)
    single.reverse()
    assert single.to_list() == [1]


def test_has_cycle_false_for_normal_list():
    ll = LinkedList()
    for v in [1, 2, 3]:
        ll.append(v)
    assert ll.has_cycle() is False


def test_has_cycle_true_when_cycle_introduced():
    ll = LinkedList()
    for v in [1, 2, 3, 4]:
        ll.append(v)
    # Manually introduce a cycle: tail points back to the second node.
    node = ll.head
    second = ll.head.next
    while node.next is not None:
        node = node.next
    node.next = second
    assert ll.has_cycle() is True
