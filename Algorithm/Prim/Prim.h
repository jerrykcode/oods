#pragma once
#include "GraphInitializer.h"
#include <queue>

template<typename T>
class Prim {
public:
	Prim();
	~Prim();

	//Calculate the MST of a graph

	/** @param pMstEdges vector of pointers of edges in the resulting MST */
	bool getMST(Graph *pGraph, T *pMstWeight, vector<Edge*>& pMstEdges);

	/* @paran mstEdges vector of edges in the resulting MST */
	bool getMST(Graph *pGraph, T *pMstWeight, vector<WEdge<T>>& mstEdges);

	/* @param pMstGraph pointer of a pointer of a graph represented the resulting MST */
	bool getMST(Graph *pGraph, T *pMstWeight, Graph **ppMstGraph);

	void setOptimize(bool use_optimze) {
		use_optimize_ = use_optimze;
	}

private:
	struct Node {
		Vertex v;
		T dist;
		Node(Vertex v, T dist) : v(v), dist(dist) {}
	};
	struct cmp {
		bool operator () (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};

	//Prim algorithm
	bool prim(Graph *pGraph, T *pMstWeight, vector<Edge*>& pMstEdges);
	bool prim_no_optimize(Graph *pGraph, T *pMstWeight, vector<Edge*>& pMstEdges);
	bool prim_optimize(Graph *pGraph, T *pMstWeight, vector<Edge*>& pMstEdges);

	void findMin(T *pMinDist, Vertex *pMinVertex);

