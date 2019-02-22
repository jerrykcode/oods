#include "Prim.h"

template<typename T>
Prim<T>::Prim() {

}

template<typename T>
Prim<T>::~Prim() {

}

template<typename T>
void Prim<T>::getMST(Graph<T> *pGraph, T *pMstWeight, vector<Edge<T>>& mstEdgeSet) {
	int nVertexes = pGraph->getVertexesNum();
	int nEdges = pGraph->getEdgesNum();
	if (nVertexes == 0 || nEdges == 0) {
		*pMstWeight = NO_VALUE;
		return;
	}
	dist_ = new T[nVertexes];
	path_ = new Vertex[nVertexes];
	fill(dist_, dist_ + nVertexes, NO_VALUE);
	fill(path_, path_ + nVertexes, NO_VALUE);
	Vertex src = 0;
	dist_[src] = 0;
	for (AdjNode<T> adjNode = pGraph->adj_iter_begin(src);
			adjNode.getAdjVertex() != NO_VALUE;
			adjNode = pGraph->adj_iter_next()) { //All vertexes adjacent to src
		Vertex adjVertex = adjNode.getAdjVertex();
		T adjWeight = adjNode.getAdjWeight();
		dist_[adjVertex] = adjWeight;
		path_[adjVertex] = src;
	}
	*pMstWeight = 0;
	int nVCollected = 1; //src already collected
	while (true) {
		Vertex minVertex;
		T minDist;
		findMin(nVertexes, &minVertex, &minDist);
		if (minDist == NO_VALUE) {
			break;
		}
		(*pMstWeight) += minDist;
		mstEdgeSet.push_back(Edge<T>(path_[minVertex], minVertex, minDist));
		dist_[minVertex] = 0;
		nVCollected++;
		for (AdjNode<T> adjNode = pGraph->adj_iter_begin(minVertex);
				adjNode.getAdjVertex() != NO_VALUE;
				adjNode = pGraph->adj_iter_next()) { //All vertexes adjacent to minVertex
			Vertex adjVertex = adjNode.getAdjVertex();
			T adjWeight = adjNode.getAdjWeight();
			if (dist_[adjVertex]) {
				if (adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					dist_[adjVertex] = adjWeight;
					path_[adjVertex] = minVertex;
				}
			}
		}
	} //while
	deleteMemory();
	if (nVCollected < nVertexes) { //Graph not connected
		*pMstWeight = 0;
		mstEdgeSet.clear();	
	}
}

template<typename T>
void Prim<T>::getMST(Graph<T>* pGraph, T * pMstWeight, Graph<T>** ppMstGraph) {
	vector<Edge<T>> mstEdgeSet;
	getMST(pGraph, pMstWeight, mstEdgeSet);
	GraphInitializer<T> graphInit;
	*ppMstGraph = graphInit.createGraph(pGraph->getVertexesNum(), mstEdgeSet);
	mstEdgeSet.clear();
	vector<Edge<T>>().swap(mstEdgeSet);
}

template<typename T>
void Prim<T>::findMin(int nVertexes, Vertex * pMinVertex, T * pMinDist) {
	*pMinDist = NO_VALUE;
	for (int i = 0; i < nVertexes; i++)
		if (dist_[i] && dist_[i] != NO_VALUE && (*pMinDist == NO_VALUE || dist_[i] < *pMinDist)) {
			*pMinDist = dist_[i];
			*pMinVertex = i;
		}
}

template<typename T>
void Prim<T>::deleteMemory() {
	free(dist_);
	free(path_);
}