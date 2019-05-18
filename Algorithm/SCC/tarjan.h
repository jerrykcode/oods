#pragma once
#include "scc.h"
#include "GraphInput.h"
#include <queue>
#include <stack>

class Tarjan : public SCC {
public:
	virtual bool getStrongConnectedComponents(Graph * p_graph, Color * color, size_t * p_num_components);
private:
	void dfs(Graph * p_graph, Vertex v, Color * color);
	void bfs(Graph * p_graph, Vertex v, Color * color);

	size_t v_count_;
	size_t component_count_;

	queue<Vertex> vqueue_;
	stack<Vertex> vstack_;

	int * dfn_;
	int * low_;
	bool * is_in_stack_;
};