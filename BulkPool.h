#ifndef	BULKPOOL_H_
#define BULKPOOL_H_
#include "BulkPackets.h"
class BulkPool
{
	private:
		slist<BulkPackets>* pool;
	public:
		BulkPool
		void init();
		void destroy();
};
#endif
