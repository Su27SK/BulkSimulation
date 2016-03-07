#include <iostream>
#include "BulkGraphNode.h"
#include "BulkGraphEdge.h"
#include "BulkFile.h"
#include "Graph.h"
#include "BulkPool.h"
using namespace std;
int main()
{
	Graph* graph = Graph::importGraph("graph.txt");
	BulkPacket modelPacket(4.0, Mb);
	cout<<modelPacket.convertToType(2, false)<<endl;
	//modelPacket.setPacketSize(4.0);
	BulkPackets modelPackets(200, &modelPacket);
	BulkPool* pool = new BulkPool(&modelPackets);
	pool->init();
	BulkPackets* packets = pool->getPacketsFromPool();
	cout<<packets->getBulkPacketsInfo()<<endl; 
	/*int nNode = graph->getVertices();*/
	/*int nEdge = graph->getEdges();*/
	/*cout<<"nNode:"<<nNode<<endl;*/
	/*cout<<"nEdge:"<<nEdge<<endl;*/
	return 0;
	BulkGraphNode* node = new BulkGraphNode(2);
	BulkGraphEdge e(2, 3, 25.0, 22.0);
	node->addBulkEdge(&e);
	BulkGraphNode testNode = *node;
	cout<<testNode.Print();
	cout<<"I Love You"<<endl;
	return 0;
}
