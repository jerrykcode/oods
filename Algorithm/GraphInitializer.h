#pragma once
#include "LGraph.h"
#include "MGraph.h"

#define MAX_MATRIX_SIZE 500

template<typename T>
class GraphInitializer {
public:
	GraphInitializer() {}
	~GraphInitializer() {}
	
	Graph * createGraph(int nVertexes, bool isDirected, bool isWeighted, vector<Edge*>& edges) {
		if (nVertexes < 1) return NULL;
		Graph *pGraph;
		int nEdges = edges.size();
		if (!isDirected) nEdges *= 2;
		if (nEdges > nVertexes * (nVertexes - 1)) return NULL;
		if (isWeighted) {
			if (nVertexes <= MAX_MATRIX_SIZE && nEdges >= (nVertexes * (nVertexes - 1) / 2)) {
				pGraph = (Graph *)(new MatrixWGraph<T>(nVertexes, nEdges, isDirected));
			}
			else {
				pGraph = (Graph *)(new ListWGraph<T>(nVertexes, nEdges, isDirected));
			}
		}
		else {
			if (nVertexes <= MAX_MATRIX_SIZE && nEdges >= (nVertexes * (nVertexes - 1) / 2)) {
				pGraph = (Graph *)(new MatrixUNWGraph(nVertexes, nEdges, isDirected));
			}
			else {
				pGraph = (Graph *)(new ListUNWGraph(nVertexes, nEdges, isDirected));
			}
		}
		for (Edge* pEdge : edges) {
			pGraph->insertEdge(pEdge);			
		}
		return pGraph;
	}
};
