#pragma once
#include "Vertex.h"

/* Adjacent node */
class AdjNode {
public:
	AdjNode() {}
	AdjNode(Vertex adj_vertex) : adj_vertex(adj_vertex) {}

	/* Returns the adjacent node */
	Vertex getAdjVertex() {
		return adj_vertex;
	}

	virtual bool hasWeight() {
		return false;
	}
protected:
	Vertex adj_vertex; //Adjacent node
};

/* Unweighted Adjacent node */
class UNWAdjNode : public AdjNode {
public:
	UNWAdjNode() {}
	UNWAdjNode(Vertex adj_vertex) : AdjNode(adj_vertex) {}
};

/* Weighted adjacent node */
template<typename T>
class WAdjNode : public AdjNode {
public:
	WAdjNode() {}
	WAdjNode(Vertex adj_vertex, T adj_weight) : AdjNode(adj_vertex), adj_weight(adj_weight) {}

	virtual bool hasWeight() {
		return true;
	}

	T getAdjWeight() {
		return adj_weight;
	}

	void setAdjWeight(T adj_weight) {
		this->adj_weight = adj_weight;
	}

protected:
	T adj_weight;
};
