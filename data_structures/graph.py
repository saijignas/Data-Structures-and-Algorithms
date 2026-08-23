"""Directed, weighted graph as an adjacency list, with BFS, DFS, and
Dijkstra's shortest path -- deliberately reusing this module's own MinHeap
rather than heapq, so the whole repo's Dijkstra implementation is traceable
to the heap implementation sitting right next to it.

Time complexity (V = vertices, E = edges):
    add_edge:        O(1)
    bfs/dfs:         O(V + E)
    dijkstra:        O((V + E) log V) with a binary heap priority queue
Space complexity: O(V + E)
"""

from collections import deque

from .heap import MinHeap


class Graph:
    def __init__(self, directed: bool = True):
        self._adjacency: dict[str, list[tuple[str, float]]] = {}
        self._directed = directed

    def add_vertex(self, vertex: str) -> None:
        self._adjacency.setdefault(vertex, [])

    def add_edge(self, u: str, v: str, weight: float = 1.0) -> None:
        self.add_vertex(u)
        self.add_vertex(v)
        self._adjacency[u].append((v, weight))
        if not self._directed:
            self._adjacency[v].append((u, weight))

    def neighbors(self, vertex: str) -> list:
        return self._adjacency.get(vertex, [])

    def vertices(self) -> list:
        return list(self._adjacency.keys())

    def bfs(self, start: str) -> list:
        if start not in self._adjacency:
            return []
        visited = {start}
        order = []
        queue = deque([start])
        while queue:
            u = queue.popleft()
            order.append(u)
            for v, _ in self._adjacency[u]:
                if v not in visited:
                    visited.add(v)
                    queue.append(v)
        return order

    def dfs(self, start: str) -> list:
        if start not in self._adjacency:
            return []
        visited = set()
        order = []

        def visit(u):
            visited.add(u)
            order.append(u)
            for v, _ in self._adjacency[u]:
                if v not in visited:
                    visit(v)

        visit(start)
        return order

    def dijkstra(self, start: str) -> dict:
        """Shortest path distances from `start` to every reachable vertex.

        Uses a lazy-deletion approach: stale (larger) distances pushed onto
        the heap before a shorter one was found are simply skipped when
        popped, rather than trying to decrease-key in place.
        """
        if start not in self._adjacency:
            return {}

        distances = {v: float("inf") for v in self._adjacency}
        distances[start] = 0

        heap = MinHeap()
        heap.push((0, start))

        while not heap.is_empty():
            dist, u = heap.pop_min()
            if dist > distances[u]:
                continue  # stale entry, a shorter path to u was already found
            for v, weight in self._adjacency[u]:
                if weight < 0:
                    raise ValueError("Dijkstra's algorithm requires non-negative weights")
                candidate = dist + weight
                if candidate < distances[v]:
                    distances[v] = candidate
                    heap.push((candidate, v))

        return distances
