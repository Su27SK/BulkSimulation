#ifndef  _BULKNETWORK_H_ 
#define  _BULKNETWORK_H_
#define MAX 100
#include "Graph.h"
#include "BulkNode.h"
#include "RandomGenerator.h"
#include <map>
class BulkLink;
class BulkSession;
using namespace std;
class BulkNetwork
{
	private:
		Graph* _topology;
	protected:
		int _nSource; //有几个Source流入点
		int _nSink;   //有几个Sink流出点
		map<int, BulkNode>* _lSourceList; //具体流入source数据包节点索引
		map<int, BulkNode>* _lSinkList;   //具体流出sink数据包节点索引
		BulkNode** nList_;
	public:
		BulkNetwork():_nSource(0), _nSink(0) {
			this->_lSourceList = new map<int, BulkNode>;
			this->_lSinkList = new map<int, BulkNode>;
			this->_topology = NULL;
			nList_ = NULL;
		}
		void init();
		void setGraph(Graph* graph);
		void startSession(BulkSession& session);
		void inputPackets(double m, BulkSession& session);
		virtual void dynamicPush(BulkLink* link) = 0;
		BulkNetwork(Graph* graph);
		BulkNetwork& setSourceNode(BulkNode& node);
		BulkNetwork& setSinkNode(BulkNode& node);
		BulkNode* getSourceNodeById(int id) const;
		BulkNode* getSinkNodeById(int id) const;
		~BulkNetwork(){};
};
#endif
