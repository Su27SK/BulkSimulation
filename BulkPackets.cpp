#include "BulkPackets.h"
BulkPackets::BulkPackets(double number, BulkPacket* packet):_sourceId(-1), _sinkId(-1), _ptr(1), _startTime(-1)
{
	this->_transmitNum = number;
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
 * @param {interge} source
 * @param {interge} sink
 * @param {BulkPacket*} packet
 */
BulkPackets::BulkPackets(double number, int source, int sink, BulkPacket* packet)
{
	this->_sourceId = source;
	this->_sinkId = sink;
	this->_transmitNum = number;
	this->_ptr = 1;
	this->_startTime = -1;
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
	this->_transmitNum = P._transmitNum;
	this->_sourceId = P._sourceId;
	this->_sinkId = P._sinkId;
	this->_ptr = P._ptr;
	this->_startTime = P._startTime;
	this->_model = new BulkPacket(*P._model);
}

/**
 * @brief BulkPackets 
 * 深拷贝构造函数
 * @param {BulkPackets} P
 */
BulkPackets::BulkPackets(BulkPackets& P)
{
	this->_transmitNum = P._transmitNum;
	this->_sourceId = P._sourceId;
	this->_sinkId = P._sinkId;
	this->_ptr = P._ptr;
	this->_startTime = P._startTime;
	this->_model = new BulkPacket(*P._model);
}

/**
 * @brief setTransmitNum 
 * 设置一次传输packet数量
 * @param {double} number
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::setTransmitNum(double number)
{
	this->_transmitNum = number;
	return *this;
}

/**
 * @brief setSourceNode 
 * 设置传输数据包的source节点
 * @param {interge} source
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::setSourceNode(int source)
{
	this->_sourceId = source;
	return *this;
}

/**
 * @brief setSinkNode 
 * 设置传输数据包的sink节点
 * @param {interge} sink
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::setSinkNode(int sink)
{
	this->_sinkId = sink;
	return *this;
}

/**
 * @brief setStartTime 
 * 设置起始时间
 * @param {double} time
 *
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::setStartTime(double time)
{
	this->_startTime = time;
	return *this;
}

/**
 * @brief getBulkPacketsSize 
 * 获得传输数据流的大小
 * @return {double}
 */
double BulkPackets::getBulkPacketsSize()
{
	return this->_model->getPacketSize() * this->_transmitNum; 
}

/**
 * @brief getBulkPacketsSize 
 * 在当前type类型下获得数据
 * @param {unit} type
 *
 * @return {double}
 */
double BulkPackets::getBulkPacketsSize(unit type)
{
	this->_model->setPacketSize(type);
	return this->getBulkPacketsSize();
}

/**
 * @brief getTransmitNum 
 * 传输packet数量
 * @return {double}
 */
double BulkPackets::getTransmitNum()
{
	return this->_transmitNum;
}

/**
 * @brief getModel 
 * 获得BulkPacket的model
 * @return {BulkPacket}
 */
BulkPacket* BulkPackets::getModel() const
{
	return this->_model;
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
		this->_transmitNum = bulkPacketsTemp._transmitNum;
		this->_sourceId = bulkPacketsTemp._sourceId;
		this->_sinkId = bulkPacketsTemp._sinkId;
		this->_ptr = bulkPacketsTemp._ptr;
		this->_startTime = bulkPacketsTemp._startTime;

		BulkPacket* pModel = bulkPacketsTemp._model;
		bulkPacketsTemp._model = this->_model;
		this->_model = pModel;
	}
	return *this;
}

/**
 * @brief addPtr 
 * 增加引用计数
 * @return {BulkPackets}
 */
BulkPackets& BulkPackets::addPtr()
{
	this->_ptr++;
	return *this;
}

/**
 * @brief reducePtr 
 * 减少引用计数
 * @return 
 */
BulkPackets& BulkPackets::reducePtr()
{
	this->_ptr--;
	return *this;
}

/**
 * @brief getPtr 
 * 获得引用计数
 * @return 
 */
int BulkPackets::getPtr()
{
	return _ptr;
}

/**
 * @brief getSourceNodeId 
 *
 * @return {interge}
 */
int BulkPackets::getSourceNodeId() const
{
	return _sourceId;
}

/**
 * @brief getSinkNodeId 
 *
 * @return {interge}
 */
int BulkPackets::getSinkNodeId() const
{
	return _sinkId;
}

double BulkPackets::getStartTime() const
{
	return _startTime;
}

BulkPackets::~BulkPackets()
{
	delete _model;
	//cout<<"Decontructor BulkPackets"<<endl;
	this->_model = NULL;
}
