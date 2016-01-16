#ifndef _BULKGRAPHNODE_H_
#define _BULKGRAPHNODE_H_
#include <ext/slist>
#include "BulkGraphEdge.h"
using namespace __gnu_cxx;
class BulkGraphNode
{
	private:
		int id;				    //id of the end node of the edge
		int numHeadQueue;       //number of the head queues
		int numTailQueue;       //number of the tail queues
		bool isTerminal ; //check the node is Terminal
		slist<BulkGraphEdge>* headEdge;
		slist<BulkGraphEdge>* tailEdge;
	public:
		//constructors
		BulkGraphNode():id(-1), numHeadQueue(0), numTailQueue(0), isTerminal(false) 
		{
			this->headEdge = new slist<BulkGraphEdge>(0);
			this->tailEdge = new slist<BulkGraphEdge>(0);
		}
		BulkGraphNode(int _id);
		bool operator == (const BulkGraphNode& node);
		bool addBulkEdge(BulkGraphEdge* edge);
		bool removeBulkEdge(BulkGraphEdge* edge);
		int getNumHeadQueue() const;
		int getNumTailQueue() const;
		int getNodeId() const;
		BulkGraphEdge* getBulkEdge(BulkGraphEdge* edge) const;
		slist<BulkGraphEdge>* getHeadEdge() const;
		slist<BulkGraphEdge>* getTailEdge() const;
		BulkGraphNode& operator = (const BulkGraphNode &node);
		int Print();
		//destructor
		virtual ~BulkGraphNode()
		{
			this->headEdge = NULL;
			this->tailEdge = NULL;
		}
};
#endif
