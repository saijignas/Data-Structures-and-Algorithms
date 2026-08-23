from data_structures.graph import Graph


def build_sample_graph():
    g = Graph(directed=True)
    g.add_edge("A", "B", 1)
    g.add_edge("A", "C", 4)
    g.add_edge("B", "C", 2)
    g.add_edge("B", "D", 5)
    g.add_edge("C", "D", 1)
    return g


def test_bfs_order():
    g = build_sample_graph()
    order = g.bfs("A")
    assert order[0] == "A"
    assert set(order) == {"A", "B", "C", "D"}


def test_dfs_reaches_all_connected_vertices():
    g = build_sample_graph()
    order = g.dfs("A")
    assert order[0] == "A"
    assert set(order) == {"A", "B", "C", "D"}


def test_bfs_dfs_on_unknown_start_returns_empty():
    g = build_sample_graph()
    assert g.bfs("Z") == []
    assert g.dfs("Z") == []


def test_dijkstra_shortest_distances():
    g = build_sample_graph()
    distances = g.dijkstra("A")
    assert distances["A"] == 0
    assert distances["B"] == 1
    # A->C direct is 4, but A->B->C is 1+2=3, which is shorter.
    assert distances["C"] == 3
    # A->B->D is 1+5=6; A->B->C->D is 1+2+1=4, which is shorter.
    assert distances["D"] == 4


def test_dijkstra_unreachable_vertex_is_infinity():
    g = build_sample_graph()
    g.add_vertex("Isolated")
    distances = g.dijkstra("A")
    assert distances["Isolated"] == float("inf")


def test_dijkstra_rejects_negative_weights():
    g = Graph(directed=True)
    g.add_edge("A", "B", -1)
    import pytest

    with pytest.raises(ValueError):
        g.dijkstra("A")


def test_undirected_graph_edge_is_symmetric():
    g = Graph(directed=False)
    g.add_edge("A", "B", 1)
    assert ("B", 1) in g.neighbors("A")
    assert ("A", 1) in g.neighbors("B")
