#include "BulkNode.h"

/**
 * @brief _defaultInit 
 * 缺省初始化函数
 */
void BulkNode::_defaultInit()
{
	output_ = new slist<BulkLink>(0);
	input_ = new slist<BulkLink>(0);
	_isTerminal = false;
	_isOriginal = false;
}


/**
 * @brief _getAllWeight 
 * 获得所有E[c(e)(t)]期望倒数之和
 * @return 
 */
double BulkNode::_getAllWeight()
{
	slist<BulkLink>::iterator iter;
	double sumWeight = 0;
	double singleWeight;
	int i = 0;
	slist<BulkLink>* pLink = output_;
	while (i < 2) {
		for (iter = pLink->begin(); iter != pLink->end(); iter++) {
			if ((singleWeight = iter->getWeight()) != 0) {
				sumWeight  += 1/singleWeight;
			}
		}
		pLink = input_;
		i++;
	}
	return sumWeight;
}

/**
 * @brief BulkNode 
 * construct function
 * @param {BulkGraphNode} node
 */
BulkNode::BulkNode(const BulkGraphNode& node):BulkGraphNode(node)
{
	this->_defaultInit();
}

/**
 * @brief BulkNode 
 * construct function
 * @param {BulkGraphNode} node
 */
BulkNode::BulkNode(BulkGraphNode& node):BulkGraphNode(node)
{
	this->_defaultInit();
}

/**
 * @brief getStoreSize 
 * get the session's Store Size(the amount of packet)
 * @param {interge} sId
 * @param {unit} type = Kb
 *
 * @return {interge}
 */
double BulkNode::getStoreSize(int sId, unit type)
{
	double amount = 0;
	int i = 0;
	slist<BulkLink>::iterator sIter;
	for (sIter = input_->begin(); sIter != input_->end(); sIter++) {
		queue<BulkPackets>* pHead = sIter->getHead(sId);
		int nSize = pHead->size();
		while (i < nSize) {
			BulkPackets& p = pHead->front();
			pHead->pop();
			amount += p.getBulkPacketsSize(type);
			pHead->push(p);
			i++;
		}
	}
	i = 0;
	for (sIter = output_->begin(); sIter != output_->end(); sIter++) {
		queue<BulkPackets>* pTail = sIter->getTail(sId);
		int nSize = pTail->size();
		while (i < nSize) {
			BulkPackets& p = pTail->front();
			pTail->pop();
			amount += p.getBulkPacketsSize(type);
			pTail->push(p);
			i++;
		}
	}
	return amount;
}

/**
 * @brief getNumLink 
 * 获得链接Link总数
 * @return 
 */
int BulkNode::getNumLink()
{
	return this->getNumHeadQueue() + this->getNumTailQueue();
}

/**
 * @brief setOriginal 
 * 设置该节点为session起点
 * @return {BulkNode}
 */
BulkNode& BulkNode::setOriginal()
{
	this->_isOriginal = true;
	return *this;
}

/**
 * @brief setTerminal 
 * 设置该节点为session终节点
 * @return {BulkNode}
 */
BulkNode& BulkNode::setTerminal()
{
	this->_isTerminal = true;
	return *this;
}

/**
 * @brief getTerminal 
 * 获得flag, 判断是否是出口点
 * @return {boolean}
 */
bool BulkNode:: getTerminal()
{
	return this->_isTerminal;
}

/**
 * @brief getOriginal 
 * 获得flag, 判断是否是起始点
 * @return {boolean}
 */
bool BulkNode::getOriginal()
{
	return this->_isOriginal;
}

/**
 * @brief getOutputLink 
 * get the link that to the next route
 * @return slist<BulkLink>
 */
slist<BulkLink>* BulkNode::getOutputLink()
{
	return output_;
}

/**
 * @brief getInputLink 
 * get the link that from the prev route
 * @return slist<BulkLink>
 */
slist<BulkLink>* BulkNode::getInputLink()
{
	return input_;
}

/**
 * @brief realloc 
 * 对在BulkNode中的特定session重新分配packet
 * @param {interge} sId
 */
void BulkNode::realloc(int sId)
{
	unit type = Kb;
	double qsv = this->getStoreSize(sId, type);
	slist<BulkLink>::iterator iter;
	double singleWeight;
	double allWeight = this->_getAllWeight();
	for (iter = output_->begin(); iter != output_->end(); iter++) {
		if ((singleWeight = iter->getWeight()) != 0) {
			double proportion = (1/singleWeight) / allWeight;
			double size = qsv * proportion;
			if (iter->tail_[sId]->size() == 0) {
				iter->setTailPackets(sId, 4);
			}
			this->_reallocPackets(iter->tail_[sId], size, type); 
		} else {
			iter->clearTailPackets(sId);
		}
	}
	for (iter = input_->begin(); iter != input_->end(); iter++) {
		if ((singleWeight = iter->getWeight()) != 0) {
			double proportion = (1/singleWeight) / allWeight;
			double size = qsv * proportion;
			if (iter->head_[sId]->size() == 0) {
				iter->setHeadPackets(sId, 4);
			}
			this->_reallocPackets(iter->head_[sId], size, type); 
		} else {
			iter->clearHeadPackets(sId);
		}
	}
}

/**
 * @brief _reallocPackets 
 * 在队列queue上重新分配packets
 * @param {queue<BulkPackets>} p(packets队列)
 * @param {double} size (该队列下总的传输数据大小)
 * @param {unit} type
 */
void BulkNode::_reallocPackets(queue<BulkPackets>* p, double size, unit type)
{
	double meanSize = size / p->size();
	int nSize = p->size();
	int i = 0;
	while (i < nSize) {
		BulkPackets& q = p->front();
		BulkPacket* pBag = q.getModel();
		pBag->setPacketSize(meanSize/100).setPacketType(type);
		q.setTransferPacketsNum(100);	
		p->pop();
		p->push(q);
		i++;
	}
}

/**
 * @brief addOutputLink 
 * 增加下一跳链路
 * @param {BulkGraphEdge*} edge
 */
void BulkNode::addOutputLink(BulkGraphEdge* edge)
{
	BulkLink* link = new BulkLink(*edge);
	this->output_->push_front(*link);
}

/**
 * @brief addInputLink 
 * 增加进到该点链路
 * @param {BulkGraphEdge} edge
 */
void BulkNode::addInputLink(BulkGraphEdge* edge)
{
	BulkLink* link = new BulkLink(*edge);
	this->input_->push_front(*link);
}

