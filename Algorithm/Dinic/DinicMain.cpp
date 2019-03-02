#include "Dinic.h"
#include "Dinic.cpp"
#include "GraphInput.h"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph<WeightType> *pGraph = graphInput.createGraphByInput();
	Dinic<WeightType> dinic;
	Vertex src, des;
	cout << "Enter the src and des: " << endl;
	cin >> src >> des;
	WeightType maxFlow;
	if (dinic.getMaxFlow(pGraph, src, des, &maxFlow)) {
		cout << "The maximum flow is " << maxFlow << endl;
	}
	else {
		cout << "Error" << endl;
	}
	pGraph->clear();
	return 0;
}