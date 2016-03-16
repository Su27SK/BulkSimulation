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
	flow_ = _demand = 0.0;
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
	flow_ = _demand = 0.0;
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
		cout<<"sinkId:"<<sinkNode_->getNodeId()<<endl;
		cout<<"push from to the sink"<<endl;
		link.pushHeadToTail(npackets, id_);
		*sourceNode_->demand_[id_] = *sinkNode_->demand_[id_] = _demand;  
		cout<<"after,sourceNodeStore:"<<sourceNode_->getStoreAmount(id_)<<endl;
		cout<<"after,sinkNodeStore:"<<sinkNode_->getStoreAmount(id_)<<endl;
		if (flag) {
			while(!link.head_[id_]->empty()) {
				BulkPackets& packets = link.head_[id_]->front();
				bulkPool.placePacketsToPool(&packets);
				link.head_[id_]->pop();
			}
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
	cout<<"npackets:"<<npackets<<endl;
	if (sourceNode_ == NULL || id_ == -1 || running_ == 0) {
		return;
	}
	queue<BulkPackets> q;
	bool flag = sourceNode_->getOriginal();
	if (flag) {
		_demand = npackets;
		for (int i = 0; i < npackets; i++) {
			BulkPackets* packets = bulkPool.getPacketsFromPool();
			//cout<<packets->getBulkPacketsInfo()<<endl;
			q.push(*packets);
		}
		*(sourceNode_->demand_[id_]) = _demand;  
		sourceNode_->initNodePackets(id_, &q);
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
	flow_ = 0.0;
}

