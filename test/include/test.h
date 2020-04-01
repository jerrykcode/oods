#pragma once    
#include "list_w_graph.h"
#include "matrix_w_graph.h"
#include "dijkstra.h"
#include "optimized_dijkstra.h"
#include <vector>
using namespace oods::oograph;
using std::vector;

template<typename EdgeWeight, typename DistWeight>
static void InitSssp(vector<Sssp<EdgeWeight, DistWeight>*>& v_p_sssp) {
    v_p_sssp.push_back(new Dijkstra<EdgeWeight, DistWeight>());
    v_p_sssp.push_back(new HeapOptimizedDijkstra<EdgeWeight, DistWeight>());
}

template<typename EdgeWeight>
static void InitWGraph(size_t num_vertices, vector<WGraph<EdgeWeight>*>& v_p_graph) {
    v_p_graph.push_back(new ListWGraph<EdgeWeight>(num_vertices, false));
    v_p_graph.push_back(new MatrixWGraph<EdgeWeight>(num_vertices, false));
}

template<typename EdgeWeight, typename DistWeight>
static void TestSssp(size_t num_vertices, void (*TestFunction)(Sssp<EdgeWeight, DistWeight>*, WGraph<EdgeWeight>*)) {

    vector<Sssp<EdgeWeight, DistWeight>*> v_p_sssp;
    vector<WGraph<EdgeWeight>*> v_p_graph;
    InitSssp(v_p_sssp);
    InitWGraph(num_vertices, v_p_graph);

    for (Sssp<EdgeWeight, DistWeight> * p_sssp : v_p_sssp)
        for (WGraph<EdgeWeight> * p_graph : v_p_graph) {
            TestFunction(p_sssp, p_graph);
            //Remove all the edges
            for (Vertex v = 0; v < num_vertices; v++)
                for (Vertex w = 0; w < num_vertices; w++) p_graph->RemoveEdge(v, w);
        }

    for (Sssp<EdgeWeight, DistWeight>* p_sssp : v_p_sssp)
        delete p_sssp;
    v_p_sssp.clear();
    for (WGraph<EdgeWeight>* p_graph : v_p_graph)
        delete p_graph;
    v_p_graph.clear();
}
