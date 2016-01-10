#ifndef _BULKPACKETS_H_
#define _BULKPACKETS_H_
#include <ext/slist>
class BulkPackets
{
	private:
		static slit<BulkPackets*> _packetsPool;
	public: 
		BulkPackets();
		BulkPackets(double size);
		void destroy();
		BulkPackets* getBulkPackets(int size);
		virtual ~BulkPackets();
};

#endif
