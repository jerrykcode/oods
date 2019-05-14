#pragma once

#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
#include "Vertex.h"
#include "Edge.h"
#include "AdjNode.h"
#include "Iterator.h"


/* Graph abstract class */
class Graph {
public:
	Graph() {}
	Graph(size_t n_vertices, bool is_directed = false) : n_vertices_(n_vertices), n_edges_(0), is_directed_(is_directed) {}
	~Graph() {}

	/* Returns the number of vertices. */
	size_t getNumVertices() {
		return n_vertices_;
	}

	/* Returns the number of edges. */
	size_t getNumEdges() {
		return n_edges_;
	}

	/* Returns true if the graph is directed. */
	bool isDirected() {
		return is_directed_;
	}

	virtual bool isWeighted() = 0;
	virtual bool insertEdge(Edge *p_edge) = 0;
	virtual Iterator * getAdjIterator(Vertex v) = 0;	
	virtual Graph * cloneGraph() = 0;
	virtual Graph * inverseGraph() = 0;
	virtual void clear() = 0;

protected:
	size_t n_vertices_, n_edges_; //The number of the vertices and edges
	bool is_directed_; //True if the graph is directed
};

/* Unweighted Graph (abstarct) */
class UNWGraph : public Graph {
public:
	UNWGraph() {}
	UNWGraph(size_t n_vertices, bool is_directed = false) : Graph(n_vertices, is_directed) {}
	~UNWGraph() {}

	virtual bool isWeighted() {
		return false;
	}
};

/*Weighted Graph(abstract) */
template<typename T>
class WGraph : public Graph {
public:
	WGraph() {}
	WGraph(size_t n_vertices, bool is_directed = false) : Graph(n_vertices, is_directed) {}

	virtual bool isWeighted() {
		return true;
	}

	virtual bool changeEdgeWeight(Vertex v, Vertex w, T new_weight) = 0;
	virtual bool getEdgeWeight(Vertex v, Vertex w, T * p_weight) = 0;
};
