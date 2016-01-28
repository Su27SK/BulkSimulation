#ifndef _BULKPACKETS_H_
#define _BULKPACKETS_H_
#include "BulkPacket.h"
#include "BulkGraphNode.h"
#include <ext/slist>
class BulkPackets
{
	private:
		double _transferPacketsNum;
		BulkGraphNode* _sourceNode;
		BulkGraphNode* _sinkNode;
		BulkPacket* _model;
	public: 
		BulkPackets(): _transferPacketsNum(0), _sourceNode(new BulkGraphNode()), _sinkNode(new BulkGraphNode()) {
			this->_model = new BulkPacket();
		};
		BulkPackets(double number, BulkPacket* packet = NULL);
		BulkPackets(double number, BulkGraphNode* source, BulkGraphNode* sink, BulkPacket* packet = NULL);
		explicit BulkPackets(const BulkPackets& P);
		BulkPackets(BulkPackets& P);
		~BulkPackets();
		double getBulkPacketsSize();
		string getBulkPacketsInfo();
		BulkPackets& setTransferPacketsNum(double number);
		BulkPackets& setSourceNode(BulkGraphNode* source);
		BulkPackets& setSinkNode(BulkGraphNode* sink);
		BulkPackets& operator = (const BulkPackets& bulkPackets);
};
#endif
