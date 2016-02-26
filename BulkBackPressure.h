#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "BulkBackPressure.h"
class BulkBackPressure: BulkBackHandle
{
	public:
		BulkBackPressure():BulkBackHandle(){}
		virtual void handle();
	private:
		BulkNetWork net;
};
#endif
