#pragma once    
#include "wgraphcreator.h"
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
static void InitWGraphCreator(vector<WGraphCreator<EdgeWeight>*>& v_p_graph) {
    v_p_graph.push_back(new ListWGraphCreator<EdgeWeight>());
    v_p_graph.push_back(new MatrixWGraphCreator<EdgeWeight>());
}

template<typename EdgeWeight, typename DistWeight>
static void TestSssp(void (*TestFunction)(Sssp<EdgeWeight, DistWeight>*, WGraphCreator<EdgeWeight>*)) {

    vector<Sssp<EdgeWeight, DistWeight>*> v_p_sssp;
    vector<WGraphCreator<EdgeWeight>*> v_p_graph_creator;
    InitSssp(v_p_sssp);
    InitWGraphCreator(v_p_graph_creator);

    for (Sssp<EdgeWeight, DistWeight> * p_sssp : v_p_sssp)
        for (WGraphCreator<EdgeWeight> * p_graph_creator : v_p_graph_creator) {
            TestFunction(p_sssp, p_graph_creator);
        }

    for (Sssp<EdgeWeight, DistWeight>* p_sssp : v_p_sssp)
        delete p_sssp;
    v_p_sssp.clear();
    for (WGraphCreator<EdgeWeight>* p_graph_creator : v_p_graph_creator)
        delete p_graph_creator;
    v_p_graph_creator.clear();
}
