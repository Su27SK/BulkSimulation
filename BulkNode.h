#ifndef _BULKNODE_H_
#define _BULKNODE_H_
#include "BulkGraphNode.h"
#include "BulkLink.h"
#include "BulkPackets.h"
#include <queue>
#include <vector>
#define MAX_SIZE 100
class BulkLink;
class BulkNode:public BulkGraphNode
{
	private:
		bool _isTerminal;    //是否是终点
		bool _isOriginal;    //是否是起点
		void _defaultInit(); //缺省初始化函数
		double _getAllWeight();  //对I(v) U O(v)求weight倒数之和
		void _reallocPackets(queue<BulkPackets> *p, double size, unit type);
	protected:
		slist<BulkLink>* output_; //链路出去
		slist<BulkLink>* input_;  //链路进来
	public: 
		vector<int> sVector;      //存放session id
		BulkNode():BulkGraphNode() {
			this->_defaultInit();
		}
		BulkNode(int _id):BulkGraphNode(_id) {
			this->_defaultInit();
		}
		BulkNode(const BulkGraphNode& node);
		BulkNode(BulkGraphNode& node);
		double getStoreSize(int sId, unit type = Kb);
		int getNumLink();
		bool getTerminal();
		bool getOriginal();
		void realloc(int sId);
		void reallocAll();
		slist<BulkLink>* getOutputLink();
		slist<BulkLink>* getInputLink();
		void addOutputLink(BulkGraphEdge* edge);
		void addInputLink(BulkGraphEdge* edge);
		BulkNode& setTerminal();
		BulkNode& setOriginal();
};
#endif
