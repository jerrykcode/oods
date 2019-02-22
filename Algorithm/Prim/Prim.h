#pragma once
#include "GraphInitializer.h"

template<typename T>
class Prim {
public:
	Prim();
	~Prim();

	void getMST(Graph<T> *pGraph, T *pMstWeight, vector<Edge<T>>& mstEdgeSet);
	void getMST(Graph<T> *pGraph, T *pMstWeight, Graph<T> **ppMstGraph);
private:
	T *dist_;
	Vertex *path_;

	void findMin(int nVertexes, Vertex *pMinVertex, T *pMinDist);
	void deleteMemory();
};


