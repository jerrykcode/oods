#pragma once
#include "LGraph.h"
#include "MGraph.h"

template<typename T>
class TopSort {
public:
	TopSort();
	~TopSort();

	bool top(Graph *pGraph, T *pMaxWeight, vector<WEdge<T>>& keyActivities);

private:

	typedef struct QNode {
		Vertex v;
		struct QNode *next;
		QNode (Vertex v) : v(v), next(NULL) {}
	} *QList;

	class VQueue {
	public:
		VQueue();
		~VQueue();

		void push(Vertex v);
		Vertex pop();
		bool empty();

	private:
		QList head, tail;
	};

	int *inDegree;
	int *outDegree;

	T *earliestStartTime;
	T *latestEndTime;

	VQueue vqueue;
};

template<typename T>
inline TopSort<T>::TopSort() {

}

template<typename T>
inline TopSort<T>::~TopSort() {

}

template<typename T>
inline bool TopSort<T>::top(Graph * pGraph, T * pMaxWeight, vector<WEdge<T>>& keyActivities) {
	if (!pGraph->isDirected()) return false;
	if (!pGraph->isWeighted()) return false;
	int nVertexes = pGraph->getVertexesNum();
	inDegree = new int[nVertexes];
	fill(inDegree, inDegree + nVertexes, 0);
	outDegree = new int[nVertexes];
	fill(outDegree, outDegree + nVertexes, 0);
	for (int i = 0; i < nVertexes; i++) 
		for (AdjNode *pAdjNode = pGraph->adj_iter_begin(i); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
			Vertex adjVeretx = pAdjNode->getAdjVertex();
			inDegree[adjVeretx]++;
			outDegree[i]++;
			pGraph->adj_iter_clear();
		}
	earliestStartTime = new T[nVertexes];
	fill(earliestStartTime, earliestStartTime + nVertexes, 0);
	int vertexCount = 0;
	for (int i = 0; i < nVertexes; i++)
		if (inDegree[i] == 0) {
			vqueue.push(i);
			vertexCount++;
		}
	while (!vqueue.empty()) {
		Vertex v = vqueue.pop();
		for (AdjNode *pAdjNode = pGraph->adj_iter_begin(v); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
			Vertex adjVertex = pAdjNode->getAdjVertex();
			T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
			if (earliestStartTime[v] + adjWeight > earliestStartTime[adjVertex])
				earliestStartTime[adjVertex] = earliestStartTime[v] + adjWeight;
			if (--inDegree[adjVertex] == 0) {
				vqueue.push(adjVertex);
				vertexCount++;
			}
			pGraph->adj_iter_clear();
		}
	}
	free(inDegree);
	*pMaxWeight = NO_VALUE;
	if (vertexCount < nVertexes) {
		free(outDegree);
		free(earliestStartTime);	
		return false;
	}	
	for (int i = 0; i < nVertexes; i++) {
		if (outDegree[i] == 0) vqueue.push(i);
		if (earliestStartTime[i] > *pMaxWeight || *pMaxWeight == NO_VALUE)
			*pMaxWeight = earliestStartTime[i];
	}
	latestEndTime = new T[nVertexes];
	fill(latestEndTime, latestEndTime + nVertexes, *pMaxWeight);
	Graph *pInverseGraph = pGraph->inverseGraph();
	while (!vqueue.empty()) {
		Vertex v = vqueue.pop();
		for (AdjNode *pAdjNode = pInverseGraph->adj_iter_begin(v); pAdjNode != NULL; pAdjNode = pInverseGraph->adj_iter_next()) {
			Vertex adjVertex = pAdjNode->getAdjVertex();
			T adjWeight = ((WAdjNode<T> *)pAdjNode)->getAdjWeight();
			if (latestEndTime[v] - adjWeight < latestEndTime[adjVertex])
				latestEndTime[adjVertex] = latestEndTime[v] - adjWeight;
			if (latestEndTime[v] - earliestStartTime[adjVertex] == adjWeight)
				keyActivities.push_back(WEdge<T>(adjVertex, v, adjWeight));
			if (--outDegree[adjVertex] == 0)
				vqueue.push(adjVertex);
			pInverseGraph->adj_iter_clear();
		}
	}
	free(outDegree);
	free(earliestStartTime);
	free(latestEndTime);
	pInverseGraph->clear();
	return true;
}

//define Vertex Queue
template<typename T>
inline TopSort<T>::VQueue::VQueue() : head(NULL), tail(NULL) {

}

template<typename T>
inline TopSort<T>::VQueue::~VQueue() {
	while (!empty()) pop();
}

template<typename T>
inline void TopSort<T>::VQueue::push(Vertex v) {
	QList qlist = new QNode(v);
	if (head == NULL) {
		head = tail = qlist;
	}
	else {
		tail->next = qlist;
		tail = qlist;
	}
}

template<typename T>
inline Vertex TopSort<T>::VQueue::pop() {
	if (empty()) return NO_VALUE;
	QList qlist = head;
	head = head->next;
	Vertex v = qlist->v;
	delete qlist;
	return v;
}

template<typename T>
inline bool TopSort<T>::VQueue::empty() {
	return head == NULL;
}