#include "BulkLink.h"
BulkLink::BulkLink(int from, int to, bool isTerminal):BulkGraphEdge(from, to)
{
	this->_isToTerminal = isTerminal;
	session_ = new slist<BulkSession>;
}

BulkLink::BulkLink(int from, int to, int weight, int capacity, bool isTerminal):BulkGraphEdge(from, to, weight, capacity)
{
	this->_isToTerminal = isTerminal;
	session_ = new slist<BulkSession>;
}

/**
 * @brief fromHeadToTail 
 * 数据包从头部传输到尾部
 * @param {interge} numPackets
 * @param {interge} sessionId
 */
void BulkLink::fromHeadToTail(int numPackets, int sessionId)
{
	slist<BulkSession>::iterator iter;
	for (iter = this->session_->begin(); iter != this->session_->end(); iter++) {
		if (iter->id_ == sessionId) {
			iter->send(numPackets);
		}
	}
	this->
}

/**
 * @brief addSession 
 * Link上增加一个session
 * @param {BulkSession} session
 */
void BulkLink::addSession(BulkSession& session)
{
	this->session_->push_front(session);
}

/**
 * @brief isUnderConstraints 
 * 是否满足小于Link中的capacity
 * @return {boolean}
 */
bool BulkLink::isUnderConstraints()
{
	slist<BulkSession>::iterator iter;
	for (iter = this->session_->begin(); iter != this->session_->end(); iter++) {
		
	}
}




