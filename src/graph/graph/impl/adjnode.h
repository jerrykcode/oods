#pragma once
#include "../vertex.h"

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight>
        struct AdjNode {
            Vertex v;
            EdgeWeight weight;
            AdjNode(Vertex v, EdgeWeight weight) : v(v), weight(weight) {} 
        };
    }
}
