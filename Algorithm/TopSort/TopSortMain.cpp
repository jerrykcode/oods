#include "GraphInput.h"
#include "TopSort.h"
#include "TopSort.cpp"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph<WeightType> * pGraph = graphInput.createGraphByInput();
	TopSort<WeightType> topSort;
	WeightType maxWeight;
	vector<Edge<WeightType>> keyActivities;
	topSort.top(pGraph, &maxWeight, keyActivities);
	if (maxWeight == NO_VALUE) {
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
		vector<Edge<WeightType>>().swap(keyActivities);
	}
	pGraph->clear();
	return 0;
}