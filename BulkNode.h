#ifndef _BULKNODE_H_
#define _BULKNODE_H_
#include "BulkGraphNode.h"
#include "BulkPackets.h"
#include <queue>
#define MAX_SIZE 100
class BulkNode:public BulkGraphNode
{
	private:
		bool _isTerminal;    //是否是终点
		void _defaultInit(); //缺省初始化函数
	protected:
		int  store_;        //总存储包数量
		int* sessionNumPacket_; //session's array(该session在该节点的存储数据包数量)
	public: 
		queue<BulkPackets>** pqueue;
		BulkNode():BulkGraphNode()
		{
			this->_defaultInit();
		}
		BulkNode(int _id):BulkGraphNode(_id)
		{
			this->_defaultInit();
		}
		BulkNode(const BulkGraphNode& node);
		BulkNode(BulkGraphNode& node);
		int getStoreSize();
		BulkNode& setTerminal();
		bool getTerminal();
		BulkNode& addSessionNum(int sessionId, int num = 1);
		BulkNode& reduceSessionNum(int sessionId, int num = 1);
};
#endif
