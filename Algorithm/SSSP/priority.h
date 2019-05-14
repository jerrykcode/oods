#pragma once
#include "Vertex.h"

template<typename T>
struct PriorityNode {
	Vertex v;
	T priority_dist;
	PriorityNode(Vertex v, T priority_dist) : v(v), priority_dist(priority_dist) {}
};

template<typename T>
struct cmp {
	bool operator () (PriorityNode<T>& a, PriorityNode<T>& b) {
		return a.priority_dist > b.priority_dist;
	}
};