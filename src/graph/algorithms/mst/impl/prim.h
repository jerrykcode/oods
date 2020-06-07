#pragma once
#include "../mst.h"
#include <algorithm>
using std::fill;

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight, typename MstWeight>
        class Prim : public Mst<EdgeWeight, MstWeight> {
        public:
            class MstRecorder {
            public:
                virtual ~MstRecorder() {}
                virtual void Record(Vertex v, MstWeight dist) = 0;
                virtual void UpdatePre(Vertex v, Vertex pre) = 0;
                virtual MstWeight GetMstWeight() = 0;
            };

            class MstWeightRecorder : public MstRecorder {
            public:
                MstWeightRecorder() : mst_weight_(0) {}
                virtual void Record(Vertex v, MstWeight dist) { mst_weight_ += dist; }
                virtual void UpdatePre(Vertex v, Vertex pre) {}
                virtual MstWeight GetMstWeight() { return mst_weight_; }
            protected:
                MstWeight mst_weight_;
            };

            class MstTreeRecorder : public MstWeightRecorder {
            public:
                MstTreeRecorder(WGraph<EdgeWeight> *p_mst) : 
                    MstWeightRecorder(), 
                    p_mst_(p_mst),
                    arr_pre_(new Vertex[p_mst->GetNumVertices()]) {}

                ~MstTreeRecorder() {
                    free(arr_pre_);
                }

                virtual void Record(Vertex v, MstWeight dist) {
                    this->mst_weight_ += dist;
                    Edge *p_edge = (Edge *)(new WEdge<EdgeWeight>(arr_pre_[v], v, dist));
                    p_mst_->AddEdge(p_edge);
                    delete p_edge;
                }
                virtual void UpdatePre(Vertex v, Vertex pre) {
                    arr_pre_[v] = pre;
                }
            private:              
                Vertex *arr_pre_;
                WGraph<EdgeWeight> *p_mst_;
            };


            Prim() {}
            ~Prim() {}
            
            /* functions inherited form Mst<EdgeWeight, MstWeight>*/

            /*
             * @function GetMstWeight
             * Calculates the weight of the MST of the graph
             * @param p_graph    The graph
             * @param p_out_mst_weight    Pointer to the weight. This is an out parameter
             * @return bool    Returns true if the function execute successfully
             */
             virtual bool GetMstWeight(WGraph<EdgeWeight> *p_graph, EdgeWeight *p_out_mst_weight) {
                if (p_graph == NULL) return false;
                MstRecorder *p_recorder = new MstWeightRecorder();
                bool result = PrimTemplate(p_graph, p_recorder);
                if (result) *p_out_mst_weight = p_recorder->GetMstWeight();
                delete p_recorder;
                return result;
             }


            /*
             * @function GetMst
             * Calculates the MST of the graph
             * @param p_graph    The graph
             * @param p_out_mst_weight    Pointer to the weight. This is an out parameter
             * @param p_out_mst    The graph represent the mst. This is an out parameter
             * @return bool    Returns true if the function execute successfully
             */
            virtual bool GetMst(
                    WGraph<EdgeWeight> *p_graph,
                    EdgeWeight *p_out_mst_weight,
                    WGraph<EdgeWeight> *p_out_mst
                   ) 
            {
                if (p_graph == NULL || p_out_mst == NULL) return false;
                if (p_out_mst->GetNumVertices() != p_graph->GetNumVertices()) return false;
                p_out_mst->RemoveAllEdges();
                MstRecorder *p_recorder = new MstTreeRecorder(p_out_mst);
                bool result = PrimTemplate(p_graph, p_recorder);
                if (result) 
                    *p_out_mst_weight = p_recorder->GetMstWeight();
                else 
                    p_out_mst->RemoveAllEdges();
                delete p_recorder;
                return result;
            }


        public:
            bool PrimTemplate(WGraph<EdgeWeight> *p_graph, MstRecorder *p_recorder);

        protected:
            virtual Vertex GetMinDistVertex();
            virtual void UpdateVertexDist(Vertex v, MstWeight dist);
        protected:
            MstWeight *arr_dist_;
            bool *arr_calculated_;
            size_t num_vertices_;
        };
    }
}

using namespace oods::oograph;

template<typename EdgeWeight, typename MstWeight>
bool Prim<EdgeWeight, MstWeight>::PrimTemplate(WGraph<EdgeWeight> *p_graph, MstRecorder *p_recorder) {
    num_vertices_ = p_graph->GetNumVertices();
    arr_dist_ = new MstWeight[num_vertices_];
    arr_calculated_ = new bool[num_vertices_];
    fill(arr_calculated_, arr_calculated_ + num_vertices_, false);
    //select a vertex for start
    Vertex start = 0;
    arr_dist_[start] = 0;
    arr_calculated_[start] = true;
    WIterator<EdgeWeight> *it = (WIterator<EdgeWeight> *)(p_graph->CreateIterator(start));
    Vertex adj_v;
    EdgeWeight adj_weight;
    while (it->HasNext()) {
        it->Next();
        adj_v = it->GetCurrentVertex();
        adj_weight = it->GetCurrentWeight();
        UpdateVertexDist(adj_v, adj_weight);
        arr_calculated_[adj_v] = true;
        p_recorder->UpdatePre(adj_v, start);
    }
    delete it;
    
    Vertex min_dist_v;
    while ((min_dist_v = GetMinDistVertex()) != NOT_A_VERTEX) {
        p_recorder->Record(min_dist_v, arr_dist_[min_dist_v]);
        arr_dist_[min_dist_v] = 0;
        it = (WIterator<EdgeWeight> *)(p_graph->CreateIterator(min_dist_v));
        while (it->HasNext()) {
            it->Next();
            adj_v = it->GetCurrentVertex();
            adj_weight = it->GetCurrentWeight();
            if (arr_calculated_[adj_v] == false || adj_weight < arr_dist_[adj_v]) {
                UpdateVertexDist(adj_v, adj_weight);
                arr_calculated_[adj_v] = true;
                p_recorder->UpdatePre(adj_v, min_dist_v);
            }
        }
        delete it;
    }
    delete arr_dist_;
    delete arr_calculated_;
    return true;
}

template<typename EdgeWeight, typename MstWeight>
Vertex Prim<EdgeWeight, MstWeight>::GetMinDistVertex() {
    Vertex min_dist_v = NOT_A_VERTEX;
    for (Vertex v = 0; v < num_vertices_; v++) 
        if (arr_dist_[v] 
                && arr_calculated_[v] 
                && (min_dist_v == NOT_A_VERTEX || arr_dist_[v] < arr_dist_[min_dist_v])) {
            min_dist_v = v;
        }
    return min_dist_v;
}

template<typename EdgeWeight, typename MstWeight>
void Prim<EdgeWeight, MstWeight>::UpdateVertexDist(Vertex v, MstWeight dist) {
    arr_dist_[v] = dist;
}
