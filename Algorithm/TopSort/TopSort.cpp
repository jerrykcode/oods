#include "TopSort.h"

template<typename T>
inline TopSort<T>::TopSort() {

}

template<typename T>
TopSort<T>::~TopSort() {

}

template<typename T>
void TopSort<T>::top(Graph<T>* pGraph, T * pMaxWeight, vector<Edge<T>>& keyActivities) {
	if (!pGraph->isGraphDirected()) {
		*pMaxWeight = NO_VALUE;
		return;
	}
	int nVertexes = pGraph->getVertexesNum();
	int nEdges = pGraph->getEdgesNum();
	if (nVertexes <= 1 || nEdges <= 0) {
		*pMaxWeight = NO_VALUE;
		return;
	}
	inDegree_ = new int[nVertexes];
	fill(inDegree_, inDegree_ + nVertexes, 0);
	outDegree_ = new int[nVertexes];
	fill(outDegree_, outDegree_ + nVertexes, 0);
	Graph<T> *pInverseGraph;
	if (nEdges >= nVertexes * (nVertexes / 2))
		pInverseGraph = new MGraph<T>(nVertexes, false);
	else
		pInverseGraph = new LGraph<T>(nVertexes, false);
	for (Vertex v = 0; v < nVertexes; v++) {
		for (AdjNode<T> adjNode = pGraph->adj_iter_begin(v);
				adjNode.getAdjVertex() != NO_VALUE;
				adjNode = pGraph->adj_iter_next()) {
			Vertex adjVertex = adjNode.getAdjVertex();
			T adjWeight = adjNode.getAdjWeight();
			inDegree_[adjVertex]++;
			outDegree_[v]++;
			pInverseGraph->insertEdge(Edge<T>(adjVertex, v, adjWeight));
		}
	}
	earliestStartTime_ = new T[nVertexes];
	fill(earliestStartTime_, earliestStartTime_ + nVertexes, 0);
	int nVertexCount = 0;
	for (Vertex v = 0; v < nVertexes; v++)
		if (inDegree_[v] == 0) {
			vqueue_.push(v);
			nVertexCount++;
		}
	while (!vqueue_.empty()) {
		Vertex v = vqueue_.front();
		vqueue_.pop();
		for (AdjNode<T> adjNode = pGraph->adj_iter_begin(v);
				adjNode.getAdjVertex() != NO_VALUE;
				adjNode = pGraph->adj_iter_next()) {
			Vertex adjVertex = adjNode.getAdjVertex();
			T adjWeight = adjNode.getAdjWeight();
			if (earliestStartTime_[v] + adjWeight > earliestStartTime_[adjVertex])
				earliestStartTime_[adjVertex] = earliestStartTime_[v] + adjWeight;
			if ((--inDegree_[adjVertex]) == 0) {
				vqueue_.push(adjVertex);
				nVertexCount++;
			}
		}
	}
	free(inDegree_);
	queue<Vertex>().swap(vqueue_);
	if (nVertexCount < nVertexes) { //Loop exist
		*pMaxWeight = NO_VALUE;
		free(outDegree_);
		free(earliestStartTime_);
		return;
	}
	*pMaxWeight = 0;
	for (Vertex v = 0; v < nVertexes; v++) {
		if (earliestStartTime_[v] > *pMaxWeight)
			*pMaxWeight = earliestStartTime_[v];
		if (outDegree_[v] == 0)
			vqueue_.push(v);
	}
	latestEndTime_ = new T[nVertexes];
	fill(latestEndTime_, latestEndTime_ + nVertexes, *pMaxWeight);
	while (!vqueue_.empty()) {
		Vertex v = vqueue_.front();
		vqueue_.pop();
		for (AdjNode<T> adjNode = pInverseGraph->adj_iter_begin(v);	
				adjNode.getAdjVertex() != NO_VALUE;	
				adjNode = pInverseGraph->adj_iter_next()) {
			Vertex adjVertex = adjNode.getAdjVertex();
			T adjWeight = adjNode.getAdjWeight();
			if (latestEndTime_[v] - adjWeight < latestEndTime_[adjVertex])
				latestEndTime_[adjVertex] = latestEndTime_[v] - adjWeight;
			if (latestEndTime_[v] - adjWeight == earliestStartTime_[adjVertex])
				keyActivities.push_back(Edge<T>(adjVertex, v, adjWeight));
			if ((--outDegree_[adjVertex]) == 0) {
				vqueue_.push(adjVertex);
			}
		}
	}
	queue<Vertex>().swap(vqueue_);
	free(outDegree_);
	free(earliestStartTime_);
	free(latestEndTime_);
}