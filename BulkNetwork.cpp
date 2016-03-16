#include"BulkNetwork.h"
/**
 * @brief BulkNetwork 
 * construct function
 */
BulkNetwork::BulkNetwork(Graph* graph):_nSource(0), _nSink(0)
{
	this->_lSourceList = new map<int, BulkNode>;
	this->_lSinkList = new map<int, BulkNode>;
	if (graph != NULL) {
		this->_topology = graph;
		this->init();
	}
}

/**
 * @brief init 
 * 初始化函数
 * 将BulkGraphNode转化为BulkNode, nList中, key(nodeId) => value(BulkNode)
 */
void BulkNetwork::init()
{
	if (this->_topology != NULL) {
		int n = this->_topology->getVertices();
		BulkGraphNode* aList = this->_topology->getList();
		nList_ = new BulkNode*[n + 1];
		int *visited = new int[n + 1];
		queue<BulkGraphNode> q;
		for (int i = 1; i < n + 1; i++) {
			visited[i] = 0;
		}
		for (int i = 1; i < n + 1; i++) {
			int bNodeId = aList[i].getNodeId();
			if (!visited[i]) {
				nList_[bNodeId] = new BulkNode(aList[i]);
				visited[i] = 1;
			}
			slist<BulkGraphEdge>* outputEdge = aList[i].getTailEdge();
			slist<BulkGraphEdge>::iterator iter;
			for (iter = outputEdge->begin(); iter != outputEdge->end();iter++) {
				BulkLink* link = new BulkLink(*iter);
				int eNodeId = iter->getGraphEdgeSink();
				if (!visited[eNodeId]) {
					nList_[eNodeId] = new BulkNode(aList[eNodeId]);
					visited[eNodeId] = 1;
				}
				nList_[bNodeId]->addOutputLink(link);
				nList_[eNodeId]->addInputLink(link);
			}
		}
	}
}

/**
 * @brief setSourceNode 
 * 设置packets数据包从Id节点进入
 * @param {interge} id
 * 
 * @return {BulkNetwork}
 */
BulkNetwork& BulkNetwork::setSourceNode(int id)
{
	int n = this->_topology->getVertices();
	if (id > n || id < 0) {
		return *this;
	}
	if (this->_topology != NULL) {
		this->_lSourceList->insert(pair<int, BulkNode>(id, *nList_[id]));
		nList_[id]->setOriginal();
		this->_nSource++;
	}
	return *this;
}

/**
 * @brief setSinkNode 
 * 设置数据包packets从Id节点流出
 * @param {interge} id
 *
 * @return {BulkNetwork}
 */
BulkNetwork& BulkNetwork::setSinkNode(int id)
{
	int n = this->_topology->getVertices();
	if (id > n || id < 0) {
		return *this;
	}
	if (this->_topology != NULL) {
		//cout<<"insert the BulkNode"<<endl;
		this->_lSinkList->insert(pair<int, BulkNode>(id, *nList_[id]));
		nList_[id]->setTerminal();
		this->_nSink++;
	}
	return *this;
}

/**
 * @brief getSourceNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return {BulkNode}
 */
BulkNode* BulkNetwork::getSourceNodeById(int id) const
{
	if (!this->_lSourceList->empty()) {
		map<int, BulkNode>::iterator iter;
		iter = this->_lSourceList->find(id);
		if (iter != _lSourceList->end()) {
			return &iter->second;
		}
	}
	return NULL;
}

/**
 * @brief getSinkNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return {BulkNode}
 */
BulkNode* BulkNetwork::getSinkNodeById(int id) const
{
	if (!this->_lSinkList->empty()) {
		map<int, BulkNode>::iterator iter;
		iter = this->_lSinkList->find(id);
		if (iter != _lSinkList->end()) {
			return &iter->second;
		}
	}
	return NULL;
}

/**
 * @brief getNodeById 
 * 通过节点id获得相应节点
 * @param {interge} id
 *
 * @return {BulkNode}
 */
BulkNode* BulkNetwork::getNodeById(int id) const
{
	int n = this->_topology->getVertices();
	if (id > n || id < 0) {
		return NULL;
	}
	return nList_[id];
}

/**
 * @brief setGraph 
 * 设置Graph
 * @param {Graph} graph
 */
void BulkNetwork::setGraph(Graph* graph)
{
	if (graph != NULL) {
		this->_topology = graph;
	}
}

/**
 * @brief startSession 
 * 网络中开启一个session(增加一个新session)
 * @param {BulkSession} session
 */
void BulkNetwork::startSession(BulkSession& session)
{
	session.start();
	int sNode = session.sourceNode_->getNodeId();
	int eNode = session.sinkNode_->getNodeId();
	if (getSourceNodeById(sNode) == NULL) {
		this->setSourceNode(sNode);
	}
	if (getSinkNodeById(eNode) == NULL) {
		this->setSinkNode(eNode);
	}
}

/**
 * @brief stopSession 
 * 网络中关闭一个session(减少一个session)
 * @param {BulkSession} session
 */
void BulkNetwork::stopSession(BulkSession& session)
{
	session.stop();
	int sNode = session.sourceNode_->getNodeId();
	int eNode = session.sinkNode_->getNodeId();
	_lSourceList->erase(_lSourceList->find(sNode));
	_lSinkList->erase(_lSinkList->find(eNode));
}

/**
 * @brief inputPackets 
 * 向系统导入数据包
 * @param {BulkSession} session
 */
void BulkNetwork::inputPackets(BulkSession& session)
{
	int m = session.getDemand();
	if (m != 0) {
		int nPack = RandomGenerator::genPoissonInt(m);
		session.recv(nPack);
	}
}
