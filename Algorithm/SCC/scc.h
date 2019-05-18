#pragma once
#include "LGraph.h"
#include "MGraph.h"

typedef int Color; //Every connected component have a color

/* Abstract class(interface) for strong connected component */
class SCC {
public:
	virtual bool getStrongConnectedComponents(Graph * p_graph, Color * color, size_t * p_num_components) = 0;
};