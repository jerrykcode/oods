#pragma once
#include "../iterator.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        //Iterator for ListUnwGraph
        class FrontListUnwIterator : public Iterator {
        private:
            FrontListUnwGraph *graph_;
            Vertex v_;
            size_t pointer_; //pointer of the current element
            size_t pre_pointer_;
            bool before_start_; // Next() will be call once before start iterating
        public:
            FrontListUnwIterator(Vertex v, FrontListUnwGraph *graph)
                 : v_(v), graph_(graph),
                   pointer_(head[v]), pre_pointer_(-1), before_start_(true) {
                
            }

            ~FrontListUnwIterator() {

            }

            virtual bool HasNext() {
                if (before_start_) {
                    return pointer_ != -1;
                }
                return graph_->next_[pointer_] != -1;
            }

            virtual bool Next() {
                if (before_start_) {
                    before_start_ = false;
                    return true;
                }
                if (graph_->next_[pointer_] != -1) {
                    pre_pointer_ = pointer_;
                    pointer_ = graph_->next_[pointer_];
                    return true;
                }
                return false;
            }

            virtual Vertex GetCurrentVertex() {
                return graph_->to_[pointer_];
            }

            virtual void RemoveCurrentElement() {
                if (pointer_ == -1) {
                    return;
                }
                if (pre_pointer_ == -1) {
                    graph_->head_[v_] = graph_->next_[pointer_];
                } else {
                    graph_->next_[pre_pointer_] = graph_->next_[pointer_];
                }
                graph_->deleted_++;
            }
        };
    }

}
