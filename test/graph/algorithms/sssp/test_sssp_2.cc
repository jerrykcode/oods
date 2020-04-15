#include "gtest/gtest.h"
#include "dijkstra.h"
#include "optimized_dijkstra.h"
#include "list_w_graph.h"
#include "matrix_w_graph.h"
#include "testequalpath.h"
#include "addedge.h"
#include "test.h"
#include <vector>
using std::vector;

void TestSsspWithNegativeEdgeWeight(Sssp<int, int> * p_sssp, WGraphCreator<int> * p_graph_creator) {

    WGraph<int> * p_graph = p_graph_creator->CreateWGraph(3, false);

    AddWEdge<int>(p_graph, 0, 1, 1);
    AddWEdge<int>(p_graph, 1, 2, 2);
    AddWEdge<int>(p_graph, 0, 2, -1);
    
    PathRecorder * p_recorder = new NoPathRecorder();
    int dist;

    bool result = p_sssp->SingleSourceShortestPath(p_graph, 0, 1, &dist, p_recorder);

    ASSERT_FALSE(result);

    delete p_recorder;
    delete p_graph;
}

TEST(Sssp, dijkstra_illegal_negative_edge_weight) {
    TestSssp<int, int>(TestSsspWithNegativeEdgeWeight);
}
