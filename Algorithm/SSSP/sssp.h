#pragma once

#include "LGraph.h"
#include "MGraph.h"
#include "pathRecorder.h"

template<typename EdgeWeight, typename DistWeight>
class SSSP {
public:
	/*
	Calculates the shortest distance from src to des
	@param p_graph Pointer to the graph
	@param src The source vertex
	@param des The destination vertex
	@param p_path_recorder The pointer to the PathRecorder
	@param p_shortest_dist The pointer to the shortest distance from src to des
	@return True if the calculation success
	*/
	virtual bool getSingleSourceShortestPath(Graph * p_graph, Vertex src, Vertex des, PathRecorder * p_path_recorder, DistWeight *p_shoretest_dist) = 0;
};

template<typename EdgeWeight, typename DistWeight>
class SSSP_MULTIPLE_GOALS : public SSSP<EdgeWeight, DistWeight> {
public:
	/*
	Calculates the shortest distances from src to all the vertices
	@param p_graph Pointer to the graph
	@param src The source vertex
	@param p_path_recorder The pointer to the PathRecorder
	@param p_shortest_dist The array stored the shortest distances form src to every vertices
	@return True if the calculation success
	*/
	virtual bool getSingleSourceMultpleGoalsShortestPath(Graph * p_graph, Vertex src, PathRecorder * p_path_recorder, DistWeight * shortest_dist) = 0;
};