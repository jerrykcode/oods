#pragma once
#include "sssp.h"
#include "priority.h"
#include <queue>

#define DIJKSTRA_NO_VALUE -1

template<typename EdgeWeight, typename DistWeight>
class Dijkstra : public SSSP_MULTIPLE_GOALS<EdgeWeight, DistWeight> {
public:
	virtual bool getSingleSourceShortestPath(Graph * p_graph, Vertex src, Vertex des, PathRecorder * p_path_recorder, DistWeight *p_shoretest_dist);
	virtual bool getSingleSourceMultpleGoalsShortestPath(Graph * p_graph, Vertex src, PathRecorder * p_path_recorder, DistWeight * shortest_dist);

private:
	/*
	Calculates the shortest distance
	This function is private and is called by getSingleSourceShortestPath and getSingleSourceMultpleGoalsShortestPath function
	@param p_graph Pointer to the graph
	@param src The source vertex
	@param des The destination vertex. And if it equals the number of vertices, it means we should calculate the shortest distance form src to every vertices
	@param p_path_recorder The pointer to the PathRecorder
	@param p_shortest_dist The array stored the shortest distances form src to every vertices
	@return True if the calculation success
	*/
	bool private_getSingleSourceShortestPath(Graph * p_graph, Vertex src, Vertex des, PathRecorder * p_path_recorder, DistWeight *shoretest_dist);	

	bool * collected_;
	priority_queue<PriorityNode<DistWeight>, vector<PriorityNode<DistWeight>>, cmp<DistWeight>> pqueue_;
};

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::getSingleSourceShortestPath(Graph * p_graph, Vertex src, Vertex des, PathRecorder * p_path_recorder, DistWeight * p_shortest_dist) {
	size_t n_vertices = p_graph->getNumVertices();
	DistWeight * shortest_dist = new DistWeight[n_vertices];
	bool result = false;
	if (private_getSingleSourceShortestPath(p_graph, src, des, p_path_recorder, shortest_dist)) {
		result = true;
		*p_shortest_dist = shortest_dist[des];
	}
	free(shortest_dist);
	return result;
}

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::getSingleSourceMultpleGoalsShortestPath(Graph * p_graph, Vertex src, PathRecorder * p_path_recorder, DistWeight * shortest_dist) {
	return private_getSingleSourceShortestPath(p_graph, src, p_graph->getNumVertices(), p_path_recorder, shortest_dist);
}

template<typename EdgeWeight, typename DistWeight>
bool Dijkstra<EdgeWeight, DistWeight>::private_getSingleSourceShortestPath(Graph * p_graph, Vertex src, Vertex des, PathRecorder * p_path_recorder, DistWeight * shortest_dist) {
	if (!p_graph->isWeighted()) return false; //Only weighted graph can call this function
	size_t n_vertices = p_graph->getNumVertices(); //The number of vertices
	if (src >= n_vertices) return false; //Vertex is always unsigned type, src always >= 0
	if (des > n_vertices) return false; //If des == n_vertices, that means we should calculate the shortest distance form src to every vertices
	fill(shortest_dist, shortest_dist + n_vertices, DIJKSTRA_NO_VALUE); //Initialize the shortest dist	
	collected_ = new bool[n_vertices]; //collected[v] equals true when the shortest distance from src to v is confirmed
	fill(collected_, collected_ + n_vertices, false);
	shortest_dist[src] = 0; //The shortest distance from src to src is 0	
	pqueue_.push(PriorityNode<DistWeight>(src, 0));
	Vertex top_v, adj_v;
	EdgeWeight adj_weight;
	DistWeight tmp_dist;
	bool result = true;
	while (!pqueue_.empty()) {
		top_v = pqueue_.top().v;
		pqueue_.pop();
		if (collected_[top_v]) continue;
		collected_[top_v] = true;
		if (top_v == des) {
			//If the shortest distance of the destination is confirmed. If des == n_vertices, we should calculate all the vertices, and top_v will never equals des.	
			break;
		}
		Iterator * it = p_graph->getAdjIterator(top_v); //Iterator that can iterate all the adjacent vertices of top_v
		for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
			//if (!p_adj_node->hasWeight()) return false; //At here, p_graph must be a weighted graph, and p_adj_node->hasWeight() will never return false
			adj_v = p_adj_node->getAdjVertex(); //The adjacent vertex
			if (!collected_[adj_v]) { //If adj_v not collected yet
				adj_weight = ((WAdjNode<EdgeWeight> *)(p_adj_node))->getAdjWeight(); //The weight of edge <top_v, adj_v>
				if (adj_weight < 0) { //If there is negative edge
					result = false;					
					goto END;
				}
				tmp_dist = shortest_dist[top_v] + (DistWeight)adj_weight; //tmp_dist = shortest distance from src to top_v + the weight of edge <top_v, adj_v>
				if (tmp_dist < shortest_dist[adj_v] || shortest_dist[adj_v] == DIJKSTRA_NO_VALUE) {
					shortest_dist[adj_v] = tmp_dist; //Update
					pqueue_.push(PriorityNode<DistWeight>(adj_v, tmp_dist));
					p_path_recorder->update(top_v, adj_v); //Update the previous vertex of adj_v on its shortest path to top_v
				}
				else if (p_path_recorder->getRecordType() == RECORD_ALL_PATH && tmp_dist == shortest_dist[adj_v]) {
					p_path_recorder->add(top_v, adj_v);
				}
			}
		} //for
	} //while
	if (des != n_vertices && !collected_[des]) result = false; //If we can not reach des from src
END:
	free(collected_);
	while (!pqueue_.empty()) pqueue_.pop();
	return result;
}