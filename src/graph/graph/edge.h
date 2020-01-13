#pragma once
#include "vertex.h"

namespace oods 
{
    namespace oograph
    {
        /* Abstract class for edge. */
        class Edge {
        public:
            Edge() {}
            Edge(Vertex v, Vertex w) : v_(v), w_(w) {}

            virtual ~Edge() {} //Virtual destructor            

            void GetVertices(Vertex * pv, Vertex * pw) {
                *pv = v_;
                *pw = w_;
            }

            virtual bool HasWeight() = 0; //Returns true if the edge has weight

            virtual Edge * InverseEdge() = 0; //Returns the inverse edge, eg. (v, w) returns (w, v)
        protected:
            Vertex v_, w_; //Two vertices of the edge
        };

        /* Implementation classes of Edge. */

        /* Unweighted edge -- edge without a weight. */
        class UnwEdge : public Edge {
        public:
            UnwEdge(Vertex v, Vertex w) : Edge(v, w) {} //Call the constructor of the base class

            ~UnwEdge() {}

            virtual bool HasWeight() {
                return false;
            }

            virtual Edge * InverseEdge() {
                return (Edge *)(new UnwEdge(w_, v_));
            }
        };


        /* Weighted edge. */
        template<typename EdgeWeight>
        class WEdge : public Edge {
        public:
            WEdge<EdgeWeight>(Vertex v, Vertex w, EdgeWeight weight) : Edge(v, w) //Call the constructor of the base class
                                                          , weight_(weight) {}

            ~WEdge() {}

            virtual bool HasWeight() {
                return true;
            }

            virtual Edge * InverseEdge() {
                return (Edge *)(new WEdge<EdgeWeight>(w_, v_, weight_));
            }

            /* Returns the weight of this edge. */
            EdgeWeight GetWeight() {
                return weight_;
            }

            /* Sets the weight of this edge. */
            void SetWeight(EdgeWeight weight) {
                weight_ = weight;
            }

        private:
            EdgeWeight weight_;
        };

    }

}
