#include "BulkNode.h"

/**
 * @brief _defaultInit 
 * 缺省初始化函数
 */
void BulkNode::_defaultInit()
{
	store_ = 0;
	sessionNumPacket_ = new int[MAX_SIZE]; //max 100 number of session				
	nextRoute_ = new slist<BulkLink>(0);
	_isTerminal = false;
	_isOriginal = false;
	pqueue = new queue<BulkPackets>*[MAX_SIZE];
	int i;
	for (i = 0; i < MAX_SIZE; i++) {
		pqueue[i] = new queue<BulkPackets>;
	}
}

/**
 * @brief BulkNode 
 * construct function
 * @param {BulkGraphNode} node
 */
BulkNode::BulkNode(const BulkGraphNode& node):BulkGraphNode(node)
{
	this->_defaultInit();
}

/**
 * @brief BulkNode 
 * construct function
 * @param {BulkGraphNode} node
 */
BulkNode::BulkNode(BulkGraphNode& node):BulkGraphNode(node)
{
	this->_defaultInit();
}

/**
 * @brief getStoreSize 
 * 获得该节点总存储数据包的数量,所有session
 * @return {interge}
 */
int BulkNode::getStoreSize()
{
	int i;
	for (i = 0; i < 100; i++) {
		store_ += sessionNumPacket_[i];
	}
	return store_;
}

/**
 * @brief setOriginal 
 * 设置该节点为session起点
 * @return {BulkNode}
 */
BulkNode& BulkNode::setOriginal()
{
	this->_isOriginal = true;
	return *this;
}

/**
 * @brief setTerminal 
 * 设置该节点为session终节点
 * @return {BulkNode}
 */
BulkNode& BulkNode::setTerminal()
{
	this->_isTerminal = true;
	return *this;
}

/**
 * @brief getTerminal 
 * 获得flag, 判断是否是出口点
 * @return {boolean}
 */
bool BulkNode:: getTerminal()
{
	return this->_isTerminal;
}

/**
 * @brief getOriginal 
 * 获得flag, 判断是否是起始点
 * @return {boolean}
 */
bool BulkNode::getOriginal()
{
	return this->_isOriginal;
}

/**
 * @brief addNextLink 
 * 增加下一跳链路
 * @param {BulkGraphEdge*} edge
 */
void BulkNode::addNextLink(BulkGraphEdge* edge)
{
	BulkLink* link = new BulkLink(*edge);
	this->nextRoute_->push_front(*link);
}

/**
 * @brief addSessionNum 
 * 增加某sessionId下存储的数据包数量
 * @param {interge} sId
 * @param {interge} num
 *
 * @return {BulkNode}
 */
BulkNode& BulkNode::addSessionNum(int sId, int num)
{
	this->sessionNumPacket_[sId] += num;
	return *this;
}

/**
 * @brief reduceSessionNum 
 * 减少某sessionId下存储的数据包数量
 * @param {interge} sId
 * @param {interge} num
 *
 * @return {BulkNode}
 */
BulkNode& BulkNode::reduceSessionNum(int sId, int num)
{
	this->sessionNumPacket_[sId] -= num;
	return *this;
}

