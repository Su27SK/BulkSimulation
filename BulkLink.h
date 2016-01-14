#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include <ext/slist>
#include <queue>
#include "BulkGraphEdge.h"
#include "BulkPackets.h"
#include "BulkControlPacket.h"
using namespace std;
class BulkLink:BulkGraphEdge
{
	private:
		bool _isToTerminal; //_to是否通向终止点
		int _numPacketsHead; //edge边头的队列
		int _numPacketsTail; //edge边尾的队列
		queue<BulkPackets>* _headQueue;
		queue<BulkPackets>* _tailQueue;
	public:
		BulkLink():BulkGraphEdge()
		{
			this->_isToTerminal = false;
			this->_numPacketsHead = this->_numPacketsTail = 0;
			this->_headQueue = new queue<BulkPackets>(0);
			this->_tailQueue = new queue<BulkPackets>(0);
		}
		BulkLink(int from, int to, bool isTerminal = false);
		BulkLink(int from, int to, int weight, int capacity, bool isTerminal = false);
		bool addNumPacketsHead(bool isAdd, int numPackets = 1);
		bool addNumPacketsTail(bool isAdd, int numPackets = 1);
};
#endif
