#include "tarjan.h"

int main() {
	GraphInput<int> graphInput;	
	SCC * tarjan = new Tarjan();
	string cmd;
	while (1) {
		Graph * p_graph = graphInput.createGraphByInput();		
		Color * color = new Color[p_graph->getNumVertices()];
		size_t num_components;
		tarjan->getStrongConnectedComponents(p_graph, color, &num_components);
		cout << "There is(are) " << num_components << " connected component(s)." << endl;
		cout << "Color of each vertex: " << endl;
		for (size_t i = 0; i < p_graph->getNumVertices(); i++) {
			if (i != 0) putchar(' ');
			cout << color[i];
		}
		delete p_graph;
		free(color);
		cout << endl << "Continue?[Y/N]" << endl;		
		while (1) {
			cin >> cmd;
			if (cmd == "Y" || cmd == "y") break;
			else if (cmd == "N" || cmd == "n") goto END;
		}
	}
END:
	delete tarjan;
	return 0;
}