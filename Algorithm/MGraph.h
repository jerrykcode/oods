#pragma once
#include "Graph.h"

class MatrixUNWGraph : public UNWGraph {
public:
	MatrixUNWGraph(int nVertexes, int nEdges, bool isDirected);
	MatrixUNWGraph(int nVertexes, int nEdges, bool isDirected, bool **matrix);
	~MatrixUNWGraph();

	virtual void insertEdge(Edge *pEdge);
	virtual AdjNode * adj_iter_begin(Vertex v);
	virtual AdjNode * adj_iter_next();
	virtual void adj_iter_clear();
	virtual void clear();
	virtual bool isWeighted();

	virtual Graph *cloneGraph();
	virtual Graph *inverseGraph();

private:

	bool **matrix_;
	UNWAdjNode *pLastUNWAdjNode;
};

inline MatrixUNWGraph::MatrixUNWGraph(int nVertexes, int nEdges, bool isDirected) : UNWGraph(nVertexes, nEdges, isDirected), pLastUNWAdjNode(NULL) {
	matrix_ = new bool *[nVertexes];
	for (int i = 0; i < nVertexes; i++) {
		matrix_[i] = new bool[nVertexes];
		fill(matrix_[i], matrix_[i] + nVertexes, false);
	}
}

inline MatrixUNWGraph::MatrixUNWGraph(int nVertexes, int nEdges, bool isDirected, bool **matrix) : MatrixUNWGraph(nVertexes, nEdges, isDirected) {
	matrix_ = matrix;
}

inline MatrixUNWGraph::~MatrixUNWGraph() {
	clear();
}

inline void MatrixUNWGraph::insertEdge(Edge * pEdge) {
	Vertex v, w;
	pEdge->getVertexes(&v, &w);
	if (v < 0 || v >= nVertexes_) return;
	if (w < 0 || w >= nVertexes_) return;
	matrix_[v][w] = true;
	if (!isDirected_) {
		matrix_[w][v] = true;
	}
}

inline AdjNode * MatrixUNWGraph::adj_iter_begin(Vertex v) {
	if (v < 0 || v >= nVertexes_) return NULL;
	for (Vertex w = 0; w < nVertexes_; w++) 
		if (matrix_[v][w]) {
			pIterArgs_stack_.push(new IterArgs(v, w + 1));
			return (AdjNode *)(pLastUNWAdjNode = new UNWAdjNode(w));
		}
	return NULL;
}

inline AdjNode * MatrixUNWGraph::adj_iter_next() {
	if (pIterArgs_stack_.empty()) return NULL;
	PIterArgs pIterArgs = pIterArgs_stack_.top();
	for (Vertex w = pIterArgs->iter_count_; w < nVertexes_; w++) 
		if (matrix_[pIterArgs->iter_v_][w]) {
			pIterArgs->iter_count_ = w + 1;
			return (AdjNode *)(pLastUNWAdjNode = new UNWAdjNode(w));
		}
	pIterArgs_stack_.pop();
	return NULL;
}

inline void MatrixUNWGraph::adj_iter_clear() {
	if (pLastUNWAdjNode != NULL) {
		delete pLastUNWAdjNode;
		pLastUNWAdjNode = NULL;
	}
}

inline void MatrixUNWGraph::clear() {
	for (int i = 0; i < nVertexes_; i++)
		free(matrix_[i]);
	free(matrix_);
}

inline bool MatrixUNWGraph::isWeighted() {
	return false;
}

inline Graph * MatrixUNWGraph::cloneGraph() {	
	bool **matrix = new bool*[nVertexes_];
	for (int i = 0; i < nVertexes_; i++) {
		matrix[i] = new bool[nVertexes_];
		memcpy(matrix[i], matrix_[i], nVertexes_ * sizeof(bool));
	}
	return (Graph *)(new MatrixUNWGraph(nVertexes_, nEdges_, isDirected_, matrix));
}

inline Graph *MatrixUNWGraph::inverseGraph() {
	if (isDirected_) {		
		bool **matrix = new bool*[nVertexes_];
		for (int i = 0; i < nVertexes_; i++) {
			matrix[i] = new bool[nVertexes_];
			for (int j = 0; j < nVertexes_; j++)
				matrix[i][j] = matrix_[j][i];
		}		
		return (Graph *)(new MatrixUNWGraph(nVertexes_, nEdges_, isDirected_, matrix));
	}
	else return cloneGraph();
}


//

template<typename T>
class MatrixWGraph : public WGraph<T> {
public:
	MatrixWGraph(int nVertexes, int nEdges, bool isDirected);
	MatrixWGraph(int nVertexes, int nEdges, bool isDirected, T **matrix);
	~MatrixWGraph();

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

	void setMatrix(T **matrix);

	T **matrix_;	
	WAdjNode<T> *pLastWAdjNode;
};

