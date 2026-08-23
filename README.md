# Data Structures & Algorithms

Core data structures and algorithms implemented from scratch in Python — not
wrappers around the standard library, and not solved LeetCode problems.
The goal is to demonstrate the reasoning behind each structure's complexity,
not just recall it: every module's docstring states time/space complexity
and the specific reason for it (e.g. *why* quicksort here uses a randomized
pivot, *why* a hash map needs resizing, *why* an unbalanced BST can degrade
to O(n)).

## What's here

| Structure / Algorithm | File | Core operations | Complexity |
|---|---|---|---|
| Dynamic array | `data_structures/dynamic_array.py` | append, insert, delete, get/set | O(1) amortized append; O(n) insert/delete |
| Singly linked list | `data_structures/linked_list.py` | append, reverse, cycle detection | O(n) reverse; O(n) time / O(1) space cycle detection (Floyd's) |
| Stack / Queue | `data_structures/stack_queue.py` | push/pop, enqueue/dequeue | O(1) each; includes a queue built from two stacks |
| Hash map | `data_structures/hash_map.py` | get, set, delete | O(1) average (separate chaining + dynamic resizing) |
| Binary search tree | `data_structures/binary_search_tree.py` | insert, search, delete, in-order | O(h) — O(log n) average, O(n) worst case (deliberately unbalanced, to make that tradeoff explicit) |
| Min-heap | `data_structures/heap.py` | push, pop_min | O(log n) each |
| Graph | `data_structures/graph.py` | BFS, DFS, Dijkstra | O(V+E) BFS/DFS; O((V+E) log V) Dijkstra, using this repo's own heap |
| Sorting | `algorithms/sorting.py` | merge sort, quicksort | O(n log n); merge sort is stable, quicksort uses a randomized pivot |
| Searching | `algorithms/searching.py` | binary search (iterative + recursive) | O(log n) |

## Running the tests

```bash
pip install -r requirements.txt
python -m pytest tests/ -v
```

53 tests, covering normal cases, edge cases (empty structures, single
elements), and a couple of randomized stress tests (heap, sorting) checked
against Python's own `sorted()` as a correctness oracle.

## Design notes

- **BST is intentionally unbalanced.** A self-balancing tree (AVL,
  Red-Black) is a reasonable next addition, but the point of this version
  is to make the O(n) degenerate case an explicit, tested behavior
  (`test_height_reflects_shape`) rather than something to hide.
- **Dijkstra reuses this repo's own `MinHeap`**, not `heapq`, so the whole
  path from priority queue to shortest-path algorithm is contained in this
  repo rather than delegated to the standard library at the one place
  where it'd matter most.
- **Quicksort here is not in-place** — it builds new lists per partition.
  That trades some memory efficiency for clarity; an in-place version with
  the same randomized-pivot approach is a reasonable follow-up.
