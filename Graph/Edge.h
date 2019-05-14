#pragma once
#include "Vertex.h"

/* Edge (abstract class) */
class Edge {
public:
	Edge() {}
	Edge(Vertex v, Vertex w) : v(v), w(w) {}

	/* Gets the vertices of the edge. */
	void getVertices(Vertex* pv, Vertex *pw) {
		*pv = v;
		*pw = w;
	}

	virtual bool hasWeight() = 0;
protected:
	Vertex v, w; //Two vertices of the edge
};

/* Unweighted Edge */
class UNWEdge : public Edge {
public:
	UNWEdge(Vertex v, Vertex w) : Edge(v, w) {}
	virtual bool hasWeight() {
		return false;
	}
};

/* Weighted Edge */
template<typename T>
class WEdge : public Edge {
public:
	WEdge(Vertex v, Vertex w, T weight) : Edge(v, w), weight(weight) {}

	virtual bool hasWeight() {
		return true;
	}

	/* Returns the weight of the edge */
	T getWeight() {
		return weight;
	}
private:
	T weight; //Weight of the edge
};
