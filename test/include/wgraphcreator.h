#pragma once
#include "list_w_graph.h"
#include "matrix_w_graph.h"
using namespace oods::oograph;

template<typename EdgeWeight>
class WGraphCreator {
public:
    virtual WGraph<EdgeWeight>* CreateWGraph(size_t num_vertices, bool is_directed) = 0;
    virtual void DeleteWGraph(WGraph<EdgeWeight> *p_graph) = 0;
};

template<typename EdgeWeight>
class MatrixWGraphCreator : public WGraphCreator<EdgeWeight> {
public:
    virtual WGraph<EdgeWeight> * CreateWGraph(size_t num_vertices, bool is_directed) {
        return (WGraph<EdgeWeight>*)(new MatrixWGraph<EdgeWeight>(num_vertices, is_directed));
    }
    virtual void DeleteWGraph(WGraph<EdgeWeight> *p_graph) {
        delete p_graph;
    }
};

template<typename EdgeWeight>
class ListWGraphCreator : public WGraphCreator<EdgeWeight> {
public:
    virtual WGraph<EdgeWeight> * CreateWGraph(size_t num_vertices, bool is_directed) {
        return (WGraph<EdgeWeight>*)(new ListWGraph<EdgeWeight>(num_vertices, is_directed));
    }
    virtual void DeleteWGraph(WGraph<EdgeWeight> *p_graph) {
        delete p_graph;
    }
};
