#pragma once

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight>
        struct MatrixNode {
            bool has_edge;
            EdgeWeight edge_weight;
            MatrixNode() : has_edge(false) {}
            MatrixNode(bool has_edge, EdgeWeight edge_weight) : has_edge(has_edge), edge_weight(edge_weight) {}
        };

    }

}

