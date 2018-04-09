#ifndef GRAF_GRAPH_H
#define GRAF_GRAPH_H
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>

class Graph {
 public:
	Graph(int);
	Graph();
	~Graph();
	void addEdge(int, int) ;
	operator std::vector<int> *();
	Graph& operator=(Graph &);
	int vertexNumber();
 private:
	std::vector<int> *graph = nullptr;
	int V;
};

class GraphReader {
 public:
	GraphReader();
	~GraphReader();
	Graph& readFromFile(const std::string &);
	Graph& readFromStd();
	Graph& getGraph();
 private:
	Graph *graph = nullptr;
};

std::vector<std::pair<int, int>> findBridges(std::vector<int> [], int);

bool checkIntegrity(std::vector<int> [], int, int, int);

void DFS(int, std::vector<int> [], int, std::vector<std::pair<int, int>> &, std::vector<bool> &);

std::vector<std::pair<int, int>> find(std::vector<int> [], int);

#endif //GRAF_GRAPH_H
