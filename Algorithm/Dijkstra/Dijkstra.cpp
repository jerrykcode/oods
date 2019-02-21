#include "Dijkstra.h"

template<typename T>
Dijkstra<T>::Dijkstra() {

}

template<typename T>
Dijkstra<T>::~Dijkstra() {

}

template<typename T>
T Dijkstra<T>::shortestPath(Graph<T> *pGraph, Vertex src, Vertex des, vector<Vertex>& path) {
	int nVertexes = pGraph->getVertexesNum();
	if (nVertexes <= 0) return NO_VALUE;
	if (pGraph->getEdgesNum() == 0) return NO_VALUE;
	if (src < 0 || src >= nVertexes || des < 0 || des >= nVertexes) return NO_VALUE;
	dist_ = new T[nVertexes];
	collected_ = new bool[nVertexes];
	path_ = new Vertex[nVertexes];
	fill(dist_, dist_ + nVertexes, NO_VALUE);
	fill(collected_, collected_ + nVertexes, false);
	fill(path_, path_ + nVertexes, NO_VALUE);
	dist_[src] = 0;
	Vertex minVertex;
	T minDist;
	while (true) {
		findMin(&minVertex, &minDist, nVertexes);	
		if (minDist == NO_VALUE) {
			break;
		}
		if (minVertex == des) {
			break;
		}
		collected_[minVertex] = true;
		for (AdjNode<T> adjNode = pGraph->adj_iter_begin(minVertex);
				adjNode.getAdjVertex() != NO_VALUE; 
				adjNode = pGraph->adj_iter_next()) {
			Vertex v = adjNode.getAdjVertex();
			T weight = adjNode.getAdjWeight();
			if (!collected_[v]) {
				if (dist_[v] == NO_VALUE || minDist + weight < dist_[v]) {
					dist_[v] = minDist + weight;
					path_[v] = minVertex;
				}
			}
		}
	}
	getPath(src, des, path);
	deleteMemory();
	return minDist;
}

template<typename T>
void Dijkstra<T>::findMin(Vertex *pMinVertex, T *pMinDist, int nVertexes) {
	*pMinDist = NO_VALUE;
	for (int i = 0; i < nVertexes; i++)
	       if (!collected_[i] && dist_[i] != NO_VALUE && (*pMinDist == NO_VALUE || dist_[i] < *pMinDist))	{
			*pMinDist = dist_[i];
			*pMinVertex = i;
	       }
}

template<typename T>
void Dijkstra<T>::getPath(Vertex src, Vertex des, vector<Vertex>& path) {
	stack<Vertex> s;
	s.push(des);
	while (des != src) {
		s.push(path_[des]);
		des = path_[des];
	}	
	while (!s.empty()) {
		path.push_back(s.top());
		s.pop();
	}	
	stack<Vertex>().swap(s);
}

template<typename T>
void Dijkstra<T>::deleteMemory() {
	free(dist_);
	free(collected_);
	free(path_);
}
