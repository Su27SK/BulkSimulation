#include "BulkBackPressure.h"

/**
 * @brief handle 
 */
void BulkBackPressure::handle()
{
	map<int, BulkNode>::iterator mIter;
	queue<int> q;
	int visited[MAX];
	for (int i = 1; i <= MAX; i++) {
		visited[i] = 0;
	}
	for (mIter = _lSourceList->begin(); mIter != _lSourceList->end(); mIter++) {
		q.push(mIter->first); 
		visited[mIter->first] = 1;
	}
	this->propagate(&q, visited);
}

/**
 * @brief dynamicPush 
 * 对每条链路动态推送数据包
 * @param {Bulklink} link
 */
void BulkBackPressure::dynamicPush(BulkLink& link)
{
	slist<BulkSession>* pSession = link.session_;
	slist<BulkSession>::iterator iter;
	for (iter = pSession->begin(); iter != pSession->end(); iter++) {
		double difference = link.diffPackets(sId);
	}
}

/**
 * @brief propagate 
 * 每个节点传送数据包(递推)
 * 类似BFS算法
 * @param {queue<int>} q
 * @param {interge*} visited
 */
void BulkBackPressure::propagate(queue<int>* q, int* visited)
{
	slist<BulkLink>::iterator iter;
	while (!q->empty()) {
		int u = q->front();  //get the front
		pushPacketsOut(u);   //push the packets out of the node 
		slist<BulkLink>* pLink = nList_[u]->getOutputLink();
		for (iter = pLink->begin(); iter != pLink->end(); iter++) {
			int iSink = iter->getGraphEdgeSink();
			if (!visited[iSink]) {
				q->push(iSink);
				visited[iSink] = 1;
			}
		}
		q->pop();
	}
}

/**
 * @brief pushPacketsOut 
 * 将节点中的数据全部传输出去
 * @param {interge} nodeId
 */
void BulkBackPressure::pushPacketsOut(int nodeId)
{
	BulkNode* pSourceNode = nList_[nodeId];
	pSourceNode->reallocAll();
	slist<BulkLink>* outlink = pSourceNode->getOutputLink();
	slist<BulkLink>::iterator iterLink; //遍历link
	vector<int>::iterator iterId;       //遍历sId (session id)
	for (iterLink = outlink->begin(); iterLink != outlink->end(); iterLink++ ) {
		int iSinkId = iterLink->getGraphEdgeSink();
		BulkNode* pSinkNode = nList_[iSinkId];
		for (iterId = sVector.begin(); iterId != sVector.end(); iterId++) {
			BulkSession* nSession = iterLink->findSession(*iterId);
			int nStore = pSourceNode->getStoreSize(*iterId); //增加或者删除session
			if (nSession == NULL && nStore != 0) {
				BulkSession* pSession = new BulkSession(sId, pSourceNode, pSinkNode);
				iterLink->addSession(*pSession);
			} else if (nSession != NULL && nStore == 0) {
				iterLink->deleteSession(sId);
			}
		}
		dynamicPush(*iter);
	}
}

