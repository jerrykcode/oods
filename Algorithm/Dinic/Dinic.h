#pragma once
#include "LGraph.h"
#include "MGraph.h"

template<typename T>
class Dinic {
public:
	Dinic();
	~Dinic();

	bool getMaxFlow(Graph<T> *pGraph, Vertex src, Vertex des, T *pMaxFlow);
private:
	bool bfs(Graph<T> *pGraph, Vertex src, Vertex des, Vertex *path);
};