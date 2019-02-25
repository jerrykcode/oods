#pragma once
#include "GraphInitializer.h"

template<typename T>
class GraphInput : public GraphInitializer<T> {
public:
	GraphInput() : GraphInitializer<T>() {}
	~GraphInput() {}

	Graph<T> *createGraphByInput() {
		bool isDirected;
		int nVertexes, nEdges;
		while (true) {
			cout << "Is the graph directed ? [Y/N]" << endl;
			string cmd;
			cin >> cmd;
			if (cmd == "Y" || cmd == "y") {
				isDirected = true;
				break;
			}
			else if (cmd == "N" || cmd == "n") {
				isDirected = false;
				break;
			}
		}
		cout << "Enter the number of vertexes: " << endl;
		cin >> nVertexes;
		cout << "Enter the number of edges: " << endl;
		cin >> nEdges;
		vector<Edge<T>> edges;
		for (int i = 0; i < nEdges; i++) {
			cout << "Eneter the 2 vertexes of the " << i << "th edge: (The vertexes numbered from 0 to " << nVertexes - 1 << ")" << endl;
			Vertex v, w;
			cin >> v >> w;
			if (v < 0 || v >= nVertexes || w < 0 || w >= nVertexes) {
				cout << "Input Error: the vertexes are numbered from 0 to " << nVertexes - 1 << ". Please input again" << endl;
				i--;
				continue;
			}
			cout << "Enter the weight of the edge: " << endl;
			T weight;
			cin >> weight;
			if (weight <= 0) {
				cout << "Input Error: the weight of the edge should be positive. Please input again" << endl;
				i--;
				continue;
			}
			edges.push_back(Edge<T>(v, w, weight));
		}
		Graph<T> *pGraph = this->createGraph(nVertexes, isDirected, edges);
		edges.clear();
		vector<Edge<T>>().swap(edges);
		return pGraph;
	}
};