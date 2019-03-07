#pragma once
#include "Graph.h"

class ListUNWGraph : public UNWGraph {
public:
	ListUNWGraph(int nVertexes, int nEdges, bool isDirected);
	~ListUNWGraph();

	virtual void insertEdge(Edge *pEdge);
	virtual AdjNode * adj_iter_begin(Vertex v);
	virtual AdjNode * adj_iter_next();
	virtual void adj_iter_clear();
	virtual void clear();
	virtual bool isWeighted();

private:
	vector<UNWAdjNode> *list_;
	Vertex iter_v_;
	int iter_count_;
};

inline ListUNWGraph::ListUNWGraph(int nVertexes, int nEdges, bool isDirected) : UNWGraph(nVertexes, nEdges, isDirected), iter_v_(NO_VALUE) {
	list_ = new vector<UNWAdjNode>[nVertexes];
}

inline ListUNWGraph::~ListUNWGraph() {
	clear();
}

inline void ListUNWGraph::insertEdge(Edge * pEdge) {
	Vertex v, w;
	pEdge->getVertexes(&v, &w);
	if (v < 0 || v >= nVertexes_) return;
	if (w < 0 || w >= nVertexes_) return;
	list_[v].push_back(UNWAdjNode(w));
	if (!isDirected_) {
		list_[w].push_back(UNWAdjNode(v));
	}
}

inline AdjNode * ListUNWGraph::adj_iter_begin(Vertex v) {
	if (v < 0 || v >= nVertexes_) return NULL;
	iter_v_ = v;
	iter_count_ = 0;
	if (list_[v].size() == 0) return NULL;
	return (AdjNode *)(&list_[v][iter_count_++]);
}

inline AdjNode * ListUNWGraph::adj_iter_next() {
	if (iter_v_ == NO_VALUE) return NULL;
	if (iter_count_ < list_[iter_v_].size()) {
		return (AdjNode *)(&list_[iter_v_][iter_count_++]);
	}
	else return NULL;
}

inline void ListUNWGraph::adj_iter_clear() {
	return;
}

inline void ListUNWGraph::clear() {
	for (int i = 0; i < nVertexes_; i++) {
		list_[i].clear();
		vector<UNWAdjNode>().swap(list_[i]);
	}
}

inline bool ListUNWGraph::isWeighted() {
	return false;
}



template<typename T>
class ListWGraph : public WGraph<T> {
public:
	ListWGraph(int nVertexes, int nEdges, bool isDirected);
	~ListWGraph();

	virtual void insertEdge(Edge *pEdge);
	virtual AdjNode * adj_iter_begin(Vertex v);
	virtual AdjNode * adj_iter_next();
	virtual void adj_iter_clear();
	virtual void clear();
	virtual bool isWeighted();

	virtual T getEdgeWeight(Vertex v, Vertex w);
	virtual void increaseEdgeWeight(Vertex v, Vertex w, T weight);

private:

	vector<WAdjNode<T>> *list_;
	Vertex iter_v_;
	int iter_count_;
};

template<typename T>
inline ListWGraph<T>::ListWGraph(int nVertexes, int nEdges, bool isDirected) : WGraph<T>(nVertexes, nEdges, isDirected), iter_v_(NO_VALUE) {
	list_ = new vector<WAdjNode<T>>[nVertexes];
}

template<typename T>
inline ListWGraph<T>::~ListWGraph() {
	clear();
}

template<typename T>
inline void ListWGraph<T>::insertEdge(Edge * pEdge) {
	if (!pEdge->isWeighted()) return;
	Vertex v, w;	
	pEdge->getVertexes(&v, &w);
	if (v < 0 || v >= this->nVertexes_) return;
	if (w < 0 || w >= this->nVertexes_) return;
	T weight = ((WEdge<T> *)pEdge)->getWeight();
	list_[v].push_back(WAdjNode<T>(w, weight));
	if (!this->isDirected_) {
		list_[w].push_back(WAdjNode<T>(v, weight));
	}
}

template<typename T>
inline AdjNode * ListWGraph<T>::adj_iter_begin(Vertex v) {
	if (v < 0 || v >= this->nVertexes_) return NULL;
	iter_v_ = v;
	iter_count_ = 0;
	if (list_[v].size() == 0) return NULL;
	return (AdjNode *)(&list_[v][iter_count_++]);
}

template<typename T>
inline AdjNode * ListWGraph<T>::adj_iter_next() {
	if (iter_v_ == NO_VALUE) return NULL;
	if (iter_count_ < list_[iter_v_].size()) {
		return (AdjNode *)(&list_[iter_v_][iter_count_++]);
	}
	else return NULL;
}

template<typename T>
inline void ListWGraph<T>::adj_iter_clear() {
	return;
}

template<typename T>
inline void ListWGraph<T>::clear() {
	for (int i = 0; i < this->nVertexes_; i++) {
		list_[i].clear();
		vector<WAdjNode<T>>().swap(list_[i]);
	}
}

template<typename T>
inline bool ListWGraph<T>::isWeighted() {
	return true;
}

template<typename T>
inline T ListWGraph<T>::getEdgeWeight(Vertex v, Vertex w) {
	if (!this->isDirected_ && list_[w].size() < list_[v].size()) {
		for (WAdjNode<T> wAdjNode : list_[w])
			if (wAdjNode.getAdjVertex() == v) {
				return wAdjNode.getAdjWeight();
			}
	}
	else {
		for (WAdjNode<T> wAdjNode : list_[v]) 
			if (wAdjNode.getAdjVertex() == w) {
				return wAdjNode.getAdjWeight();
			}
	}
}

template<typename T>
inline void ListWGraph<T>::increaseEdgeWeight(Vertex v, Vertex w, T weight) {
	if (v < 0 || v >= this->nVertexes_) return;
	if (w < 0 || w >= this->nVertexes_) return;
	for (WAdjNode<T> wAdjNode : list_[v]) {
		if (wAdjNode.getAdjVertex() == w) {
			wAdjNode.increaseAdjWeight(weight);
			break;
		}
	}
	if (!this->isDirected_) {
		for (WAdjNode<T> wAdjNode : list_[w]) 
			if (wAdjNode.getAdjVertex() == v) {
				wAdjNode.increaseAdjWeight(weight);
				break;
			}
	}
}