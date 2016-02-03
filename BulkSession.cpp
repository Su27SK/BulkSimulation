#include "BulkSession.h"
/**
 * @brief send 
 * 该session每次从sinkNode向后推送npackets的数据
 * @param {interge} npackets
 */
void BulkSession::send(int npackets)
{
	if (this->_sinkNode == NULL) {
		return;
	}
	int i;
	for (i = 0; i < npackets; i++) {
		BulkPackets* packets = this->_tailQueue->front();
		this->_tailQueue->pop();
		bulkpool_.placePacketsToPool(*packets);
	}
}

/**
 * @brief recv 
 * 该session每次从sourceNode获得npackets的数据
 * @param {interge} npackets
 */
void BulkSession::recv(int npackets)
{
	if (this->_sourceNode == NULL) {
		return;
	}
	int i;
	for (i = 0; i < npackets; i++) {
		BulkPackets* packets = bulkpool_.getPacketsFromPool();
		this->_headQueue->push(*packets);
	}
}

/**
 * @brief diffPackets 
 * 计算q_s(tail(e))(t) - q_s(head(e))(t)
 * @return {interge}
 */
int BulkSession::diffPackets()
{
	return this->_tailQueue.size() - this->_headQueue.size();
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

