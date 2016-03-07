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
	slist<BulkLink>* pLink = this->sourceNode_->getOutputLink();
	slist<BulkLink>::iterator iter;
	bool flag = this->sinkNode_->getTerminal();
	for (iter = pLink->begin(); iter != pLink->end(); iter++) {
		if (iter->getGraphEdgeSink() == this->sinkNode_->getNodeId()) {
			iter->pushHeadToTail(npackets, id_);
			if (flag) {
				while(!iter->head_[id_]->empty()) {
					BulkPackets& packets = iter->head_[id_]->front();
					bulkPool_.placePacketsToPool(&packets);
					iter->head_[id_]->pop();
				}
			}
			break;
		}
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
		for (int i = 0; i < npackets; i++) {
			BulkPackets* packets = bulkPool_.getPacketsFromPool();
		}
		sourceNode_->realloc(id_);
	}
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

