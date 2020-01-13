#pragma once
#include "../iterator.h"
#include "adjnode.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        template<typename EdgeWeight>
        class ListWIterator : public WIterator<EdgeWeight> {
        private:
            vector<AdjNode<EdgeWeight>>& vlist_;
            size_t pointer_;
        public:
            ListWIterator<EdgeWeight>(vector<AdjNode<EdgeWeight>>& vlist) :vlist_(vlist), pointer_(-1) {}
            ~ListWIterator<EdgeWeight>() {}

            virtual bool HasNext();
            virtual bool Next();
            virtual Vertex GetCurrentVertex();
            virtual void RemoveCurrentElement();
            virtual EdgeWeight GetCurrentWeight();     
            virtual void SetCurrentWeight(EdgeWeight edge_weight);
        };

    }

}

//Implementations
//templates can only be write in one file

using namespace oods::oograph;

template<typename EdgeWeight>
bool ListWIterator<EdgeWeight>::HasNext() {
    return pointer_ + 1 < vlist_.size();
}

template<typename EdgeWeight>
bool ListWIterator<EdgeWeight>::Next() {
    if (!HasNext()) return false;
    pointer_++;
    return true;
}

template<typename EdgeWeight>
Vertex ListWIterator<EdgeWeight>::GetCurrentVertex() {
    return vlist_[pointer_].v;
}

template<typename EdgeWeight>
void ListWIterator<EdgeWeight>::RemoveCurrentElement() {
    vlist_.erase(vlist_.begin() + pointer_);
}

template<typename EdgeWeight>
EdgeWeight ListWIterator<EdgeWeight>::GetCurrentWeight() {
    return vlist_[pointer_].weight;
}

template<typename EdgeWeight>
void ListWIterator<EdgeWeight>::SetCurrentWeight(EdgeWeight edge_weight) {
    vlist_[pointer_].weight = edge_weight;
}
