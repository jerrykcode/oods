#include "LGraph.h"
#include "MGraph.h"

template<typename T>
class GraphInitializer {
public:
	GraphInitializer() {}
	~GraphInitializer() {}
	
	Graph<T> * createGraph(int nVertexes, vector<Edge<T>>& edges) {
		Graph<T> *pGraph;
		if (edges.size() >= nVertexes * (nVertexes / 4)) {
			pGraph = (Graph<T> *)(new MGraph<T>(nVertexes));
		}
		else {
			pGraph = (Graph<T> *)(new LGraph<T>(nVertexes));
		}
		for (Edge<T> edge : edges) {
			pGraph->insertEdge(edge);			
		}
		return pGraph;
	}
};
