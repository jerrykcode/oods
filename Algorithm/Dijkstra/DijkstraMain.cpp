#include "GraphInput.h"
#include "Dijkstra.h"
#include "Dijkstra.cpp"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph<WeightType> *pGraph =	graphInput.createGraphByInput();
	Dijkstra<WeightType> dijkstra;
	Vertex src, des;
	cout << "Enter the src and des: " << endl;
	cin >> src >> des;
	vector<Vertex> path;
	int dist = dijkstra.shortestPath(pGraph, src, des, path);
	if (dist == NO_VALUE) {
		cout << "Graph is not connected. We can not travel from " << src << " to " << des << endl;
	}
	else {
		cout << "The shortest distance between " << src << " and " << des  << " is " << dist << endl;
		cout << "The shortest path :";
		for (Vertex v : path) {
			cout << " " << v;
		}
	}
	cout << endl;
	pGraph->clear();
	return 0;
}
