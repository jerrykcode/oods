#include "Dinic.h"
#include "queue"

template<typename T>
inline Dinic<T>::Dinic() {

}

template<typename T>
Dinic<T>::~Dinic() {

}

template<typename T>
bool Dinic<T>::getMaxFlow(Graph<T>* pGraph, Vertex src, Vertex des, T *pMaxFlow) {
	if (!pGraph->isGraphDirected()) return false;
	*pMaxFlow = 0;
	int nVertexes = pGraph->getVertexesNum();
	Vertex *path = new Vertex[nVertexes];
	T minFlowOnPath;
	while (bfs(pGraph, src, des, path)) {
		minFlowOnPath = NO_VALUE;
		for (Vertex v = des; v != src; v = path[v]) {
			T weight = pGraph->getEdgeWeight(path[v], v);
			if (weight < minFlowOnPath || minFlowOnPath == NO_VALUE) {
				minFlowOnPath = weight;
			}
		}
		(*pMaxFlow) += minFlowOnPath;
		for (Vertex v = des; v != src; v = path[v]) {
			pGraph->increaseEdgeWeight(path[v], v, (-1) * minFlowOnPath);
			pGraph->increaseEdgeWeight(v, path[v], minFlowOnPath);
		}
	}
	free(path);
	return true;
}

template<typename T>
bool Dinic<T>::bfs(Graph<T>* pGraph, Vertex src, Vertex des, Vertex * path) {
	queue<Vertex> vqueue;
	int nVertexes = pGraph->getVertexesNum();
	bool *collected = new bool[nVertexes];
	fill(collected, collected + nVertexes, false);
	vqueue.push(src);
	collected[src] = true;	
	while (!vqueue.empty()) {
		Vertex v = vqueue.front();
		vqueue.pop();
		for (AdjNode<T> adjNode = pGraph->adj_iter_begin(v);
				adjNode.getAdjVertex() != NO_VALUE;
				adjNode = pGraph->adj_iter_next()) {
			if (adjNode.getAdjWeight() == 0) continue;
			Vertex adjVertex = adjNode.getAdjVertex();
			if (!collected[adjVertex]) {
				path[adjVertex] = v;			
				if (adjVertex == des) {
					free(collected);
					queue<Vertex>().swap(vqueue);
					return true;
				}
				collected[adjVertex] = true;
				vqueue.push(adjVertex);
			}
		}
	}
	free(collected);
	queue<Vertex>().swap(vqueue);
	return false;
}