	bool use_optimize_;
	T *dist_;
	Vertex *pre_;
	int nVertexes_;
};

template<typename T>
inline Prim<T>::Prim() : use_optimize_(false) {

}

template<typename T>
inline Prim<T>::~Prim() {

}

template<typename T>
inline bool Prim<T>::getMST(Graph * pGraph, T * pMstWeight, vector<Edge*>& pMstEdges) {
	return prim(pGraph, pMstWeight, pMstEdges);
}

template<typename T>
inline bool Prim<T>::getMST(Graph * pGraph, T * pMstWeight, vector<WEdge<T>>& mstEdges) {
	vector<Edge *> pMstEdges;
	if (prim(pGraph, pMstWeight, pMstEdges)) {
		for (auto it = pMstEdges.begin(); it != pMstEdges.end(); it++) {			
			if (*it != NULL) 
				mstEdges.push_back(*((WEdge<T> *)(*it)));
			}
		return true;
	}
	else return false;
}

template<typename T>
inline bool Prim<T>::getMST(Graph * pGraph, T * pMstWeight, Graph ** ppMstGraph) {
	vector<Edge *> pMstEdges;
	if (prim(pGraph, pMstWeight, pMstEdges)) {
		//Create the MST graph
		GraphInitializer<T> graphInit;
		*ppMstGraph = graphInit.createGraph(pGraph->getVertexesNum(), false, true, pMstEdges);
		for (auto it = pMstEdges.begin(); it != pMstEdges.end(); it++)
			if (*it != NULL) {
				delete (*it);
				*it = NULL;
			}
		pMstEdges.clear();
		vector<Edge*>().swap(pMstEdges);
		return true;
	}
	else return false;
}

template<typename T>
inline bool Prim<T>::prim(Graph * pGraph, T * pMstWeight, vector<Edge*>& pMstEdges) {
	return use_optimize_ ? prim_optimize(pGraph, pMstWeight, pMstEdges) : prim_no_optimize(pGraph, pMstWeight, pMstEdges);
}

template<typename T>
inline bool Prim<T>::prim_no_optimize(Graph * pGraph, T * pMstWeight, vector<Edge*>& pMstEdges) {
	if (!pGraph->isWeighted()) return false; //The graph must be weighted
	if (pGraph->isDirected()) return false; //The graph must NOT be directed
	*pMstWeight = 0;
	if (!pMstEdges.empty()) {
		for (auto it = pMstEdges.begin(); it != pMstEdges.end(); it++)
			if (*it != NULL) {
				delete (*it);
				*it = NULL;
			}
		pMstEdges.clear();
	}
	nVertexes_ = pGraph->getVertexesNum();
	dist_ = new T[nVertexes_]; //dist_[v] means the current minimum distance between v and the MST
	fill(dist_, dist_ + nVertexes_, NO_VALUE);
	pre_ = new Vertex[nVertexes_];
	fill(pre_, pre_ + nVertexes_, NO_VALUE);
	Vertex src = 0;
	dist_[src] = 0;
	int vertexCount = 1;
	for (AdjNode * pAdjNode = pGraph->adj_iter_begin(src); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
		//For every vertex adjacent to src, initialize the minimum distance between MST and the vertex to be
		//the weight of the edge bwtween src and it
		Vertex adjVertex = pAdjNode->getAdjVertex();
		T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
		pGraph->adj_iter_clear();
		if (adjWeight < 0) {
			free(dist_);
			free(pre_);
			return false;
		}
		dist_[adjVertex] = adjWeight;
		pre_[adjVertex] = src;
	}
	T minDist;
	Vertex minVertex;
	while (true) {
		findMin(&minDist, &minVertex);
		if (minDist == NO_VALUE) {
			break;
		}
		(*pMstWeight) += minDist;
		pMstEdges.push_back((Edge *)(new WEdge<T>(pre_[minVertex], minVertex, minDist)));
		dist_[minVertex] = 0;
		vertexCount++;
		for (AdjNode *pAdjNode = pGraph->adj_iter_begin(minVertex); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
			//For every vertex adjacent to minVertex
			Vertex adjVertex = pAdjNode->getAdjVertex();
			T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
			pGraph->adj_iter_clear();
			if (adjWeight < 0) {
				goto CLEAR;
			}
			if (dist_[adjVertex]) { //If adjVertex has not collected into the MST yet
				if (adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					dist_[adjVertex] = adjWeight;
					pre_[adjVertex] = minVertex;
				}
			}
		}
	} //while
CLEAR:
	free(dist_);
	free(pre_);
	if (vertexCount < nVertexes_) { //If the graph is not connected
		for (auto it = pMstEdges.begin(); it != pMstEdges.end(); it++)
			if (*it != NULL) {
				delete (*it);
				*it = NULL;
			}
		pMstEdges.clear();
		vector<Edge*>().swap(pMstEdges);
		return false;
	}
	return true;
}


template<typename T>
inline void Prim<T>::findMin(T * pMinDist, Vertex * pMinVertex) {
	*pMinDist = NO_VALUE;
	for (int i = 0; i < nVertexes_; i++)
		if (dist_[i] && dist_[i] != NO_VALUE && (dist_[i] < (*pMinDist) || (*pMinDist) == NO_VALUE)) {
			*pMinDist = dist_[i];
			*pMinVertex = i;
		}
}

template<typename T>
inline bool Prim<T>::prim_optimize(Graph * pGraph, T * pMstWeight, vector<Edge*>& pMstEdges)
{
	if (!pGraph->isWeighted()) return false; //The graph must be weighted
	if (pGraph->isDirected()) return false; //The graph must NOT be directed
	if (!pMstEdges.empty()) {
		//clear pMstEdges
		for (auto it = pMstEdges.begin(); it != pMstEdges.end(); it++)
			if (*it != NULL) {
				delete (*it);
				*it = NULL;
			}
		pMstEdges.clear();
	}
	*pMstWeight = 0; //Initialize
	nVertexes_ = pGraph->getVertexesNum();	
	if (nVertexes_ < 1) return false;
	else if (nVertexes_ == 1) return true;
	dist_ = new T[nVertexes_];
	fill(dist_, dist_ + nVertexes_, NO_VALUE);
	pre_ = new Vertex[nVertexes_];
	Vertex src = 0;
	dist_[src] = 0;
	pre_[src] = 0;
	priority_queue<Node, vector<Node>, cmp> q;
	q.push(Node(src, dist_[src]));
	int vcount = 0;
	while (!q.empty()) {
		Vertex minVertex = q.top().v;
		q.pop();
		if (minVertex != src) {
			if (dist_[minVertex] == 0) continue;
			*pMstWeight += dist_[minVertex];
			pMstEdges.push_back((Edge *)(new WEdge<T>(pre_[minVertex], minVertex, dist_[minVertex])));
			dist_[minVertex] = 0;
		}
		vcount++;
		for (AdjNode *pAdjNode = pGraph->adj_iter_begin(minVertex); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
			//For every vertexes adjacent to minVertex
			Vertex adjVertex = pAdjNode->getAdjVertex();
			T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
			pGraph->adj_iter_clear();
			if (adjWeight < 0) {
				goto CLEAR;
			}
			if (dist_[adjVertex] != 0) {
				if (adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					dist_[adjVertex] = adjWeight;
					q.push(Node(adjVertex, dist_[adjVertex]));
					pre_[adjVertex] = minVertex;
				}
			}
		}
	} //while
CLEAR:
	free(dist_);
	free(pre_);
	if (vcount < nVertexes_) {
		for (auto it = pMstEdges.begin(); it != pMstEdges.end(); it++)
			if (*it != NULL) {
				delete (*it);
				*it = NULL;
			}
		pMstEdges.clear();
		vector<Edge *>().swap(pMstEdges);
		return false;
	}
	return true;
}
