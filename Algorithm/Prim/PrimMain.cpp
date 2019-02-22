#include "Prim.h"
#include "Prim.cpp"
#include "GraphInput.h"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph<WeightType> *pGraph = graphInput.createGraphByInput();
	Prim<WeightType> prim;
	int mstWeight;
	Graph<WeightType> *pMstGraph = NULL;
	prim.getMST(pGraph, &mstWeight, &pMstGraph);
	if (mstWeight)
		cout << "The weight of the MST:" << mstWeight << endl;
	else
		cout << "Graph not connected!" << endl;
	pGraph->clear();
	pMstGraph->clear();
	return 0;
}
