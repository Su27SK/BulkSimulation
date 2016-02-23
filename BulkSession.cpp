#include "BulkSession.h"
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
		BulkPackets& packets = this->_sourceNode->pqueue[id_]->front();
		this->_sourceNode->pqueue[id_]->pop();
		this->_sourceNode->reduceSessionNum(id_);
		if (flag) {
			_bulkPool->placePacketsToPool(&packets);
		} else {
			this->_sinkNode->pqueue[id_]->push(packets);
			this->_sinkNode->addSessionNum(id_);
		}
		flow_ += packets.getBulkPacketsSize();
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
		BulkPackets* packets = _bulkPool->getPacketsFromPool();
		this->_sourceNode->pqueue[id_]->push(*packets);
		this->_sourceNode->addSessionNum(id_);
	}
}

/**
 * @brief diffPackets 
 * 计算q_s(tail(e))(t) - q_s(head(e))(t)
 * @return {interge}
 */
int BulkSession::diffPackets()
{
	return this->_sinkNode->pqueue[id_]->size() - this->_sourceNode->pqueue[id_]->size();
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

