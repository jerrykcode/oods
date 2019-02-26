#pragma once
#include "Graph.h"
#include "MGraph.h"
#include "LGraph.h"
#include <stack>

template<typename T>
class Dijkstra {
public:
	Dijkstra();
	~Dijkstra();

	T shortestPath(Graph<T> *pGraph, Vertex src, Vertex des, vector<Vertex>& path);
	void shortestPath(Graph<T> *pGraph, Vertex src, T *dists, vector<Vertex>* paths);

private:
	T *dist_;
	bool *collected_;
	Vertex *path_;

	bool dijkstra(Graph<T> *pGraph, Vertex src, Vertex des);
	void findMin(Vertex *pMinVertex, T *pMinDist, int nVertexes);
	void getPath(Vertex src, Vertex des, vector<Vertex>& path);
};
