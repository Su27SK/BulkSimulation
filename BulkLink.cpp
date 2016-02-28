#include "BulkLink.h"
BulkLink::BulkLink(int from, int to):BulkGraphEdge(from, to)
{
	this->_defaultInit();
}

BulkLink::BulkLink(int from, int to, int weight, int capacity):BulkGraphEdge(from, to, weight, capacity)
{
	this->_defaultInit();
}

/**
 * @brief BulkLink 
 * 构造函数
 * @param {BulkGraphEdge} edge
 */
BulkLink::BulkLink(BulkGraphEdge& edge):BulkGraphEdge(edge)
{
	this->_defaultInit();
}

/**
 * @brief _defaultInit 
 */
void BulkLink::_defaultInit()
{
	int i;
	session_ = new slist<BulkSession>;
	head = new queue<BulkPackets>*[MAX_SIZE];
	for (i = 0; i < MAX_SIZE; i++) {
		head[i] = new queue<BulkPackets>;
	}
	tail = new queue<BulkPackets>*[MAX_SIZE];
	for (i = 0; i < MAX_SIZE; i++) {
		tail[i] = new queue<BulkPackets>;
	}
}

/**
 * @brief fromHeadToTail 
 * 数据包从头部传输到尾部
 * @param {interge} numPackets
 * @param {interge} sId
 */
void BulkLink::fromHeadToTail(int numPackets, int sId)
{
	slist<BulkSession>::iterator iter;
	int i;
	for (i = 0; i < numPackets; i++) {
		tail[sId]->pop();
		BulkPackets& packets = tail[sId]->front();
		head[sId]->push(packets);
	}
	for (iter = this->session_->begin(); iter != this->session_->end(); iter++) {
		if (iter->id_ == sId) {
			iter->send(numPackets);
			break;
		}
	}
}

/**
 * @brief addSession 
 * Link上增加一个session
 * @param {BulkSession} session
 *
 * @return {boolean}
 */
bool BulkLink::addSession(BulkSession& session)
{
	int source = this->getGraphEdgeSource();
	int sink = this->getGraphEdgeSink();
	int sId = session.id_;
	if (session.isSessionEqualLink(source, sink, sId)) {
		this->session_->push_front(session);
		return true;
	}
	return false;
}

/**
 * @brief deleteSession 
 * Link上删除一个session
 * @param {interge} sId {session id}
 *
 * @return {boolean}
 */
bool BulkLink::deleteSession(int sId)
{
	bool isFound = false;
	slist<BulkSession>::iterator iter;
	for (iter = this->session_->begin(); iter != this->session_->end(); iter++) {
		if (iter->id_ == sId) {
			this->session_->erase(iter);
			isFound = true;
			break;
		}
	}
	return isFound;
}

/**
 * @brief findSession 
 * Link中寻找session（通过sId）
 * @param {interge} sId
 *
 * @return {BulkSession}
 */
BulkSession* BulkLink::findSession(int sId)
{
	slist<BulkSession>::iterator iter;
	for (iter = session_->begin(); iter != session_->end(); iter++) {
		if (iter->id_ == sId) {
			return &*iter;
		}
	}
	return NULL;
}

/**
 * @brief isUnderConstraints 
 * 是否满足小于Link中的capacity
 * @return {boolean}
 */
//bool BulkLink::isUnderConstraints()
//{
	//slist<BulkSession>::iterator iter;
	//for (iter = this->session_->begin(); iter != this->session_->end(); iter++) {
		
	//}
//}
