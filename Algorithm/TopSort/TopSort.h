#pragma once
#include "MGraph.h"
#include "LGraph.h"

#include <queue>

template<typename T>
class TopSort {
public:
	TopSort();
	~TopSort();

	void top(Graph<T> *pGraph, T *pMaxWeight, vector<Edge<T>>& keyActivities);
private:
	queue<Vertex> vqueue_;
	int *inDegree_;
	int *outDegree_;
	T *earliestStartTime_;
	T *latestEndTime_;
};