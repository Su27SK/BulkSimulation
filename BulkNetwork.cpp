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
		int i;
		for (i = 0; i < n; i++) {
			int nodeId = aList[i].getNodeId();
			nList_[nodeId] = new BulkNode(aList[i]);
			slist<BulkGraphEdge>* sEdge = aList[i].getHeadEdge();
			slist<BulkGraphEdge>::iterator iter;
			for (iter = sEdge->begin(); iter != sEdge->end();iter++) {
					nList_[nodeId]->addNextLink(&*iter);
			}
		}
	}
}

/**
 * @brief setSourceNode 
 * 设置packets数据包从Id节点进入
 * @param {BulkNode} node
 * 
 * @return {BulkNetwork}
 */
BulkNetwork& BulkNetwork::setSourceNode(BulkNode& node)
{
	int id = node.getNodeId();
	if (this->_topology != NULL) {
		this->_lSourceList->insert(pair<int, BulkNode>(id, node));
		node.setOriginal();
		this->_nSource++;
	}
	return *this;
}

/**
 * @brief setSinkNode 
 * 设置数据包packets从Id节点流出
 * @param {BulkNode} node
 *
 * @return {BulkNetwork}
 */
BulkNetwork& BulkNetwork::setSinkNode(BulkNode& node)
{
	int id =node.getNodeId();
	if (this->_topology != NULL) {
		this->_lSinkList->insert(pair<int, BulkNode>(id, node));
		node.setTerminal();
		this->_nSink++;
	}
	return *this;
}

/**
 * @brief getSourceNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return {BulkNode&}
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
 * @return {BulkNode&}
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
 * 开始一个session(增加一个新session)
 * @param {BulkSession} session
 */
void BulkNetwork::startSession(BulkSession& session)
{
	int sNode = session.sourceNode_->getNodeId();
	int eNode = session.sinkNode_->getNodeId();
	if (getSourceNodeById(sNode) == NULL) {
		this->setSourceNode(*session.sourceNode_);
	}
	if (getSinkNodeById(eNode) == NULL) {
		this->setSinkNode(*session.sinkNode_);
	}
}

/**
 * @brief inputPackets 
 * 向系统导入数据包
 * @param {double} m
 * @param {BulkSession} session
 */
void BulkNetwork::inputPackets(double m, BulkSession& session)
{
	int nPack = RandomGenerator::genPoissonInt(m);
	session.recv(nPack);
}

