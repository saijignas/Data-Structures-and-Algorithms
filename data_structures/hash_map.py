"""Hash map built from scratch with separate-chaining collision resolution
and dynamic resizing, to make the "why is dict O(1)" argument concrete.

Time complexity (average case, assuming a reasonable hash distribution):
    get/set/delete: O(1) average, O(n) worst case (all keys collide)
Resizing (doubling when load factor > 0.75) keeps the average bucket length
bounded as the map grows, which is what keeps operations O(1) on average.
Space complexity: O(n)
"""


class HashMap:
    _LOAD_FACTOR_THRESHOLD = 0.75

    def __init__(self, initial_capacity: int = 8):
        self._capacity = max(8, initial_capacity)
        self._buckets = [[] for _ in range(self._capacity)]
        self._size = 0

    def __len__(self) -> int:
        return self._size

    def __contains__(self, key) -> bool:
        bucket = self._buckets[self._bucket_index(key)]
        return any(k == key for k, _ in bucket)

    def _bucket_index(self, key) -> int:
        return hash(key) % self._capacity

    def _resize(self, new_capacity: int) -> None:
        old_items = [item for bucket in self._buckets for item in bucket]
        self._capacity = new_capacity
        self._buckets = [[] for _ in range(self._capacity)]
        self._size = 0
        for key, value in old_items:
            self._insert_no_resize(key, value)

    def _insert_no_resize(self, key, value) -> None:
        bucket = self._buckets[self._bucket_index(key)]
        for i, (k, _) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, value)
                return
        bucket.append((key, value))
        self._size += 1

    def set(self, key, value) -> None:
        self._insert_no_resize(key, value)
        if self._size / self._capacity > self._LOAD_FACTOR_THRESHOLD:
            self._resize(self._capacity * 2)

    def get(self, key, default=None):
        bucket = self._buckets[self._bucket_index(key)]
        for k, v in bucket:
            if k == key:
                return v
        return default

    def delete(self, key) -> bool:
        bucket = self._buckets[self._bucket_index(key)]
        for i, (k, _) in enumerate(bucket):
            if k == key:
                bucket.pop(i)
                self._size -= 1
                return True
        return False

    def keys(self):
        return [k for bucket in self._buckets for k, _ in bucket]

    def items(self):
        return [(k, v) for bucket in self._buckets for k, v in bucket]

    def max_bucket_length(self) -> int:
        """Diagnostic: how skewed the distribution currently is."""
        return max((len(b) for b in self._buckets), default=0)
