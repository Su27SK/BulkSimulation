BulkTest: BulkNode.o BulkLink.o BulkSession.o BulkGraphEdge.o BulkGraphNode.o BulkFile.o Graph.o BulkPacket.o BulkPackets.o BulkPool.o Scheduler.o TimerHandler.o Process.o BulkNetwork.o BulkBackHandle.o BulkBackPressure.o
	g++  BulkNode.o BulkLink.o BulkSession.o BulkGraphEdge.o BulkGraphNode.o BulkFile.o Graph.o BulkPacket.o BulkPackets.o BulkPool.o Scheduler.o TimerHandler.o Process.o BulkNetwork.o BulkBackHandle.o BulkBackPressure.o -o BulkTest -g BulkTest.c

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
Scheduler.o: Scheduler.h Scheduler.cpp
	g++ -Wall -c -g Scheduler.cpp
TimerHandler.o: TimerHandler.h TimerHandler.cpp
	g++ -Wall -c -g TimerHandler.cpp
Process.o: Process.h Process.cpp
	g++ -Wall -c -g Process.cpp
BulkSession.o: Application.h BulkSession.h BulkSession.cpp
	g++ -Wall -c -g BulkSession.cpp
BulkNode.o: BulkGraphNode.h BulkNode.h BulkNode.cpp
	g++ -Wall -c -g BulkNode.cpp
BulkLink.o: BulkGraphNode.h BulkLink.h BulkLink.cpp
	g++ -Wall -c -g BulkLink.cpp
BulkNetwork.o: BulkNetwork.h BulkNetwork.cpp
	g++ -Wall -c -g BulkNetwork.cpp
BulkBackHandle.o: BulkBackHandle.h BulkBackHandle.cpp
	g++ -Wall -c -g BulkBackHandle.cpp
BulkBackPressure.o: BulkBackPressure.h BulkBackPressure.cpp
	g++ -Wall -c -g BulkBackPressure.cpp
clean:
	rm -rf *.o  BulkTest 

