#ifndef BULKSESSION_H_
#define BULKSESSION_H_
#include "Graph.h"
class BulkSession
{
	private:
		GraphNode* _sourceNode;
		GraphNode* _sinkNode;
	public:
		BulkSession():_sourceNode(NULL), _sinkNode(NULL) {
		}
		BulkSession(GraphNode* source, GraphNode* sink) {
			this->_sourceNode = source;
			this->_sinkNode = sink;
		}
};
#endif
