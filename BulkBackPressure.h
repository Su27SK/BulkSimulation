#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "BulkBackHandle.h"
#include "BulkNetwork.h"
class BulkBackPressure: public BulkBackHandle, public BulkNetwork
{
	private:
		
	public:
		BulkBackPressure():BulkBackHandle(), BulkNetwork(){}
		inline virtual void handle();
		inline virtual void dynamicPush(BulkLink& link);
		void propagate(queue<int>* q, int* visited);
		void pushPacketsOut(int nodeId);
};
#endif
