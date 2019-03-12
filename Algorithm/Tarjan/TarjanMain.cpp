#include "Tarjan.h"
#include "GraphInput.h"

int main() {
	GraphInput<int> graphInput;
	Graph *pGraph = graphInput.createGraphByInput();
	Tarjan tarjan;
	vector<vector<Vertex>> components;
	tarjan.connectedComponent(pGraph, components);
	for (auto it = components.begin(); it != components.end(); it++) {
		cout << "Vertexes in the component:";
		for (Vertex v : *it) {
			cout << " " << v;
		}
		cout << endl;
		it->clear();
		vector<Vertex>().swap(*it);
	}
	components.clear();
	vector<vector<Vertex>>().swap(components);
}