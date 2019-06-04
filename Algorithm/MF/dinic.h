#pragma once
#include "mf.h"
#include <cstdint>
#include <queue>

#ifdef EDGE_WEIGHT_NO_VALUE
#undef EDGE_WEIGHT_NO_VALUE
#endif

#define EDGE_WEIGHT_NO_VALUE -1

template<typename EdgeWeight, typename FlowWeight>
class Dinic : public MF<EdgeWeight, FlowWeight> {
public:
	//Implements pure virtual functions (abstract methods) in MF<EdgeWeight, FlowWeight> class
	virtual bool getMaximumFlow(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex sink, FlowWeight * p_max_flow);
private:

	bool bfs(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex sink);
	EdgeWeight dfs(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, EdgeWeight min_flow);
	EdgeWeight min(EdgeWeight a, EdgeWeight b);

	uint32_t * dist_;
	queue<Vertex> vqueue_;
};

template<typename EdgeWeight, typename FlowWeight>
bool Dinic<EdgeWeight, FlowWeight>::getMaximumFlow(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex sink, FlowWeight * p_max_flow) {
	size_t n_vertices = p_graph->getNumVertices();
	if (n_vertices == 0) return false;
	dist_ = new uint32_t[n_vertices];
	EdgeWeight flow;
	*p_max_flow = 0;
	bool result = false;
	while (bfs(p_graph, src, sink)) {
		result = true;
		while (flow = dfs(p_graph, src, sink, EDGE_WEIGHT_NO_VALUE)) {
			*p_max_flow += flow;
		}
	}
	free(dist_);
	return result;
}

template<typename EdgeWeight, typename FlowWeight>
bool Dinic<EdgeWeight, FlowWeight>::bfs(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex sink) {
	size_t n_vertices = p_graph->getNumVertices(); //n_vertices > 0 in here
	fill(dist_, dist_ + n_vertices, EDGE_WEIGHT_NO_VALUE);
	dist_[src] = 0;
	vqueue_.push(src);
	Vertex front_v, adj_v;
	EdgeWeight adj_weight;
	while (!vqueue_.empty()) {
		front_v = vqueue_.front();
		vqueue_.pop();
		Iterator * it = p_graph->getAdjIterator(front_v);
		for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
			adj_v = p_adj_node->getAdjVertex();
			adj_weight = ((WAdjNode<EdgeWeight> *)p_adj_node)->getAdjWeight();
			if (adj_weight < 0) {
				while (!vqueue_.empty()) vqueue_.pop();
				return false;
			}
			if (adj_weight && dist_[adj_v] == EDGE_WEIGHT_NO_VALUE) {
				dist_[adj_v] = dist_[front_v] + 1;
				vqueue_.push(adj_v);
			}
		} //for
		delete it;
	} //while
	return dist_[sink] != EDGE_WEIGHT_NO_VALUE;
}

template<typename EdgeWeight, typename FlowWeight>
EdgeWeight Dinic<EdgeWeight, FlowWeight>::dfs(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex des, EdgeWeight min_flow) {
	if (src == des) {
		return min_flow;
	}
	Vertex adj_v;
	EdgeWeight adj_weight, tmp_flow;
	Iterator * it = p_graph->getAdjIterator(src);
	for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
		adj_v = p_adj_node->getAdjVertex();
		adj_weight = ((WAdjNode<EdgeWeight>*)p_adj_node)->getAdjWeight();
		if (adj_weight && dist_[adj_v] == dist_[src] + 1) { //Weight of the edge<src, adj_v> is not 0, and adj_v is come from src
			if (tmp_flow = dfs(p_graph, adj_v, des, min(min_flow, adj_weight))) { //If from adj_v we can reach des
				//Now tmp_flow is the minimum flow on the path from src to des
				min_flow = tmp_flow;
				if (it->isGraphReference())  //If the p_adj_node is a reference
					((WAdjNode<EdgeWeight> *)p_adj_node)->setAdjWeight(adj_weight - min_flow);				
				else 
					p_graph->increaseEdgeWeight(src, adj_v, -1 * min_flow);
				p_graph->increaseEdgeWeight(adj_v, src, min_flow);
				return min_flow;
			}
		}
	} //for
	delete it;
	return 0;
}

template<typename EdgeWeight, typename FlowWeight>
EdgeWeight Dinic<EdgeWeight, FlowWeight>::min(EdgeWeight a, EdgeWeight b) {
	if (a == EDGE_WEIGHT_NO_VALUE) return b;
	if (b == EDGE_WEIGHT_NO_VALUE) return a;
	return a < b ? a : b;
}
