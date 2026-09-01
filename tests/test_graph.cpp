#include <limits>

#include "../include/data_structures/graph.h"
#include "../include/test_framework.h"

TEST_CASE("graph: bfs visits in breadth-first order") {
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);
    auto order = g.bfs(0);
    std::vector<int> expected = {0, 1, 2, 3, 4, 5};
    CHECK(order == expected);
}

TEST_CASE("graph: dfs visits depth-first before backtracking") {
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    auto order = g.dfs(0);
    std::vector<int> expected = {0, 1, 3, 4, 2};
    CHECK(order == expected);
}

TEST_CASE("graph: bfs/dfs on a single isolated vertex") {
    Graph g(1);
    CHECK(g.bfs(0) == std::vector<int>{0});
    CHECK(g.dfs(0) == std::vector<int>{0});
}

TEST_CASE("graph: dijkstra finds shortest paths on a weighted graph") {
    Graph g(5);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 1);
    g.add_edge(2, 1, 2);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 3, 5);
    g.add_edge(3, 4, 3);
    auto dist = g.dijkstra(0);
    // shortest 0->1 is via 2 (1+2=3), not the direct edge (4)
    CHECK(dist[1] == 3);
    CHECK(dist[2] == 1);
    CHECK(dist[3] == 4);
    CHECK(dist[4] == 7);
}

TEST_CASE("graph: dijkstra leaves unreachable vertices at INT_MAX") {
    Graph g(3);
    g.add_edge(0, 1, 1);
    // vertex 2 has no edges at all
    auto dist = g.dijkstra(0);
    CHECK(dist[0] == 0);
    CHECK(dist[1] == 1);
    CHECK(dist[2] == std::numeric_limits<int>::max());
}

TEST_CASE("graph: directed edges only traverse one way") {
    Graph g(3);
    g.add_edge(0, 1, 1, /*directed=*/true);
    auto dist_from_0 = g.dijkstra(0);
    auto dist_from_1 = g.dijkstra(1);
    CHECK(dist_from_0[1] == 1);
    CHECK(dist_from_1[0] == std::numeric_limits<int>::max());
}
