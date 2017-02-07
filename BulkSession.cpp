#include "BulkSession.h"
BulkPackets BulkSession::initPackets;
BulkPool BulkSession::bulkPool(&initPackets);
/**
 * @brief BulkSession 
 * constructor function
 */
BulkSession::BulkSession():sourceNode_(NULL), sinkNode_(NULL) {
	id_ = -1;
	running_ = 0;
	flow_ = _demand = time_ = 0.0;
}

/**
 * @brief BulkSession 
 * constructor function
 */
BulkSession::BulkSession(int id, BulkNode* source, BulkNode* sink) {
	sourceNode_ = source;
	sinkNode_ = sink;
	id_ = id;
	running_ = 0;
	flow_ = _demand = time_ = 0.0;
}

/**
 * @brief send 
 * 该session每次从sourceNode向后推送npackets的数据
 * @param {interge} npackets
 * @param {BulkLink} link 
 */
void BulkSession::send(int npackets, BulkLink& link)
{
	if (sinkNode_ == NULL || id_ == -1 || running_ == 0 || npackets <= 0) {
		return;
	}
	bool flag = sinkNode_->getTerminal();
	if (link.getGraphEdgeSink() == sinkNode_->getNodeId()) {
		link.pushHeadToTail(npackets, id_);
		*sourceNode_->demand_[id_] = *sinkNode_->demand_[id_] = _demand;  
		if (flag) {
			FILE* fp = fopen("Bulk_Log/SinkInfo.txt", "a+"); 
			int id = sinkNode_->getNodeId(); 
			int outSize, size = link.head_[id_]->size();
			for (outSize = 0; outSize < size; outSize++) {
				BulkPackets& packets = link.head_[id_]->front();
				double startTime = packets.getStartTime();
				if (packets.getSinkNodeId() == id) {
					FILE* flowFp = fopen("Bulk_Log/PacketsInfo.txt", "a+"); 
					bulkPool.placePacketsToPool(&packets);
					link.head_[id_]->pop();
					double intervalTime = time_ + 1 - startTime;
					fprintf(flowFp, "IntervalTime:%f, sinkNodeId:%d, sId:%d, startTime:%f, arriveTime:%f\n", intervalTime, id, id_, startTime, time_ + 1);
					fclose(flowFp);
				} else if(!link.head_[id]->empty()) {
					link.head_[id_]->pop();
					link.head_[id_]->push(packets);
				}
			}
			fprintf(fp, "time:%f, sinkNodeId:%d, sId:%d, number:%d\n",time_ + 1, id, id_, outSize);
			fclose(fp);
		}
	}
}

/**
 * @brief recv 
 * 该session每次从originNode获得npackets的数据
 * @param {interge} npackets
 * @param {double} time
 * @param {FILE} fp 
 */
void BulkSession::recv(int npackets, double time, FILE* fp)
{
	if (sourceNode_ == NULL || id_ == -1 || running_ == 0) {
		return;
	}
	queue<BulkPackets> q;
	bool flag = sourceNode_->getOriginal();
	if (flag) {
		int iSource = sourceNode_->getNodeId();
		int iSink = sinkNode_->getNodeId();
		for (int i = 0; i < npackets; i++) {
			BulkPackets* packets = bulkPool.getPacketsFromPool();
			packets->setStartTime(time);
			packets->setSourceNode(iSource);
			packets->setSinkNode(iSink);
			q.push(*packets);
		}
		*(sourceNode_->demand_[id_]) = _demand;  
		sourceNode_->initNodePackets(id_, &q);
		int id = sourceNode_->getNodeId(); 
		fprintf(fp, "time:%f, sourceNodeId:%d, sId:%d, number:%d\n",time, id, id_, npackets);
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
	if (sourceNode_->getNodeId() != bId || 
		sinkNode_->getNodeId() != eId || id_ != sId) {
		return false;
	}
	return true;
}

/**
 * @brief setDemand 
 * 设置平均流入系统的数据包值
 * @param {double} demand
 */
BulkSession& BulkSession::setDemand(double demand)
{
	_demand = demand;
	return *this;
}

/**
 * @brief getDemand 
 * 获得demand值
 * @return {double}
 */
double BulkSession::getDemand()
{
	return _demand;
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
	flow_ = time_ = 0.0;
}

