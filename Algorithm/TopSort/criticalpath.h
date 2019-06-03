#pragma once
#include "topsort.h"

template<typename EdgeWeight, typename TimeWeight>
class CriticalPath {
public:
	bool getCriticalPath(WGraph<EdgeWeight> * p_graph, TimeWeight * p_max_time, vector<UNWEdge>& critical_paths);
	bool getCriticalPath(WGraph<EdgeWeight> * p_graph, TimeWeight * p_max_time, vector<WEdge<EdgeWeight>>& critical_paths);

private:
	bool getCriticalPath(WGraph<EdgeWeight> * p_graph, TimeWeight * p_max_time, CPRecorder<EdgeWeight> * p_CPRecorder);
private:
	class VertexCounter_findMax : public VertexCounter {
	public:
		VertexCounter_findMax(TimeWeight * earliest_time) : earliest_time_(earliest_time), max_(0), count_(0) {}

		virtual void count(Vertex v) {
			count_++;
			if (earliest_time_[v] > max_) max_ = earliest_time_[v];
		}

		virtual size_t size() {
			return count_;
		}

		TimeWeight getMax() {
			return max_;
		}
	private:
		TimeWeight * earliest_time_;
		TimeWeight max_;

		size_t count_;		
	};

	class NoVertexCounter : public VertexCounter {
	public:
		virtual void count(Vertex v) {}
		virtual size_t size() { return 0; }
	};

private:
	TopSort topsort_;
};

template<typename EdgeWeight, typename TimeWeight>
bool CriticalPath<EdgeWeight, TimeWeight>::getCriticalPath(WGraph<EdgeWeight> * p_graph, TimeWeight * p_max_time, vector<UNWEdge>& critical_paths) {
	CPRecorder<EdgeWeight> * p_CPRecorder = new UNWEdgeCPRecorder<EdgeWeight>(critical_paths);
	bool result = getCriticalPath(p_graph, p_max_time, p_CPRecorder);
	delete p_CPRecorder;
	return result;
}

template<typename EdgeWeight, typename TimeWeight>
bool CriticalPath<EdgeWeight, TimeWeight>::getCriticalPath(WGraph<EdgeWeight> * p_graph, TimeWeight * p_max_time, vector<WEdge<EdgeWeight>>& critical_paths) {
	CPRecorder<EdgeWeight> * p_CPRecorder = new WEdgeCPRecorder<EdgeWeight>(critical_paths);
	bool result = getCriticalPath(p_graph, p_max_time, p_CPRecorder);
	delete p_CPRecorder;
	return result;
}

template<typename EdgeWeight, typename TimeWeight>
bool CriticalPath<EdgeWeight, TimeWeight>::getCriticalPath(WGraph<EdgeWeight> * p_graph, TimeWeight * p_max_time, CPRecorder<EdgeWeight> * p_CPRecorder) {
	int n_vertices = p_graph->getNumVertices();
	if (!n_vertices) return false;
	TimeWeight * earliest_time = new TimeWeight[n_vertices];
	fill(earliest_time, earliest_time + n_vertices, 0);
	VertexQueue * p_queue = new Queue();
	VertexCounter * p_counter = new VertexCounter_findMax(earliest_time);
	AOE * p_aoe = new AOE_forward<EdgeWeight, TimeWeight>(earliest_time);
	bool result = true;
	if (topsort_.topological_sort(p_graph, p_queue, p_counter, p_aoe)) {
		*p_max_time = ((VertexCounter_findMax *)p_counter)->getMax();
		TimeWeight * latest_time = new TimeWeight[n_vertices];
		fill(latest_time, latest_time + n_vertices, *p_max_time);
		WGraph<EdgeWeight> * p_inverse_graph = (WGraph<EdgeWeight> *)p_graph->inverseGraph();
		delete p_counter;
		p_counter = new NoVertexCounter();
		delete p_aoe;
		p_aoe = new AOE_backward<EdgeWeight, TimeWeight>(earliest_time, latest_time, p_CPRecorder);
		topsort_.topological_sort(p_inverse_graph, p_queue, p_counter, p_aoe);
		free(earliest_time);
		free(latest_time);
		delete p_inverse_graph;		
	}
	else {
		result = false;
		free(earliest_time);		
	}
	delete p_queue;
	delete p_counter;
	delete p_aoe;
	return result;
}