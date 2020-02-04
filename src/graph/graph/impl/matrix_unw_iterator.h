#pragma once
#include "../iterator.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        //Iterator for MatrixUnwGraph
        class MatrixUnwIterator : public Iterator {
        private:
            vector<bool>& vrow_; //Reference
            size_t pointer_, last_;
            bool reach_end_;
        public:
            MatrixUnwIterator(vector<bool>& vrow) : vrow_(vrow), pointer_(-1), last_(-1), reach_end_(false) {
            }
            ~MatrixUnwIterator() {
                //Do not delete vrow_ because it is only a reference
            }

            /*
             * The recommended order is to call HasNext() and then Next(),
             * 
             *  while (HasNext()) {
             *      Next();
             *  }
             *
             * HasNext() looks for the next element by traversing vrow_ with pointer_, while Next() specifies last_ to pointer_.
             * But when calling HasNext() multiple times without calling Next(), or calling Next() without calling HasNext(), 
             * the code still works.
             */

            virtual bool HasNext() {
                if (reach_end_) return false;
                if (pointer_ == last_) {
                    for (pointer_++; pointer_ < vrow_.size(); pointer_++)
                        if (vrow_[pointer_]) {
                            return true;
                        }
                    reach_end_ = true;
                    return false;
                }
                else {
                    return true;
                }
            }

            virtual bool Next() {
                if (reach_end_) return false;
                if (pointer_ == last_) {
                    for (pointer_++; pointer_ < vrow_.size(); pointer_++)
                        if (vrow_[pointer_]) {
                            last_ = pointer_;
                            return true;
                        }
                    reach_end_ = true;
                    return false;
                }
                else {
                    last_ = pointer_;
                    return true;
                }

            }

            virtual Vertex GetCurrentVertex() {
                return (Vertex)pointer_;
            }

            virtual void RemoveCurrentElement() {
                vrow_[pointer_] = false;
            }
        };
    }

}
