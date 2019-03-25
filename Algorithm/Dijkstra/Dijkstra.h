#pragma once
#include "Graph.h"
#include "MGraph.h"
#include "LGraph.h"
#include <stack>
#include <queue>

template<typename T>
class Dijkstra {
public:
	Dijkstra();
	~Dijkstra();

	/* Return the shortest distance between src and des. */
	T shortestPath(Graph *pGraph, Vertex src, Vertex des, vector<Vertex>& path);

	/* Get the shortest distance between src and all the vertexes. */
	void shortestPath(Graph *pGraph, Vertex src, T *dists, vector<Vertex>* paths);

	void setOptimize(bool heapOptimize) {
		heapOptimize_ = heapOptimize;
	}

private:
	T *dist_;
	bool *collected_;
	Vertex *path_;

	bool heapOptimize_;

	bool dijkstra(Graph *pGraph, Vertex src, Vertex des);
	bool dijkstra_no_optimize(Graph *pGraph, Vertex src, Vertex des);	
	void findMin(Vertex *pMinVertex, T *pMinDist, int nVertexes);
	bool dijkstra_optimize(Graph *pGraph, Vertex src, Vertex des);
	void getPath(Vertex src, Vertex des, vector<Vertex>& path);

	bool memory_alloced_;

	//Data structures used by priority_queue
	struct Node {
		Vertex v;
		T dist;
		Node(Vertex v, T dist) : v(v), dist(dist) {}
	};

	struct cmp {
		bool operator() (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};
};


template<typename T>
Dijkstra<T>::Dijkstra() : heapOptimize_(false) {

}

template<typename T>
Dijkstra<T>::~Dijkstra() {

}

template<typename T>
T Dijkstra<T>::shortestPath(Graph *pGraph, Vertex src, Vertex des, vector<Vertex>& path) {
	T result;
	if (dijkstra(pGraph, src, des)) {
		result = dist_[des];
		getPath(src, des, path);
	}
	else result = NO_VALUE;
	if (memory_alloced_) {
		free(dist_);
		free(path_);
	}
	return result;
}

template<typename T>
void Dijkstra<T>::shortestPath(Graph *pGraph, Vertex src, T * dists, vector<Vertex>* paths) {
	if (dijkstra(pGraph, src, NO_VALUE)) {
		for (int i = 0; i < pGraph->getVertexesNum(); i++) {
			dists[i] = dist_[i];
			getPath(src, i, paths[i]);
		}
	}
	else {
		fill(dists, dists + pGraph->getVertexesNum(), NO_VALUE);
	}
	if (memory_alloced_) {
		free(dist_);
		free(path_);
	}
}

template<typename T>
inline bool Dijkstra<T>::dijkstra(Graph * pGraph, Vertex src, Vertex des) {
	return heapOptimize_ ? dijkstra_optimize(pGraph, src, des) : dijkstra_no_optimize(pGraph, src, des);
}

template<typename T>
bool Dijkstra<T>::dijkstra_no_optimize(Graph *pGraph, Vertex src, Vertex des) {
	memory_alloced_ = false;
	if (!pGraph->isWeighted()) return false;
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
	memory_alloced_ = true;
	dist_[src] = 0;
	collected_[src] = true;
	for (AdjNode * pAdjNode = pGraph->adj_iter_begin(src); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
		//For every vertex adjacent to src, initialize the minimum distance from src to the vertex to be
		//the weight of the edge between src and it
		Vertex adjVertex = pAdjNode->getAdjVertex();
		T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
		pGraph->adj_iter_clear();
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
		for (AdjNode *pAdjNode = pGraph->adj_iter_begin(minVertex); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
			//For every vertexes adjacent to minVertex
			Vertex adjVertex = pAdjNode->getAdjVertex();
			T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
			pGraph->adj_iter_clear();
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
		if (!collected_[i] && dist_[i] != NO_VALUE && (*pMinDist == NO_VALUE || dist_[i] < *pMinDist)) {
			*pMinDist = dist_[i];
			*pMinVertex = i;
		}
}

template<typename T>
inline bool Dijkstra<T>::dijkstra_optimize(Graph * pGraph, Vertex src, Vertex des) {
	memory_alloced_ = false;
	if (!pGraph->isWeighted()) return false;
	//Calculates the shortest distance by dijkstra algorithm with an optimization by priority queue
	int nVertexes = pGraph->getVertexesNum();
	if (nVertexes <= 1) return false;
	if (src < 0 || src >= nVertexes) return false;
	if (des != NO_VALUE && (des < 0 || des >= nVertexes)) return false;
	//allocate memory
	dist_ = new T[nVertexes];
	fill(dist_, dist_ + nVertexes, NO_VALUE);
	path_ = new Vertex[nVertexes];
	fill(path_, path_ + nVertexes, NO_VALUE);
	collected_ = new bool[nVertexes];
	fill(collected_, collected_ + nVertexes, false);
	memory_alloced_ = true;
	dist_[src] = 0;
	path_[src] = src;
	priority_queue<Node, vector<Node>, cmp> q;
	q.push(Node(src, dist_[src]));
	while (!q.empty()) {
		Vertex minV = q.top().v;
		q.pop();
		if (collected_[minV]) continue;
		collected_[minV] = true;
		if (des != NO_VALUE && des == minV) {
			break;
		}
		for (AdjNode *pAdjNode = pGraph->adj_iter_begin(minV); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
			Vertex adjVertex = pAdjNode->getAdjVertex();
			T adjWeight = ((WAdjNode<T>*)pAdjNode)->getAdjWeight();
			pGraph->adj_iter_clear();
			if (adjWeight < 0) {
				free(collected_);
				return false;
				//delete memory of dist_ and path_ in shortestPath function
			}
			if (!collected_[adjVertex]) {
				if (dist_[minV] + adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					dist_[adjVertex] = dist_[minV] + adjWeight;
					q.push(Node(adjVertex, dist_[adjVertex]));
					path_[adjVertex] = minV;
				}
			}
		}
	} //while
	free(collected_);
	//delete memory of dist_ and path_ in shortestPath function
	return true;
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