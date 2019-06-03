#pragma once
#include "Edge.h"
#include <vector>
using namespace std;

//Critical path recoder
template<typename EdgeWeight>
class CPRecorder {
public:
	virtual void record(Vertex from, Vertex to, EdgeWeight weight) = 0;
};

template<typename EdgeWeight>
class UNWEdgeCPRecorder : public CPRecorder<EdgeWeight> {
public:
	UNWEdgeCPRecorder(vector<UNWEdge>& cp) : cp_(cp) {}

	virtual void record(Vertex from, Vertex to, EdgeWeight weight) {
		cp_.push_back(UNWEdge(to, from));
	}

private:
	vector<UNWEdge>& cp_;
};

template<typename EdgeWeight>
class WEdgeCPRecorder : public CPRecorder<EdgeWeight> {
public:
	WEdgeCPRecorder(vector<WEdge<EdgeWeight>>& cp) : cp_(cp) {}

	virtual void record(Vertex from, Vertex to, EdgeWeight weight) {
		cp_.push_back(WEdge<EdgeWeight>(to, from, weight));
	}
	
private:
	vector<WEdge<EdgeWeight>>& cp_;
};