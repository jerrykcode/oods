#pragma once

#include "Graph.h"

class ListGraph {
public:

};

/* Unweighted Graph represented by adjacent list */
class ListUNWGraph : public UNWGraph, public ListGraph {
public:
	ListUNWGraph(size_t n_vertices, bool is_directed = false);
	ListUNWGraph(vector<UNWAdjNode> *list, size_t n_vertices, size_t n_edges, bool is_directed = false);
	~ListUNWGraph();

	virtual bool insertEdge(Edge *p_edge);
	virtual Iterator * getAdjIterator(Vertex v);
	virtual Graph * cloneGraph();
	virtual Graph * inverseGraph();
	virtual void clear();


private:
	vector<UNWAdjNode> *list_; //Adjacent list. list_[v] contains all the adjacent nodes of v
	bool memory_alloced;
};

ListUNWGraph::ListUNWGraph(size_t n_vertices,bool is_directed) : UNWGraph(n_vertices, is_directed), memory_alloced(true) {
	list_ = new vector<UNWAdjNode>[this->n_vertices_];
}

ListUNWGraph::ListUNWGraph(vector<UNWAdjNode> *list, size_t n_vertices, size_t n_edges, bool is_directed) :
	UNWGraph(n_vertices, is_directed), memory_alloced(true), list_(list) {
	this->n_edges_ = n_edges;
}

ListUNWGraph::~ListUNWGraph() {
	clear();
}

bool ListUNWGraph::insertEdge(Edge *p_edge) {
	Vertex v, w;
	p_edge->getVertices(&v, &w);
	if (v >= this->n_vertices_) return false; //Vertex is alway unsigned type, >= 0
	if (w >= this->n_vertices_) return false;
	list_[v].push_back(UNWAdjNode(w));
	this->n_edges_++;
	if (!isDirected()) {
		list_[w].push_back(UNWAdjNode(v));
		this->n_edges_++;
	}
	return true;
}

Iterator * ListUNWGraph::getAdjIterator(Vertex v) {
	if (v >= this->n_vertices_) {
		return NULL;
	}
	return (Iterator *)(new ListUNWIterator(list_[v]));
}

Graph * ListUNWGraph::cloneGraph() {
	vector<UNWAdjNode> *list = new vector<UNWAdjNode>[this->n_vertices_];
	for (Vertex i = 0; i < this->n_vertices_; i++) {
		list[i].resize(list_[i].size());
		for (size_t j = 0; j < list_[i].size(); j++)
			list[i][j] = list_[i][j];
	}
	return (Graph *)(new ListUNWGraph(list, this->n_vertices_, this->n_edges_, this->is_directed_));
}

Graph * ListUNWGraph::inverseGraph() {
	if (this->is_directed_) {
		vector<UNWAdjNode> *list = new vector<UNWAdjNode>[this->n_vertices_];
		for (Vertex i = 0; i < this->n_vertices_; i++) {
			for (auto it = list_[i].begin(); it != list_[i].end(); it++) {
				list[it->getAdjVertex()].push_back(UNWAdjNode(i));
			}
		}
		return (Graph *)(new ListUNWGraph(list, this->n_vertices_, this->n_edges_, this->is_directed_));
	}
	else return cloneGraph();
}

void ListUNWGraph::clear() {
	if (!memory_alloced) return;
	for (size_t i = 0; i < this->n_vertices_; i++) {
		vector<UNWAdjNode>().swap(list_[i]);
	}
	memory_alloced = false;
}

/* Weighted Graph represented by adjacent list */
template<typename T>
class ListWGraph : public WGraph<T>, public ListGraph {
public:
	ListWGraph(size_t n_vertices, bool is_directed = false);
	ListWGraph(vector<WAdjNode<T>>* list, size_t n_vertices, size_t n_edges = 0, bool is_directed = false);
	~ListWGraph();

	//Inherited from Graph abstract class
	virtual bool insertEdge(Edge *p_edge);
	virtual Iterator * getAdjIterator(Vertex v);
	virtual Graph * cloneGraph();
	virtual Graph * inverseGraph();
	virtual void clear();

	//Inherited from WGraph<T> abstract class
	virtual bool changeEdgeWeight(Vertex v, Vertex w, T new_weight);
	virtual bool getEdgeWeight(Vertex v, Vertex w, T * p_weight);

private:
	vector<WAdjNode<T>> *list_; //Adjacent list. list_[v] contains all the adjacent nodes of v
	bool memory_alloced_;
};

