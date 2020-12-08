#pragma once
#include "../../graph/graph.h"
#include "path_recorder.h"

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight, typename DistWeight>
        class Sssp {
        public:
            /* @function SingleSourceShortestPath
             * Calculates the shortest distance between a single source and a destination
             * @param p_graph Pointer to the weighted graph
             * @param src The source vertex
             * @param des The destination vertex
             * @param p_out_dist Pointer to a value(DistWeight type) indicating the shortest distance between src and des. This is an 'out parameter'
             * @param p_out_recorder Pointer to a PathRecorder. This may records the shortest path. It is also an 'out parameter'
             * @return bool Returns true if this function execute successfully 
             */
            virtual bool SingleSourceShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * p_out_dist, PathRecorder * p_out_recorder) = 0;

            /* @function SingleSourceMultipleGoalShortestPath
             * Calculates the shortest distances between a single source and all other vertices
             * @param p_graph Pointer to the weighted graph
             * @param src The source vertex
             * @param arr_out_dist An array of values(DistWeight type). arr_out_dist[v] indicates the shortest distance between src and 'v'. This is an 'out parameter'.
             * @param p_out_recorder Pointer to a PathRecorder. This may records the shortest path. It is also an 'out parameter'
             * @return bool Returns true if this function execute successfully
             */
            virtual bool SingleSourceMultipleGoalShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, DistWeight * arr_out_dist, PathRecorder * p_out_recorder) = 0;

            virtual ~Sssp() {} //Virtual destructor
        };
    }
}
