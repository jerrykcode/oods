#pragma once
#include "LGraph.h"
#include "MGraph.h"
#include <stack>

typedef int Color;

class Tarjan {
public:
	Tarjan();
	~Tarjan();

	void connectedComponent(Graph *pGraph, Color *color);
	void connectedComponent(Graph *pGraph, vector<vector<Vertex>>& components);

private:
	int *dfn_;
	int *low_;
	stack<Vertex> vstack_;
	bool *isInStack_;

	int vcount_;
	int color_count_;

	void dfs(Graph *pGraph, Vertex v, Color *color);
};