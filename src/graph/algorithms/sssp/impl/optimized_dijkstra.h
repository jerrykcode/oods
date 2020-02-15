#pragma once
#include "dijkstra.h"
#include "priority.h"
#include <queue>
using std::priority_queue;

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight, typename DistWeight>
        class HeapOptimizedDijkstra : public Dijkstra<EdgeWeight, DistWeight> {
        protected:
            virtual void Initialize(size_t num_vertices, Vertex src);
            virtual Vertex GetMinDistVertex();
            virtual void Update(Vertex v, DistWeight dist);
            virtual void Clear();
        private:
            priority_queue<PriorityNode<DistWeight>, vector<PriorityNode<DistWeight>>, cmp<DistWeight>> queue_;
 
        };
    }

}

using namespace oods::oograph;

template<typename EdgeWeight, typename DistWeight>
void HeapOptimizedDijkstra<EdgeWeight, DistWeight>::Initialize(size_t num_vertices, Vertex src) {
    this->num_vertices_ = num_vertices;
    queue_.push(PriorityNode<DistWeight>(src, 0));
}

template<typename EdgeWeight, typename DistWeight>
Vertex HeapOptimizedDijkstra<EdgeWeight, DistWeight>::GetMinDistVertex() {
    Vertex top = NOT_A_VERTEX;
    while (!queue_.empty()) {
        top = queue_.top().v;
        queue_.pop();
        if (!this->arr_collected_[top]) break;
    }
    return top;
}

template<typename EdgeWeight, typename DistWeight>
void HeapOptimizedDijkstra<EdgeWeight, DistWeight>::Update(Vertex v, DistWeight dist) {
    queue_.push(PriorityNode<DistWeight>(v, dist));
}

template<typename EdgeWeight, typename DistWeight>
void HeapOptimizedDijkstra<EdgeWeight, DistWeight>::Clear() {
                //priority_queue<PriorityNode<DistWeight>, vector<PriorityNode<DistWeight>>>().swap(queue_);
}
