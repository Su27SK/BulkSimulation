#include "BulkPool.h"
BulkPool::BulkPool():_packets(new BulkPackets())
{
	this->_pool = new slist<BulkPackets>(0);
}

BulkPool::BulkPool(BulkPackets* packetsModel)
{
	this->_pool = new slist<BulkPackets>(0);
	this->_packets = packetsModel;
}

void BulkPool::init()
{
	int i;
	for (i = 0; i < this->INITSIZE; i++) {
		newPackets = new BulkPackets();
		this->_pool.push_front(newP
	}
}

void BulkPool::destroy()
{

}


