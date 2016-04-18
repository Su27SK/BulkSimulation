#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "BulkBackHandle.h"
#include "BulkNetwork.h"
#include <string.h>
#define THRESHOLD 0.1 //ε
class BulkBackPressure: public BulkBackHandle, public BulkNetwork
{
	private:
		FILE* _lHandle;
		FILE* _nodeHandle;
		FILE* _sinkHandle;
		FILE* _packetHandle;
		double _computeS(map<double, int>& sorted, BulkLink link, double capacity);
		void _realloc();
	public:
		BulkBackPressure():BulkBackHandle(), BulkNetwork() {
			_lHandle = _nodeHandle = _sinkHandle = _packetHandle = NULL;
		}
		virtual void handle();
		//virtual void dynamicPush(BulkLink& link);
		virtual float dynamicPush(BulkLink& link);
		void propagate(queue<int>* q, int* visited);
		void pushPacketsOut(int nodeId);
		double getCapacityFromFile(double time, int source, int sink);
};
#endif
