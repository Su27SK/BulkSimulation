#ifndef _BULKGRAPHNODE_H_
#define _BULKGRAPHNODE_H_
class BulkGraphNode
{
public:
	int id;				    //id of the end node of the edge
	int numHeadQueue;       //number of the head queues
	int numTailQueue;       //number of the tail queues
	bool isTerminal;        //check the node is Terminal
public:
	//constructors
	BulkGraphNode():numHeadQueue(0), numTailQueue(0), isTerminal(false)
	{}
	BulkGraphNode(int _id);
	bool operator == (const BulkGraphNode& node);
	int getNumHeadQueue() const;
	int getNumTailQueue() const;
	BulkGraphNode& operator++(int);
	BulkGraphNode& operator++();
	BulkGraphNode& operator--(int);
	BulkGraphNode& operator--();
	//destructor
	virtual ~BulkGraphNode()
	{}
};

#endif
