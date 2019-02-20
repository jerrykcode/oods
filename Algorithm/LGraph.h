#pragma once
#include "Graph.h"

template<typename T>
class LGraph : public Graph<T> {
public:
	LGraph(int nVertexes) {
		this->nVertexes_ = nVertexes;
		this->nEdges_ = 0;
		list_ = new vector<AdjNode<T>>[nVertexes];
	}
	~LGraph() {
		clear();
	}

	virtual void insertEdge(Edge<T> edge) {
		Vertex v, w;
		edge.getVertexes(&v, &w);
		T weight = edge.getWeight();
		list_[v].push_back(AdjNode<T>(w, weight));
		list_[w].push_back(AdjNode<T>(v, weight));
		this->nEdges_++;
	}

	virtual AdjNode<T> adj_iter_begin(Vertex v) {
		if (list_[v].size() == 0) return AdjNode<T>(NO_VALUE, NO_VALUE);
		iter_count = 0;
		iter_v = v;
		return list_[v][0];
	}

	virtual AdjNode<T> adj_iter_next() {
		if ((++iter_count) < list_[iter_v].size())
			return list_[iter_v][iter_count];
		else
			return AdjNode<T>(NO_VALUE, NO_VALUE);
	}

	virtual void clear() {
		for (int i = 0; i < this->nVertexes_; i++) {
			list_[i].clear();
			vector<AdjNode<T>>().swap(list_[i]);
		}
	}
private:
	vector<AdjNode<T>> *list_;
	int iter_count;
	Vertex iter_v;
};