#pragma once
#include "../sssp.h"
#include <algorithm>
using std::fill;

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight, typename DistWeight>
        class Dijkstra : public Sssp<EdgeWeight, DistWeight> {        
        public:
            Dijkstra() {}
            ~Dijkstra() {}

            //Inherits from Sssp

            /* @function SingleSourceShortestPath
             * Calculates the shortest distance between a single source and a destination
             * @param p_graph Pointer to the weighted graph
             * @param src The source vertex
             * @param des The destination vertex
             * @param p_out_dist Pointer to a value(DistWeight type) indicating the shortest distance between src and des. 
             *  This is an 'out parameter'
             * @param p_out_recorder Pointer to a PathRecorder. This may records the shortest path. It is also an 
             *  'out parameter'
             * @return bool Returns true if this function execute successfully 
             */ 
            virtual bool SingleSourceShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * p_out_dist, PathRecorder * p_out_recorder);

            /* @function SingleSourceMultipleGoalShortestPath
             * Calculates the shortest distances between a single source and all other vertices
             * @param p_graph Pointer to the weighted graph
             * @param src The source vertex
             * @param arr_out_dist An array of values(DistWeight type). arr_out_dist[v] indicates the shortest distance between src 
             *  and 'v'. This is an 'out parameter'
             * @param p_out_recorder Pointer to a PathRecorder. This may records the shortest path. It is also an 'out parameter'
             * @return bool Returns true if this function execute successfully
             */ 
            virtual bool SingleSourceMultipleGoalShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, DistWeight * arr_out_dist, PathRecorder * p_out_recorder);

        private:

            /* @function _Dijkstra
             * The two virtual functions inherited from Sssp are implemented by calling this private function
             * @param p_graph The pointer to the weighted graph
             * @param src The source vertex
             * @param des If des is 'NOT_A_VERTEX'(0xffffffff) then the distances between src and all other vertices needed to be 
             *  calcualted, while only the distance between src and des needed to be calcualted if des is any other number
             * @param p_out_recorder Pointer to a PathRecorder. This may records the shortest path. This is an 'out parameter'
             * @return bool Returns true if this function execute successfully
             */
            bool _Dijkstra(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, PathRecorder * p_out_recorder);

        protected:
            virtual void Initialize(size_t num_vertices, Vertex src);
            virtual Vertex GetMinDistVertex();
            virtual void Update(Vertex v, DistWeight dist);
            virtual void Clear();

            bool * arr_collected_;
            bool * arr_calculated_;
            DistWeight * arr_dist_;
            size_t num_vertices_;
        };
    }

}

using namespace oods::oograph;

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::SingleSourceShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * p_out_dist, PathRecorder * p_out_recorder) {
    arr_dist_ = new DistWeight[p_graph->GetNumVertices()];
    bool result = _Dijkstra(p_graph, src, des, p_out_recorder);
    if (result) *p_out_dist = arr_dist_[des];
    free(arr_dist_);
    return result;
}

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::SingleSourceMultipleGoalShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, DistWeight * arr_out_dist, PathRecorder * p_out_recorder) {
    arr_dist_ = arr_out_dist;
    return _Dijkstra(p_graph, src, NOT_A_VERTEX, p_out_recorder);
}

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::_Dijkstra(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, PathRecorder * p_out_recorder) {
    size_t num_vertices = p_graph->GetNumVertices();
    arr_collected_ = new bool[num_vertices];
    fill(arr_collected_, arr_collected_ + num_vertices, false);
    arr_calculated_ = new bool[num_vertices];
    fill(arr_calculated_, arr_calculated_ + num_vertices, false);
    arr_dist_[src] = DistWeight(0);
    arr_calculated_[src] = true;
    Initialize(num_vertices, src);
    Vertex min_v, adj_v;
    DistWeight tmp_dist; 
    while ((min_v = GetMinDistVertex()) != NOT_A_VERTEX) {
        arr_collected_[min_v] = true;
        if (des == min_v) {
            break;
        }
        WIterator<EdgeWeight> * it = (WIterator<EdgeWeight> *)p_graph->CreateIterator(min_v);
        while (it->HasNext()) {
            it->Next();
            if (it->GetCurrentWeight() < 0) {
                free(arr_collected_);
                free(arr_calculated_);
                return false;
            }
            adj_v = it->GetCurrentVertex();
            if (!arr_collected_[adj_v]) {
                tmp_dist = arr_dist_[min_v] + it->GetCurrentWeight();
                if (tmp_dist < arr_dist_[adj_v] || !arr_calculated_[adj_v]) {
                    arr_dist_[adj_v] = tmp_dist;
                    arr_calculated_[adj_v] = true;
                    Update(adj_v, tmp_dist);
                    p_out_recorder->Update(min_v, adj_v);
                }
                else if (p_out_recorder->GetRecorderType() == ALL_PATHS_RECORDER && tmp_dist == arr_dist_[adj_v]) {
                    p_out_recorder->Add(min_v, adj_v);
                }
            }
        }
        p_graph->CloseIterator(it);
    }
    free(arr_collected_);
    free(arr_calculated_);
    Clear();
    return true;
}

template<typename EdgeWeight, typename DistWeight>
void Dijkstra<EdgeWeight, DistWeight>::Initialize(size_t num_vertices, Vertex src) {
    this->num_vertices_ = num_vertices;
}

template<typename EdgeWeight, typename DistWeight>
Vertex Dijkstra<EdgeWeight, DistWeight>::GetMinDistVertex() {
    Vertex min = NOT_A_VERTEX;
    for (Vertex v = 0; v < num_vertices_; v++)
        if (!arr_collected_[v] && arr_calculated_[v])
            if (min == NOT_A_VERTEX || arr_dist_[v] < arr_dist_[min]) 
                min = v;
    return min;
}

template<typename EdgeWeight, typename DistWeight>
void Dijkstra<EdgeWeight, DistWeight>::Update(Vertex v, DistWeight dist) {
    //Nothing to do in here
}

template<typename EdgeWeight, typename DistWeight>
void Dijkstra<EdgeWeight, DistWeight>::Clear() {
    //Nothing to do in here
}
