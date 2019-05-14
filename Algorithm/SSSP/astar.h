#pragma once
#include "sssp.h"
#include "priority.h"
#include <queue>

#define ASTAR_NO_VALUE -1

template<typename EdgeWeight, typename DistWeight>
class Astar : public SSSP<EdgeWeight, DistWeight> {
public:
	Astar() : heuristic_dist_seted_(false) {}

	virtual bool getSingleSourceShortestPath(Graph * p_graph, Vertex src, Vertex des, PathRecorder * path_recorder, DistWeight *p_shoretest_dist);
	void set_heuristic_distance(DistWeight * heuristic_dist);
private:

	bool heuristic_dist_seted_;

	//f = g + h
	DistWeight * heuristic_dist_; //h
	DistWeight * shortest_dist_; //g
	bool * collected_;
	priority_queue <PriorityNode<DistWeight>, vector<PriorityNode<DistWeight>>, cmp<DistWeight>> pqueue_;
};


template<typename EdgeWeight, typename DistWeight>
void Astar<EdgeWeight, DistWeight>::set_heuristic_distance(DistWeight * heuristic_dist) {
	heuristic_dist_ = heuristic_dist;
	heuristic_dist_seted_ = true;
}


template<typename EdgeWeight, typename DistWeight>
bool Astar<EdgeWeight, DistWeight>::getSingleSourceShortestPath(Graph * p_graph, Vertex src, Vertex des, PathRecorder * p_path_recorder, DistWeight * p_shortest_dist) {
	if (!heuristic_dist_seted_) return false; //Heuristic distance must be set before
	if (!p_graph->isWeighted()) return false; //Graph must be weighted
	size_t n_vertices = p_graph->getNumVertices(); //Number of vertices
	if (src >= n_vertices) return false; //Vertex is always unsigned type, src always >= 0
	if (des >= n_vertices) return false; //Vertex is always unsigned type, src always >= 0
	shortest_dist_ = new DistWeight[n_vertices];
	fill(shortest_dist_, shortest_dist_ + n_vertices, ASTAR_NO_VALUE); //Initialize
	collected_ = new bool[n_vertices];
	fill(collected_, collected_ + n_vertices, false);
	shortest_dist_[src] = 0;
	pqueue_.push(PriorityNode<DistWeight>(src, shortest_dist_[src] + heuristic_dist_[src])); //f[src] = g[src] + h[src]
	Vertex top_v, adj_v;
	EdgeWeight adj_weight;
	DistWeight tmp_dist;
	bool result;
	while (!pqueue_.empty()) {
		top_v = pqueue_.top().v;
		pqueue_.pop();
		if (collected_[top_v]) continue;
		collected_[top_v] = true;
		if (top_v == des) {
			//If the shortest distance of the destination is confirmed
			break;
		}
		Iterator * it = p_graph->getAdjIterator(top_v);
		for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
			adj_v = p_adj_node->getAdjVertex(); //Adjacent vertex
			if (!collected_[adj_v]) {
				adj_weight = ((WAdjNode<EdgeWeight> *)p_adj_node)->getAdjWeight(); //Weight of edge <top_v, adj_v>
				if (adj_weight < 0) {
					result = false;
					goto END;
				}
				tmp_dist = shortest_dist_[top_v] + (DistWeight)adj_weight; 
				if (tmp_dist < shortest_dist_[adj_v] || shortest_dist_[adj_v] == ASTAR_NO_VALUE) {
					shortest_dist_[adj_v] = tmp_dist; //g[adj_v]
					pqueue_.push(PriorityNode<DistWeight>(adj_v, shortest_dist_[adj_v] + heuristic_dist_[adj_v])); //f = g + h
					p_path_recorder->update(top_v, adj_v);
				}
				else if (p_path_recorder->getRecordType() == RECORD_ALL_PATH && tmp_dist == shortest_dist_[adj_v]) {
					p_path_recorder->add(top_v, adj_v);
				}
			} //if
		} //for
	} //while
	result = collected_[des];
	if (result) {
		*p_shortest_dist = shortest_dist_[des];
	}
END:
	free(shortest_dist_);
	free(collected_);
	while (!pqueue_.empty()) pqueue_.pop();
	return result;
}