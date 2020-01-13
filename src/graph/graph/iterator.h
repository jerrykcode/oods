#pragma once
#include "vertex.h"
#include <cstdlib>

namespace oods
{
    namespace oograph {

        /* Iterator use to iterate all the adjacent vertices of a vertex. 
         * usage: (to traverse all the adjacent vertices of a vertex v in graph)
         *
         *     Iterator * it = graph.CreateIterator(v); 
         *     while (it->HasNext()) {
         *         it->Next();
         *         Vertex w = it->GetCurrentVertex(); //w is an adjacent vertex of v
         *     }
         *     delete it;
         *
         * or more simple:
         *
         *     Iterator * it = graph.CreateIterator(v);
         *     while (it->Next()) {
         *         Vertex w = it->GetCurrentVertex(); //w is an adjacent vertex of v
         *     }
         *     delete it;
         *
         * Iterator is an abstract class. */
        class Iterator {
        public:
            virtual bool HasNext() = 0;
            virtual bool Next() = 0;
            virtual Vertex GetCurrentVertex() = 0;
            virtual void RemoveCurrentElement() = 0; 
            virtual ~Iterator() {} //Virtual destructor
        };
        
        /* WIterator<EdgeWeight> Iterator for weighted graphs.
         * This is also an abstract class 
         * usage for WIterator<EdgeWeight>
         *
         *     WIterator<EdgeWeight> * it = (WIterator<EdgeWeight> *)graph.CreateIterator(); //graph is weighted graph
         *     while (it->HasNext()) {
         *         it->Next();
         *         Vertex w = it->GetCurrentVertex(); //w is an adjacent vertex of v
         *         EdgeWight weight = it->GetCurrentWeight(); //the weight of edge between v and w
         *         it->SetCurrentWeight(0); //You can set the weight of edge between v and w to any value;
         *     } 
         *     delete it;
         *
         */

        template<typename EdgeWeight>
        class WIterator : public Iterator {
        public:
            virtual EdgeWeight GetCurrentWeight() = 0;
            virtual void SetCurrentWeight(EdgeWeight edge_weight) = 0;
        };

    }

}
