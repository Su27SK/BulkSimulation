#ifndef _BULKPACKETS_H_
#define _BULKPACKETS_H_
#include "BulkPacket.h"
#include "BulkGraphNode.h"
#include <ext/slist>
class BulkPackets
{
	private:
		double _transmitNum;
		int _sourceId;
		int _sinkId;
		int _ptr;
		double _startTime;
		BulkPacket* _model;
	public: 
		BulkPackets(): _transmitNum(10), _sourceId(-1), _sinkId(-1), _ptr(1), _startTime(-1) {
			this->_model = new BulkPacket();
		};
		BulkPackets(double number, BulkPacket* packet = NULL);
		BulkPackets(double number, int source, int sink, BulkPacket* packet = NULL);
		explicit BulkPackets(const BulkPackets& P);
		BulkPackets(BulkPackets& P);
		~BulkPackets();
		double getBulkPacketsSize();
		double getBulkPacketsSize(unit type);
		double getTransmitNum();
		BulkPacket* getModel() const;
		string getBulkPacketsInfo();
		BulkPackets& setTransmitNum(double number);
		BulkPackets& setSourceNode(int source);
		BulkPackets& setSinkNode(int sink);
		BulkPackets& setStartTime(double time);
		BulkPackets& operator = (const BulkPackets& bulkPackets);
		BulkPackets& addPtr();
		BulkPackets& reducePtr();
		int getPtr();
		int getSourceNodeId() const;
		int getSinkNodeId() const;
		double getStartTime() const;
};
#endif
