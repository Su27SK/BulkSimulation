#include "BulkSession.h"
/**
 * @brief send 
 * 该session每次从sourceNode向后推送npackets的数据
 * @param {interge} npackets
 */
void BulkSession::send(int npackets)
{
	if (this->sinkNode_ == NULL || id_ == -1 || running_ == 0) {
		return;
	}
	int i;
	bool flag = this->sinkNode_->getTerminal();
	for (i = 0; i < npackets; i++) {
		BulkPackets& packets = this->sourceNode_->pqueue[id_]->front();
		this->sourceNode_->pqueue[id_]->pop();
		this->sourceNode_->reduceSessionNum(id_);
		if (flag) {
			bulkPool_.placePacketsToPool(&packets);
		} else {
			this->sinkNode_->pqueue[id_]->push(packets);
			this->sinkNode_->addSessionNum(id_);
		}
		flow_ += packets.getBulkPacketsSize();
	}
}

/**
 * @brief recv 
 * 该session每次从originNode获得npackets的数据
 * @param {interge} npackets
 */
void BulkSession::recv(int npackets)
{
	if (this->sourceNode_ == NULL || id_ == -1 || running_ == 0) {
		return;
	}
	bool flag = this->sourceNode_->getOriginal();
	if (flag) {
		int i;
		for (i = 0; i < npackets; i++) {
			BulkPackets* packets = bulkPool_.getPacketsFromPool();
			this->sourceNode_->pqueue[id_]->push(*packets);
			this->sourceNode_->addSessionNum(id_);
		}
	}
}

/**
 * @brief diffPackets 
 * 计算q_s(tail(e))(t) - q_s(head(e))(t)
 * @return {interge}
 */
int BulkSession::diffPackets()
{
	return this->sinkNode_->pqueue[id_]->size() - this->sourceNode_->pqueue[id_]->size();
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
	if (this->sourceNode_->getNodeId() != bId || 
		this->sinkNode_->getNodeId() != eId || id_ != sId) {
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
	running_ = 1;
}

/**
 * @brief stop 
 * session停止
 */
void BulkSession::stop()
{
	running_ = 0;
	flow_ = 0.0;
}

