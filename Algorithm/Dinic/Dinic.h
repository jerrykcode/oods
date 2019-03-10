#pragma once
#include "LGraph.h"
#include "MGraph.h"

template<typename T>
class Dinic {
public:
	Dinic();
	~Dinic();

	bool getMaxFlow(Graph *pGraph, Vertex src, Vertex des, T *pMaxFlow, bool keepOriginalGraph);

private:

	bool bfs(Graph *pGraph, Vertex src, Vertex des);
	bool dinic(Graph *pGraph, Vertex src, Vertex des, T *pMaxFlow);

	Vertex *path_;

};

template<typename T>
inline Dinic<T>::Dinic() {

}

template<typename T>
inline Dinic<T>::~Dinic() {

}

template<typename T>
bool Dinic<T>::getMaxFlow(Graph * pGraph, Vertex src, Vertex des, T * pMaxFlow, bool keepOriginalGraph) {
	if (keepOriginalGraph) {
		//In function dinic, the graph passed in will be altered.
		//If keepOriginalkGraph == true, a copy of the graph will be passed into the function
		//and the original graph keep unchange
		Graph *pCloneGraph = pGraph->cloneGraph();
		bool result = dinic(pCloneGraph, src, des, pMaxFlow);
		pCloneGraph->clear();
		return result;
	}
	else {
		return dinic(pGraph, src, des, pMaxFlow);
	}
}

template<typename T>
inline bool Dinic<T>::bfs(Graph * pGraph, Vertex src, Vertex des) {
	//Find a path from src to des
	//The path is stored in var path_
	VQueue vqueue;
	vqueue.push(src);
	int nVertexes = pGraph->getVertexesNum();
	bool *collected = new bool[nVertexes];
	fill(collected, collected + nVertexes, false);
	collected[src] = true;
	while (!vqueue.empty()) {
		Vertex v = vqueue.pop();
		for (AdjNode *pAdjNode = pGraph->adj_iter_begin(v); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
			Vertex adjVertex = pAdjNode->getAdjVertex();
			T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
			if (!collected[adjVertex] && adjWeight != 0) {
				path_[adjVertex] = v;
				if (adjVertex == des) {
					free(collected);
					vqueue.~VQueue();
					return true;
				}
				collected[adjVertex] = true;
				vqueue.push(adjVertex);
			}
		}
	} //while
	free(collected);
	return false;
}

template<typename T>
inline bool Dinic<T>::dinic(Graph * pGraph, Vertex src, Vertex des, T * pMaxFlow) {
	if (!pGraph->isDirected()) return false;
	if (!pGraph->isWeighted()) return false;
	int nVertexes = pGraph->getVertexesNum();
	path_ = new Vertex[nVertexes];
	*pMaxFlow = 0;
	while (bfs(pGraph, src, des)) {
		//Find the minimum flow on the path
		T minFlowOnPath = NO_VALUE;
		for (Vertex v = des; v != src; v = path_[v]) {
			T flow = ((WGraph<T> *)pGraph)->getEdgeWeight(path_[v], v);
			if (flow < minFlowOnPath || minFlowOnPath == NO_VALUE)
				minFlowOnPath = flow;
		}
		(*pMaxFlow) += minFlowOnPath;
		for (Vertex v = des; v != src; v = path_[v]) {
			((WGraph<T> *)pGraph)->increaseEdgeWeight(path_[v], v, (-1) * minFlowOnPath);
			((WGraph<T> *)pGraph)->increaseEdgeWeight(v, path_[v], minFlowOnPath);
		}
	}
	free(path_);
	return true;
}