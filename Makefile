BulkTest: BulkGraphEdge.o BulkGraphNode.o
	g++  BulkGraphEdge.o BulkGraphNode.o -o BulkTest BulkTest.c

BulkGraphEdge.o: BulkGraphEdge.h BulkGraphEdge.cpp
	g++ -Wall -c -g BulkGraphEdge.cpp

BulkGraphNode.o: BulkGraphNode.h BulkGraphNode.cpp
	g++ -Wall -c -g BulkGraphNode.cpp
clean:
	rm -rf *.o  BulkTest 

