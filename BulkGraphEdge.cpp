#include "BulkGraphEdge.h"
BulkGraphEdge::BulkGraphEdge(int v1, int v2, double weight, double capacity)
{
	this->_v1 = v1;
	this->_v2 = v2;
	this->_weight = weight;
	this->_capacity = capacity;
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
	return (v1 == edge.v1) && (v2 == edge.v2);
}

/**
 * @brief setWeight 
 * 设置该边的权值
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
 * 获得权值
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
