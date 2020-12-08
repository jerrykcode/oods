#pragma once
#include "../iterator.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        //Iterator for ListUnwGraph
        class ListUnwIterator : public Iterator {
        private:
            vector<Vertex>& vlist_;
            size_t pointer_; //pointer of the current element
        public:
            ListUnwIterator(vector<Vertex>& vlist) : vlist_(vlist), pointer_(-1) {
                
            }

            ~ListUnwIterator() {

            }

            virtual bool HasNext() {
                return pointer_ + 1 < vlist_.size(); // returns true if the next pointer exists
            }


            virtual bool Next() {
                if (HasNext()) {
                    pointer_++;
                    return true;
                }
                else return false;
            }

            virtual Vertex GetCurrentVertex() {
                return vlist_[pointer_];
            }

            virtual void RemoveCurrentElement() {
                vlist_.erase(vlist_.begin() + pointer_);
            }
        };
    }

}
