#pragma once
#include "../iterator.h"
#include "matrix_node.h"
#include <vector>
using std::vector;

namespace oods
{
    namespace oograph
    {
        //Iterator for MatrixWGraph
        template<typename EdgeWeight>
        class MatrixWIterator : public WIterator<EdgeWeight> {
        private:
            vector<MatrixNode<EdgeWeight>>& vrow_; //Reference
            size_t pointer_, last_;
            bool reach_end_;
        public:
            MatrixWIterator<EdgeWeight>(vector<MatrixNode<EdgeWeight>>& vrow) : vrow_(vrow), pointer_(-1), last_(-1), reach_end_(false) {}
            ~MatrixWIterator<EdgeWeight>() {
                //Do not delete vrow_ because it is only a reference
            }

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

template<typename EdgeWeight>
bool MatrixWIterator<EdgeWeight>::HasNext() {
    if (reach_end_) return false;
    if (pointer_ == last_) {
        for (pointer_++ ; pointer_ < vrow_.size(); pointer_++)
            if (vrow_[pointer_].has_edge) {
                return true;        
            }
        reach_end_ = true;
        return false;
    }
    else {
        //Call HasNext() several times without calling Next()
        return true;
    }
}

template<typename EdgeWeight>
bool MatrixWIterator<EdgeWeight>::Next() {
    if (reach_end_) return false;
    if (pointer_ == last_) {
        //Call Next() without calling HasNext()
        for (pointer_++ ; pointer_ < vrow_.size(); pointer_++)
            if (vrow_[pointer_].has_edge) {
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

template<typename EdgeWeight>
Vertex MatrixWIterator<EdgeWeight>::GetCurrentVertex() {
    return (Vertex)last_;
}

template<typename EdgeWeight>
void MatrixWIterator<EdgeWeight>::RemoveCurrentElement() {
    vrow_[last_].has_edge = false;
}

template<typename EdgeWeight>
EdgeWeight MatrixWIterator<EdgeWeight>::GetCurrentWeight() {
    return vrow_[last_].edge_weight;
}

template<typename EdgeWeight>
void MatrixWIterator<EdgeWeight>::SetCurrentWeight(EdgeWeight edge_weight) {
    vrow_[last_].edge_weight = edge_weight;
}
