#pragma once

#include "edge.h"
#include "iterator.h"
#include <cstdlib>

namespace oods
{
    namespace oograph
    {

        /* Graph abstract class. */
        class Graph {
        public:
            size_t GetNumVertices() {
                return num_vertices_;
            }
            size_t GetNumEdges() {
                return num_edges_;
            }
            bool IsDirected() {
                return p_direction_->IsDirected();
            }
            
            //Add an edge.
            void AddEdge(Edge * p_edge) {
               p_direction_->AddEdge(this, p_edge);
            }

            //Remove an edge
            void RemoveEdge(Vertex v, Vertex w) {
                p_direction_->RemoveEdge(this, v, w);
            }

            //Get the inverse of this graph.
            Graph * InverseGraph() {
                return p_direction_->InverseGraph(this);
            }

            /*
             * Difference between AddEdge and DoAddEdge:
             *
             * With edge(v, w) as an example, 
             * AddEdge function adds only one edge(v, w) into the graph if the graph is directed, while adds both the edge(v, w) 
             * and the inverse(w, v) for undirected graph.
             *
             * DoAddEdge function just adds one edge(v, w) into the graph without considering wether the graph is directed.
             *
             * For all graph(no matter how it's implemented), AddEdge should call DoAddEdge twice for undirected case while call 
             * it once for directed case, and this is implemented by calling the AddEdge function defined by Direction abstract class. 
             * The subclasses  of Direction encapsulates the details about how to calling OnAddEdge function for both directed and 
             * undirected cases.
             *
             * DoAddEdge is pure virtual function because it actually adds an edge into the graph and this procedure is different 
             * according to different graph implementations.
             *
             * 
             * Difference between RemoveEdge and DoRemoveEdge:
             * For directed graph, only one edge is removed while for undirected case both the edge and the inverse of this edge would
             * be removed. DoRemoveEdge just removes one edge from the graph while RemoveEdge acts differently according to whether the
             * graph is directed.             
             *
             * Difference between InverseGraph and DoInverseGraph:
             *
             * Create the inverse of a graph needs to handle the inverse of all the original edges for directed graph while for 
             * undirected graph, the inverse of it is just as the same and a deep copy is enough. InverseGraph function just calls 
             * the function defined in Direction abstract class, and the subclasses of Direction encapsulates the details about 
             * calling DoInverseGraph for directed case or DeepCopyGraph for undirected case.
             *
             * DoInverseGraph is also pure virtual.
             */
            virtual bool HasEdge(Vertex v, Vertex w) = 0;
            virtual void DoAddEdge(Edge * p_edge) = 0;
            virtual void DoRemoveEdge(Vertex v, Vertex w) = 0;
            virtual Graph * DoInverseGraph() = 0;
           
            /* Add a new vertex into the graph. Original vertices are numbered from 0 to num_vertices_ - 1 and the new one is numbered num_vertice_. */ 
            virtual void AddVertex() = 0;
            
            virtual bool IsWeighted() = 0; //Returned true of the graph is weighted.
            virtual Iterator * CreateIterator(Vertex v) = 0; //Create an iterator for adjacent nodes of a vertex.
            virtual Graph * DeepCopyGraph() = 0; //Return the deep copy of the graph.
          
            Graph(size_t num_vertices, bool is_directed) : num_vertices_(num_vertices), num_edges_(0) {
            }
            
            virtual ~Graph() {
                delete p_direction_;
            } //Virtual destructor
        protected:

            size_t num_vertices_;
            size_t num_edges_;

        protected:
            /* Abstarct class. Defines the direction of a graph. */
            class Direction {
            public:
                virtual bool IsDirected() = 0;
                virtual void AddEdge(Graph * p_graph, Edge * p_egde) = 0;
                virtual void RemoveEdge(Graph * p_graph, Vertex v, Vertex w) = 0;
                virtual Graph * InverseGraph(Graph * p_graph) = 0;
                virtual ~Direction() {}
            };

