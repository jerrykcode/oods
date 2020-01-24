#pragma once
#include "../../../graph/vertex.h"

namespace oods
{
    namespace oograph
    {
        template<typename DistWeight>
        struct PriorityNode {
            Vertex v;
            DistWeight priority_dist;
            PriorityNode(Vertex v, DistWeight priority_dist) : v(v), priority_dist(priority_dist) {}
        };

        template<typename DistWeight>
        struct cmp {
            bool operator () (PriorityNode<DistWeight>& a, PriorityNode<DistWeight>& b) {
                return a.priority_dist > b.priority_dist;
            }
        };
    }
}
