#ifndef _BULKBACKHANDLE_H_
#define _BULKBACKHANDLE_H_
#include "TimerHandler.h"
#include "Timer.h"
#include "BulkBackPressure.h"
class BulkBackHandle;
class BulkBackHandleTimer : public TimerHandler
{
	public:
		BulkBackPressureTimer(BulkBackPressure* t): TimerHandler(), t_(t){}
		BulkBackPressureTimer(): TimerHandler(){}
		inline virtual void expire(Event*) {
			t_->handle();
			t_->timeout();
			cout<<"expire"<<endl;
		}
	protected:
		BulkBackHandle* t_;
};

class BulkBackHandle
{
	private:
		BulkTime _execTime;
	public:
		BulkBackHandle():running_(0){}
		virtual void handle() = 0;
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
