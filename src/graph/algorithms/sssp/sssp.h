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
            virtual bool SingleSourceShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, DistWeight * p_out__dist, PathRecorder * p_out_recorder) = 0;
            virtual bool SingleSourceMultpleGoalShortestPath(WGraph<EdgeWeight> * p_graph, Vertex src, DistWeight * arr_out_dist, PathRecorder * p_out_recorder) = 0;
        };
    }
}
