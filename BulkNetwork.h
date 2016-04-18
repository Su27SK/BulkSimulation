#ifndef  _BULKNETWORK_H_ 
#define  _BULKNETWORK_H_
#define MAXNODE 300
#include "Graph.h"
#include "BulkNode.h"
#include "RandomGenerator.h"
#include "Timer.h"
#include <map>
class BulkLink;
class BulkSession;
using namespace std;
class BulkNetwork
{
	private:
		FILE* _sourceHandle;
	protected:
		int _nSource; //有几个Source流入点
		int _nSink;   //有几个Sink流出点
		map<int, BulkNode>* _lSourceList; //具体流入source数据包节点索引
		map<int, BulkNode>* _lSinkList;   //具体流出sink数据包节点索引
		BulkNode** nList_;
		Graph* _topology;
	public:
		static Timer timer;  
		BulkNetwork():_nSource(0), _nSink(0) {
			this->_lSourceList = new map<int, BulkNode>;
			this->_lSinkList = new map<int, BulkNode>;
			this->_topology = NULL;
			nList_ = NULL;
			_sourceHandle = NULL;
		}
		void init();
		void setGraph(Graph* graph);
		void startSession(BulkSession& session);
		void stopSession(BulkSession& session);
		void inputPackets(BulkSession& session);
		virtual float dynamicPush(BulkLink& link) = 0;
		BulkNetwork(Graph* graph);
		BulkNetwork& setSourceNode(int id);
		BulkNetwork& setSinkNode(int id);
		BulkNode* getNodeById(int id) const;
		BulkNode* getSourceNodeById(int id) const;
		BulkNode* getSinkNodeById(int id) const;
		~BulkNetwork(){};
};
#endif
