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
	Graph* graph = Graph::importGraph("Bulk_Config_File/graph.txt");
	BulkBackPressure test;
	test.setGraph(graph);
	test.init();
	RandomGenerator::init(time(NULL));
	BulkNode* bNode = test.getNodeById(1);
	BulkNode* eNode = test.getNodeById(4);
	BulkSession one(1, bNode, eNode);
	one.setDemand(10);
	test.startSession(one);
	for (int t = 0; t < 300; t++) {
		test.handle();
		test.inputPackets(one);
	}
	return 0;
}
