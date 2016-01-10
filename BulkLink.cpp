#include "BulkLink.h"

/**
 * @brief addNumPacketsHead 
 * Link中的q(head)增加数据包
 * @param {boolean} isAdd {true:增加 false:减少}
 * @param {interge} numPackets
 *
 * @return {boolean} 
 */
bool BulkLink::addNumPacketsHead(bool isAdd, int numPackets = 1)
{
	if (this->_headQueue == NULL) {
		this->_headQueue = new queue<BulkPackets>;
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
bool BulkLink::addNumPacketsTail(bool isAdd, int numPackets = 1)
{
	if (this->_tailQueue == NULL) {
		this->_tailQueue = new queue<BulkPackets>;
	}
	if (isAdd) {
		this->
		this->_numPacketsTail = this->_numPacketsTail + numPackets;
	} else {
		this->_numPacketsTail = this->_numPacketsTail - numPackets;
	}
	return true;
}
