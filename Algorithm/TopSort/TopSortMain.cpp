#include "GraphInput.h"
#include "TopSort.h"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph * pGraph = graphInput.createGraphByInput();
	TopSort<WeightType> topSort;
	WeightType maxWeight;
	vector<WEdge<WeightType>> keyActivities;	
	if (!topSort.top(pGraph, &maxWeight, keyActivities)) {
		cout << "It is impossible to finish the task" << endl;
	}
	else {
		cout << "The total weight to finish the task is " << maxWeight << endl;
		cout << "There are " << keyActivities.size() << " key activities : " << endl;
		Vertex v, w;
		WeightType weight;
		for (auto it = keyActivities.begin(); it != keyActivities.end(); it++) {
			it->getVertexes(&v, &w);
			weight = it->getWeight();
			cout << v << " -> " << w << ". Weight of this edge is " << weight << "." << endl;
		}
		keyActivities.clear();
		vector<WEdge<WeightType>>().swap(keyActivities);
	}
	pGraph->clear();
	return 0;
}