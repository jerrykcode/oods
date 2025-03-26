#pragma once
#include "../graph.h"
#include "list_unw_iterator.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        /* Implementation of UnwGraph by 链式前向星 */
        class FrontListUnwGraph : public UnwGraph {
        public:
            FrontListUnwGraph(size_t num_vertices, bool is_directed) : UnwGraph(num_vertices, is_directed) {
                head_.resize(num_vertices, -1);
                deleted_ = 0;
            }

            ~ListUnwGraph() {
               vector<int>().swap(head_);
               vector<int>().swap(next_);
               vector<int>().swap(to_);
            }

            virtual bool HasEdge(Vertex v, Vertex w) {
                Iterator * it = CreateIterator(v);
                while (it->Next()) {
                    if (it->GetCurrentVertex() == w) return true;
                }
                return false;
            }

            virtual void DoAddEdge(Edge * p_edge) {
                Vertex v, w;
                p_edge->GetVertices(&v, &w);
                if (v < this->num_vertices_ && w < this->num_vertices_) {
                    next_.push_back(head_[v]);
                    to_.push_back(w);
                    int cnt = next_.size() - 1;
                    head_[v] = cnt;
                }
            }

            virtual void DoRemoveEdge(Vertex v, Vertex w) {
                Iterator * it = CreateIterator(v);
                while (it->Next()) {
                    if (it->GetCurrentVertex() == w) {
                        it->RemoveCurrentElement();
                        break;
                    }
                }
            }

            virtual void RemoveAllEdges() {
                if (this->num_edges_ == 0) return;
                next_.clear();
                to_.clear();
                for (int i = 0 ; i < num_vertices_; i++) {
                    head_[i] = -1;
                }
                deleted_ = 0;
            }

            virtual Graph * DoInverseGraph() {
                FrontListUnwGraph * inverse = new FrontListUnwGraph(num_vertices_, IsDirected());
                for (Vertex v = 0; v < num_vertices_; v++) {//Traverse all vertices
                    Iterator * it = CreateIterator(v);
                    while (it->Next()) {
                        inverse->DoAddEdge(new UnwEdge(it->GetCurrentVertex(), v)); //Add inverse edge into inverse graph
                    }
                    delete it;
                }
                return (Graph *)inverse;
            }

            virtual void AddVertex() {
                head_.push_back(-1);
                num_vertices_++;
            }

            virtual Iterator * CreateIterator(Vertex v) {
                if (v < num_vertices_) {
                    return (Iterator *)(new FrontListUnwIterator(v, head_, next_, to_)); //vvlist_[v] is a vector
                }
                else return NULL;
            }

            virtual Graph * DeepCopyGraph() {
                ListUnwGraph * deep_copy = new ListUnwGraph(num_vertices_, IsDirected());
                for (Vertex v = 0; v < num_vertices_; v++) { //Traverse all the vertices
                    Iterator * it = CreateIterator(v);
                    while (it->Next()) {
                        deep_copy->DoAddEdge(new UnwEdge(v, it->GetCurrentVertex()));
                    }
                    delete it;
                }
                return (Graph *)deep_copy;
            }

        private:
            vector<int> head_, next_, to_;
            int deleted_;
        };

    }

}
