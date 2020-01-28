#pragma once
#include "../sssp.h"
#include "optimizer.h"

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight, DistWeight>
        class Dijkstra : public Sssp<EdgeWeight, DistWeight> {        
        public:
            Dijkstra(Optimizer * p_optimizer) : p_optimizer_(p_optimizer) {}
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
            virtual bool SingleSourceMultpleGoalShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, DistWeight * arr_out_dist, PathRecorder * p_out_recorder);

        private:
            Optimizer * p_optimizer_;

            /* @function dijkstra
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
            bool dijkstra(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * arr_out_dist, PathRecorder * p_out_recorder);
        };
    }

}

using namespace oods::oograph;
bool 
