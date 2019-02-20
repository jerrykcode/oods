#include "GraphInitializer.h"
#include "Dijkstra.h"
#include "Dijkstra.cpp"

typedef int WeightType;

int main() {
	GraphInitializer<WeightType> graphInit;
	Dijkstra<WeightType> dijkstra;
	int nVertexes;
	int nEdges;
	cin >> nVertexes >> nEdges;
	vector<Edge<WeightType>> edges;
	edges.resize(nEdges);
	for (int i = 0; i < nEdges; i++) {
		Vertex v, w;
		WeightType weight;
		cin >> v >> w >> weight;
		edges[i] = Edge<WeightType>(v, w, weight);
	}
	Graph<WeightType> *pGraph = graphInit.createGraph(nVertexes, edges);
	edges.clear();
	vector<Edge<WeightType>>().swap(edges);
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		Vertex src, des;
		cin >> src >> des;
		vector<Vertex> path;
		int dist = dijkstra.shortestPath(pGraph, src, des, path);
		cout << "shortest dist : " << dist << endl;
		cout << "path :";
		for (auto it = path.begin(); it != path.end(); it++)
			cout << " " << *it;
		cout << endl;
	}
	pGraph->clear();
	return 0;
}
