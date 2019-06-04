#pragma once
#include "mst.h"
#include "../SSSP/priority.h"
#include <queue>

#ifdef PRIM_NO_VALUE
#undef PRIM_NO_VALUE
#endif

#define PRIM_NO_VALUE -1

template<typename EdgeWeight, typename MstWeight>
class Prim : public Mst<EdgeWeight, MstWeight> {
public:
	//Implements the pure virtual functions(abstract methods) in Mst
	virtual bool getMstWeight(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight);
	virtual WGraph<EdgeWeight> * getMst(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight);
private:	
	/*
	Private inner abstract class Recorder
	*/
	class Recorder {
	public:
		virtual bool update(Vertex from, Vertex to) = 0;
		virtual bool insert(Vertex v, EdgeWeight dist) = 0;
		virtual WGraph<EdgeWeight> * getMstGraph() = 0;
	};

	class NoRecorder : public Recorder {
	public:
		virtual bool update(Vertex from, Vertex to) { return false; }
		virtual bool insert(Vertex v, EdgeWeight dist) { return false; }
		virtual WGraph<EdgeWeight> * getMstGraph() { return NULL; }
	};

	class MstRecorder : public Recorder {
	public:
		MstRecorder(size_t n_vertices);
		~MstRecorder();

		virtual bool update(Vertex from, Vertex to);
		virtual bool insert(Vertex v, EdgeWeight dist);
		virtual WGraph<EdgeWeight> * getMstGraph();
	private:
		size_t n_vertices_;
		Vertex * pre_;
		WGraph<EdgeWeight> * p_mst_graph_;
	};
private:
	//private
	/*
	Calculates the weight of the minimum spanning tree(mst) and record the mst
	@param p_graph Pointer to the graph
	@param p_mst_weight Pointer to the weight of the mst
	@param p_recorder Pointer to the recorder
	@return bool True if the calculation success
	*/
	bool prim_getMst(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight, Recorder * p_recorder);

	//private member variables
	EdgeWeight * dist_;
	priority_queue<PriorityNode<EdgeWeight>, vector<PriorityNode<EdgeWeight>>, cmp<EdgeWeight>> pqueue_;

};

//Prim
template<typename EdgeWeight, typename MstWeight>
bool Prim<EdgeWeight, MstWeight>::getMstWeight(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight) {
	return prim_getMst(p_graph, p_mst_weight, new NoRecorder()); //Do not record the mst, only calculates the weight
}

template<typename EdgeWeight, typename MstWeight>
WGraph<EdgeWeight> * Prim<EdgeWeight, MstWeight>::getMst(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight) {	
	WGraph<EdgeWeight> * result = NULL;
	if (p_graph->getNumVertices() == 0) return result;
	Recorder * p_recorder = new MstRecorder(p_graph->getNumVertices());
	if (prim_getMst(p_graph, p_mst_weight, p_recorder)) {
		result = p_recorder->getMstGraph();
	}
	delete p_recorder;
	return result;
}

//private
template<typename EdgeWeight, typename MstWeight>
bool Prim<EdgeWeight, MstWeight>::prim_getMst(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight, Recorder * p_recorder) {	
	if (p_graph->isDirected()) return false; //The graph must NOT be directed
	size_t n_vertices = p_graph->getNumVertices();
	if (n_vertices == 0) return false;
	dist_ = new EdgeWeight[n_vertices];
	//If EdgeWeight is signed type, then PRIM_NO_VALUE is -1; if EdgeWeight is unsigned type, PRIM_NO_VALUE is the possible max value of EdgeWeight
	fill(dist_, dist_ + n_vertices, PRIM_NO_VALUE);
	Vertex src = 0; //Set a source, it can be any vertex in the graph
	dist_[src] = 0;
	pqueue_.push(PriorityNode<EdgeWeight>(src, 0));
	*p_mst_weight = 0;
	int v_count = 1; //src already in the mst
	bool result = true;
	Vertex top_v, adj_v;
	EdgeWeight adj_weight;
	while (!pqueue_.empty()) {
		top_v = pqueue_.top().v;
		pqueue_.pop();		
		if (top_v != src) {
			if (dist_[top_v] == 0) continue;
			*p_mst_weight += dist_[top_v];
			p_recorder->insert(top_v, dist_[top_v]);
			dist_[top_v] = 0;
			v_count++;
		}
		Iterator * it = p_graph->getAdjIterator(top_v); //Iterator used to iterate over top_v's adjacency vertices
		for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
			adj_v = p_adj_node->getAdjVertex();
			if (dist_[adj_v]) {
				adj_weight = ((WAdjNode<EdgeWeight> *)p_adj_node)->getAdjWeight();
				if (adj_weight < 0) {
					result = false;
					goto END;
				}
				if (adj_weight < dist_[adj_v] || dist_[adj_v] == PRIM_NO_VALUE) {
					dist_[adj_v] = adj_weight;
					pqueue_.push(PriorityNode<EdgeWeight>(adj_v, adj_weight));
					p_recorder->update(top_v, adj_v);
				}
			}
		} //for
		delete it;
	} //while
	if (result) result = v_count == n_vertices;
END:
	free(dist_);
	while (!pqueue_.empty()) pqueue_.pop();
	return result;
}

//MstRecorder

template<typename EdgeWeight, typename MstWeight>
Prim<EdgeWeight, MstWeight>::MstRecorder::MstRecorder(size_t n_vertices) : n_vertices_(n_vertices) {
	pre_ = new Vertex[n_vertices];
	p_mst_graph_ = new ListWGraph<EdgeWeight>(n_vertices, false);
}

template<typename EdgeWeight, typename MstWeight>
Prim<EdgeWeight, MstWeight>::MstRecorder::~MstRecorder() {
	free(pre_);
}

template<typename EdgeWeight, typename MstWeight>
bool Prim<EdgeWeight, MstWeight>::MstRecorder::update(Vertex from, Vertex to) {
	if (from >= n_vertices_) return false; //Vertex is always unsigned type, from >= 0
	if (to >= n_vertices_) return false;
	pre_[to] = from;
	return true;
}

template<typename EdgeWeight, typename MstWeight>
bool Prim<EdgeWeight, MstWeight>::MstRecorder::insert(Vertex v, EdgeWeight dist) {
	if (v >= n_vertices_) return false;
	p_mst_graph_->insertEdge(new WEdge<EdgeWeight>(pre_[v], v, dist));
	return true;
}

template<typename EdgeWeight, typename MstWeight>
WGraph<EdgeWeight> * Prim<EdgeWeight, MstWeight>::MstRecorder::getMstGraph() {
	return p_mst_graph_;
}