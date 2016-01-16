#include <iostream>
#include "BulkGraphNode.h"
#include "BulkGraphEdge.h"
using namespace std;
int main()
{
	BulkGraphNode* node = new BulkGraphNode(2);
	BulkGraphEdge e(2, 3, 25.0, 22.0);
	node->addBulkEdge(&e);
	BulkGraphNode testNode = *node;
	cout<<testNode.Print();
	cout<<"I Love You"<<endl;
	return 0;
}
