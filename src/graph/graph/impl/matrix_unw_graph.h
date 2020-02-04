#pragma once
#include "../graph.h"
#include "matrix_unw_iterator.h"
#include <vector>
#include <algorithm>
using std::vector;

namespace oods
{
    namespace oograph
    {
        /* Implementation of UnwGraph by adjacent matrix. */
        class MatrixUnwGraph : public UnwGraph {
        protected:
            vector<vector<bool>> vvmatrix_;
        public:
            MatrixUnwGraph(size_t num_vertices, bool is_directed) : UnwGraph(num_vertices, is_directed) {
                vvmatrix_.resize(num_vertices_);
                for (int i = 0; i < num_vertices_; i++) {
                    vvmatrix_[i].resize(num_vertices_);
                    std::fill(vvmatrix_[i].begin(), vvmatrix_[i].end(), false);
                }
            }

            ~MatrixUnwGraph() {
                for (int i = 0; i < vvmatrix_.size(); i++)
                    vector<bool>().swap(vvmatrix_[i]);
                vector<vector<bool>>().swap(vvmatrix_);
            }

            virtual bool HasEdge(Vertex v, Vertex w) {
                return vvmatrix_[v][w];
            }

            virtual void DoAddEdge(Edge * p_edge) {
                Vertex v, w;
                p_edge->GetVertices(&v, &w);
                if (v < this->num_vertices_ && w < this->num_vertices_) {
                    vvmatrix_[v][w] = true;
                    this->num_edges_++;
                }
            }

            virtual void DoRemoveEdge(Vertex v, Vertex w) {
                if (v < this->num_vertices_ && w < this->num_vertices_) {
                    vvmatrix_[v][w] = false;
                    this->num_edges_--;
                }
            }

            virtual Graph * DoInverseGraph() {
                vector<vector<bool>> vvmatrix_inverse;
                vvmatrix_inverse.resize(vvmatrix_[0].size());
                for (int i = 0 ; i < vvmatrix_inverse.size(); i++) {
                    vvmatrix_inverse[i].resize(vvmatrix_.size());
                    for (int j = 0; j < vvmatrix_.size(); j++)
                        vvmatrix_inverse[i][j] = vvmatrix_[j][i];
                }
                MatrixUnwGraph * p_graph = new MatrixUnwGraph(vvmatrix_inverse, IsDirected());
                return (Graph *)p_graph;
            }

            virtual void AddVertex() {
                num_vertices_++;
                for (int i = 0; i < vvmatrix_.size(); i++)
                    vvmatrix_[i].push_back(false);
                vector<bool> vrow;
                vrow.resize(num_vertices_);
                std::fill(vrow.begin(), vrow.end(), false);
                vvmatrix_.push_back(vrow);
            }

            virtual Iterator * CreateIterator(Vertex v) {
                if (v < num_vertices_)
                    return (Iterator *)(new MatrixUnwIterator(vvmatrix_[v]));
                return NULL;
            }

            virtual Graph * DeepCopyGraph() {
                vector<vector<bool>> vvmatrix_deepcopy;
                vvmatrix_deepcopy.resize(vvmatrix_.size());
                for (int i = 0; i < vvmatrix_deepcopy.size(); i++) {
                    vvmatrix_deepcopy[i].resize(vvmatrix_[i].size());
                    for (int j = 0; j < vvmatrix_deepcopy[i].size(); j++)
                        vvmatrix_deepcopy[i][j] = vvmatrix_[i][j];
                }
                return (Graph *)(new MatrixUnwGraph(vvmatrix_deepcopy, IsDirected()));
            }

        private:
            MatrixUnwGraph(vector<vector<bool>>& vvmatrix, bool is_directed) : UnwGraph(vvmatrix.size(), is_directed),
                                                                               vvmatrix_(vvmatrix) {}
        };
    }

}
