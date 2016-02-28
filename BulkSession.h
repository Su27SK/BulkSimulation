#ifndef _BULKSESSION_H_
#define _BULKSESSION_H_
#include <queue>
#include "Graph.h"
#include "BulkNode.h"
#include "BulkPool.h"
#include "Application.h"
class BulkSession : public Application<BulkPackets>
{
	public:
		BulkNode* sourceNode_;
		BulkNode* sinkNode_;
		static BulkPool bulkPool_;  
		int id_;       //该session中的id
		double flow_;  //该session传输flow_大小(从source节点传输到sink节点)
		static void initPool() {
			static BulkPackets bulkpackets;
			bulkPool_.setPacketsType(&bulkpackets);
			bulkPool_.init(); //内存池初始化
		}
		BulkSession():Application(), sourceNode_(NULL), sinkNode_(NULL) {
			id_ = -1;
			running_ = 0;
			flow_ = 0.0;
		}
		BulkSession(int id, BulkNode* source, BulkNode* sink):Application() {
			this->sourceNode_ = source;
			this->sinkNode_ = sink;
			id_ = id;
			running_ = 0;
			flow_ = 0.0;
		}
		int diffPackets();
		bool isSessionEqualLink(int bId, int eId, int sId);
		virtual void send(int npackets);
		virtual void recv(int npackets);
	protected:
		int running_;
		void start();
		void stop();
};
#endif
