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
	int M = this->_topology->getVertices();
	cout<<"Link:"<<link.getCapacity()<<endl;
	map<double, int> sorted; 
	//遍历session
	for (iter = pSession->begin(); iter != pSession->end(); iter++) {
		double difference = link.diffPackets(iter->id_);
		double demand = iter->getDemand();
		double value;
		cout<<"difference:"<<difference<<endl;
		if (link.getCapacity() > THRESHOLD * demand / M && difference > 0) {
			value = difference / pow(demand, 2);
		} else {
			iter->flow_ = 0.0;
			value = 0.0;
		}
		sorted.insert(pair<double, int>(value, iter->id_)); //存储 diff/demand^2 => sId
	}
	double s = _computeS(sorted, link);
	map<double, int>::iterator iterS;
	for (iterS = sorted.begin(); iterS != sorted.end(); iterS++) {
		int sId = iterS->second;
		BulkSession* qSession;
		if ((qSession = link.findSession(sId)) != 0) { 
			double difference = link.diffPackets(sId);
			double demand = qSession->getDemand();
			int fi = ROUND((difference - s * pow(demand, 2)) / 2);
			cout<<"fi:"<<fi<<endl;
			qSession->send(fi, link);
			cout<<"sink_packets:"<<qSession->sinkNode_->getStoreAmount(1)<<endl;
		}
	}
}

/**
 * @brief _computeS 
 * back算法配套的排序函数(求出S+集合域), 并求出s
 * @param {map<double, int>} sorted //map遍历，从小到大
 * @param {BulkLink} link //边
 * @return {double} 返回计算之后的s
 */
double BulkBackPressure::_computeS(map<double, int> sorted, BulkLink link)
{
	map<double, int>::iterator iter;
	double sfake = sorted.begin()->first;
	double sum = 0.0, over = 0.0, low = 0.0;
	for (iter = sorted.begin(); iter != sorted.end(); iter++) {
		int sId = iter->second;
		BulkSession* p =  link.findSession(sId);
		double demand = p->getDemand();
		sum += link.diffPackets(sId) - sfake * pow(demand, 2) / 2;
		if (sum <= link.getCapacity()) {
			over += link.diffPackets(sId) - 2 * link.getCapacity();
			low  += pow(demand, 2);
		}
	}
	return over/low < 0.0 ? 0.0 : over/low;
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
		cout<<"-----------"<<endl;
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
	cout<<"sourceId:"<<nodeId<<endl;
	BulkNode* pSourceNode = nList_[nodeId];
	pSourceNode->reallocAll();
	slist<BulkLink>* outlink = pSourceNode->getOutputLink();
	slist<BulkLink>::iterator iterLink; //遍历link
	vector<int>::iterator iterId;       //遍历sId (session id)
	//遍历outlink
	for (iterLink = outlink->begin(); iterLink != outlink->end(); iterLink++) {
		int iSinkId = iterLink->getGraphEdgeSink();
		cout<<"iSinkId:"<<iSinkId<<endl;
		BulkNode* pSinkNode = nList_[iSinkId];
		//outlink上的session
		for (iterId = pSourceNode->sVector.begin(); iterId != pSourceNode->sVector.end(); iterId++) {
			BulkSession* nSession = iterLink->findSession(*iterId);
			int nStore = pSourceNode->getStoreAmount(*iterId); //增加或者删除session
			cout<<"nStore:"<<nStore<<endl;
			//if (nSession == NULL && nStore != 0) {
				//nSession = new BulkSession(*iterId, pSourceNode, pSinkNode);
				//double demand = *pSourceNode->demand_[*iterId];
				//nSession->setDemand(demand);
				//iterLink->addSession(*nSession);
			//} else if (nSession != NULL && nStore == 0) {
				////iterLink->deleteSession(*iterId);
				//pSourceNode->sVector.erase(iterId);
			//} 
			if (nStore != 0) {
				if (nSession == NULL) {
					nSession = new BulkSession(*iterId, pSourceNode, pSinkNode);
					double demand = *pSourceNode->demand_[*iterId];
					nSession->setDemand(demand);
					iterLink->addSession(*nSession);
				}
				iterLink->findSession(*iterId)->start();  
			} else {
				if (nSession != NULL) {
					iterLink->findSession(*iterId)->stop();
					pSourceNode->sVector.erase(iterId);
				}
			} //启动session(use the start and stop function in session)

			if (!pSinkNode->sIdExisted(*iterId)) {
				pSinkNode->sVector.push_back(*iterId);
			}
		}
		dynamicPush(*iterLink);
	}
}

