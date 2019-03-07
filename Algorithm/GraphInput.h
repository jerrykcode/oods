#pragma once
#include "GraphInitializer.h"

template<typename T>
class GraphInput : public GraphInitializer<T> {
public:
	GraphInput() : GraphInitializer<T>() {}
	~GraphInput() {}

	Graph *createGraphByInput() {
		bool isDirected, isWeighted;
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
		while (true) {
			cout << "Is the graph weighted ? [Y/N]" << endl;
			string cmd;
			cin >> cmd;
			if (cmd == "Y" || cmd == "y") {
				isWeighted = true;
				break;
			}
			else if (cmd == "N" || cmd == "n") {
				isWeighted = false;
				break;
			}
		}
		cout << "Enter the number of vertexes: " << endl;
		cin >> nVertexes;
		cout << "Enter the number of edges: " << endl;
		cin >> nEdges;
		vector<Edge *> edges;
		for (int i = 0; i < nEdges; i++) {
			cout << "Eneter the 2 vertexes of the " << i << "th edge: (The vertexes numbered from 0 to " << nVertexes - 1 << ")" << endl;
			Vertex v, w;
			cin >> v >> w;
			if (v < 0 || v >= nVertexes || w < 0 || w >= nVertexes) {
				cout << "Input Error: the vertexes are numbered from 0 to " << nVertexes - 1 << ". Please input again" << endl;
				i--;
				continue;
			}
			if (isWeighted) {
				cout << "Enter the weight of the edge: " << endl;
				T weight;
				cin >> weight;
				if (weight <= 0) {
					cout << "Input Error: the weight of the edge should be positive. Please input again" << endl;
					i--;
					continue;
				}
				edges.push_back((Edge *)(new WEdge<T>(v, w, weight)));
			}
			else {
				edges.push_back((Edge *)(new UNWEdge(v, w)));
			}
		}
		Graph *pGraph = this->createGraph(nVertexes, isDirected, isWeighted, edges);
		for (auto it = edges.begin(); it != edges.end(); it++)
			if (*it != NULL) {
				delete (*it);
				*it = NULL;
			}
		edges.clear();
		vector<Edge *>().swap(edges);
		return pGraph;
	}
};