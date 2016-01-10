#include "BulkPackets.h"
BulkPackets::BulkPackets():_packetsPool(new slist<BulkPackets*>(1))
{

}

BulkPackets::BulkPackets(double size)
{
	this->_packetsPool = new slist<BulkPackets*>(size);
}

BulkPackets::~BulkPackets()
{
	slist<BulkPackets*>::iterator 
}


