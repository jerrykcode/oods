#include "Dinic.h"
#include "GraphInput.h"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph *pGraph = graphInput.createGraphByInput();
	Dinic<WeightType> dinic;
	Vertex src, des;
	cout << "Enter the src and des: " << endl;
	cin >> src >> des;
	WeightType maxFlow;
	if (dinic.getMaxFlow(pGraph, src, des, &maxFlow, false)) {
		cout << "The maximum flow is " << maxFlow << endl;
	}
	else {
		cout << "Error" << endl;
	}
	pGraph->clear();
	return 0;
}