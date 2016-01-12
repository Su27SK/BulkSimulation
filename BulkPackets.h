#ifndef _BULKPACKETS_H_
#define _BULKPACKETS_H_
#include "BulkPacket.h"
#include "Graph.h"
#include <ext/slist>
class BulkPackets
{
	private:
		double _transferPacketsNum;
		GraphNode* _sourceNode;
		GraphNode* _sinkNode;
		BulkPacket* _model;
	public: 
		BulkPackets():_sourceNode(new GraphNode()), _sinkNode(new GraphNode()), _transferPacketsNum(1) {
			this->_model = new BulkPacket();
		};
		BulkPackets(double number, BulkPacket* packet = NULL);
		BulkPackets(double number, GraphNode* source, GraphNode* sink, BulkPacket* packet = NULL);
		double getBulkPacketsSize();
		string getBulkPacketsInfo();
		BulkPackets& setTransferPacketsNum(double number);
		BulkPackets& setSourceNode(GraphNode* source);
		BulkPackets& setSinkNode(GraphNode* sink);
		~BulkPackets();
};
#endif
