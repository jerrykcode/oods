#include "GraphInput.h"
#include "Dijkstra.h"
#include "Dijkstra.cpp"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph<WeightType> *pGraph =	graphInput.createGraphByInput();
	Dijkstra<WeightType> dijkstra;
	Vertex src, des;
	cout << "Enter the src: " << endl;
	cin >> src;
	cout << "Enter the des, enter " << NO_VALUE << " to calculate the shortest disance bewteen src and every vertexes: " << endl;
	cin >> des;
	if (des != NO_VALUE) {
		vector<Vertex> path;
		WeightType dist = dijkstra.shortestPath(pGraph, src, des, path);
		if (dist == NO_VALUE) {
			cout << "Error!" << endl;
		}
		else {
			cout << "The shortest distance between " << src << " and " << des << " is " << dist << endl;
			cout << "The shortest path :";
			for (Vertex v : path) {
				cout << " " << v;
			}
			cout << endl;
		}
	}
	else {
		int nVertexes = pGraph->getVertexesNum();
		WeightType *dists = new WeightType[nVertexes];
		vector<Vertex> *paths = new vector<Vertex>[nVertexes];
		dijkstra.shortestPath(pGraph, src, dists, paths);
		if (dists[0] == NO_VALUE) {
			cout << "Error!" << endl;
		}
		else {
			for (Vertex v = 0; v < nVertexes; v++) {
				cout << "The shortest distance between " << src << " and " << v << " is " << dists[v] << endl;
				cout << "The shortest path :";
				for (Vertex w : paths[v]) {
					cout << " " << w;
				}
				cout << endl;
			}
		}
		free(dists);
		for (int i = 0; i < nVertexes; i++) {
			paths[i].clear();
			vector<Vertex>().swap(paths[i]);
		}
	}	
	pGraph->clear();
	return 0;
}
