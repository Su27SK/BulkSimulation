#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "BulkBackHandle.h"
#include "BulkNetwork.h"
#define THRESHOLD 0.1 //ε
class BulkBackPressure: public BulkBackHandle, public BulkNetwork
{
	private:
		double _computeS(map<double, int> sorted, BulkLink link);
	public:
		BulkBackPressure():BulkBackHandle(), BulkNetwork(){}
		virtual void handle();
		virtual void dynamicPush(BulkLink& link);
		void propagate(queue<int>* q, int* visited);
		void pushPacketsOut(int nodeId);
};
#endif
