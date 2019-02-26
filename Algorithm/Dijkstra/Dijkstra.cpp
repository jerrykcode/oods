#include "Dijkstra.h"

template<typename T>
Dijkstra<T>::Dijkstra() {

}

template<typename T>
Dijkstra<T>::~Dijkstra() {

}

template<typename T>
T Dijkstra<T>::shortestPath(Graph<T> *pGraph, Vertex src, Vertex des, vector<Vertex>& path) {
	T result;
	if (dijkstra(pGraph, src, des)) {
		result = dist_[des];
		getPath(src, des, path);		
	}
	else result = NO_VALUE;
	free(dist_);
	free(path_);
	return result;
}

template<typename T>
void Dijkstra<T>::shortestPath(Graph<T>* pGraph, Vertex src, T * dists, vector<Vertex>* paths) {
	if (dijkstra(pGraph, src, NO_VALUE)) {
		for (int i = 0; i < pGraph->getVertexesNum(); i++) {
			dists[i] = dist_[i];
			getPath(src, i, paths[i]);
		}
	}
	else {
		fill(dists, dists + pGraph->getVertexesNum(), NO_VALUE);
	}
	free(dist_);
	free(path_);
}

template<typename T>
bool Dijkstra<T>::dijkstra(Graph<T>* pGraph, Vertex src, Vertex des) {
	//Calculate shortest distance by Dijkstra
	int nVertexes = pGraph->getVertexesNum();
	if (nVertexes <= 1) return false;
	if (src < 0 || src >= nVertexes) return false;
	if (des != NO_VALUE && (des < 0 || des >= nVertexes)) return false;
	dist_ = new T[nVertexes];
	fill(dist_, dist_ + nVertexes, NO_VALUE);
	path_ = new Vertex[nVertexes];
	fill(path_, path_ + nVertexes, NO_VALUE);
	collected_ = new bool[nVertexes];
	fill(collected_, collected_ + nVertexes, false);
	dist_[src] = 0;
	collected_[src] = true;
	for (AdjNode<T> adjNode = pGraph->adj_iter_begin(src);
			adjNode.getAdjVertex() != NO_VALUE;
			adjNode = pGraph->adj_iter_next()) {
		//For every vertexes adjacent to src, the minimum distance from src to the vertex is the
		//weight of the edge between src and it
		Vertex adjVertex = adjNode.getAdjVertex();
		T adjWeight = adjNode.getAdjWeight();
		if (adjWeight < 0) {
			free(collected_);
			return false;
			//Delete the memory of dist_, path_ in shortestPath function
		}
		dist_[adjVertex] = adjWeight;
		path_[adjVertex] = src;
	}
	Vertex minVertex;
	T minDist;
	while (true) {
		findMin(&minVertex, &minDist, nVertexes);
		if (minVertex == des) { 
			//If des != NO_VALUE, minVertex == des means we find the shortest distance from src to des,
			//if des == NO_VALUE, we need to find the shortest distance between src and every other vertexes,
			//and minVertex == des, that is minVertex == NO_VALUE, means we have finished the task
			break;
		}
		if (minVertex == NO_VALUE) {
			//This case occurs when des != NO_VALUE, but we can not travel from src to des
			break;
		}
		//The shortest distance from src to minVertex can not be changed, collected it
		collected_[minVertex] = true;
		for (AdjNode<T> adjNode = pGraph->adj_iter_begin(minVertex);
				adjNode.getAdjVertex() != NO_VALUE;
				adjNode = pGraph->adj_iter_next()) {
			//For every vertexes adjacent to minVertex
			Vertex adjVertex = adjNode.getAdjVertex();
			T adjWeight = adjNode.getAdjWeight();
			if (adjWeight < 0) {
				free(collected_);
				return false;
				//Delete the memory of dist_, path_ in shortestPath function
			}
			if (!collected_[adjVertex]) {
				if (minDist + adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					//If the distance between src and minVertex + the distance from minVertex to adjVertex 
					//is shorter than dist_[adjVertex], any distance is shorter than NO_VALUE
					dist_[adjVertex] = minDist + adjWeight;
					path_[adjVertex] = minVertex;
				}
			}
		}
	} //while
	free(collected_);
	return true;
	//Delete the memory of dist_, path_ in shortestPath function
}

template<typename T>
void Dijkstra<T>::findMin(Vertex *pMinVertex, T *pMinDist, int nVertexes) {
	*pMinVertex = NO_VALUE;
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