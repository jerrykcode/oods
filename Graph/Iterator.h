#pragma once

#include <vector>
using namespace std;
#include "AdjNode.h"

/* Iterator abstract class */
class Iterator {
public:
	/* Returns the next AdjNode *, or NULL if not exist. */
	virtual AdjNode * next() = 0;

	/* Returns true if the AdjNode * returned from next function is a reference to the adjacent node in graph. */
	virtual bool isGraphReference() = 0;
};

/* Iterator for ListUNWGraph */
class ListUNWIterator : public Iterator {
public:	
	ListUNWIterator(vector<UNWAdjNode>& list);
	virtual AdjNode * next();
	virtual bool isGraphReference();
private:
	vector<UNWAdjNode>& list_;
	size_t adj_v_idx_;
};

inline ListUNWIterator::ListUNWIterator(vector<UNWAdjNode>& list) : list_(list), adj_v_idx_(0) {

}

inline AdjNode * ListUNWIterator::next() {
	if (adj_v_idx_ < list_.size()) {
		return (AdjNode *)(&list_[adj_v_idx_++]);
	}
	return NULL;
}

inline bool ListUNWIterator::isGraphReference() {
	return true;
}

/* Iterator for ListWGraph */
template<typename T>
class ListWIterator : public Iterator {
public:
	ListWIterator(vector<WAdjNode<T>>& list);
	virtual AdjNode * next();
	virtual bool isGraphReference();
private:
	vector<WAdjNode<T>>& list_;
	size_t adj_v_idx_;
};

template<typename T>
inline ListWIterator<T>::ListWIterator(vector<WAdjNode<T>>& list) : list_(list), adj_v_idx_(0) {

}

template<typename T>
inline AdjNode * ListWIterator<T>::next() {
	if (adj_v_idx_ < list_.size()) {
		return (AdjNode *)(&list_[adj_v_idx_++]);
	}
	return NULL;
}

template<typename T>
inline bool ListWIterator<T>::isGraphReference() {
	return true;
}

/* Iterator for MatrixUNWGraph */
class MatrixUNWIterator : public Iterator {
public:
	MatrixUNWIterator(bool *adj_nodes, size_t n_vertices);
	~MatrixUNWIterator();
	virtual AdjNode * next();
	virtual bool isGraphReference();
private:
	bool * has_edge_;
	size_t n_vertices_;
	size_t adj_v_idx_;
	UNWAdjNode * last_;
};

inline MatrixUNWIterator::MatrixUNWIterator(bool * has_edge, size_t n_vertices) : has_edge_(has_edge), n_vertices_(n_vertices), adj_v_idx_(0), last_(NULL) {

}

inline MatrixUNWIterator::~MatrixUNWIterator() {
	if (last_ != NULL) {
		delete last_;
	}
}

inline AdjNode * MatrixUNWIterator::next() {
	if (last_ != NULL) {
		delete last_;
	}
	for (; adj_v_idx_ < n_vertices_; adj_v_idx_++) {
		if (has_edge_[adj_v_idx_]) {
			last_ = new UNWAdjNode(adj_v_idx_);
			adj_v_idx_++;
			return (AdjNode *)last_;
		}
	}
	return NULL;
}

inline bool MatrixUNWIterator::isGraphReference() {
	return false;
}

/* Iterator for MatrixWGraph */
template<typename T>
class MatrixWIterator : public Iterator {
public:
	MatrixWIterator(bool * has_edge, T * edge_weight, size_t n_vertices);
	~MatrixWIterator();
	virtual AdjNode * next();
	virtual bool isGraphReference();
private:
	bool * has_edge_;
	T * edge_weight_;
	size_t n_vertices_;
	size_t adj_v_idx_;
	WAdjNode<T> * last_;
};

template<typename T>
inline MatrixWIterator<T>::MatrixWIterator(bool * has_edge, T * edge_weight, size_t n_vertices) :
	has_edge_(has_edge) , 
	edge_weight_(edge_weight),
	n_vertices_(n_vertices),
	adj_v_idx_(0),
	last_(NULL) {}

template<typename T>
inline MatrixWIterator<T>::~MatrixWIterator() {
	if (last_ != NULL) {
		delete last_;
	}
}

template<typename T>
inline AdjNode * MatrixWIterator<T>::next() {
	if (last_ != NULL) {
		delete last_;
	}
	for (; adj_v_idx_ < n_vertices_; adj_v_idx_++) {
		if (has_edge_[adj_v_idx_]) {
			last_ = new WAdjNode<T>(adj_v_idx_, edge_weight_[adj_v_idx_]);
			adj_v_idx_++;
			return (AdjNode *)last_;
		}
	}
	return NULL;
}

template<typename T>
inline bool MatrixWIterator<T>::isGraphReference() {
	return false;
}