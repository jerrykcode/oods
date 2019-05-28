#include "dinic.h"
#include "GraphInput.h"

int main() {
	GraphInput<uint16_t> graph_input;
	Graph * p_graph = graph_input.createGraphByInput();	
	MF<uint16_t, uint32_t> * p_dinic = new Dinic<uint16_t, uint32_t>();
	if (!p_graph->isWeighted()) {
		cout << "error!" << endl;
		goto END;
	}
	uint32_t max_flow;
	Vertex src, sink;
	cout << "Enter the source and sink";
	cin >> src >> sink;
	if (src >= p_graph->getNumVertices() || sink >= p_graph->getNumVertices()) {
		cout << "error" << endl;
		goto END;
	}
	if (p_dinic->getMaximumFlow((WGraph<uint16_t> *)p_graph, src, sink, &max_flow)) {
		cout << "Maximum flow: " << max_flow << endl;
	}
	else cout << "error" << endl;
END:
	delete p_graph;
	delete p_dinic;
	return 0;
}