#include "gtest/gtest.h"
#include "dijkstra.h"

template<typename EdgeWeight>
void AddWEdge(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
    Edge * p_edge = new WEdge<EdgeWeight>(v, w, edge_weight);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}

void TestSsspIntInt(Sssp<int, int> * p_sssp) {
    WGraph<int> * p_graph = new ListWGraph<int>(7, true);
    AddEdge<int>(p_graph, 0, 1, 2);
    AddEdge<int>(p_graph, 0, 2, 4);
    AddEdge<int>(p_graph, 0, 6, 10);
    AddEdge<int>(p_graph, 1, 2, 1);
    AddEdge<int>(p_graph, 1, 5, 1);
    AddEdge<int>(p_graph, 1, 6, 5);
    AddEdge<int>(p_graph, 2, 3, 2);
    AddEdge<int>(p_graph, 3, 4, 5);
    AddEdge<int>(p_graph, 5, 6, 2);
    AddEdge<int>(p_graph, 5, 4, 10);
    int dist;
    PathRecorder * p_recorder = new NoPathRecorder();
    p_sssp->SingleSourceShortestPath(p_graph, 0, 4, &dist, p_recorder);
    EXPECT_EQ(dist, 10);
    p_recorder->clear();
    p_sssp->SingleSourceShortestPath(p_graph, 0, 6, &dist, p_recorder);
    EXPECT_EQ(dist, 5);
    delete p_recorder;
    p_recorder = new SinglePathRecorder(7);
    p_sssp->SingleSourceShortestPath(p_graph, 1, 4, &dist, p_recorder);
    EXPECT_EQ(dist, 8);
    vector<Vertex> path;
    ((SinglePathRecorder *)p_recorder)->GetSinglePath(1, 4, path);
    
}


TEST(Algorithm, dijkstra) {
    WGraph<int> * p_graph = new ListWGraph<int>(6, true);
    
}
