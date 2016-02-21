#ifndef _BULKSESSION_H_
#define _BULKSESSION_H_
#include <queue>
#include "Graph.h"
#include "BulkNode.h"
#include "BulkPool.h"
#include "Application.h"
#include "TimerHandler.h"
#include "getClass.h"
class BulkSession;
class BulkSessionTimer : public TimerHandler
{
	public:
		BulkSessionTimer(BulkSession* t): TimerHandler(), t_(t){}
		BulkSessionTimer(): TimerHandler(){}
		inline virtual void expire(Event*);
		inline virtual void handle(Event*);
	protected:
		BulkSession* t_;
};

class BulkSession : public Application<BulkPackets>
{
	private:
		BulkNode* _sourceNode;
		BulkNode* _sinkNode;
		static BulkPool* _bulkPool;  
	public:
		int id_;       //该session中的id
		double flow_;  //该session传输flow_大小(从source节点传输到sink节点)
		static void initPool()
		{
			if (_bulkPool == 0) {
				static BulkPackets bulkpackets;
				_bulkPool = new BulkPool(&bulkpackets);
				_bulkPool->init(); //内存池初始化
			}
		}
		BulkSession():Application(), _sourceNode(NULL), _sinkNode(NULL) {
			id_ = -1;
			flow_ = 0.0;
		}
		BulkSession(int id, BulkNode* source, BulkNode* sink):Application() {
			this->_sourceNode = source;
			this->_sinkNode = sink;
			id_ = id;
			flow_ = 0.0;
		}
		int diffPackets();
		bool isSessionEqualLink(int bId, int eId, int sId);
		virtual void send(int npackets);
		virtual void recv(int npackets);
	protected:
		void start();
		void stop();
		BulkSessionTimer timer_;
};
#endif
