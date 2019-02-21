#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define NO_VALUE -1

typedef int Vertex;

template<typename T>
class Edge {
public:
	Edge() {}
	Edge(Vertex v, Vertex w, T weight) : v(v), w(w), weight(weight) {}
	~Edge() {}
	void getVertexes(Vertex *pV, Vertex *pW) {
		*pV = v;
		*pW = w;
	}
	T getWeight() { return weight; }
private:
	Vertex v, w;
	T weight;
};

template<typename T>
class AdjNode {
public:
	AdjNode(Vertex adjVertex, T adjWeight) : adjVertex(adjVertex), adjWeight(adjWeight)	 {}
	~AdjNode() {}

	Vertex getAdjVertex() { return adjVertex; }
	T getAdjWeight() { return adjWeight; }
private:
	Vertex adjVertex;
	T adjWeight;
};

template<typename T>
class Graph {
public:
	Graph() {}
	Graph(int nVertexes) : nVertexes_(nVertexes), nEdges_(0) {}
	~Graph() {}

	int getVertexesNum() { return nVertexes_; }
	int getEdgesNum() { return nEdges_; }
	
	virtual void insertEdge(Edge<T> edge) = 0;
	virtual AdjNode<T> adj_iter_begin(Vertex v) = 0;
	virtual AdjNode<T> adj_iter_next() = 0;
	virtual void clear() = 0;
protected:
	int nVertexes_;
	int nEdges_;
};


