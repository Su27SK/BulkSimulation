#include"BulkNetwork.h"
BulkNetwork::BulkNetwork(Graph& graph):_nSource(0), _nSink(0)
{
	this->_lSourceList = new map<int, BulkGraphNode>;
	this->_lSinkList = new map<int, BulkGraphNode>;
	this->_topology = graph;
}

/**
 * @brief setSourceNodeById 
 * 设置packets数据包从Id节点进入
 * @param {integer} id
 * 
 * @return {BulkNetwork}
 */
BulkNetwork& BulkNetwork::setSourceNodeById(int id)
{
	int i;
	if (this->_topology != NULL) {
		BulkGraphNode* aList = this->_topology->getList();
		for (i = 1; i < this->_topology->getVertices(); i++) {
			int nodeId = aList[i].getNodeId();
			if (nodeId == id) {
				this->_lSourceList->insert(pair<int, BulkGraphNode>(id, aList[i]));
				this->_nSource++;
			}
		}
	}
	return *this;
}

/**
 * @brief setSinkNodeById 
 * 设置数据包packets从Id节点流出
 * @param {interge} id
 *
 * @return {BulkNetwork}
 */
BulkNetwork& BulkNetwork::setSinkNodeById(int id)
{
	int i;
	if (this->_topology != NULL) {
		for (i = 1; i < this->_topology->getVertices(); i++) {
			int nodeId = aList[i].getNodeId();
			if (nodeId == id) {
				this->_lSinkList->insert(pair<int, BulkGraphNode>(id, aList[i])); 
				aList[i].setTerminal(true);
				this->_nSink++;
			}
		}
	}
	return *this;
}

/**
 * @brief getSourceNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return {BulkGraphNode*}
 */
BulkGraphNode* BulkNetwork::getSourceNodeById(int id) const
{
	if (!this->_lSourceList->empty()) {
		return this->_lSourceList[id];
	}
}

/**
 * @brief getSinkNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return {BulkGraphNode*}
 */
BulkGraphNode* BulkNetwork::getSinkNodeById(int id) const
{
	if (!this->_lSinkList->empty()) {
		return this->_lSinkList[i];
	}
}
