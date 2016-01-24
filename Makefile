BulkTest: BulkGraphEdge.o BulkGraphNode.o BulkFile.o Graph.o 
	g++  BulkGraphEdge.o BulkGraphNode.o BulkFile.o Graph.o  -o BulkTest BulkTest.c

BulkGraphEdge.o: BulkGraphEdge.h BulkGraphEdge.cpp
	g++ -Wall -c -g BulkGraphEdge.cpp

BulkGraphNode.o: BulkGraphNode.h BulkGraphNode.cpp
	g++ -Wall -c -g BulkGraphNode.cpp
BulkFile.o: BulkFile.h BulkFile.cpp
	g++ -Wall -c -g BulkFile.cpp
Graph.o: Graph.h Graph.cpp
	g++ -Wall -c -g Graph.cpp
clean:
	rm -rf *.o  BulkTest 

