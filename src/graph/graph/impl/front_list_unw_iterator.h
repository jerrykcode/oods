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
            vector<int>& head_, & next_, &to_;
            Vertex v_;
            size_t pointer_; //pointer of the current element
            size_t pre_pointer_;
            bool before_start_; // Next() will be call once before start iterating
        public:
            FrontListUnwIterator(Vertex v, vector<int>& head, vector<int>& next, vector<int>& to)
                 : v_(v), head_(head), next_(next), to_(to),
                   pointer_(head[v]), pre_pointer_(-1), before_start_(true) {
                
            }

            ~FrontListUnwIterator() {

            }

            virtual bool HasNext() {
                if (before_start_) {
                    return pointer_ != -1;
                }
                return next_[pointer_] != -1;
            }

            virtual bool Next() {
                if (before_start_) {
                    before_start_ = false;
                    return true;
                }
                if (next_[pointer_] != -1) {
                    pre_pointer_ = pointer_;
                    pointer_ = next_[pointer_];
                    return true;
                }
                return false;
            }

            virtual Vertex GetCurrentVertex() {
                return to_[pointer_];
            }

            virtual void RemoveCurrentElement() {
                if (pointer_ == -1) {
                    return;
                }
                if (pre_pointer_ == -1) {
                    head_[v_] = next_[pointer_];
                } else {
                    next_[pre_pointer_] = next_[pointer_];
                }
            }
        };
    }

}
