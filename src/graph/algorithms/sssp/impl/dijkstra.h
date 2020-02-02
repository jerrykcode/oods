#pragma once
#include "../sssp.h"
#include "optimizer.h"
#include <algorithm>
using std::fill;

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight, typename DistWeight>
        class Dijkstra : public Sssp<EdgeWeight, DistWeight> {        
        public:
            Dijkstra(Optimizer<DistWeight> * p_optimizer) : p_optimizer_(p_optimizer) {}
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
            Optimizer<DistWeight> * p_optimizer_;

            /* @function _Dijkstra
             * The two virtual functions inherited from Sssp are implemented by calling this function
             * @param p_graph The pointer to the weighted graph
             * @param src The source vertex
             * @param des If des is 'NOT_A_VERTEX'(0xffffffff) then the distances between src and all other vertices needed to be 
             *  calcualted, while only the distance between src and des needed to be calcualted if des is any other number
             * @param arr_dist An array of values(DistWeight type). arr_out_dist[v] indicates the shortest distance between src 
             *  and 'v'. This is an 'out parameter'
             * @param p_out_recorder Pointer to a PathRecorder. This may records the shortest path. This is an 'out parameter'
             * @return bool Returns true if this function execute successfully
             */
            bool _Dijkstra(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * arr_out_dist, PathRecorder * p_out_recorder);
        };
    }

}

using namespace oods::oograph;

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::SingleSourceShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * p_out_dist, PathRecorder * p_out_recorder) {
    DistWeight * dist = new DistWeight[p_graph->GetNumVertices()];
    bool result = _Dijkstra(p_graph, src, des, dist, p_out_recorder);
    if (result) *p_out_dist = dist[des];
    free(dist);
    return result;
}

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::SingleSourceMultipleGoalShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, DistWeight * arr_out_dist, PathRecorder * p_out_recorder) {
    return _Dijkstra(p_graph, src, NOT_A_VERTEX, arr_out_dist, p_out_recorder);
}

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::_Dijkstra(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * arr_out_dist, PathRecorder * p_out_recorder) {
    size_t num_vertices = p_graph->GetNumVertices();
    bool * collected = new bool[num_vertices];
    fill(collected, collected + num_vertices, false);
    bool * calculated = new bool[num_vertices];
    fill(calculated, calculated + num_vertices, false);
    arr_out_dist[src] = 0;
    calculated[src] = true;
    p_optimizer_->Initialize(arr_out_dist, collected, calculated, num_vertices, src);
    Vertex min_v, adj_v;
    DistWeight tmp_dist; 
    while ((min_v = p_optimizer_->GetMinDistVertex()) != NOT_A_VERTEX) {
        collected[min_v] = true;
        if (des == min_v) {
            break;
        }
        WIterator<EdgeWeight> * it = (WIterator<EdgeWeight> *)p_graph->CreateIterator(min_v);
        while (it->HasNext()) {
            it->Next();
            if (it->GetCurrentWeight() < 0) {
                free(collected);
                free(calculated);
                return false;
            }
            adj_v = it->GetCurrentVertex();
            if (!collected[adj_v]) {
                tmp_dist = arr_out_dist[min_v] + it->GetCurrentWeight();
                if (tmp_dist < arr_out_dist[adj_v] || !calculated[adj_v]) {
                    arr_out_dist[adj_v] = tmp_dist;
                    calculated[adj_v] = true;
                    p_optimizer_->Update(adj_v, tmp_dist);
                    p_out_recorder->Update(min_v, adj_v);
                }
                else if (p_out_recorder->GetRecorderType() == ALL_PATHS_RECORDER && tmp_dist == arr_out_dist[adj_v]) {
                    p_out_recorder->Add(min_v, adj_v);
                }
            }
        }
    }
    free(collected);
    free(calculated);
    return true;
}
