#include "prim.h"
#include "GraphInput.h"

typedef unsigned short word;
typedef unsigned long dword;

int main() {
	GraphInput<word> graph_input;
	Graph * p_graph = graph_input.createGraphByInput();
	if (!p_graph->isWeighted()) {
		cout << "error!";
	}
	else {
		Mst<word, dword> * prim = new Prim<word, dword>();
		dword mst_weight;
		if (prim->getMstWeight((WGraph<word> *)p_graph, &mst_weight)) {
			cout << "Mst weight : " << mst_weight << endl;
		}
		else cout << "prim->getMstWeight: error!" << endl;
		WGraph<word> * p_mst_graph = prim->getMst((WGraph<word> *)p_graph, &mst_weight);
		if (p_mst_graph != NULL) {
			cout << "Mst weight : " << mst_weight << endl;
			//bfs traverse all the edges of mst
			queue<Vertex> q;
			q.push(0);
			bool * visited = new bool[p_mst_graph->getNumVertices()];
			fill(visited, visited + p_mst_graph->getNumVertices(), false);			
			while (!q.empty()) {
				Vertex v = q.front();
				q.pop();
				visited[v] = true;
				Iterator * it = p_mst_graph->getAdjIterator(v);
				for (AdjNode * p_adj_node = it->next(); p_adj_node != NULL; p_adj_node = it->next()) {
					Vertex adj_v = p_adj_node->getAdjVertex();
					if (!visited[adj_v]) {
						cout << "edge between " << v << " and " << adj_v << " : " << ((WAdjNode<word> *)p_adj_node)->getAdjWeight() << endl;
						q.push(adj_v);
					}				
				}
				delete it;
			}
			free(visited);
			delete p_mst_graph;
		}
		else cout << "prim->getMst: error!" << endl;
	}
	delete p_graph;
	return 0;
}