template<typename T>
ListWGraph<T>::ListWGraph(size_t n_vertices, bool is_directed) : WGraph<T>(n_vertices, is_directed), memory_alloced_(true) {
	list_ = new vector<WAdjNode<T>>[n_vertices];
}

template<typename T>
ListWGraph<T>::ListWGraph(vector<WAdjNode<T>>* list, size_t n_vertices, size_t n_edges, bool is_directed) :
	WGraph<T>(n_vertices, is_directed), memory_alloced_(true), list_(list) {
	this->n_edges_ = n_edges;
}

template<typename T>
ListWGraph<T>::~ListWGraph() {
	clear();
}

template<typename T>
bool ListWGraph<T>::insertEdge(Edge * p_edge) {
	if (p_edge->hasWeight()) {
		Vertex v, w;
		p_edge->getVertices(&v, &w);
		if (v >= this->n_vertices_) return false; //Vertex is always unsigned type, >= 0
		if (w >= this->n_vertices_) return false;
		T weight = ((WEdge<T> *)p_edge)->getWeight();
		list_[v].push_back(WAdjNode<T>(w, weight));
		this->n_edges_++;
		if (!isDirected()) {
			list_[w].push_back(WAdjNode<T>(v, weight));
			this->n_edges_++;
		}
		return true;
	}
	else return false;
}

template<typename T>
Iterator * ListWGraph<T>::getAdjIterator(Vertex v) {
	if (v >=this->n_vertices_) {
		return NULL;
	}
	return (Iterator *)(new ListWIterator<T>(list_[v]));
}

template<typename T>
Graph * ListWGraph<T>::cloneGraph() {
	vector<WAdjNode<T>> * list = new vector<WAdjNode<T>>[this->n_vertices_];
	for (Vertex i = 0; i < this->n_vertices_; i++) {
		list[i].resize(list_[i].size());
		for (size_t j = 0; j < list_[i].size(); j++)
			list[i][j] = list_[i][j];
	}
	return (Graph *)(new ListWGraph<T>(list, this->n_vertices_, this->n_edges_, this->is_directed_));
}

template<typename T>
Graph * ListWGraph<T>::inverseGraph() {
	if (isDirected()) {
		vector<WAdjNode<T>> * list = new vector<WAdjNode<T>>[this->n_vertices_];
		for (Vertex i = 0; i < this->n_vertices_; i++) {
			for (auto it = list_[i].begin(); it != list_[i].end(); it++) {
				list[it->getAdjVertex()].push_back(WAdjNode<T>(i, it->getAdjWeight()));
			}
		}
		return (Graph *)(new ListWGraph<T>(list, this->n_vertices_, this->n_edges_, this->is_directed_));
	}
	else return cloneGraph();
}

template<typename T>
void ListWGraph<T>::clear() {
	if (!memory_alloced_) return;
	for (size_t i = 0; i < this->n_vertices_; i++) {
		vector<WAdjNode<T>>().swap(list_[i]);
	}
	memory_alloced_ = false;
}

template<typename T>
bool ListWGraph<T>::changeEdgeWeight(Vertex v, Vertex w, T new_weight) {
	if (v >= this->n_vertices_) return false;
	if (w >= this->n_vertices_) return false;
	bool flag = false;
	for (auto it = list_[v].begin(); it != list_[v].end(); it++) {
		if (it->getAdjVertex() == w) {
			it->setAdjWeight(new_weight);
			flag = true;
			break;
		}
	}
	if (!isDirected() && flag) {
		for (auto it = list_[w].begin(); it != list_[w].end(); it++) {
			if (it->getAdjVertex() == v) {
				it->setAdjWeight(new_weight);
				break;
			}
		}
	}
	return flag;
}

template<typename T>
bool ListWGraph<T>::getEdgeWeight(Vertex v, Vertex w, T * p_weight) {
	if (v >= this->n_vertices_) return false;
	if (w >= this->n_vertices_) return false;
	if (!isDirected() && list_[v].size() > list_[w].size()) {
		Vertex tmp = v;
		v = w;
		w = tmp;	
	}
	for (auto it = list_[v].begin(); it != list_[v].end(); it++) {
		if (it->getAdjVertex() == w) {
			*p_weight = it->getAdjWeight();
			return true;
		}
	}
	return false;
}
