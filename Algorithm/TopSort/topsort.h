#pragma once
#include "LGraph.h"
#include "MGraph.h"
#include "vertexqueue.h"
#include "vertexcounter.h"
#include "aoe.h"

class TopSort {
public:
	bool topological_sort(Graph * p_graph, VertexQueue * p_queue, VertexCounter * p_counter, AOE * p_aoe);

private:
	size_t * in_degree_;
};

bool TopSort::topological_sort(Graph * p_graph, VertexQueue * p_queue, VertexCounter * p_counter, AOE * p_aoe) {
	size_t n_vertices = p_graph->getNumVertices();
	if (n_vertices == 0) return false;
	in_degree_ = new size_t[n_vertices];
	fill(in_degree_, in_degree_ + n_vertices, 0);
	//Calculates in_degree_
	for (size_t v = 0; v < n_vertices; v++) {
		Iterator * it = p_graph->getAdjIterator(v);
		Vertex adj_v;
		for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
			adj_v = p_adj_node->getAdjVertex();
			in_degree_[adj_v]++;
		}
		delete it;
	}
	for (size_t v = 0; v < n_vertices; v++) 
		if (in_degree_[v] == 0)
			p_queue->push(v); //Push vertex with in_degree_ of zero into the queue
	Vertex top_v, adj_v;
	while (!p_queue->empty()) {
		top_v = p_queue->top();
		p_queue->pop();
		p_counter->count(top_v); //Count top_v
		Iterator * it = p_graph->getAdjIterator(top_v);
		for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
			adj_v = p_adj_node->getAdjVertex();
			if (!--in_degree_[adj_v]) {
				p_queue->push(adj_v);
			}
			p_aoe->act(top_v, p_adj_node); //Activity on edge
		}
		delete it;
	}
	free(in_degree_);
	return p_counter->size() == n_vertices;
}