#pragma once
#include "AdjNode.h"
#include "Edge.h"
#include "cprecorder.h"
#include <vector>
using namespace std;

class AOE {
public:
	virtual void act(Vertex from, AdjNode * p_to_adj_node) = 0;
};

class NoAOE : public AOE {
public:
	virtual void act(Vertex from, AdjNode * p_to_adj_node) {
		//do nothing
	}
};

//class for forward procedure in critical path
template<typename EdgeWeight, typename TimeWeight>
class AOE_forward : public AOE {
public:
	AOE_forward(TimeWeight * earliest_time) : earliest_time_(earliest_time) {}

	virtual void act(Vertex from, AdjNode * p_to_adj_node) {
		Vertex to = p_to_adj_node->getAdjVertex();
		EdgeWeight adj_weight = ((WAdjNode<EdgeWeight> *)p_to_adj_node)->getAdjWeight();
		if (earliest_time_[from] + (TimeWeight)adj_weight > earliest_time_[to]) {
			earliest_time_[to] = earliest_time_[from] + (TimeWeight)adj_weight;
		}
	}
private:
	TimeWeight * earliest_time_;
};

//class for backward procedure in critical path
template<typename EdgeWeight, typename TimeWeight>
class AOE_backward : public AOE {
public:
	AOE_backward(TimeWeight * earliest_time, TimeWeight * lastest_time, CPRecorder<EdgeWeight> * p_CPRecorder) :
		earliest_time_(earliest_time), 
		lastest_time_(lastest_time),
		p_CPRecorder_(p_CPRecorder) {}

	virtual void act(Vertex from, AdjNode * p_to_adj_node) {
		Vertex to = p_to_adj_node->getAdjVertex();
		EdgeWeight adj_weight = ((WAdjNode<EdgeWeight> *)p_to_adj_node)->getAdjWeight();
		if (lastest_time_[from] - (TimeWeight)adj_weight < lastest_time_[to]) {
			lastest_time_[to] = lastest_time_[from] - (TimeWeight)adj_weight;
		}
		if (lastest_time_[from] - earliest_time_[to] == (TimeWeight)adj_weight) {
			p_CPRecorder_->record(from, to, adj_weight);
		}
	}

private:
	TimeWeight * earliest_time_;
	TimeWeight * lastest_time_;
	CPRecorder<EdgeWeight> * p_CPRecorder_;
};