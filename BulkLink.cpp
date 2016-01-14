#include "BulkLink.h"

BulkLink::BulkLink(int from, int to, bool isTerminal):
BulkGraphEdge(from, to),_numPacketsHead(0),_numPacketsTail(0)
{
	this->_isToTerminal = isTerminal;
	this->_headQueue = new queue<BulkPackets>(0);
	this->_tailQueue = new queue<BulkPackets>(0);
}

BulkLink::BulkLink(int from, int to, int weight, int capacity,bool isTerminal = false):BulkGraphEdge(from, to, weight, capacity), _numPacketsHead(0),_numPacketsTail(0)
{
	this->_isToTerminal = isTerminal;
	this->_headQueue = new queue<BulkPackets>(0);
	this->_tailQueue = new queue<BulkPackets>(0);
}

/**
 * @brief addNumPacketsHead 
 * Link中的q(head)增加数据包
 * @param {boolean} isAdd {true:增加 false:减少}
 * @param {interge} numPackets
 *
 * @return {boolean} 
 */
bool BulkLink::addNumPacketsHead(bool isAdd, int numPackets)
{
	if (this->_headQueue == NULL) {
		this->_headQueue = new queue<BulkPackets>(0);
	}
	if (isAdd) {
		this->
		this->_numPacketsHead = this->_numPacketsHead + numPackets;
	} else {
		this->_numPacketsHead = this->_numPacketsHead - numPackets;
	}
	return true;
}

/**
 * @brief addNumPacketsTail 
 * Link中的q(tail)增加/减少数据包
 * @param {boolean} isAdd {true：增加 false: 减少}
 * @param {interge} numPackets
 *
 * @return {boolean}
 */
bool BulkLink::addNumPacketsTail(bool isAdd, int numPackets)
{
	if (this->_tailQueue == NULL) {
		this->_tailQueue = new queue<BulkPackets>(0);
	}
	if (isAdd) {
		this->
		this->_numPacketsTail = this->_numPacketsTail + numPackets;
	} else {
		this->_numPacketsTail = this->_numPacketsTail - numPackets;
	}
	return true;
}
