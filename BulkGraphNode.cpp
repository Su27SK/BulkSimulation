#include "BulkGraphNode.h"
BulkGraphNode::BulkGraphNode(int _id):id(_id), numHeadQueue(0), numTailQueue(0)
{
	if (this->id < 1) {
		this->id = -1;
	}
	this->headEdge = new slist<BulkGraphEdge>(0);
	this->tailEdge = new slist<BulkGraphEdge>(0);
}

/**
 * @brief BulkGraphNode 
 * 显式深拷贝构造函数
 * @param {BulkGraphNode} Node
 */
BulkGraphNode::BulkGraphNode(const BulkGraphNode& Node)
{
	this->id = Node.id;
	this->numHeadQueue = Node.numHeadQueue;
	this->numTailQueue = Node.numTailQueue;
	slist<BulkGraphEdge>::iterator iterS;
	slist<BulkGraphEdge>::iterator iterE;
	iterS = Node.headEdge->begin();
	iterE = Node.headEdge->end();
	this->headEdge = new slist<BulkGraphEdge>(iterS, iterE);
	iterS = Node.tailEdge->begin();
	iterE = Node.tailEdge->end();
	this->tailEdge = new slist<BulkGraphEdge>(iterS, iterE);
}

/**
 * @brief BulkGraphNode 
 * 深拷贝构造函数
 * @param {BulkGraphNode} Node
 */
BulkGraphNode::BulkGraphNode(BulkGraphNode& Node)
{
	this->id = Node.id;
	this->numHeadQueue = Node.numHeadQueue;
	this->numTailQueue = Node.numTailQueue;
	slist<BulkGraphEdge>::iterator iterS;
	slist<BulkGraphEdge>::iterator iterE;
	iterS = Node.headEdge->begin();
	iterE = Node.headEdge->end();
	this->headEdge = new slist<BulkGraphEdge>(iterS, iterE);
	iterS = Node.tailEdge->begin();
	iterE = Node.tailEdge->end();
	this->tailEdge = new slist<BulkGraphEdge>(iterS, iterE);
}

bool BulkGraphNode::operator == (const BulkGraphNode& node)
{
	return id == node.id;
}


/**
 * @brief getNumHeadQueue 
 * 获得该节点中的head queues的数量
 * @return {integer}
 */
int BulkGraphNode::getNumHeadQueue() const
{
	return this->numHeadQueue;
}

/**
 * @brief getNumTailQueue 
 * 获得该节点中的tail queues的数量
 * @return {integer}
 */
int BulkGraphNode::getNumTailQueue() const
{
	return this->numTailQueue;
}

/**
 * @brief getNodeId 
 * 获得node的id号
 * @return {interger}
 */
int BulkGraphNode::getNodeId() const
{
	return this->id;
}

/**
 * @brief getHeadEdge 
 *
 * @return slist<BulkGraphEdge>*
 */
slist<BulkGraphEdge>* BulkGraphNode::getHeadEdge() const
{
	return this->headEdge;
}

/**
 * @brief getTailEdge 
 *
 * @return slist<BulkGraphEdge>*
 */
slist<BulkGraphEdge>* BulkGraphNode::getTailEdge() const
{
	return this->tailEdge;
}

/**
 * @brief addBulkEdge 
 * 节点中增加与节点相连的边
 * @param {BulkGraphEdge} edge
 *
 * @return {boolean}
 */
bool BulkGraphNode::addBulkEdge(BulkGraphEdge* edge)
{
	if (this->id == edge->getGraphEdgeSource()) {
		this->tailEdge->push_front(*edge);
		this->numHeadQueue++;
		return true;
	} else if (this->id == edge->getGraphEdgeSink()) {
		this->headEdge->push_front(*edge);
		this->numTailQueue++;
		return true;
	} else {
		return false;
	}
}

/**
 * @brief removeBulkEdge 
 * 节点中删除与节点相连的边
 * @param {BulkGraphEdge} edge
 *
 * @return {boolean}
 */
bool BulkGraphNode::removeBulkEdge(BulkGraphEdge* edge)
{
	slist<BulkGraphEdge>::iterator iter;
	slist<BulkGraphEdge>::iterator iterEnd;
	if (this->id == edge->getGraphEdgeSource()) {
		iter = this->headEdge->begin();
		iterEnd = this->headEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				this->headEdge->erase(iter);
				return true;
			}
		}
	} else if (this->id == edge->getGraphEdgeSink()) {
		iter = this->tailEdge->begin();
		iterEnd = this->tailEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				this->headEdge->erase(iter);
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief operator= 
 * 重载操作符
 * @param {BulkGraphNode} node
 *
 * @return {BulkGraphNode}
 */
BulkGraphNode& BulkGraphNode::operator=(const BulkGraphNode &node)
{
	if (this != &node) {
		BulkGraphNode nodeTemp(node);
		this->id = nodeTemp.id;
		this->numHeadQueue = nodeTemp.numHeadQueue;
		this->numTailQueue = nodeTemp.numTailQueue;
		slist<BulkGraphEdge>* pHTemp = nodeTemp.headEdge;
		nodeTemp.headEdge = this->headEdge;
		this->headEdge = pHTemp;

		slist<BulkGraphEdge>* pTTemp = nodeTemp.tailEdge;
		nodeTemp.tailEdge = this->tailEdge;
		this->tailEdge = pTTemp;
	}
	return *this;
}

/**
 * @brief getBulkEdge 
 * 通过edge 返回向量边,包含具体信息，比如weight, capacity信息
 * (*iter == *edge) 主要比较(from, to)的数值
 * @param {BulkGraphEdge} edge
 *
 * @return {BulkGraphEdge}
 */
BulkGraphEdge* BulkGraphNode::getBulkEdge(BulkGraphEdge* edge) const
{
	slist<BulkGraphEdge>::iterator iter;
	slist<BulkGraphEdge>::iterator iterEnd;
	if (this->id == edge->getGraphEdgeSource()) {
		iter = this->headEdge->begin();
		iterEnd = this->headEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				return &(*iter);
			}
		}
	} else if (this->id == edge->getGraphEdgeSink()) {
		iter = this->tailEdge->begin();
		iterEnd = this->tailEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				return &(*iter);
			}
		}
	} 
	if (iter == iterEnd) {
		return NULL; 
	}
	return NULL;
}

int BulkGraphNode::Print()
{
	slist<BulkGraphEdge>::iterator iter;
	iter = this->headEdge->begin();
	return iter->getGraphEdgeSource();
}

/**
 * @brief setId 
 * 设置节点ID号
 * @param {interge} id
 *
 * @return {BulkGraphNode}
 */
BulkGraphNode& BulkGraphNode::setId(int id)
{
	this->id = id;
	return *this;
}

