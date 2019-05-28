#pragma once

#include "Graph.h"

class MatrixGraph {
public:

protected:
	bool **matrix_; //Adjacent matrix
};


/* Unweighted Graph represented by adjacent matrix */
class MatrixUNWGraph : public UNWGraph, public MatrixGraph {
public:
	MatrixUNWGraph(size_t n_vertices, bool is_directed = false);
	MatrixUNWGraph(bool **matrix, size_t n_vertices, size_t n_edges = 0, bool is_directed = false);
	~MatrixUNWGraph();

	virtual bool insertEdge(Edge * p_edge);
	virtual Iterator * getAdjIterator(Vertex v);
	virtual Graph * cloneGraph();
	virtual Graph * inverseGraph();
	virtual void clear();

private:
	bool memory_alloced;
};

inline MatrixUNWGraph::MatrixUNWGraph(size_t n_vertices, bool is_directed) : UNWGraph(n_vertices, is_directed), memory_alloced(true) {
	this->matrix_ = new bool*[n_vertices];
	for (size_t i = 0; i < n_vertices; i++) {
		this->matrix_[i] = new bool[n_vertices];
		fill(this->matrix_[i], this->matrix_[i] + n_vertices, false);
	}
}

inline MatrixUNWGraph::MatrixUNWGraph(bool **matrix, size_t n_vertices, size_t n_edges, bool is_directed) :
	UNWGraph(n_vertices, is_directed), memory_alloced(true) {
	this->n_edges_ = n_edges;
	this->matrix_ = matrix;
}

inline MatrixUNWGraph::~MatrixUNWGraph() {
	clear();
}

inline bool MatrixUNWGraph::insertEdge(Edge * p_edge) {
	Vertex v, w;
	p_edge->getVertices(&v, &w);
	if (v >= this->n_vertices_) return false; //Vertex is always unsigned type, >= 0
	if (w >= this->n_vertices_) return false;
	this->matrix_[v][w] = true;
	this->n_edges_++;
	if (!isDirected()) {
		this->matrix_[w][v] = true;
		this->n_edges_++;
	}
	return true;
}

inline Iterator * MatrixUNWGraph::getAdjIterator(Vertex v) {
	if (v >= this->n_vertices_) return NULL;
	return (Iterator *)(new MatrixUNWIterator(this->matrix_[v], this->n_vertices_));
}

inline Graph * MatrixUNWGraph::cloneGraph() {
	bool **matrix = new bool*[this->n_vertices_];
	for (size_t i = 0; i < this->n_vertices_; i++) {
		matrix[i] = new bool[this->n_vertices_];
		memcpy(matrix[i], this->matrix_[i], this->n_vertices_ * sizeof(bool));
	}
	return (Graph *)(new MatrixUNWGraph(matrix, this->n_vertices_, this->n_edges_, this->is_directed_));
}

inline Graph * MatrixUNWGraph::inverseGraph() {
	if (isDirected()) {
		bool **matrix = new bool*[this->n_vertices_];
		for (size_t i = 0; i < this->n_vertices_; i++) {
			matrix[i] = new bool[this->n_vertices_];
			fill(matrix[i], matrix[i] + this->n_vertices_, false);
		}
		for (size_t i = 0; i < this->n_vertices_; i++) {
			for (size_t j = 0; j < this->n_vertices_; i++) {
				if (this->matrix_[i][j]) {
					matrix[j][i] = true;
				}
			}
		}
		return (Graph *)(new MatrixUNWGraph(matrix, this->n_vertices_, this->n_edges_, this->is_directed_));
	}
	else return cloneGraph();
}

inline void MatrixUNWGraph::clear() {
	if (!memory_alloced) return;
	for (size_t i = 0; i < this->n_vertices_; i++) {
		free(matrix_[i]);
	}
	free(matrix_);
	memory_alloced = false;
}


/* Weighted Graph represented by adjacent matrix */
template<typename T>
class MatrixWGraph : public WGraph<T>, public MatrixGraph {
public:
	MatrixWGraph(size_t n_vertices, bool is_directed = false);
	MatrixWGraph(bool **matrix, T **w_matrix, size_t n_vertices, size_t n_edges = 0, bool is_directed = false);
	~MatrixWGraph();

	//Inherited from Graph abstract class
	virtual bool insertEdge(Edge * p_edge);
	virtual Iterator * getAdjIterator(Vertex v);
	virtual Graph * cloneGraph();
	virtual Graph * inverseGraph();
	virtual void clear();

	//Inherited from WGraph<T> abstract class
	virtual bool increaseEdgeWeight(Vertex v, Vertex w, T new_weight);
	virtual bool getEdgeWeight(Vertex v, Vertex w, T * p_weight);
private:
	T **w_matrix_;
	bool memory_alloced_;
};

