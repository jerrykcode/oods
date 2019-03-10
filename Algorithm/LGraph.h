#pragma once
#include "Graph.h"

class ListUNWGraph : public UNWGraph {
public:
	ListUNWGraph(int nVertexes, int nEdges, bool isDirected);
	ListUNWGraph(int nVertexes, int nEdges, bool isDirected, vector<UNWAdjNode> *list);
	~ListUNWGraph();

	virtual void insertEdge(Edge *pEdge);
	virtual AdjNode * adj_iter_begin(Vertex v);
	virtual AdjNode * adj_iter_next();
	virtual void adj_iter_clear();
	virtual void clear();
	virtual bool isWeighted();

	virtual Graph *cloneGraph();
	virtual Graph *inverseGraph();

private:
	vector<UNWAdjNode> *list_;
	Vertex iter_v_;
	int iter_count_;
};

inline ListUNWGraph::ListUNWGraph(int nVertexes, int nEdges, bool isDirected) : UNWGraph(nVertexes, nEdges, isDirected), iter_v_(NO_VALUE) {
	list_ = new vector<UNWAdjNode>[nVertexes];
}

inline ListUNWGraph::ListUNWGraph(int nVertexes, int nEdges, bool isDirected, vector<UNWAdjNode> *list) : ListUNWGraph(nVertexes, nEdges, isDirected) {
	list_ = list;
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

inline Graph * ListUNWGraph::cloneGraph() {
	vector<UNWAdjNode> *list = new vector<UNWAdjNode>[nVertexes_];
	for (int i = 0; i < nVertexes_; i++) {
		list[i].resize(list_[i].size());
		for (int j = 0; j < list_[i].size(); j++) {
			list[i][j] = list_[i][j];
		}
	}
	return (Graph *)(new ListUNWGraph(nVertexes_, nEdges_, isDirected_, list));
}

inline Graph * ListUNWGraph::inverseGraph() {
	if (isDirected_) {
		vector<UNWAdjNode> *list = new vector<UNWAdjNode>[nVertexes_];
		for (int i = 0; i < nVertexes_; i++) {
			for (UNWAdjNode unwAdjNode : list_[i]) {
				list[unwAdjNode.getAdjVertex()].push_back(UNWAdjNode(i));
			}
		}
		return (Graph *)(new ListUNWGraph(nVertexes_, nEdges_, isDirected_, list));
	}
	else return cloneGraph();
}



template<typename T>
class ListWGraph : public WGraph<T> {
public:
	ListWGraph(int nVertexes, int nEdges, bool isDirected);
	ListWGraph(int nVertexes, int nEdges, bool isDirected, vector<WAdjNode<T>> *list);
	~ListWGraph();

	virtual void insertEdge(Edge *pEdge);
	virtual AdjNode * adj_iter_begin(Vertex v);
	virtual AdjNode * adj_iter_next();
	virtual void adj_iter_clear();
	virtual void clear();
	virtual bool isWeighted();

	virtual T getEdgeWeight(Vertex v, Vertex w);
	virtual void increaseEdgeWeight(Vertex v, Vertex w, T weight);

	virtual Graph *cloneGraph();
	virtual Graph *inverseGraph();

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
inline ListWGraph<T>::ListWGraph(int nVertexes, int nEdges, bool isDirected, vector<WAdjNode<T>> *list) : ListWGraph<T>(nVertexes, nEdges, isDirected) {
	list_ = list;
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
		return NO_VALUE;
	}
	else {
		for (WAdjNode<T> wAdjNode : list_[v]) 
			if (wAdjNode.getAdjVertex() == w) {
				return wAdjNode.getAdjWeight();
			}
		return NO_VALUE;
	}
}

template<typename T>
inline void ListWGraph<T>::increaseEdgeWeight(Vertex v, Vertex w, T weight) {
	if (v < 0 || v >= this->nVertexes_) return;
	if (w < 0 || w >= this->nVertexes_) return;
	for (auto it = list_[v].begin(); it != list_[v].end(); it++)
		if (it->getAdjVertex() == w) {
			it->increaseAdjWeight(weight);
			return;
		}
	insertEdge((Edge *)new WEdge<T>(v, w, weight));
}

template<typename T>
inline Graph * ListWGraph<T>::cloneGraph() {
	vector<WAdjNode<T>> *list = new vector<WAdjNode<T>>[this->nVertexes_];
	for (int i = 0; i < this->nVertexes_; i++) {
		list[i].resize(list_[i].size());
		for (int j = 0; j < list_[i].size(); j++) {
			list[i][j] = list_[i][j];
		}
	}
	return (Graph *)(new ListWGraph<T>(this->nVertexes_, this->nEdges_, this->isDirected_, list));
}

template<typename T>
inline Graph * ListWGraph<T>::inverseGraph() {
	if (this->isDirected_) {
		vector<WAdjNode<T>> *list = new vector<WAdjNode<T>>[this->nVertexes_];
		for (int i = 0; i < this->nVertexes_; i++) {
			for (WAdjNode<T> wAdjNode : list_[i]) {
				list[wAdjNode.getAdjVertex()].push_back(WAdjNode<T>(i, wAdjNode.getAdjWeight()));
			}
		}
		return (Graph *)(new ListWGraph<T>(this->nVertexes_, this->nEdges_, this->isDirected_, list));
	}
	else return cloneGraph();
}