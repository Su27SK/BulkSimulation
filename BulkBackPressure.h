#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "TimerHandler.h"
#include "BulkTime.h"
class BulkBackPressure;
class BulkBackPressureTimer : public TimerHandler
{
	public:
		BulkBackPressureTimer(BulkBackPressure* t): TimerHandler(), t_(t){}
		BulkBackPressureTimer(): TimerHandler(){}
		inline virtual void expire(Event*) {
			cout<<"expire"<<endl;
		}
	protected:
		BulkBackPressure* t_;
};

class BulkBackPressure
{
	public:
		void start();
		void stop();
		void timeout();
	protected:
		int running_;
		BulkBackPressureTimer timer_;
};
#endif
