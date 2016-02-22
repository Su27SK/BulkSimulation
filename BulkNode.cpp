#include "BulkNode.h"

/**
 * @brief _defaultInit 
 * 缺省初始化函数
 */
void BulkNode::_defaultInit()
{
	store_ = 0;
	sessionNumPacket_ = new int[MAX_SIZE]; //max 100 number of session				
	_isTerminal = false;
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
 * @brief setTerminal 
 * 设置该节点为终节点
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
 * @return 
 */
bool BulkNode:: getTerminal()
{
	return this->_isTerminal;
}

/**
 * @brief addSessionNum 
 * 增加某sessionId下存储的数据包数量
 * @param {interge} sessionId
 * @param {interge} num
 *
 * @return {BulkNode}
 */
BulkNode& BulkNode::addSessionNum(int sessionId, int num)
{
	this->sessionNumPacket_[sessionId] += num;
	return *this;
}

/**
 * @brief reduceSessionNum 
 * 减少某sessionId下存储的数据包数量
 * @param {interge} sessionId
 * @param {interge} num
 *
 * @return {BulkNode}
 */
BulkNode& BulkNode::reduceSessionNum(int sessionId, int num)
{
	this->sessionNumPacket_[sessionId] -= num;
	return *this;
}

