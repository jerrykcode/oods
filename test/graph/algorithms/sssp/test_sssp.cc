#include "gtest/gtest.h"
#include "dijkstra.h"
#include "list_w_graph.h"
using namespace oods::oograph;

template<typename EdgeWeight>
void AddWEdge(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
    Edge * p_edge = new WEdge<EdgeWeight>(v, w, edge_weight);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}

void TestSsspIntInt(Sssp<int, int> * p_sssp) {
    WGraph<int> * p_graph = new ListWGraph<int>(7, true);
    AddWEdge<int>(p_graph, 0, 1, 2);
    AddWEdge<int>(p_graph, 0, 2, 4);
    AddWEdge<int>(p_graph, 0, 6, 10);
    AddWEdge<int>(p_graph, 1, 2, 1);
    AddWEdge<int>(p_graph, 1, 5, 1);
    AddWEdge<int>(p_graph, 1, 6, 5);
    AddWEdge<int>(p_graph, 2, 3, 2);
    AddWEdge<int>(p_graph, 3, 4, 5);
    AddWEdge<int>(p_graph, 5, 6, 2);
    AddWEdge<int>(p_graph, 5, 4, 10);
    int dist;
    bool result;
    PathRecorder * p_recorder = new NoPathRecorder();
    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 4, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist, 10);
    p_recorder->Clear();
    result = p_sssp->SingleSourceShortestPath(p_graph, 0, 6, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist, 5);
    delete p_recorder;
    p_recorder = (PathRecorder *)(new SinglePathRecorder(7));
    result = p_sssp->SingleSourceShortestPath(p_graph, 1, 4, &dist, p_recorder);
    ASSERT_TRUE(result);
    EXPECT_EQ(dist, 8);
    Path * p_path = new Path();
    ((SinglePathRecorder *)p_recorder)->GetSinglePath(1, 4, p_path);
    vector<Vertex>& v = p_path->GetPathRef();
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    delete p_path;
    delete p_recorder;
    delete p_graph;
}


TEST(Algorithm, dijkstra) {
    Optimizer<int> * p_optimizer = new HeapOptimizer<int>();
    Sssp<int, int> * p_sssp = new Dijkstra<int, int>(p_optimizer);
    TestSsspIntInt(p_sssp);
    delete p_optimizer;
    delete p_sssp;
}
