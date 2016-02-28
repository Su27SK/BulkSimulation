#ifndef _BULKNODE_H_
#define _BULKNODE_H_
#include "BulkGraphNode.h"
#include "BulkLink.h"
#include "BulkPackets.h"
#include <queue>
#define MAX_SIZE 100
class BulkLink;
class BulkNode:public BulkGraphNode
{
	private:
		bool _isTerminal;    //是否是终点
		bool _isOriginal;    //是否是起点
		void _defaultInit(); //缺省初始化函数
	protected:
		int  store_;        //总存储包数量
		int* sNumPackets_;  //session's array(该session在该节点的存储数据包数量)
		slist<BulkLink>* output_; //链路出去
		slist<BulkLink>* input_;  //链路进来
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
		int getStoreSize(int sId);
		int getStoreSize();
		bool getTerminal();
		bool getOriginal();
		void realloc(int sId);
		slist<BulkLink>* getOutputLink();
		slist<BulkLink>* getInputLink();
		void addOutputLink(BulkGraphEdge* edge);
		void addInputLink(BulkGraphEdge* edge);
		BulkNode& setTerminal();
		BulkNode& setOriginal();
		BulkNode& addSessionNum(int sId, int num = 1);
		BulkNode& reduceSessionNum(int sId, int num = 1);
};
#endif
