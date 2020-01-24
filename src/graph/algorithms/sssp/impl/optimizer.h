#pragma once
#include "priority.h"
#include <queue>
using std::priority_queue;

namespace oods
{
    namespace oograph
    {
        template<typename DistWeight>
        class Optimizer {
        public:
            virtual void Initialize(DistWeight * arr_dist, bool * arr_collectedi, size_t num, Vertex src) = 0;
            virtual Vertex GetMinDistVertex() = 0;
            virtual void Update(Vertex v, DistWeight dist) = 0;
        protected:
            DistWeight * arr_dist_;
            bool * arr_collected_;
            size_t num_;
        };

        template<typename DistWeight>
        class NoOptimizer : public Optimizer<DistWeight> {
        public:
        };

        template<typename DistWeight>
        class HeapOptimizer : public Optimizer<DistWeight> {
        public:

        private:
            priority_queue<PriorityNode<DistWeight>, vector<PriorityNode<DistWeight>>, cmp<DistWeight>> queue_;
        };
    }

}


using namespace oods::oograph;

/* Implementation of NoOptimizer. */
template<typename DistWeight>
void NoOptimizer::Initialize(DistWeight * arr_dist, bool * arr_collected, size_t num, Vertex src) {
    this->arr_dist_ = arr_dist;
    this->arr_collected_ = arr_collected;
    this->num_ = num;
}

template<typename DistWeight>
Vertex NoOptimizer::GetMinDistVertex() {
    Vertex min = NOT_A_VERTEX;
    for (Vertex v = 0; v < this->num_; v++)
        if (!this->arr_collected_[v])
            if (min == NOT_A_VERTEX || this->arr_dist_[v] < this->arr_dist_[min]) 
                min = v;
    return min;
}

template<typename DistWeight>
void NoOptimizer::Update(Vertex v, DistWeight dist) {
    
}


/* Implementation of HeapOptimizer. */
template<typename DistWeight>
void HeapOptimizer::Initialize(DistWeight * arr_dist, bool * arr_collected, size_t num, Vertex src) {
    this->arr_dist_ = arr_dist;
    this->arr_collected_ = arr_collected;
    this->num_ = num;
    queue_.push(PriorityNode<DistWeight>(src, 0));
}

template<typename DistWeight>
Vertex HeapOptimizer::GetMinDistVertex() {
    Vertex top = NOT_A_VERTEX;
    while (!queue_.empty()) {
        top = queue_.top().v;
        queue_.pop();
        if (!this->arr_collected_[top]) break;
    }
    return top;
}

template<typename DistWeight>
void HeapOptimizer::Update(Vertex v, DistWeight dist) {
    queue_.push(PriorityNode<DistWeight>(v, dist));
}
