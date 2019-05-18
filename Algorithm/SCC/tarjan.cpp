#include "tarjan.h"

bool Tarjan::getStrongConnectedComponents(Graph * p_graph, Color * color, size_t * p_num_components) {
	size_t n_vertices = p_graph->getNumVertices();
	if (n_vertices == 0) return false;
	component_count_ = 0;
	if (p_graph->isDirected()) {
		//tarjan
		v_count_ = 0;
		dfn_ = new int[n_vertices];
		fill(dfn_, dfn_ + n_vertices, 0);
		low_ = new int[n_vertices];
		is_in_stack_ = new bool[n_vertices];
		fill(is_in_stack_, is_in_stack_ + n_vertices, false);
		for (Vertex v = 0; v < n_vertices; v++) {
			if (!dfn_[v]) {
				dfs(p_graph, v, color);
			}
		}
		free(dfn_);
		free(low_);
		free(is_in_stack_);
	}
	else {
		//simple bfs
		fill(color, color + n_vertices, -1);
		for (Vertex v = 0; v < n_vertices; v++) {
			if (color[v] == -1) bfs(p_graph, v, color);
		}
	}
	*p_num_components = component_count_;
	return true;
}

//dfs in tarjan algorithm(directed graph)
void Tarjan::dfs(Graph * p_graph, Vertex v, Color * color) {
	if (dfn_[v]) return;
	dfn_[v] = ++v_count_;
	low_[v] = dfn_[v];
	vstack_.push(v);
	is_in_stack_[v] = true;
	Iterator * it = p_graph->getAdjIterator(v);
	Vertex adj_v;
	for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
		adj_v = p_adj_node->getAdjVertex();
		if (!dfn_[adj_v]) {
			dfs(p_graph, adj_v, color);
			if (low_[adj_v] < low_[v]) low_[v] = low_[adj_v];
		}
		else if (is_in_stack_[adj_v]) {
			if (dfn_[adj_v] < low_[v]) low_[v] = dfn_[adj_v];
		}
	}
	delete it;
	if (dfn_[v] == low_[v]) {
		while (vstack_.top() != v) {
			color[vstack_.top()] = component_count_;
			is_in_stack_[vstack_.top()] = false;
			vstack_.pop();			
		}
		color[vstack_.top()] = component_count_;
		is_in_stack_[vstack_.top()] = false;
		vstack_.pop();
		component_count_++;
	}
}

//bfs to compute the connected components of undirected graph
void Tarjan::bfs(Graph * p_graph, Vertex v, Color * color) {
	if (color[v] != -1) return;
	vqueue_.push(v);
	color[v] = component_count_;
	Vertex top_v, adj_v;
	while (!vqueue_.empty()) {
		top_v = vqueue_.front();
		vqueue_.pop();
		Iterator * it = p_graph->getAdjIterator(top_v);
		for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
			adj_v = p_adj_node->getAdjVertex();
			if (color[adj_v] == -1) {
				color[adj_v] = component_count_;
				vqueue_.push(adj_v);
			}
		}
		delete it;
	} //while
	component_count_++;
}