template<typename T>
inline MatrixWGraph<T>::MatrixWGraph(size_t n_vertices, bool is_directed) : WGraph<T>(n_vertices, is_directed), memory_alloced_(true) {
	this->matrix_ = new bool * [n_vertices];
	w_matrix_ = new T * [n_vertices];
	for (size_t i = 0; i < n_vertices; i++) {
		this->matrix_[i] = new bool[n_vertices];
		fill(this->matrix_[i], this->matrix_[i] + n_vertices, false);
		w_matrix_[i] = new T[n_vertices];		
	}
}

template<typename T>
inline MatrixWGraph<T>::MatrixWGraph(bool **matrix, T **w_matrix, size_t n_vertices, size_t n_edges, bool is_directed) :
	WGraph<T>(n_vertices, is_directed), memory_alloced_(true), w_matrix_(w_matrix) {
	this->n_edges_ = n_edges;
	this->matrix_ = matrix;
}

template<typename T>
inline MatrixWGraph<T>::~MatrixWGraph() {
	clear();
}

template<typename T>
inline bool MatrixWGraph<T>::insertEdge(Edge * p_edge) {
	if (p_edge->hasWeight()) {
		Vertex v, w;
		p_edge->getVertices(&v, &w);
		if (v >= this->n_vertices_) return false;
		if (v >= this->n_vertices_) return false;
		T weight = ((WEdge<T> *)p_edge)->getWeight();
		this->matrix_[v][w] = true;
		w_matrix_[v][w] = weight;
		this->n_edges_++;
		if (!this->isDirected()) {
			this->matrix_[w][v] = true;
			w_matrix_[w][v] = weight;
			this->n_edges_++;
		}
		return true;
	}
	else return false;
}

template<typename T>
inline Iterator * MatrixWGraph<T>::getAdjIterator(Vertex v) {
	if (v >= this->n_vertices_) return NULL;
	return (Iterator *)(new MatrixWIterator<T>(this->matrix_[v], w_matrix_[v], this->n_vertices_));
}

template<typename T>
inline Graph * MatrixWGraph<T>::cloneGraph() {
	bool ** matrix = new bool * [this->n_vertices_];
	T ** w_matrix = new T * [this->n_vertices_];
	for (size_t i = 0; i < this->n_vertices_; i++) {
		matrix[i] = new bool[this->n_vertices_];
		memcpy(matrix[i], this->matrix_[i], this->n_vertices_ * sizeof(bool));
		w_matrix[i] = new T[this->n_vertices_];
		memcpy(w_matrix[i], w_matrix_[i], this->n_vertices_ * sizeof(T));
	}
	return (Graph *)(new MatrixWGraph<T>(matrix, w_matrix, this->n_vertices_, this->n_edges_, this->is_directed_));
}

template<typename T>
inline Graph * MatrixWGraph<T>::inverseGraph() {
	if (this->isDirected()) {
		bool ** matrix = new bool * [this->n_vertices_];
		T ** w_matrix = new T * [this->n_vertices_];
		for (size_t i = 0; i < this->n_vertices_; i++) {
			matrix[i] = new bool[this->n_vertices_];
			fill(matrix[i], matrix[i] + this->n_vertices_, false);
			w_matrix[i] = new T[this->n_vertices_];
		}
		for (size_t i = 0; i < this->n_vertices_; i++) {
			for (size_t j = 0; j < this->n_vertices_; j++) {
				if (this->matrix_[i][j]) {
					matrix[j][i] = true;
					w_matrix[j][i] = w_matrix_[i][j];
				}
			}
		}
		return (Graph *)(new MatrixWGraph<T>(matrix, w_matrix, this->n_vertices_, this->n_edges_, this->is_directed_));
	}
	else return cloneGraph();
}


template<typename T>
inline void MatrixWGraph<T>::clear() {
	if (!memory_alloced_) return;
	for (size_t i = 0; i < this->n_vertices_; i++) {
		free(this->matrix_[i]);
		free(w_matrix_[i]);
	}
	free(this->matrix_);
	free(w_matrix_);	
}

template<typename T>
inline bool MatrixWGraph<T>::increaseEdgeWeight(Vertex v, Vertex w, T increase_weight) {
	if (v >= this->n_vertices_) return false;
	if (w >= this->n_vertices_) return false;
	if (this->matrix_[v][w]) {
		w_matrix_[v][w] += increase_weight;		
	}
	else {
		w_matrix_[v][w] = increase_weight;	
	}
	return true;
}

template<typename T>
inline bool MatrixWGraph<T>::getEdgeWeight(Vertex v, Vertex w, T * p_weight) {
	if (v >= this->n_vertices_) return false;
	if (w >= this->n_vertices_) return false;
	if (this->matrix_[v][w]) {
		*p_weight = w_matrix_[v][w];
		return true;
	}
	return false;
}
