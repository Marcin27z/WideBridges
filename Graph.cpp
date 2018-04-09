#include "Graph.h"

Graph::Graph(int V): V(V){
	graph = new std::vector<int>[V];
}

Graph::Graph() {}

Graph::~Graph() {
	delete[] graph;
}

void Graph::addEdge(int u, int v) {
	graph[u].push_back(v);
	graph[v].push_back(u);
}

Graph::operator std::vector<int> *() {
	return graph;
}

Graph& Graph::operator=(Graph &rhsGraph) {
	V = rhsGraph.V;
	delete[] graph;
	graph = new std::vector<int> [V];
	for(int i = 0;i < V; i++) {
		graph[i] = rhsGraph.graph[i];
	}
	return *this;
}

int Graph::vertexNumber() {
	return V;
}

Graph& GraphReader::readFromStd() {
	int vertexNumber;
	std::cin >> vertexNumber;
	delete graph;
	graph = new Graph(vertexNumber);
	int u, v;
	while (std::cin >> u >> v) {
		graph->addEdge(u, v);
	}
	return *graph;
}

Graph& GraphReader::readFromFile(const std::string &fileName) {
	int vertexNumber;
	std::fstream in;
	in.exceptions(std::fstream::failbit | std::fstream::badbit);
	try {
		in.open(fileName, std::fstream::in);
		in >> vertexNumber;
	}
	catch (std::ifstream::failure &e) {
		std::cout << e.what();
		return *graph;
	}
	delete graph;
	graph = new Graph(vertexNumber);
	int u, v;
	try {
		while (!in.eof()) {
			in >> u >> v;
			graph->addEdge(u, v);
		}
	}
	catch (std::ifstream::failure &e) {
		std::cout << e.what();
	}
	return *graph;
}

Graph& GraphReader::getGraph() {
	return *graph;
}

GraphReader::GraphReader() {}

GraphReader::~GraphReader() {
	delete graph;
}

std::vector<std::pair<int, int>> findBridges(std::vector<int> adj[], int V) {
	std::vector<bool> visited(V, false);
	std::stack<int> stack;
	stack.push(0);
	//visited[0] = true;
	std::vector<std::pair<int, int>> bridges;
	while (!stack.empty()) {
		int vertex = stack.top();
		stack.pop();
		if(!visited[vertex]) {
			//cout << vertex <<"\n";
			visited[vertex] = true;
			for (int j = 0; j < adj[vertex].size(); j++) {
				int adjacent = adj[vertex][j];
				if ((vertex == adjacent) || (visited[adjacent] == true))
					continue;
				if (!checkIntegrity(adj, vertex, adjacent, V))
					bridges.push_back(std::make_pair(vertex, adjacent));
				if (visited[adjacent] == false)
					stack.push(adjacent);
			}
		}
	}
	return bridges;
}

void DFS(int v, std::vector<int> adj[], int V, std::vector<std::pair<int, int>> &bridges, std::vector<bool> &visited) {

	for (int i = 0; i < adj[v].size(); i++) {
		int adjacent = adj[v][i];
		if ((v == adjacent) || (visited[adjacent] == true))
			continue;
		if (!checkIntegrity(adj, v, adjacent, V))
			bridges.push_back(std::make_pair(v, adjacent));
		visited[v] = true;
		DFS(adjacent, adj, V, bridges, visited);
	}
};

std::vector<std::pair<int, int>> find(std::vector<int> adj[], int V) {
	std::vector<std::pair<int, int>> bridges;
	std::vector<bool> visited(V, false);
	DFS(0, adj, V, bridges, visited);
	return bridges;
};

bool checkIntegrity(std::vector<int> adj[], int u, int v, int V) {
	if (V == 0)
		return true;
	std::vector<bool> visited(V, false);
	visited[u] = true;
	visited[v] = true;
	int counter = 0;
	std::stack<int> stack;
	for (int i = 0; i < V; i++) {
		if (visited[i] == false) {
			stack.push(i);
			visited[i] = true;
			break;
		}
	}
	while (!stack.empty()) {
		int vertex = stack.top();
		stack.pop();
		counter++;
		for (int i = 0; i < adj[vertex].size(); i++) {
			if (visited[adj[vertex][i]] == false) {
				stack.push(adj[vertex][i]);
				visited[adj[vertex][i]] = true;
			}
		}
	}
	if (counter == V - 2)
		return true;
	return false;
}