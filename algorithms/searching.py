"""Binary search over a sorted sequence, in both iterative and recursive
form -- the iterative version is what you'd actually want in production
(no recursion-depth concern, no extra stack frames); the recursive version
is included because it's what most interviews ask for first and the two
are worth being able to translate between.

Time complexity:  O(log n)
Space complexity: O(1) iterative, O(log n) recursive (call stack)
"""


def binary_search(items: list, target) -> int:
    """Iterative binary search. Returns the index of `target`, or -1."""
    low, high = 0, len(items) - 1
    while low <= high:
        mid = (low + high) // 2
        if items[mid] == target:
            return mid
        elif items[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1


def binary_search_recursive(items: list, target, low: int = 0, high: int = None) -> int:
    if high is None:
        high = len(items) - 1
    if low > high:
        return -1
    mid = (low + high) // 2
    if items[mid] == target:
        return mid
    elif items[mid] < target:
        return binary_search_recursive(items, target, mid + 1, high)
    else:
        return binary_search_recursive(items, target, low, mid - 1)
