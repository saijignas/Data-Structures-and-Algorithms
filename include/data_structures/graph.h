// Weighted graph as an adjacency list, vertices labeled 0..n-1.
// bfs:      O(V+E) -- uses this repo's own Queue, not std::queue.
// dfs:      O(V+E) -- iterative, using this repo's own Stack, not
//           recursion (which risks a stack overflow on a long path in
//           a way an explicit Stack of vertices doesn't).
// dijkstra: O((V+E) log V) -- uses this repo's own MinHeap of
//           (distance, vertex) pairs, so the whole path from priority
//           queue to shortest-path algorithm stays inside this repo
//           rather than delegating to std::priority_queue at the one
//           place it would matter most.
#pragma once

#include <limits>
#include <utility>
#include <vector>

#include "heap.h"
#include "stack_queue.h"

class Graph {
public:
    explicit Graph(std::size_t num_vertices) : adj_(num_vertices) {}

    std::size_t num_vertices() const { return adj_.size(); }

    void add_edge(int u, int v, int weight = 1, bool directed = false) {
        adj_[u].emplace_back(v, weight);
        if (!directed) adj_[v].emplace_back(u, weight);
    }

    std::vector<int> bfs(int start) const {
        std::vector<bool> visited(adj_.size(), false);
        std::vector<int> order;
        Queue<int> queue;
        queue.enqueue(start);
        visited[start] = true;
        while (!queue.empty()) {
            int u = queue.dequeue();
            order.push_back(u);
            for (const auto& edge : adj_[u]) {
                int v = edge.first;
                if (!visited[v]) {
                    visited[v] = true;
                    queue.enqueue(v);
                }
            }
        }
        return order;
    }

    std::vector<int> dfs(int start) const {
        std::vector<bool> visited(adj_.size(), false);
        std::vector<int> order;
        Stack<int> stack;
        stack.push(start);
        while (!stack.empty()) {
            int u = stack.pop();
            if (visited[u]) continue;
            visited[u] = true;
            order.push_back(u);
            // Push in reverse so the traversal visits lower-indexed
            // neighbors first, matching typical recursive-DFS order.
            for (auto it = adj_[u].rbegin(); it != adj_[u].rend(); ++it) {
                if (!visited[it->first]) stack.push(it->first);
            }
        }
        return order;
    }

    // Shortest distance from `start` to every vertex. Unreachable
    // vertices are left at INT_MAX.
    std::vector<int> dijkstra(int start) const {
        const int INF = std::numeric_limits<int>::max();
        std::vector<int> dist(adj_.size(), INF);
        dist[start] = 0;
        MinHeap<std::pair<int, int>> heap;  // (distance, vertex)
        heap.push({0, start});

        while (!heap.empty()) {
            auto top = heap.pop_min();
            int d = top.first;
            int u = top.second;
            if (d > dist[u]) continue;  // stale entry, a shorter path was already found
            for (const auto& edge : adj_[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    heap.push({dist[v], v});
                }
            }
        }
        return dist;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> adj_;  // adj_[u] = list of (v, weight)
};
