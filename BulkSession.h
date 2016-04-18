#ifndef _BULKSESSION_H_
#define _BULKSESSION_H_
#include <queue>
#include "Graph.h"
#include "BulkNode.h"
#include "BulkPool.h"
#include "Application.h"
#include "RandomGenerator.h"
class BulkLink;
class BulkSession 
{
	private: 
		static BulkPool bulkPool;  
		static BulkPackets initPackets;
		double _demand; //sink to the meeting point v 平均值
	public:
		BulkNode* sourceNode_;
		BulkNode* sinkNode_;
		int id_;       //该session中的id
		double flow_;  //该session传输flow_大小(packets num)
		double time_;  //设置log时间
		static void initPool(BulkPackets& model) {
			bulkPool.setPacketsType(&model);
			bulkPool.init(); //内存池初始化
		}
		BulkSession();
		BulkSession(int id, BulkNode* source, BulkNode* sink);
		bool isSessionEqualLink(int bId, int eId, int sId);
		BulkSession& setDemand(double demand);
		double getDemand();
		virtual void send(int npackets, BulkLink& link, FILE* fp, FILE* flowFp);
		virtual void recv(int npackets, double time, FILE* fp);
		void start();
		void stop();
	protected:
		int running_;
		void running();
};
#endif
