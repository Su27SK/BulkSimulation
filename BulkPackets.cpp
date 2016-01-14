#include "BulkPackets.h"
BulkPackets::BulkPackets(double number, BulkPacket* packet):_sourceNode(new GraphNode()), _sinkNode(new GraphNode())
{
	this->_transferPacketsNum = number;
	if (packet != NULL) {
		this->_model = packet;
	} else {
		this->_model = new packet();
	}
}

BulkPackets::BulkPackets(double number, GraphNode* source, GraphNode* sink, BulkPacket* packet)
{
	this->_sourceNode = source;
	this->_sinkNode = sink;
	this->_transferPacketsNum = number;
	if (packet != NULL) {
		this->_model = packet;
	} else {
		this->_model = new packet();
	}
}

/**
 * @brief setTransferPacketsNum 
 * 设置一次传输packet数量
 * @param {double} number
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::setTransferPacketsNum(double number)
{
	this->_transferPacketsNum = number;
	return *this;
}

/**
 * @brief setSourceNode 
 * 设置传输数据包的source节点
 * @param {GraphNode} source
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::setSourceNode(GraphNode* source)
{
	this->_sourceNode = source;
	return *this;
}

/**
 * @brief setSinkNode 
 * 设置传输数据包的sink节点
 * @param {GraphNode} sink
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::setSinkNode(GraphNode* sink)
{
	this->_sinkNode = sink;
	return *this;
}

/**
 * @brief getBulkPacketsSize 
 * 获得传输数据流的大小
 * @return {double}
 */
double BulkPackets::getBulkPacketsSize()
{
	return this->_model->getPacketSize() * this->_transferPacketsNum; 
}

/**
 * @brief getBulkPacketsInfo 
 * 获得传输数据流的具体信息，(as 2.5Gb, 3Mb)
 * @return {string}
 */
string getBulkPacketsInfo()
{
	double totalNum = this->getBulkPacketsSize();
	stringstream ss;
	string value;
	ss<<totalNum;
	value<<ss;
	ss.clear();
	return value + this->_model->getPacketUnit();
}

/**
 * @brief operator= 
 * 重载操作符
 * @param {BulkPackets} bulkPackets
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::operator=(const BulkPackets& bulkPackets)
{
	if (this != bulkPackets) {
		BulkPackets bulkPackTemp(bulkPackets);
			
	}
}

BulkPackets::~BulkPackets()
{
}
