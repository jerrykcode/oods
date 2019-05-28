#pragma once
#include "LGraph.h"
#include "MGraph.h"

//Maximum flow

template<typename EdgeWeight, typename FlowWeight>
class MF {
public:
	virtual bool getMaximumFlow(WGraph<EdgeWeight> * p_graph, Vertex src, Vertex sink, FlowWeight * p_max_flow) = 0;
};