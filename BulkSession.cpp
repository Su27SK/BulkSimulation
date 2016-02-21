#include "BulkSession.h"

/**
 * @brief expire 
 * 
 * @param {Event} e
 */
void BulkSessionTimer::expire(Event* e)
{

}

/**
 * @brief handle 
 *
 * @param {Event} e
 */
void BulkSessionTimer::handle(Event* e)
{

}

/**
 * @brief send 
 * 该session每次从sourceNode向后推送npackets的数据
 * @param {interge} npackets
 */
void BulkSession::send(int npackets)
{
	if (this->_sinkNode == NULL || id_ == -1) {
		return;
	}
	int i;
	bool flag = this->_sinkNode->getTerminal();
	for (i = 0; i < npackets; i++) {
		BulkPackets* packets = this->_sourceNode->queue[id_]->front();
		this->_sourceNode->queue[id_]->pop();
		this->_sourceNode->reduce(id_);
		if (flag) {
			_bulkPool.placePacketsToPool(*packets);
		} else {
			this->_sinkNode->queue[id_]->push(*packets);
			this->_sinkNode->addSession(id_);
		}
		flow_ += packets->getBulkPacketsSize();
	}
}

/**
 * @brief recv 
 * 该session每次从sourceNode获得npackets的数据
 * @param {interge} npackets
 */
void BulkSession::recv(int npackets)
{
	if (this->_sourceNode == NULL || id_ == -1) {
		return;
	}
	int i;
	for (i = 0; i < npackets; i++) {
		BulkPackets* packets = _bulkPool.getPacketsFromPool();
		this->_sourceNode->queue[id_]->push(*packets);
		this->_sourceNode->addSession(id_);
	}
}

/**
 * @brief diffPackets 
 * 计算q_s(tail(e))(t) - q_s(head(e))(t)
 * @return {interge}
 */
int BulkSession::diffPackets()
{
	return this->_sinkNode->queue[id_]->size() - this->_sourceNode->queue[id_]->size();
}

/**
 * @brief isSessionEqualLink 
 * 检查link与session是否匹配
 * @param {interge} bId {起点node的id}
 * @param {interge} eId {终点node的id}
 * @param {interge} sId {session的id}
 *
 * @return {boolean}
 */
bool BulkSession::isSessionEqualLink(int bId, int eId, int sId)
{
	if (this->_sourceNode->getNodeId() != bId || 
		this->_sinkNode->getNodeId() != eId || id_ != sId) {
		return false;
	}
	return true;
}

/**
 * @brief start 
 * session启动
 */
void BulkSession::start()
{
	
}

/**
 * @brief stop 
 * session停止
 */
void BulkSession::stop()
{

}

