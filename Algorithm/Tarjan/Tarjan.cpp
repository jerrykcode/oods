#include "Tarjan.h"

Tarjan::Tarjan() {

}

Tarjan::~Tarjan() {

}

void Tarjan::connectedComponent(Graph * pGraph, Color * color) {
	int nVertexes = pGraph->getVertexesNum();
	if (pGraph->isDirected()) {
		dfn_ = new int[nVertexes];
		fill(dfn_, dfn_ + nVertexes, 0);
		low_ = new int[nVertexes];
		isInStack_ = new bool[nVertexes];
		fill(isInStack_, isInStack_ + nVertexes, false);
		vcount_ = 0;
		color_count_ = 0;
		for (int i = 0; i < nVertexes; i++)
			if (!dfn_[i]) {
				dfs(pGraph, i, color);
			}
		free(dfn_);
		free(low_);
		free(isInStack_);
	}
	else {

	}
}

void Tarjan::connectedComponent(Graph * pGraph, vector<vector<Vertex>>& components) {
	int nVertexes = pGraph->getVertexesNum();
	Color *color = new Color[nVertexes];
	connectedComponent(pGraph, color);
	components.resize(color_count_);
	for (int i = 0; i < nVertexes; i++) {
		components[color[i]].push_back(i);
	}
	free(color);
}

void Tarjan::dfs(Graph *pGraph, Vertex v, Color *color) {	
	dfn_[v] = low_[v] = ++vcount_;
	isInStack_[v] = true;
	vstack_.push(v);
	for (AdjNode *pAdjNode = pGraph->adj_iter_begin(v); pAdjNode != NULL; pAdjNode = pGraph->adj_iter_next()) {
		Vertex adjVertex = pAdjNode->getAdjVertex();
		if (!dfn_[adjVertex]) { //dfn_[adjVertex] == 0, adjVertex has not been collected
			dfs(pGraph, adjVertex, color);
			if (low_[adjVertex] < low_[v]) low_[v] = low_[adjVertex];
		}
		else if (isInStack_[adjVertex]) {
			//adjVertex has already been collected, and it is in the stack.
			//This means that (v, adjVertex) and (adjVertex, v) is connected
			if (dfn_[adjVertex] < low_[v]) low_[v] = dfn_[adjVertex];
		}
		pGraph->adj_iter_clear();
	}
	if (dfn_[v] == low_[v]) {
		while (vstack_.top() != v) {
			color[vstack_.top()] = color_count_;
			isInStack_[vstack_.top()] = false;
			vstack_.pop();
		}
		color[v] = color_count_++;
		isInStack_[v] = false;
		vstack_.pop();
	}
}
