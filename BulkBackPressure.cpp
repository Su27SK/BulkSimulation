#include "BulkBackPressure.h"

/**
 * @brief handle 
 */
void BulkBackPressure::handle()
{
	
}

/**
 * @brief dynamicPush 
 * 对每条链路动态推送数据包
 * @param {Bulklink} link
 */
void BulkBackPressure::dynamicPush(BulkLink* link)
{
	
}

/**
 * @brief propagate 
 * session中数据包传播
 * @param {BulkSession} session
 */
void BulkBackPressure::propagate(BulkSession& session)
{
	BulkNode* sNode = session.sourceNode_;
	BulkNode* eNode = session.sinkNode_;
	while (sNode->getNodeId() != eNode->getNodeId()) {
		if (sNode->getStoreSize(session.id_) != 0) {

	}
}



