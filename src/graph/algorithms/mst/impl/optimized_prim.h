#pragma once
#include "prim.h"
#include "../../sssp/impl/priority.h"
#include <queue>
using std::priority_queue;

namespace oods{
    namespace oograph {
        template<typename EdgeWeight, typename MstWeight>
        class HeapOptimizedPrim : public Prim<EdgeWeight, MstWeight> {
        public:
            HeapOptimizedPrim() {}
            ~HeapOptimizedPrim() {
                //delete queue
            }
        protected:
            virtual Vertex GetMinDistVertex() {
                Vertex min_dist_v;
                while (!queue_.empty()) {
                    min_dist_v = queue_.top().v;
                    queue_.pop();
                    if (this->arr_dist_[min_dist_v]) return min_dist_v;
                }
                return NOT_A_VERTEX;
            }
            virtual void UpdateVertexDist(Vertex v, MstWeight dist) {
                this->arr_dist_[v] = dist;
                queue_.push(PriorityNode<MstWeight>(v, dist));
            }
        private:
            priority_queue<PriorityNode<MstWeight>, vector<PriorityNode<MstWeight>>, cmp<MstWeight>> queue_;
        };
    }
}
