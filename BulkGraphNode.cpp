#include "BulkGraphNode.h"
BulkGraphNode::BulkGraphNode(int _id):id(_id), numHeadQueue(0), numTailQueue(0), isTerminal(false)
{
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
 * @brief operator++ 
 * 后缀++操作符(用于numTailQueue的计数++)
 * @return 
 */
BulkGraphNode& BulkGraphNode::operator++(int)
{
	this->numTailQueue++;
	return *this;
}

/**
 * @brief operator++ 
 * 前缀++操作符(用于numHeadQueue的计数++)
 * @return 
 */
BulkGraphNode& BulkGraphNode::operator++()
{
	++this->numHeadQueue;
	return *this;
}

/**
 * @brief operator-- 
 * 后缀++操作符(用于numTailQueue的计数--)
 * @return 
 */
BulkGraphNode& BulkGraphNode::operator--(int)
{
	this->numTailQueue--;
	return *this;
}

/**
 * @brief operator-- 
 * 前缀--操作符(用于numHeadQueue的计数--)
 * @return 
 */
BulkGraphNode& BulkGraphNode::operator--()
{
	--this->numHeadQueue;
	return *this;
}