            /* Implementations of Direction. */
            class DirectedType : public Direction {
            private:
            public:
                DirectedType() {}
                ~DirectedType() {}
                virtual bool IsDirected() {
                    return true;
                }
                
                virtual void AddEdge(Graph * p_graph, Edge * p_edge) {
                    p_graph->DoAddEdge(p_edge);
                }

                virtual void RemoveEdge(Graph * p_graph, Vertex v, Vertex w) {
                    p_graph->DoRemoveEdge(v, w);
                }

                virtual Graph * InverseGraph(Graph * p_graph) {
                    return p_graph->DoInverseGraph();
                }

            };

            class UnDirectedType : public Direction {
            public:
                UnDirectedType() {}; 
                ~UnDirectedType() {}

                virtual bool IsDirected() {
                     return false;
                }

                virtual void AddEdge(Graph * p_graph, Edge * p_edge) {
                    p_graph->DoAddEdge(p_edge);
                    Edge * inverse = p_edge->InverseEdge();
                    p_graph->DoAddEdge(inverse);
                    delete inverse;
                }

                virtual void RemoveEdge(Graph * p_graph, Vertex v, Vertex w) {
                    p_graph->DoRemoveEdge(v, w);
                    p_graph->DoRemoveEdge(w, v);
                }

                virtual Graph * InverseGraph(Graph * p_graph) {
                    return p_graph->DeepCopyGraph();
                }
            };

        protected:
            
            Direction * p_direction_;

        };


        /* Unweight graph. 
         * This is also an abstract class. */
        class UnwGraph : public Graph {
        public:

            UnwGraph(size_t num_vertices, bool is_directed) : Graph(num_vertices, is_directed) {
                p_direction_ = is_directed ? ((Direction *) new DirectedType()) : ((Direction *)new UnDirectedType());
            }
            virtual ~UnwGraph() {} //Virtual destructor

            virtual bool IsWeighted() { return false; }
        };


        /* Weighted graph.
         * This is also an abstract class. */
        template<typename EdgeWeight>
        class WGraph : public Graph {
        public:
            WGraph(size_t num_vertices, bool is_directed) : Graph(num_vertices, is_directed) {
                if (is_directed) {
                    WDirectedType * p = new WDirectedType();
                    p_direction_ = (Direction *)p;
                    p_w_direction_ = (WDirection *)p;
                }
                else {
                    WUnDirectedType * p = new WUnDirectedType();
                    p_direction_ = (Direction *)p;
                    p_w_direction_ = (WDirection *)p;
                }
            }
            virtual ~WGraph<EdgeWeight>() {} //Virtual destructor

            virtual bool IsWeighted() { return true; }

            virtual EdgeWeight GetEdgeWeight(Vertex v, Vertex w) = 0;
            void SetEdgeWeight(Vertex v, Vertex w, EdgeWeight edge_weight) {
                p_w_direction_->SetEdgeWeight(this, v, w, edge_weight);
            }

            virtual void DoSetEdgeWeight(Vertex v, Vertex w, EdgeWeight edge_weight) = 0;

        protected:
            class WDirection {
            public:
                virtual void SetEdgeWeight(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) = 0; 
                virtual ~WDirection() {}
            };

            class WDirectedType : public DirectedType, public WDirection {
            public:
   
                virtual ~WDirectedType() {}

                virtual void SetEdgeWeight(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
                    p_graph->DoSetEdgeWeight(v, w, edge_weight);
                }
            };

            class WUnDirectedType : public UnDirectedType, public WDirection {

                virtual ~WUnDirectedType() {}

                virtual void SetEdgeWeight(WGraph<EdgeWeight> * p_graph, Vertex v, Vertex w, EdgeWeight edge_weight) {
                    p_graph->DoSetEdgeWeight(v, w, edge_weight);
                    p_graph->DoSetEdgeWeight(w, v, edge_weight);
                }
            };
        protected:
            WDirection * p_w_direction_;
        };

    }

}
