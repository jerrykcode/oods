#pragma once
#include "list_unw_graph.h"
#include "matrix_unw_graph.h"
using namespace oods::oograph;

class UnwGraphCreator {
public:
    virtual UnwGraph * CreateUnwGraph(size_t num_vertices, bool is_directed) = 0;
    virtual void DeleteUnwGraph(UnwGraph *p_graph) = 0;
};

class MatrixUnwGraphCreator : public UnwGraphCreator {
public:
    virtual UnwGraph * CreateUnwGraph(size_t num_vertices, bool is_directed) {
        return (UnwGraph *)(new MatrixUnwGraph(num_vertices, is_directed));
    }
    virtual void DeleteUnwGraph(UnwGraph *p_graph) {
        delete p_graph;
    }
};

class ListUnwGraphCreator : public UnwGraphCreator {
public:
    virtual UnwGraph * CreateUnwGraph(size_t num_vertices, bool is_directed) {
        return (UnwGraph *)(new ListUnwGraph(num_vertices, is_directed));
    }
    virtual void DeleteUnwGraph(UnwGraph *p_graph) {
        delete p_graph;
    }
};
