#pragma once
#include "../../graph/graph.h"

namespace oods 
{
    namespace oograph
    {
        template<typename EdgeWeight, typename MstWeight>
        class Mst {
        public:
            /*
             * @function GetMstWeight
             * Calculates the weight of the MST of the graph
             * @param p_graph    The graph
             * @param p_out_mst_weight    Pointer to the weight. This is an out parameter
             * @return bool    Returns true if the function execute successfully
             */
            virtual bool GetMstWeight(WGraph<EdgeWeight> *p_graph, EdgeWeight *p_out_mst_weight) = 0;
            
            
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
                 ) = 0;

            virtual ~Mst() {} //Virtual destructor
        };
    }
}
