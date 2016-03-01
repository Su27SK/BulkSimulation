#include "BulkPackets.h"
BulkPackets::BulkPackets(double number, BulkPacket* packet):_sourceNode(new BulkGraphNode()), _sinkNode(new BulkGraphNode())
{
	this->_transferPacketsNum = number;
	if (packet != NULL) {
		this->_model = new BulkPacket(*packet);
	} else {
		this->_model = new BulkPacket();
	}
}

/**
 * @brief BulkPackets 
 *
 * @param {double} number
 * @param {BulkGraphNode*} source
 * @param {BulkGraphNode*} sink
 * @param {BulkPacket*} packet
 */
BulkPackets::BulkPackets(double number, BulkGraphNode* source, BulkGraphNode* sink, BulkPacket* packet)
{
	this->_sourceNode = source;
	this->_sinkNode = sink;
	this->_transferPacketsNum = number;
	if (packet != NULL) {
		this->_model = new BulkPacket(*packet);
	} else {
		this->_model = new BulkPacket();
	}
}

/**
 * @brief BulkPackets 
 * 显式深拷贝构造函数
 * @param {BulkPackets} P
 */
BulkPackets::BulkPackets(const BulkPackets& P)
{
	this->_transferPacketsNum = P._transferPacketsNum;
	this->_sourceNode = new BulkGraphNode(*P._sourceNode);
	this->_sinkNode = new BulkGraphNode(*P._sinkNode);
	this->_model = new BulkPacket(*P._model);
}

/**
 * @brief BulkPackets 
 * 深拷贝构造函数
 * @param {BulkPackets} P
 */
BulkPackets::BulkPackets(BulkPackets& P)
{
	this->_transferPacketsNum = P._transferPacketsNum;
	this->_sourceNode = new BulkGraphNode(*P._sourceNode);
	this->_sinkNode = new BulkGraphNode(*P._sinkNode);
	this->_model = new BulkPacket(*P._model);
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
BulkPackets& BulkPackets::setSourceNode(BulkGraphNode* source)
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
BulkPackets& BulkPackets::setSinkNode(BulkGraphNode* sink)
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
 * @brief getTransferPacketsNum 
 * 传输packet数量
 * @return {double}
 */
double BulkPackets::getTransferPacketsNum()
{
	return this->_transferPacketsNum;
}

/**
 * @brief getBulkPacketsInfo 
 * 获得传输数据流的具体信息，(as 2.5Gb, 3Mb)
 * @return {string}
 */
string BulkPackets::getBulkPacketsInfo()
{
	double totalNum = this->getBulkPacketsSize();
	stringstream ss;
	string value;
	ss<<totalNum;
	ss>>value;
	ss.clear();
	return value + this->_model->getPacketUnit();
}

/**
 * @brief operator= 
 * 重载操作符,赋值操作
 * @param {BulkPackets} bulkPackets
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::operator = (const BulkPackets& bulkPackets)
{
	if (this != &bulkPackets) {
		BulkPackets bulkPacketsTemp(bulkPackets);
		this->_transferPacketsNum = bulkPacketsTemp._transferPacketsNum;
			
		BulkGraphNode* pHeadTemp = bulkPacketsTemp._sourceNode;
		bulkPacketsTemp._sourceNode = this->_sourceNode;
		this->_sourceNode = pHeadTemp;

		BulkGraphNode* pTailTemp = bulkPacketsTemp._sinkNode;
		bulkPacketsTemp._sinkNode = this->_sinkNode;
		this->_sinkNode = pTailTemp;

		BulkPacket* pModel = bulkPacketsTemp._model;
		bulkPacketsTemp._model = this->_model;
		this->_model = pModel;
	}
	return *this;
}

BulkPackets::~BulkPackets()
{
	delete _sourceNode;
	delete _sinkNode;
	delete _model;
	//cout<<"Decontructor BulkPackets"<<endl;
	this->_sourceNode = NULL;
	this->_sinkNode = NULL;
	this->_model = NULL;
}
