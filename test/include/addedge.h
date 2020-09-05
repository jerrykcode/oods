#pragma once
#include "graph.h"

template<typename EdgeWeight>
static void AddWEdge(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
    Edge * p_edge = new WEdge<EdgeWeight>(v, w, edge_weight);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}

static void AddUnwEdge(Graph * p_graph, Vertex v, Vertex w) {
    Edge * p_edge = new UnwEdge(v, w);
    p_graph->AddEdge(p_edge);
    delete p_edge;
}