template<typename T>
inline MatrixWGraph<T>::MatrixWGraph(int nVertexes, int nEdges, bool isDirected) : WGraph<T>(nVertexes, nEdges, isDirected), pLastWAdjNode(NULL) {
	matrix_ = new T*[nVertexes];
	for (int i = 0; i < nVertexes; i++) {
		matrix_[i] = new T[nVertexes];
		fill(matrix_[i], matrix_[i] + nVertexes, NO_VALUE);
	}
}

template<typename T>
inline MatrixWGraph<T>::MatrixWGraph(int nVertexes, int nEdges, bool isDirected, T **matrix) : MatrixWGraph<T>(nVertexes, nEdges, isDirected) {
	matrix_ = matrix;
}

template<typename T>
inline MatrixWGraph<T>::~MatrixWGraph() {
	clear();
}

template<typename T>
inline void MatrixWGraph<T>::insertEdge(Edge * pEdge) {
	if (!pEdge->isWeighted()) return;
	Vertex v, w;
	pEdge->getVertexes(&v, &w);
	if (v < 0 || v >= this->nVertexes_) return;
	if (w < 0 || w >= this->nVertexes_) return;
	T weight = ((WEdge<T> *)(pEdge))->getWeight();
	matrix_[v][w] = weight;
	if (!this->isDirected_) {
		matrix_[w][v] = weight;
	}
}

template<typename T>
inline AdjNode * MatrixWGraph<T>::adj_iter_begin(Vertex v) {
	if (v < 0 || v >= this->nVertexes_) return NULL;
	for (Vertex w = 0; w < this->nVertexes_; w++)
		if (matrix_[v][w] != NO_VALUE) {
			this->pIterArgs_stack_.push(new Graph::IterArgs(v, w + 1));
			return (AdjNode *)(pLastWAdjNode = new WAdjNode<T>(w, matrix_[v][w]));
		}
	return NULL;
}

template<typename T>
inline AdjNode * MatrixWGraph<T>::adj_iter_next() {
	if (this->pIterArgs_stack_.empty()) return NULL;
	Graph::PIterArgs pIterArgs = this->pIterArgs_stack_.top();
	for (Vertex w = pIterArgs->iter_count_; w < this->nVertexes_; w++)
		if (matrix_[pIterArgs->iter_v_][w] != NO_VALUE) {
			pIterArgs->iter_count_ = w + 1;
			return (AdjNode *)(pLastWAdjNode = new WAdjNode<T>(w, matrix_[pIterArgs->iter_v_][w]));
		}
	this->pIterArgs_stack_.pop();
	return NULL;
}

template<typename T>
inline void MatrixWGraph<T>::adj_iter_clear() {
	if (pLastWAdjNode != NULL) {
		delete pLastWAdjNode;
		pLastWAdjNode = NULL;
	}
}

template<typename T>
inline void MatrixWGraph<T>::clear() {
	for (int i = 0; i < this->nVertexes_; i++) {
		free(matrix_[i]);
	}
	free(matrix_);
}

template<typename T>
inline bool MatrixWGraph<T>::isWeighted() {
	return true;
}

template<typename T>
inline T MatrixWGraph<T>::getEdgeWeight(Vertex v, Vertex w) {
	if (v < 0 || v >= this->nVertexes_) return (T)NO_VALUE;
	if (w < 0 || w >= this->nVertexes_) return (T)NO_VALUE;
	return matrix_[v][w];
}

template<typename T>
inline void MatrixWGraph<T>::increaseEdgeWeight(Vertex v, Vertex w, T weight) {
	if (v < 0 || v >= this->nVertexes_) return;
	if (w < 0 || w >= this->nVertexes_) return;
	if (matrix_[v][w] == NO_VALUE) matrix_[v][w] = 0;
	matrix_[v][w] += weight;
}

template<typename T>
inline Graph * MatrixWGraph<T>::cloneGraph() {
	T **matrix = new T*[this->nVertexes_];
	for (int i = 0; i < this->nVertexes_; i++) {
		matrix[i] = new T[this->nVertexes_];
		memcpy(matrix[i], matrix_[i], this->nVertexes_ * sizeof(T));
	}
	return (Graph *)(new MatrixWGraph(this->nVertexes_, this->nEdges_, this->isDirected_, matrix));
}

template<typename T>
inline Graph * MatrixWGraph<T>::inverseGraph() {
	if (this->isDirected_) {
		T **matrix = new T*[this->nVertexes_];
		for (int i = 0; i < this->nVertexes_; i++) {
			matrix[i] = new T[this->nVertexes_];
			for (int j = 0; j < this->nVertexes_; j++)
				matrix[i][j] = matrix_[j][i];
		}
		return (Graph *)(new MatrixWGraph<T>(this->nVertexes_, this->nEdges_, this->isDirected_, matrix));
	}
	else return cloneGraph();
}