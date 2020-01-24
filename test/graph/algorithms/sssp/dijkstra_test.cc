#include "gtest/gtest.h"
#include "dijkstra.h"

template<typename EdgeWeight>
void AddWEdge(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
    Edge * p_edge = new WEdge<EdgeWeight>(v, w, edge_weight);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}




TEST(Algorithm, dijkstra) {
    WGraph<int> * p_graph = new ListWGraph<int>(6, true);
     
}
