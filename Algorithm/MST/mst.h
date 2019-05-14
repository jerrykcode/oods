#pragma once
#include "LGraph.h"
#include "MGraph.h"

template<typename EdgeWeight, typename MstWeight>
class Mst {
public:
	/*
	Calculates the weight of the minimum spanning tree(mst)
	@param p_graph Pointer to the graph
	@param p_mst_weight Pointer to the weight of the mst
	@return bool True if the calculation success
	*/
	virtual bool getMstWeight(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight) = 0;

	/*
	Calculates the weight of the minimum spanning tree(mst) and return the mst
	@param p_graph Pointer to the graph
	@param p_mst_weight Pointer to the weight of the mst	
	@return WGraph<EdgeWeight> * Pointer to the graph represented the mst
	*/
	virtual WGraph<EdgeWeight> * getMst(WGraph<EdgeWeight> * p_graph, MstWeight * p_mst_weight) = 0;
};