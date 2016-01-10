#include"BulkNetwork.h"

/**
 * @brief setSourceNodeById 
 * 设置packets数据包从Id节点进入
 * @param {integer} id
 * 
 * @return BulkNetwork 
 */
BulkNetwork& BulkNetwork::setSourceNodeById(int id)
{
	slist<GraphNode>* aList = this->_topology->aList;
	int length = strlen(aList);
	int sourceLength = strlen(this->_lSourceList);
	int i = 0;
	bool isIncreased = false;
	if (sourceLength >= this->_nSource) {
		slist<GraphNode>* temp = new slist<GraphNode>[this->_nSource * 1.5];
		for (i = 0; i < sourceLength; i++) {
			temp[i] = this->_lSourceList[i];
			delete[] this->_lSourceList;
			this->_lSourceList = temp;
		}
		isIncreased = true;
	}
	if (id < 0 || id >= length) {
		printf("The node Id %d is not existed", id);
	} else {
		this->_lSourceList[sourceLength] = aList[id];
		isIncreased && this->_nSource++;
	}
	return *this;
}

/**
 * @brief setSinkNodeById 
 * 设置数据包packets从Id节点流出
 * @param id
 *
 * @return BulkNetwork
 */
BulkNetwork& BulkNetwork::setSinkNodeById(int id)
{
	slist<GraphNode>* aList = this->_topology->aList;
	int length = strlen(aList);
	int sinkLength = strlen(this->_lSinkList);
	int i = 0;
	bool isIncreased = false;
	if (sinkLength >= this->_nSink) {
		slist<GraphNode>* temp = new slist<GraphNode>[this->_nSink * 1.5];
		for (i = 0; i < sinkLength; i++) {
			temp[i] = this->_lSinkList[i];
			delete[] this->_lSinkList;
			this->_lSourceList = temp;
		}
		isIncreased = true;
	}
	if (id < 0 || id >= length) {
		printf("The node Id %d is not existed", id);
	} else {
		this->_lSinkList = aList[id];
		isIncreased && this->_nSink++;
	}
	return *this;
}

/**
 * @brief getSourceNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return slist<GraphNode>*
 */
slist<GraphNode>* BulkNetwork::getSourceNodeById(int id) const
{
	int length = strlen(this->_lSourceList);
	if (id < 0 || id >= length) {
		printf("The source node Id %d is not existed", id);
		return NULL;
	} else {
		return this->_lSourceList[id];
	}
}

/**
 * @brief getSinkNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return slist<GraphNode>*
 */
slist<GraphNode>* BulkNetwork::getSinkNodeById(int id) const
{
	int length = strlen(this->_lSinkList);
	if (id < 0 || id >= length) {
		printf("The sink node Id %d is not existed", id);
		return NULL;
	} else {
		return this->_lSinkList[id];
	}
}
