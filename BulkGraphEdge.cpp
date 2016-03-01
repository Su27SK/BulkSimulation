#include "BulkGraphEdge.h"
BulkGraphEdge::BulkGraphEdge(int v1, int v2, double weight, double capacity)
{
	this->_v1 = v1;
	this->_v2 = v2;
	this->_weight = weight;
	this->_capacity = capacity;
}

BulkGraphEdge::BulkGraphEdge(BulkGraphEdge& edge)
{
	_v1 = edge._v1;
	_v2 = edge._v2;
	_weight = edge._weight;
	_capacity = edge._weight;
}

BulkGraphEdge::BulkGraphEdge(const BulkGraphEdge& edge)
{
	_v1 = edge._v1;
	_v2 = edge._v2;
	_weight = edge._weight;
	_capacity = edge._weight;
}

/**
 * @brief operator == 
 * 是否为同一条边(有向边)
 * @param {BulkGraphEdge} edge
 * 
 * @return {boolean}
 */
bool BulkGraphEdge::operator == (const BulkGraphEdge& edge)
{
	return (this->_v1 == edge._v1) && (this->_v2 == edge._v2);
}

/**
 * @brief setWeight 
 * 设置该边的权值(数学期望)
 * @param {double} weight (权值)
 *
 * @return {BulkGraphEdge}
 */
BulkGraphEdge& BulkGraphEdge::setWeight(double weight)
{
	this->_weight = weight;
	return *this;
}

/**
 * @brief setCapacity 
 * 设置改变的带宽,当前传输能力
 * @param {double} capacity
 *
 * @return {BulkGraphEdge}
 */
BulkGraphEdge& BulkGraphEdge::setCapacity(double capacity)
{
	this->_capacity = capacity;
	return *this;
}

/**
 * @brief getWeight 
 * 获得权值(数学期望)
 * @return {double}
 */
double BulkGraphEdge::getWeight() const
{
	return this->_weight;
}

/**
 * @brief getCapacity 
 * 获得当前带宽
 * @return {double}
 */
double BulkGraphEdge::getCapacity() const
{
	return this->_capacity;
}

/**
 * @brief getGraphEdgeSource 
 *
 * @return {interge}
 */
int BulkGraphEdge::getGraphEdgeSource() const
{
	return _v1;
}

/**
 * @brief getGraphEdgeSink 
 *
 * @return {interge}
 */
int BulkGraphEdge::getGraphEdgeSink() const
{
	return this->_v2;
}
