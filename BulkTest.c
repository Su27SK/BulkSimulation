#include <iostream>
/*#include "BulkGraphNode.h"*/
/*#include "BulkGraphEdge.h"*/
#include "BulkFile.h"
#include "Graph.h"
#include "BulkPool.h"
#include "BulkBackPressure.h"
#include "RandomGenerator.h"
using namespace std;
int main()
{
	RandomGenerator::init(time(NULL));
	Graph* graph = Graph::importGraph("graph.txt");
	BulkBackPressure test;
	test.setGraph(graph);

	BulkNode sourceNode;
	BulkNode sinkNode;
	
	srand((unsigned)time(NULL));

	BulkLink* link = new BulkLink(1, 2, 20.0, 0.0);
	for (int i = 1 ; i <= 10; i++) {
		BulkSession* pSession = new BulkSession(i, &sourceNode, &sinkNode);
		for (int j = 1 ; j <= 10; j++) {
			BulkPackets* packets = new BulkPackets();
			link->tail_[i]->push(*packets);
		}
		pSession->setDemand(i);
		link->addSession(*pSession);
	}
	//link->addSession(*pSession);
	/*BulkPackets packets1;*/
	/*BulkPackets packets2;*/
	/*BulkPackets packets3;*/
	/*BulkPackets packets4;*/
	/*BulkSession* pSession = new BulkSession(1, &sourceNode, &sinkNode);*/
	/*pSession->setDemand(2);*/

	/*BulkLink* link = new BulkLink(1, 2, 10.0, 0.0);*/
	/*link->addSession(*pSession);*/

	/*link->tail_[1]->push(packets1);*/
	/*link->tail_[1]->push(packets2);*/
	/*link->tail_[1]->push(packets3);*/
	/*link->tail_[1]->push(packets4);*/

	/*BulkSession* qSession = new BulkSession(2, &sourceNode, &sinkNode);*/
	/*qSession->setDemand(4);*/
	
	/*link->addSession(*qSession);*/
	/*link->tail_[2]->push(packets1);*/
	/*link->tail_[2]->push(packets2);*/
	/*link->tail_[2]->push(packets3);*/
	/*link->tail_[2]->push(packets4);*/

	test.dynamicPush(*link);

	/*Graph* graph = Graph::importGraph("graph.txt");*/
	/*BulkBackPressure test;*/
	/*test.setGraph(graph);*/
	/*test.init();*/
	/*[>test.setSourceNode(1);<]*/
	/*[>test.setSinkNode(4);<]*/
	/*RandomGenerator::init(time(NULL));*/
	/*[>for (int i = 0; i < 5; i++) {<]*/
		/*[>int m = RandomGenerator::genPoissonInt(4);<]*/
		/*[>cout<<m<<endl;<]*/
	/*[>}<]*/
	/*BulkNode* bNode = test.getNodeById(1);*/
	/*BulkNode* eNode = test.getNodeById(4);*/
	/*BulkSession one(1, bNode, eNode);*/
	/*one.setDemand(10);*/
	/*test.startSession(one);*/
	/*test.inputPackets(one);*/
	/*test.inputPackets(one);*/
	/*test.handle();*/

	/*BulkPacket modelPacket(4.0, Mb);*/
	/*cout<<modelPacket.convertToType(2, false)<<endl;*/
	/*modelPacket.setPacketSize(4.0);*/
	/*BulkPackets modelPackets(200, &modelPacket);*/
	/*BulkPool* pool = new BulkPool(&modelPackets);*/
	/*pool->init();*/
	/*BulkPackets* packets = pool->getPacketsFromPool();*/
	/*cout<<packets->getBulkPacketsInfo()<<endl; */
	/*int nNode = graph->getVertices();*/
	/*int nEdge = graph->getEdges();*/
	/*cout<<"nNode:"<<nNode<<endl;*/
	/*cout<<"nEdge:"<<nEdge<<endl;*/
	/*BulkGraphNode* node = new BulkGraphNode(2);*/
	/*BulkGraphEdge e(2, 3, 25.0, 22.0);*/
	/*node->addBulkEdge(&e);*/
	/*BulkGraphNode testNode = *node;*/
	/*cout<<testNode.Print();*/
	/*cout<<"I Love You"<<endl;*/
	/*return 0;*/
}
