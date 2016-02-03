#ifndef BULKSESSION_H_
#define BULKSESSION_H_
#include <queue>
#include "Graph.h"
#include "Application.h"
#include "TimerHandler.h"
#include "BulkPackets.h"
#include "BulkPool.h"
static BulkPackets bulkpackets;
static BulkPool bulkpool_(&bulkpackets);
bulkpool_.init(); //内存池初始化
class BulkSessionTimer : public TimerHandler
{
	public:
		BulkSessionTimer(BulkSession* t): TimerHandler(), t_(t){}
		inline virtual void expire(Event*);
	protected:
		BulkSession* t_;
};

class BulkSession : public Application<bulkpackets>
{
	private:
		BulkGraphNode* _sourceNode;
		BulkGraphNode* _sinkNode;
		queue<BulkPackets>* _headQueue;
		queue<BulkPackets>* _tailQueue;
	public:
		int id_;    //该session中的id
		int flow_;  //该session传输flow_大小
		BulkSession():Application(), _sourceNode(NULL), _sinkNode(NULL) {
			this->_headQueue = new queue<BulkPackets>(0);
			this->_tailQueue = new queue<BulkPackets>(0);
			id_ = -1;
		}
		BulkSession(int id, BulkGraphNode* source, BulkGraphNode* sink):Application() {
			id_ = id;
			this->_sourceNode = source;
			this->_sinkNode = sink;
			this->_headQueue = new queue<BulkPackets>(0);
			this->_tailQueue = new queue<BulkPackets>(0);
		}
		int diffPackets();
	protected:
		void start();
		void stop();
		virtual static void send(int npackets);
		virtual static void recv(int npackets);
		BulkSessionTimer timer_;
};
#endif
