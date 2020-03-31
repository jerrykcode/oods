#pragma once
#include "../graph.h"
#include "list_w_iterator.h"
#include "adjnode.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight>
        class ListWGraph : public WGraph<EdgeWeight> {
        private:
            /* Adjacent list of a vertex(say, the vertex is v, for example) in an unweighted graph stores all the vertices 
             * adjacent to v, but if v is in a weighted graph, then the weights of the edges between v and all the adjacent 
             * vertices should also be stored. And these information are stored in a structure named AdjNode.*/
            vector<vector<AdjNode<EdgeWeight>>> vvlist_; //Similar to what we have used in ListUnwGraph, but the element type is AdjNode in this case
        public:
            ListWGraph<EdgeWeight>(size_t num_vertices, bool is_directed) : WGraph<EdgeWeight>(num_vertices, is_directed) {
                vvlist_.resize(num_vertices);
            }

            ~ListWGraph<EdgeWeight>() {
                for (int i = 0; i < vvlist_.size(); i++)
                    vector<AdjNode<EdgeWeight>>().swap(vvlist_[i]);
                vector<vector<AdjNode<EdgeWeight>>>().swap(vvlist_);
            }

            virtual bool HasEdge(Vertex v, Vertex w);
            virtual void DoAddEdge(Edge * p_edge);
            virtual void DoRemoveEdge(Vertex v, Vertex w);
            virtual Graph * DoInverseGraph();
            virtual void AddVertex();
            virtual Iterator * CreateIterator(Vertex v);
            virtual Graph * DeepCopyGraph();
            virtual EdgeWeight GetEdgeWeight(Vertex v, Vertex w);
            virtual void DoSetEdgeWeight(Vertex v, Vertex w, EdgeWeight edge_weight);

        private:
            //This constructor initialize the graph with a list directly
            //Note : the vvlist is not a reference but a deep copy
            //This constructor is only used in DeepCopyGraph function
            ListWGraph<EdgeWeight>(vector<vector<AdjNode<EdgeWeight>>> vvlist, bool is_directed) : WGraph<EdgeWeight>(vvlist.size(), is_directed),
                                                                                vvlist_(vvlist) {}
        };
    }

}

//Implementations
//tmplates can only be write in the same file
using namespace oods::oograph;

template<typename EdgeWeight>
bool ListWGraph<EdgeWeight>::HasEdge(Vertex v, Vertex w) {
    Iterator * it = CreateIterator(v);
    while (it->Next()) {
        if (it->GetCurrentVertex() == w) {
            return true;
        }
    }
    return false;
}

template<typename EdgeWeight>
void ListWGraph<EdgeWeight>::DoAddEdge(Edge * p_edge) {
    if (!p_edge->HasWeight()) return;
    Vertex v, w;
    p_edge->GetVertices(&v, &w);
    if (v < this->num_vertices_ && w < this->num_vertices_) {
        vvlist_[v].push_back(AdjNode<EdgeWeight>(w, ((WEdge<EdgeWeight> *)(p_edge))->GetWeight()));
        this->num_edges_++;
    } 
}

template<typename EdgeWeight>
void ListWGraph<EdgeWeight>::DoRemoveEdge(Vertex v, Vertex w) {
    Iterator * it = CreateIterator(v);
    while (it->Next()) {
        if (it->GetCurrentVertex() == w) {
            it->RemoveCurrentElement();
            this->num_edges_--;
            break;
        }
    }
}

template<typename EdgeWeight>
Graph * ListWGraph<EdgeWeight>::DoInverseGraph() {
    WGraph<EdgeWeight> * inverse = new ListWGraph<EdgeWeight>(this->num_vertices_, this->IsDirected());
    for (Vertex v = 0; v < this->num_vertices_; v++) { //Traverse vertices
        WIterator<EdgeWeight> * it = (WIterator<EdgeWeight> *)(CreateIterator(v));
        while (it->Next()) {
            inverse->DoAddEdge((Edge *)(new WEdge<EdgeWeight>(it->GetCurrentVertex(), v, it->GetCurrentWeight())));
        }
    }
    return (Graph *)inverse;
}

template<typename EdgeWeight>
void ListWGraph<EdgeWeight>::AddVertex() {
    vector<AdjNode<EdgeWeight>> vlist;
    vvlist_.push_back(vlist);
    this->num_vertices_++;
}

template<typename EdgeWeight>
Iterator * ListWGraph<EdgeWeight>::CreateIterator(Vertex v) {
    vector<AdjNode<EdgeWeight>>& vlist = vvlist_[v];
    return (Iterator *)(new ListWIterator<EdgeWeight>(vlist));
}

template<typename EdgeWeight>
Graph * ListWGraph<EdgeWeight>::DeepCopyGraph() {
    return (Graph *)(new ListWGraph<EdgeWeight>(vvlist_, this->IsDirected()));
}

template<typename EdgeWeight>
EdgeWeight ListWGraph<EdgeWeight>::GetEdgeWeight(Vertex v, Vertex w) {
    WIterator<EdgeWeight> * it = (WIterator<EdgeWeight> *)CreateIterator(v);
    while (it->Next()) {
        if (it->GetCurrentVertex() == w) {
            EdgeWeight result = it->GetCurrentWeight();
            delete it;
            return result;
        }
    }
    return EdgeWeight(0);
}

template<typename EdgeWeight>
void ListWGraph<EdgeWeight>::DoSetEdgeWeight(Vertex v, Vertex w, EdgeWeight edge_weight) {
    WIterator<EdgeWeight> * it = (WIterator<EdgeWeight> *)CreateIterator(v);
    while (it->Next()) {
        if (it->GetCurrentVertex() == w) {
            it->SetCurrentWeight(edge_weight);
            delete it;
            return;
        }
    }
}
