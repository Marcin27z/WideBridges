LINKOBJ = main.o graph.o
BIN = mosty
CC = g++

$(BIN): $(LINKOBJ)
	$(CC) $(LINKOBJ) -o $(BIN)

main.o: main.cpp
	$(CC) -c main.cpp -o main.o -std=c++11

graph.o: Graph.cpp
	$(CC) -c Graph.cpp -o graph.o -std=c++11
