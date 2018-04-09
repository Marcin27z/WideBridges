#include "Graph.h"

using namespace std;


int main(int argc, char *argv[]) {
	GraphReader graphReader;
	Graph graph;
	if(argc < 2)
		graph = graphReader.readFromStd();
	else
		graph = graphReader.readFromFile(argv[1]);
	vector<pair<int, int>> bridges = findBridges(graph, graph.vertexNumber());
	for (auto &&it: bridges)
		cout << it.first << " " << it.second << "\n";
	return 0;
}
