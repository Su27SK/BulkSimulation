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
	session_ = new slist<BulkSession>;
	head_ = new queue<BulkPackets>*[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) {
		head_[i] = new queue<BulkPackets>;
	}
	tail_ = new queue<BulkPackets>*[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) {
		tail_[i] = new queue<BulkPackets>;
	}
}

/**
 * @brief pushHeadToTail 
 * 数据包从头部传输到尾部
 * @param {interge} numPackets
 * @param {interge} sId
 */
void BulkLink::pushHeadToTail(int numPackets, int sId)
{
	slist<BulkSession>::iterator iter;
	for (int i = 0; i < numPackets; i++) {
		BulkPackets& packets = tail_[sId]->front();
		tail_[sId]->pop();
		head_[sId]->push(packets);
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
 * @brief getHead 
 * get the head_ packets from the link
 * @param {interge} sId
 *
 * @return {queue<BulkPackets>*}
 */
queue<BulkPackets>* BulkLink::getHead(int sId)
{
	return &*head_[sId];
}

/**
 * @brief getTail 
 * get the tail_ packets from the link
 * @param {interge} sId
 *
 * @return {queue<BulkPackets>*}
 */
queue<BulkPackets>* BulkLink::getTail(int sId)
{
	return &*tail_[sId];
}

/**
 * @brief setHeadPackets 
 * set the link's head packets into the head_
 * @param {interge} sId
 * @param {interge} num
 * @param {BulkPackets} packets
 */
void BulkLink::setHeadPackets(int sId, int num, BulkPackets* packets)
{
	if (packets == NULL) {
		BulkGraphNode* pSource = new BulkGraphNode(getGraphEdgeSource());
		BulkGraphNode* pSink = new BulkGraphNode(getGraphEdgeSink());
		packets = new BulkPackets(0, pSource, pSink);
	} 
	if (num <= 0) {
		num = 1;
	}
	this->head_[sId]->push(*packets);
	for (int i = 1; i < num; i++) {
		BulkPackets* p = new BulkPackets(*packets);
		this->head_[sId]->push(*p);
	}
}

/**
 * @brief setTailPackets 
 * set the link's tail packets into the tail_
 * @param {interge} sId
 * @param {interge} num
 * @param {BulkPackets} packets
 */
void BulkLink::setTailPackets(int sId, int num, BulkPackets* packets)
{	
	if (packets == NULL) {
		BulkGraphNode* pSource = new BulkGraphNode(getGraphEdgeSource());
		BulkGraphNode* pSink = new BulkGraphNode(getGraphEdgeSink());
		packets = new BulkPackets(0, pSource, pSink);
	}
	if (num <= 0) {
		num = 1;
	}
	this->tail_[sId]->push(*packets);
	for (int i = 1; i < num; i++) {
		BulkPackets* p = new BulkPackets(*packets);
		this->tail_[sId]->push(*p);
	}
}

/**
 * @brief clearHeadPackets 
 * @param {interge} sId
 */
void BulkLink::clearHeadPackets(int sId)
{
	int i = 0, nSize = head_[sId]->size();
	while (i < nSize) {
		BulkPackets& pTemp = head_[sId]->front();
		head_[sId]->pop();
		pTemp.~BulkPackets();
		i++;
	}
}

/**
 * @brief clearTailPackets 
 * @param {interge} sId
 */
void BulkLink::clearTailPackets(int sId)
{
	int i = 0, nSize = tail_[sId]->size();
	while (i < nSize) {
		BulkPackets& pTemp = tail_[sId]->front();
		tail_[sId]->pop();
		pTemp.~BulkPackets();
		i++;
	}
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
