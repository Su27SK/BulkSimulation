#ifndef	_BULKPOOL_H_
#define _BULKPOOL_H_
#include "BulkPackets.h"
class BulkPool
{
	private:
		slist<BulkPackets>* _pool;
		BulkPackets* _packets;
		static const int MAXSIZE = 1000;
		static const int INITSIZE = 100;
	public:
		BulkPool();
		BulkPool(BulkPackets* packetsModel);
		~BulkPool();
		void init();
		void destroy();
		void placePacketsToPool(BulkPackets* packets);
		BulkPackets* getPacketsFromPool();
};
#endif
