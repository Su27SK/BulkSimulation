#ifndef  _BULKNETWORK_H_ 
#define  _BULKNETWORK_H_
#include"Graph.h"
#include <map>
using namespace std;
class BulkNetwork
{
	private:
		int _nSource; //有几个Source流入点
		int _nSink;   //有几个Sink流出点
		map<int, BulkGraphNode>* _lSourceList; //具体流入source数据包节点索引
		map<int, BulkGraphNode>* _lSinkList;   //具体流出sink数据包节点索引
		Graph* _topology;
	public:
		BulkNetwork():_nSource(0), _nSink(0) {
			this->_lSourceList = new map<int, BulkGraphNode>;
			this->_lSinkList = new map<int, BulkGraphNode>;
			this->_topology = NULL;
		}
		BulkNetwork(Graph& graph);
		BulkNetwork& setSourceNodeById(int id);
		BulkNetwork& setSinkNodeById(int id);
		BulkGraphNode* getSourceNodeById(int id) const;
		BulkGraphNode* getSinkNodeById(int id) const;
		~BulkNetwork(){};
};
#endif
