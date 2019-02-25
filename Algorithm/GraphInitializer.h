#pragma once
#include "LGraph.h"
#include "MGraph.h"

template<typename T>
class GraphInitializer {
public:
	GraphInitializer() {}
	~GraphInitializer() {}
	
	Graph<T> * createGraph(int nVertexes, bool isDirected, vector<Edge<T>>& edges) {
		Graph<T> *pGraph;
		int nEdges;
		if (isDirected)
			nEdges = edges.size();
		else
			nEdges = edges.size() * 2;
		if (nEdges >= nVertexes * (nVertexes / 2)) {
			pGraph = (Graph<T> *)(new MGraph<T>(nVertexes, isDirected));
		}
		else {
			pGraph = (Graph<T> *)(new LGraph<T>(nVertexes, isDirected));
		}
		for (Edge<T> edge : edges) {
			pGraph->insertEdge(edge);			
		}
		return pGraph;
	}
};
