#ifndef	BULKPOOL_H_
#define BULKPOOL_H_
#include "BulkPackets.h"
class BulkPool
{
	private:
		slist<BulkPackets>* _pool;
		BulkPackets* _packets;
		static int MAXSIZE = 1000;
		static int INITSIZE = 100;
	public:
		BulkPool();
		BulkPool(BulkPackets* packetsModel);
		void init();
		void destroy();
		void placePacketsToPool(BulkPackets* packets);
		BulkPackets* getPacketsFromPool();
};
#endif
