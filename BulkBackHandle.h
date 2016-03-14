#ifndef _BULKBACKHANDLE_H_
#define _BULKBACKHANDLE_H_
#include "TimerHandler.h"
#include "Timer.h"
class BulkBackHandle;
class BulkBackHandleTimer : public TimerHandler
{
	public:
		BulkBackHandleTimer(BulkBackHandle* t): TimerHandler(), t_(t){}
		BulkBackHandleTimer(): TimerHandler(){}
		virtual void expire(Event*);
	protected:
		BulkBackHandle* t_;
};

class BulkBackHandle
{
	public:
		BulkBackHandle():running_(0){}
		virtual void handle(){}
		void start();
		void stop();
		void timeout();
		double next(double interval);
		double next();
		double getNowTime();
	protected:
		int running_;
		BulkBackHandleTimer timer_;
};
#endif
