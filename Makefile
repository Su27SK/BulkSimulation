BulkTest: BulkGraphEdge.o BulkGraphNode.o BulkFile.o Graph.o BulkPacket.o BulkPackets.o BulkPool.o 
	g++  BulkGraphEdge.o BulkGraphNode.o BulkFile.o Graph.o BulkPacket.o BulkPackets.o BulkPool.o -o BulkTest -g BulkTest.c

BulkGraphEdge.o: BulkGraphEdge.h BulkGraphEdge.cpp
	g++ -Wall -c -g BulkGraphEdge.cpp

BulkGraphNode.o: BulkGraphNode.h BulkGraphNode.cpp
	g++ -Wall -c -g BulkGraphNode.cpp
BulkFile.o: BulkFile.h BulkFile.cpp
	g++ -Wall -c -g BulkFile.cpp
Graph.o: Graph.h Graph.cpp
	g++ -Wall -c -g Graph.cpp
BulkPacket.o: BulkPacket.h BulkPacket.cpp
	g++ -Wall -c -g BulkPacket.cpp
BulkPackets.o: BulkPackets.h BulkPackets.cpp
	g++ -Wall -c -g BulkPackets.cpp
BulkPool.o: BulkPool.h BulkPool.cpp
	g++ -Wall -c -g BulkPool.cpp
clean:
	rm -rf *.o  BulkTest 

