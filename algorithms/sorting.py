"""Merge sort and quicksort, implemented to make their complexity and
stability tradeoffs concrete rather than just quoted from memory.

merge_sort:
    Time:  O(n log n) worst, average, and best case -- always divides in
           half and does a linear merge, regardless of input order.
    Space: O(n) extra (the merge step allocates new lists).
    Stable: yes (equal elements keep their relative order).

quicksort:
    Time:  O(n log n) average case; O(n^2) worst case (e.g. an
           already-sorted array against a naive last-element pivot -- this
           implementation uses a randomized pivot specifically to make that
           worst case exponentially unlikely rather than structurally
           guaranteed).
    Space: O(log n) average (recursion stack; this implementation is
           not in-place -- it builds new lists per partition, trading some
           memory for clarity).
    Stable: no.
"""

import random


def merge_sort(items: list) -> list:
    if len(items) <= 1:
        return list(items)
    mid = len(items) // 2
    left = merge_sort(items[:mid])
    right = merge_sort(items[mid:])
    return _merge(left, right)


def _merge(left: list, right: list) -> list:
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result


def quicksort(items: list) -> list:
    if len(items) <= 1:
        return list(items)
    pivot = items[random.randrange(len(items))]
    less = [x for x in items if x < pivot]
    equal = [x for x in items if x == pivot]
    greater = [x for x in items if x > pivot]
    return quicksort(less) + equal + quicksort(greater)
