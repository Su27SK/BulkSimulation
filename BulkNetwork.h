#ifdef  BULKNETWORK_H_ 
#define BULKNETWORK_H_
#include"Graph.h"
#include<ext/slist>
class BulkNetwork
{
	private:
		int _nSource; //有几个Source流入点
		int _nSink;   //有几个Sink流出点
		slist<GNraphNode>* _lSourceList;
		slist<GraphNode>* _lSinkList;
		Graph* _topology;
	public:
		BulkNetwork():_nSource(0), _nSink(0){}
		BulkNetwork(int nSour, int nSink, Graph& graph = NULL):_nSource(0), _nSink(0)
		{
			this->_nSource = nSour;
			this->_nSink = nSink;
			this->_lSourceList = new slist<GraphNode>[this->_nSource];
			this->_lSinkList = new slist<GraphNode>[this->_nSink];
			if (graph != NULL) {
				int nodeNum = this->_nSource + this->_nSink;
				this->_topology = new Graph(nodeNum);
			} else {
				this->_topology = graph;
			}
		}
		BulkNetwork& setSourceNodeById(int id);
		BulkNetwork& setSinkNodeById(int id);
		slist<GraphNode>* getSourceNodeById(int id) const;
		slist<GraphNode>* getSinkNodeById(int id) const;
		virtual ~BulkNetwork();
};
#endif
