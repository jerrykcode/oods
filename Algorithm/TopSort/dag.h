#pragma once
#include "topsort.h"

class DAG {
public:
	bool isAcyclic(Graph * p_graph);
	bool getTopSequence(Graph * p_graph, bool lexicographical_order, vector<Vertex>& sequence);
private:
	TopSort topsort_;
};

bool DAG::isAcyclic(Graph * p_graph) {
	VertexQueue * p_queue = new Queue();
	VertexCounter * p_counter = new Counter();
	AOE * p_aoe = new NoAOE();
	bool result = topsort_.topological_sort(p_graph, p_queue, p_counter, p_aoe);
	delete p_queue;
	delete p_counter;
	delete p_aoe;
	return result;
}

bool DAG::getTopSequence(Graph * p_graph, bool lexicographical_order, vector<Vertex>& sequence) {
	VertexQueue * p_queue = lexicographical_order ?  (VertexQueue *)new PriorityQueue() : (VertexQueue *)new Queue();
	VertexCounter * p_counter = new VertexSequence(sequence);
	AOE * p_aoe = new NoAOE();
	bool result = topsort_.topological_sort(p_graph, p_queue, p_counter, p_aoe);
	delete p_queue;
	delete p_counter;
	delete p_aoe;
	return result;
}