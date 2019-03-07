#include "Prim.h"
#include "GraphInput.h"

typedef int WeightType;

int main() {
	GraphInput<WeightType> graphInput;
	Graph *pGraph = graphInput.createGraphByInput();
	Prim<WeightType> prim;
	WeightType mstWeight;
	Graph *pMstGraph = NULL;
	if (prim.getMST(pGraph, &mstWeight, &pMstGraph)) {
		cout << "The weight of the MST:" << mstWeight << endl;		
		pMstGraph->clear();
		vector<WEdge<WeightType>> mstEdges;
		prim.getMST(pGraph, &mstWeight, mstEdges);
		Vertex v, w;
		WeightType weight;
		for (WEdge<WeightType> edge : mstEdges) {
			edge.getVertexes(&v, &w);
			weight = edge.getWeight();
			cout << v << " " << w << " : " << weight << endl;
		}
		mstEdges.clear();
		vector<WEdge<WeightType>>().swap(mstEdges);
	}
	else
		cout << "Error!" << endl;	
	pGraph->clear();
	return 0;
}
