from data_structures.hash_map import HashMap


def test_set_get_basic():
    m = HashMap()
    m.set("a", 1)
    m.set("b", 2)
    assert m.get("a") == 1
    assert m.get("b") == 2
    assert m.get("missing") is None
    assert m.get("missing", "default") == "default"


def test_overwrite_existing_key():
    m = HashMap()
    m.set("a", 1)
    m.set("a", 2)
    assert m.get("a") == 2
    assert len(m) == 1


def test_delete():
    m = HashMap()
    m.set("a", 1)
    m.set("b", 2)
    assert m.delete("a") is True
    assert m.get("a") is None
    assert m.delete("a") is False
    assert len(m) == 1


def test_contains():
    m = HashMap()
    m.set("a", 1)
    assert "a" in m
    assert "b" not in m


def test_resizes_and_stays_correct_under_many_inserts():
    m = HashMap(initial_capacity=8)
    for i in range(1000):
        m.set(f"key{i}", i)
    assert len(m) == 1000
    for i in range(1000):
        assert m.get(f"key{i}") == i
    # After resizing for load factor, no bucket should be wildly long.
    assert m.max_bucket_length() < 20


def test_keys_and_items():
    m = HashMap()
    m.set("a", 1)
    m.set("b", 2)
    assert set(m.keys()) == {"a", "b"}
    assert set(m.items()) == {("a", 1), ("b", 2)}
