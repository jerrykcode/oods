#include "sssp.h"
#include "dijkstra.h"
#include "astar.h"
#include "Graph.h"
#include "LGraph.h"
#include "MGraph.h"
#include "GraphInitializer.h"
#include "GraphInput.h"


template<typename EdgeWeight, typename DistWeight>
class SSSP_TEST {
public:
	void sssp_test(Graph * p_graph, Vertex src, Vertex des, SSSP<EdgeWeight, DistWeight> * sssp) {
		DistWeight dist;
		//Record no path
		PathRecorder * p_path_recorder = new NoPathRecorder();
		if (sssp->getSingleSourceShortestPath(p_graph, src, des, p_path_recorder, &dist)) {
			cout << "The shortest distance from " << src << " to " << des << "is: " << dist << endl;
		}
		else cout << "error!" << endl;
		cout << endl;
		delete p_path_recorder;
		//Record one path
		p_path_recorder = NULL;
		p_path_recorder = new OnePathRecorder(p_graph->getNumVertices());
		if (sssp->getSingleSourceShortestPath(p_graph, src, des, p_path_recorder, &dist)) {
			cout << "The shortest distance from " << src << " to " << des << "is: " << dist << endl;
			vector<vector<Vertex>> paths;
			if (p_path_recorder->getPath(src, des, paths)) {
				for (auto it = paths[0].begin(); it != paths[0].end(); it++) {
					if (it != paths[0].begin()) putchar(' ');
					cout << *it;
				}
			}
			else cout << "error!" << endl;
			vector<Vertex>().swap(paths[0]);
			vector<vector<Vertex>>().swap(paths);
		}
		else cout << "error!" << endl;
		cout << endl;
		delete p_path_recorder;
		//Record all paths
		p_path_recorder = NULL;
		p_path_recorder = new AllPathRecorder(p_graph->getNumVertices());
		if (sssp->getSingleSourceShortestPath(p_graph, src, des, p_path_recorder, &dist)) {
			cout << "The shortest distance from " << src << " to " << des << "is: " << dist << endl;
			vector<vector<Vertex>> paths;
			if (p_path_recorder->getPath(src, des, paths)) {
				for (size_t i = 0; i < paths.size(); i++) {
					for (auto it = paths[i].begin(); it != paths[i].end(); it++) {
						if (it != paths[i].begin()) putchar(' ');
						cout << *it;
					}
					cout << endl;
				}
			}
			else cout << "error!" << endl;
			for (size_t i = 0; i < paths.size(); i++)
				vector<Vertex>().swap(paths[i]);
			vector<vector<Vertex>>().swap(paths);
		}
		else cout << "error!" << endl;
		cout << endl;
		delete p_path_recorder;
	}
};


typedef unsigned short word;

int main() {
	GraphInput<word> graphInput; //weight of edges in this graph is unsigned char type
	Graph * p_graph = graphInput.createGraphByInput();
	SSSP<word, short> * dijkstra = new Dijkstra<word, short>();
	SSSP<word, short> * astar = new Astar<word, short>();
	SSSP_TEST<word, short> * sssp_test = new SSSP_TEST<word, short>();
	Vertex src, des;
	cout << "Enter the source: " << endl;
	cin >> src;
	cout << "Enter the destination" << endl;
	cin >> des;
	cout << "dijkstra:" << endl;
	sssp_test->sssp_test(p_graph, src, des, dijkstra);
	//h for astar
	Graph * p_inverse_graph = p_graph->inverseGraph();
	short * dist = new short[p_inverse_graph->getNumVertices()];
	((Dijkstra<word, short> *)dijkstra)->getSingleSourceMultpleGoalsShortestPath(p_inverse_graph, des, new NoPathRecorder(), dist);
	for (size_t i = 0; i < p_inverse_graph->getNumVertices(); i++)
		dist[i] /= 2;
	((Astar<word, short> *)astar)->set_heuristic_distance(dist);
	cout << "astar:" << endl;
	sssp_test->sssp_test(p_graph, src, des, astar);
	delete p_graph;
	delete p_inverse_graph;
	return 0;
}