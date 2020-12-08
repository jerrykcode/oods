#pragma once
#include "../graph.h"
#include "matrix_w_iterator.h"
#include "matrix_unw_graph.h"

namespace oods
{
    namespace oograph
    {
        /* Implementation of WGraph<EdgeWeight> by adjacent matrix. */
        template<typename EdgeWeight>
        class MatrixWGraph : public WGraph<EdgeWeight> {
        private:
            vector<vector<MatrixNode<EdgeWeight>>> vvmatrix_;
        public:
            MatrixWGraph<EdgeWeight>(size_t num_vertices, bool is_directed) : WGraph<EdgeWeight>(num_vertices, is_directed) {
                vvmatrix_.resize(this->num_vertices_);
                for (int i = 0; i < this->num_vertices_; i++)
                    vvmatrix_[i].resize(this->num_vertices_);
            }

            ~MatrixWGraph<EdgeWeight>() {
                for (int i = 0; i < vvmatrix_.size(); i++)
                    vector<MatrixNode<EdgeWeight>>().swap(vvmatrix_[i]);
                vector<vector<MatrixNode<EdgeWeight>>>().swap(vvmatrix_);
            }

            virtual bool HasEdge(Vertex v, Vertex w);
            virtual void DoAddEdge(Edge * p_edge);
            virtual void DoRemoveEdge(Vertex v, Vertex w);
            virtual void RemoveAllEdges();
            virtual Graph * DoInverseGraph();
            virtual void AddVertex();
            virtual Iterator * CreateIterator(Vertex v);
            virtual Graph * DeepCopyGraph();
            virtual EdgeWeight GetEdgeWeight(Vertex v, Vertex w);
            virtual void DoSetEdgeWeight(Vertex v, Vertex w, EdgeWeight edge_weight);
        private:
            //This constructor initialize the graph with a matrix directly            
            //This private constructor is only used in DoInverseGraph
            //and DeepCopyGraph function
            //The vvmatrix is a reference.
            MatrixWGraph<EdgeWeight>(vector<vector<MatrixNode<EdgeWeight>>>& vvmatrix, bool is_directed) : WGraph<EdgeWeight>(vvmatrix.size(), is_directed), vvmatrix_(vvmatrix) {}
        };
    }

}

using namespace oods::oograph;

template<typename EdgeWeight>
bool MatrixWGraph<EdgeWeight>::HasEdge(Vertex v, Vertex w) {
    return vvmatrix_[v][w].has_edge;
}

template<typename EdgeWeight>
void MatrixWGraph<EdgeWeight>::DoAddEdge(Edge * p_edge) {
    Vertex v, w;
    p_edge->GetVertices(&v, &w);
    if (v < this->num_vertices_ && w < this->num_vertices_) {
        vvmatrix_[v][w].has_edge = true;
        vvmatrix_[v][w].edge_weight = ((WEdge<EdgeWeight> *)p_edge)->GetWeight();
    }
}

template<typename EdgeWeight>
void MatrixWGraph<EdgeWeight>::DoRemoveEdge(Vertex v, Vertex w) {
    if (v < this->num_vertices_ && w < this->num_vertices_) {
        vvmatrix_[v][w].has_edge = false;
    }
}

template<typename EdgeWeight>
void MatrixWGraph<EdgeWeight>::RemoveAllEdges() {
    if (this->num_edges_ == 0) return;
    for (Vertex v = 0; v < this->num_vertices_; v++)
        for (Vertex w = 0; w < this->num_vertices_; w++) {
            vvmatrix_[v][w].has_edge = false;
        }
    this->num_edges_ = 0;
}

template<typename EdgeWeight>
Graph * MatrixWGraph<EdgeWeight>::DoInverseGraph() {
    vector<vector<MatrixNode<EdgeWeight>>> vvmatrix_inverse;
    vvmatrix_inverse.resize(vvmatrix_[0].size());
    for (int i = 0; i < vvmatrix_inverse.size(); i++) {
        vvmatrix_inverse[i].resize(vvmatrix_.size());
        for (int j = 0; j < vvmatrix_inverse[i].size(); j++)
            vvmatrix_inverse[i][j] = vvmatrix_[j][i];
    }
    return (Graph *)(new MatrixWGraph<EdgeWeight>(vvmatrix_inverse, this->IsDirected()));
}

template<typename EdgeWeight>
void MatrixWGraph<EdgeWeight>::AddVertex() {
    for (int i = 0; i < vvmatrix_.size(); i++)
        vvmatrix_[i].push_back(MatrixNode<EdgeWeight>());
    this->num_vertices_++;
    vector<MatrixNode<EdgeWeight>> new_row;
    new_row.resize(this->num_vertices_);
    for (int i = 0; i < this->num_vertices_; i++)
        new_row[i] = MatrixNode<EdgeWeight>();
    vvmatrix_.push_back(new_row);
}

template<typename EdgeWeight>
Iterator * MatrixWGraph<EdgeWeight>::CreateIterator(Vertex v) {
    return (Iterator *)(new MatrixWIterator<EdgeWeight>(vvmatrix_[v]));
}

template<typename EdgeWeight>
Graph * MatrixWGraph<EdgeWeight>::DeepCopyGraph() {
    vector<vector<MatrixNode<EdgeWeight>>> vvmatrix_deepcopy;
    vvmatrix_deepcopy.resize(vvmatrix_.size());
    for (int i = 0; i < vvmatrix_deepcopy.size(); i++) {
        vvmatrix_deepcopy[i].resize(vvmatrix_[i].size());
        for (int j = 0; j < vvmatrix_deepcopy[i].size(); j++)
            vvmatrix_deepcopy[i][j] = vvmatrix_[i][j];
    }
    return (Graph *)(new MatrixWGraph(vvmatrix_deepcopy, this->IsDirected()));
}

template<typename EdgeWeight>
EdgeWeight MatrixWGraph<EdgeWeight>::GetEdgeWeight(Vertex v, Vertex w) {
    return vvmatrix_[v][w].edge_weight;
}

template<typename EdgeWeight>
void MatrixWGraph<EdgeWeight>::DoSetEdgeWeight(Vertex v, Vertex w, EdgeWeight edge_weight) {
    vvmatrix_[v][w].edge_weight = edge_weight;
}
