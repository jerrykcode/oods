#pragma once    
#include "unwgraphcreator.h"
#include "wgraphcreator.h"
#include "dijkstra.h"
#include "optimized_dijkstra.h"
#include "prim.h"
#include "optimized_prim.h"
#include "tarjan.h"
#include <vector>
using namespace oods::oograph;
using std::vector;

static void InitUnwGraphCreator(vector<UnwGraphCreator*>& v_p_unwgraph_creator) {
    v_p_unwgraph_creator.push_back(new MatrixUnwGraphCreator());
    v_p_unwgraph_creator.push_back(new ListUnwGraphCreator());
}

template<typename EdgeWeight, typename DistWeight>
static void InitSssp(vector<Sssp<EdgeWeight, DistWeight>*>& v_p_sssp) {
    v_p_sssp.push_back(new Dijkstra<EdgeWeight, DistWeight>());
    v_p_sssp.push_back(new HeapOptimizedDijkstra<EdgeWeight, DistWeight>());
}

template<typename EdgeWeight>
static void InitWGraphCreator(vector<WGraphCreator<EdgeWeight>*>& v_p_wgraph_creator) {
    v_p_wgraph_creator.push_back(new ListWGraphCreator<EdgeWeight>());
    v_p_wgraph_creator.push_back(new MatrixWGraphCreator<EdgeWeight>());
}

template<typename EdgeWeight, typename MstWeight>
static void InitMst(vector<Mst<EdgeWeight, MstWeight>*>& v_p_mst) {
    v_p_mst.push_back(new Prim<EdgeWeight, MstWeight>());
    v_p_mst.push_back(new HeapOptimizedPrim<EdgeWeight, MstWeight>());
}

//test graph
static void TestUnwGraph(void (*TestFunction)(UnwGraphCreator*)) {
    vector<UnwGraphCreator*> v_p_unwgraph_creator;
    InitUnwGraphCreator(v_p_unwgraph_creator);
    for (UnwGraphCreator *p_unwgraph_creator : v_p_unwgraph_creator) {
        TestFunction(p_unwgraph_creator);
        delete p_unwgraph_creator;
    }
    v_p_unwgraph_creator.clear();
}

template<typename EdgeWeight>
static void TestWGraph(void (*TestFunction)(WGraphCreator<EdgeWeight>*)) {
    vector<WGraphCreator<EdgeWeight>*> v_p_wgraph_creator;
    InitWGraphCreator(v_p_wgraph_creator);
    for (WGraphCreator<EdgeWeight> *p_wgraph_creator : v_p_wgraph_creator) {
        TestFunction(p_wgraph_creator);
        delete p_wgraph_creator;
    }
    v_p_wgraph_creator.clear();
}

//test sssp
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

//test mst
template<typename EdgeWeight, typename MstWeight>
static void TestMst(void (*TestFunction)(Mst<EdgeWeight, MstWeight>*, WGraphCreator<EdgeWeight>*)) {
    vector<Mst<EdgeWeight, MstWeight>*> v_p_mst;
    vector<WGraphCreator<EdgeWeight>*> v_p_wgraph_creator;
    InitMst(v_p_mst);
    InitWGraphCreator(v_p_wgraph_creator);
    for (Mst<EdgeWeight, MstWeight> *p_mst : v_p_mst) {
        for (WGraphCreator<EdgeWeight> *p_w_graph_creator : v_p_wgraph_creator) {
            TestFunction(p_mst, p_w_graph_creator);
        }
    }
    for (Mst<EdgeWeight, MstWeight> *p_mst : v_p_mst)
        delete p_mst;
    v_p_mst.clear();
    for (WGraphCreator<EdgeWeight>* p_wgraph_creator: v_p_wgraph_creator)
        delete p_wgraph_creator;
    v_p_wgraph_creator.clear();
}

//test scc
static void TestScc(void (*TestFunction)(Scc*, UnwGraphCreator*)) {
    vector<UnwGraphCreator*> v_p_creator;
    InitUnwGraphCreator(v_p_creator);
    Scc *p_scc = new Tarjan();
    for (UnwGraphCreator *p_creator : v_p_creator) {
        TestFunction(p_scc, p_creator);
    }
    for (UnwGraphCreator *p_creator : v_p_creator) 
        delete p_creator;
    v_p_creator.clear();
    delete p_scc;
}
