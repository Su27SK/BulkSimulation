#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include <ext/slist>
#include <queue>
#include "Graph.h"
#include "BulkPackets.h"
#include "BulkControlPacket.h"
class BulkLink
{
	private:
		int _from;
		int _to;
		bool _isToTerminal; //_to是否通向终止点
		int _numPacketsHead; //edge边头的队列
		int _numPacketsTail; //edge边尾的队列
		queue<BulkPackets>* _headQueue;
		queue<BulkPackets>* _tailQueue;
	public:
		BulkLink()
		{
			this->_from = -1;
			this->_to = -1;
			this->_isToTerminal = false;
			this->_headQueue = this->_tailQueue = NULL;
			this->_numPacketsHead = this->_numPacketsTail = 0;
		}

		BulkLink(int from, int to, bool isTerminal = false):
		_headQueue(NULL), _tailQueue(NULL), _numPacketsHead(0),_numPacketsTail(0)
		{
			this->_from = from;
			this->_to = to;
			this->_isToTerminal = isTerminal;
		}

		bool addNumPacketsHead(bool isAdd, int numPackets = 1);
		bool addNumPacketsTail(bool isAdd, int numPackets = 1);
		
};
#endif
