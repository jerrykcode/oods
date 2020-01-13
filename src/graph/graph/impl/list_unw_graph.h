#pragma once
#include "../graph.h"
#include "list_unw_iterator.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        /* Implmentations of both UnwGraph and WGraph by adjacent list. */

        /* Implementation of UnwGraph by adjacent list*/
        class ListUnwGraph : public UnwGraph {
        public:
            ListUnwGraph(size_t num_vertices, bool is_directed) : UnwGraph(num_vertices, is_directed) {
                vvlist_.resize(num_vertices_);
            }

            ~ListUnwGraph() {
                for (int i = 0; i < vvlist_.size(); i++)
                    vector<Vertex>().swap(vvlist_[i]);
                vector<vector<Vertex>>().swap(vvlist_);
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
                    p_edge->GetVertices(&v, &w);
                    vvlist_[v].push_back(w);
                    this->num_edges_++;
                }
            }

            virtual void DoRemoveEdge(Vertex v, Vertex w) {
                Iterator * it = CreateIterator(v);
                while (it->Next()) {
                    if (it->GetCurrentVertex() == w) {
                        it->RemoveCurrentElement();
                        this->num_edges_--;
                        break;
                    }
                }
            }

            virtual Graph * DoInverseGraph() {
                ListUnwGraph * inverse = new ListUnwGraph(num_vertices_, IsDirected());
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
                vector<Vertex> vlist;
                vvlist_.push_back(vlist);
                num_vertices_++;
            }

            virtual Iterator * CreateIterator(Vertex v) {
                if (v < num_vertices_) {
                    return (Iterator *)(new ListUnwIterator(vvlist_[v])); //vvlist_[v] is a vector
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
            vector<vector<Vertex>> vvlist_; //vector of vector
        };

    }

}
