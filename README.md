# Data Structures & Algorithms (C++)
![CI](https://github.com/saijignas/Data-Structures-and-Algorithms/actions/workflows/ci.yml/badge.svg)

Core data structures and algorithms implemented from scratch in C++ —
not wrappers around the standard library (no `std::vector`-backed
"dynamic array" that's secretly just `std::vector`, no
`std::priority_queue` standing in for the heap), and not solved
LeetCode problems. Every header states the time/space complexity of
each operation and *why* — e.g. why quicksort here uses a randomized
pivot, why a hash map needs resizing, why an unbalanced BST can degrade
to O(n).

**Stack:** C++14, no external dependencies (a from-scratch, ~60-line
test framework in `include/test_framework.h` replaces a library like
GoogleTest/doctest — a deliberate choice, in keeping with the rest of
this repo: built from scratch, not delegated).

## What's here

| Structure / Algorithm | File | Core operations | Complexity |
|---|---|---|---|
| Dynamic array | `include/data_structures/dynamic_array.h` | append, insert, remove_at, get/set | O(1) amortized append; O(n) insert/remove |
| Singly linked list | `include/data_structures/linked_list.h` | append, reverse, cycle detection | O(n) reverse; O(n) time / O(1) space cycle detection (Floyd's) |
| Stack / Queue | `include/data_structures/stack_queue.h` | push/pop, enqueue/dequeue | O(1) each; includes a queue built from two stacks |
| Hash map | `include/data_structures/hash_map.h` | get, set, remove | O(1) average (separate chaining + dynamic resizing) |
| Binary search tree | `include/data_structures/binary_search_tree.h` | insert, search, remove, in-order | O(h) — O(log n) average, O(n) worst case (deliberately unbalanced, to make that tradeoff explicit) |
| Min-heap | `include/data_structures/heap.h` | push, pop_min | O(log n) each |
| Graph | `include/data_structures/graph.h` | BFS, DFS, Dijkstra | O(V+E) BFS/DFS; O((V+E) log V) Dijkstra, using this repo's own heap and its own Stack/Queue |
| Sorting | `include/algorithms/sorting.h` | merge sort, quicksort | O(n log n); merge sort is stable, quicksort uses a randomized pivot |
| Searching | `include/algorithms/searching.h` | binary search (iterative + recursive) | O(log n) |

## Running the tests

```bash
make test
```

60 test cases / 471 individual checks, covering normal cases, edge cases
(empty structures, single elements, out-of-range access), and two
randomized stress tests (heap, sorting) checked against `std::sort` as a
correctness oracle. No CMake, no external test framework to install —
`make test` compiles and runs everything with just a C++14 compiler.

Verified against both a modern toolchain and a genuinely old one
(MinGW.org GCC 6.3.0, 2016) — the latter turned out to lack `std::mutex`
and a couple of Windows CRT functions that mainstream test frameworks
(doctest, in this case) assume are always available, which is the
direct reason this repo has its own minimal test runner instead of a
vendored dependency.

## Design notes

- **BST is intentionally unbalanced.** A self-balancing tree (AVL,
  Red-Black) is a reasonable next addition, but the point of this
  version is to make the O(n) degenerate case an explicit, tested
  behavior (`bst: height reflects shape`) rather than something to hide.
- **Dijkstra reuses this repo's own `MinHeap`**, and BFS/DFS reuse this
  repo's own `Queue`/`Stack` — not `std::priority_queue`, `std::queue`,
  or recursion for DFS (an explicit stack avoids a stack-overflow risk
  on a long path that recursive DFS would have). The whole path from
  primitive data structure to graph algorithm stays inside this repo.
- **Quicksort here is not in-place** — it builds new vectors per
  partition. That trades memory efficiency for clarity; an in-place
  version with the same randomized-pivot approach is a reasonable
  follow-up.
- **Templates over `void*`/inheritance-based genericity.** Every
  container is a template (`DynamicArray<T>`, `HashMap<K, V>`, ...),
  the idiomatic way to get compile-time-checked generic containers in
  C++ rather than the runtime-typed genericity Python gives you for
  free.
