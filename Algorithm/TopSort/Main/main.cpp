#include "dag.h"
#include "criticalpath.h"
#include "GraphInput.h"

int main() {
	GraphInput<uint16_t> graphInput;
	Graph * p_graph = graphInput.createGraphByInput();
	DAG dag;
	bool flag = dag.isAcyclic(p_graph);
	cout << "This graph is " << (flag ? "" : "not ") << "Acyclic." << endl;
	if (!flag) {
		delete p_graph;
		exit(0);
	}
	vector<Vertex> sequence;
	dag.getTopSequence(p_graph, false, sequence);
	cout << "This is a topological sequence:";
	for (auto it = sequence.begin(); it != sequence.end(); it++) {
		putchar(' ');
		cout << *it;
	}
	cout << endl;
	sequence.clear();
	dag.getTopSequence(p_graph, true, sequence);
	cout << "This is the topological sequence with the minimum lexicographical order:";
	for (auto it = sequence.begin(); it != sequence.end(); it++) {
		putchar(' ');
		cout << *it;
	}
	cout << endl;
	vector<Vertex>().swap(sequence);
	CriticalPath<uint16_t, uint32_t> critical_path;
	uint32_t max_time;
	vector<UNWEdge> cp;
	critical_path.getCriticalPath((WGraph<uint16_t> *)p_graph, &max_time, cp);
	cout << "This is the time of finishing the task discribed by this AOE graph: " << max_time << endl;
	cout << "These are the critical paths:" << endl;
	for (auto it = cp.begin(); it != cp.end(); it++) {
		Vertex v, w;
		it->getVertices(&v, &w);
		cout << "<" << v << ", " << w << ">" << endl;
	}
	vector<UNWEdge>().swap(cp);
	vector<WEdge<uint16_t>> wcp;
	critical_path.getCriticalPath((WGraph<uint16_t> *)p_graph, &max_time, wcp);
	cout << "These are the critical paths with their weights:" << endl;
	for (auto it = wcp.begin(); it != wcp.end(); it++) {
		Vertex v, w;
		it->getVertices(&v, &w);
		uint16_t weight = it->getWeight();
		cout << "<" << v << ", " << w << ">, weight :" << weight << endl;
	}
	vector<WEdge<uint16_t>>().swap(wcp);
	delete p_graph;
	return 0;
}