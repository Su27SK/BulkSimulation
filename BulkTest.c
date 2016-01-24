#include <iostream>
#include "BulkGraphNode.h"
#include "BulkGraphEdge.h"
#include "BulkFile.h"
#include "Graph.h"
using namespace std;
int main()
{
	Graph* graph = Graph::importGraph("graph.txt");
	int nNode = graph->getVertices();
	int nEdge = graph->getEdges();
	cout<<"nNode:"<<nNode<<endl;
	cout<<"nEdge:"<<nEdge<<endl;
	BulkGraphNode* node = new BulkGraphNode(2);
	BulkGraphEdge e(2, 3, 25.0, 22.0);
	node->addBulkEdge(&e);
	BulkGraphNode testNode = *node;
	cout<<testNode.Print();
	cout<<"I Love You"<<endl;
	return 0;
}
