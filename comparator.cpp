#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

using namespace std;

class Edge {
public:
	int u, v;
	bool equals(Edge &edge) {
		return ((u == edge.u && v == edge.v) || (u == edge.v && v == edge.u));
	}
};

int main(int argc, char *argv[]) {
	fstream in_1;
    //in_1.exceptions(fstream::failbit|fstream::badbit);
	fstream in_2;
    //in_2.exceptions(fstream::failbit|fstream::badbit);
    //try {
	in_1.open(argv[1], ifstream::in); //to be tested
	in_2.open(argv[2], ifstream::in); //good
    //} catch (fstream::failure &e) {
     //   cout << e.what();
    //}
	vector <Edge> edges1;
	vector <Edge> edges2;
	Edge edge;
	while (!in_1.eof()) {
		in_1 >> edge.u >> edge.v;
		edges1.push_back(edge);
	}
	while (!in_2.eof()) {
		in_2 >> edge.u >> edge.v;
		edges2.push_back(edge);
	}
	edges1.pop_back();
	edges2.pop_back();
	bool error = false;
	for (int i = 0; i < edges1.size(); ++i) {
		for (int j = 0; j < edges1.size(); ++j) {
			if (edges1[i].equals(edges1[j]) && i != j) {
				cout << "Krawedz " << edges1[i].u << " " << edges1[i].v << " sie powtarza\n";
				error = true;
            }
		}
	}
	bool flag = false;
	for (int i = 0; i < edges1.size(); ++i) {
		for (auto edgeIt = edges2.begin(); edgeIt != edges2.end(); ++edgeIt) {
			if (edges1[i].equals(*edgeIt)) {
				flag = true;
				edges2.erase(edgeIt);
				break;
			}
		}
		if (flag == false) {
			cout << "Krawedz " << edges1[i].u << " " << edges1[i].v << " nie jest mostem\n";
			error = true;
		}
		flag = false;
	}
	if(!error)
		cout << "OK\n";
    in_1.close();
    in_2.close();
	return 0;
}
