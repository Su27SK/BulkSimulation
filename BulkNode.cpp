#include "BulkNode.h"

/**
 * @brief _defaultInit 
 * 缺省初始化函数
 */
void BulkNode::_defaultInit()
{
	store_ = 0;
	sNumPackets_ = new int[MAX_SIZE]; //max 100 number of session				
	output_ = new slist<BulkLink>(0);
	_isTerminal = false;
	_isOriginal = false;
	pqueue = new queue<BulkPackets>*[MAX_SIZE];
	int i;
	for (i = 0; i < MAX_SIZE; i++) {
		pqueue[i] = new queue<BulkPackets>;
	}
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
 * 获得该节点总存储数据包的数量,所有session
 * @return {interge}
 */
int BulkNode::getStoreSize()
{
	int i;
	for (i = 0; i < 100; i++) {
		store_ += sNumPackets_[i];
	}
	return store_;
}

/**
 * @brief getStoreSize 
 * get the session's Store Size
 * @param {interge} sId
 *
 * @return {interge}
 */
int BulkNode::getStoreSize(int sId)
{
	return sNumPackets_[sId];
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
 * 对在BulkNode中的特定session重新分配packets
 * @param {interge} sId
 */
void BulkNode::realloc(int sId)
{
	//int mOutputLink = this->getNumTailQueue();
	//int nPerLink = this->sNumPackets_[sId]/mOutputLink;
	//for () {
		
	//}
	slist<BulkLink>::iterator iter;
	for (iter = output_->begin(); iter != output_->end(); iter++) {
		;	
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

/**
 * @brief addSessionNum 
 * 增加某sessionId下存储的数据包数量
 * @param {interge} sId
 * @param {interge} num
 *
 * @return {BulkNode}
 */
BulkNode& BulkNode::addSessionNum(int sId, int num)
{
	this->sNumPackets_[sId] += num;
	return *this;
}

/**
 * @brief reduceSessionNum 
 * 减少某sessionId下存储的数据包数量
 * @param {interge} sId
 * @param {interge} num
 *
 * @return {BulkNode}
 */
BulkNode& BulkNode::reduceSessionNum(int sId, int num)
{
	this->sNumPackets_[sId] -= num;
	return *this;
}

