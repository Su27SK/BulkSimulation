#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "BulkBackPressure.h"
#include "BulkNetwork.h"
class BulkBackPressure: public BulkBackHandle, public BulkNetwork
{
	public:
		BulkBackPressure():BulkBackHandle(), BulkNetwork(){}
		inline virtual void handle();
		inline virtual void dynamicPush(BulkLink* link);
		void propagate(BulkSession& session);
};
#endif
