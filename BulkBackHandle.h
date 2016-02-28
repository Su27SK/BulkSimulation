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
		inline virtual void expire(Event*) {
			t_->handle();
			t_->timeout();
			//cout<<"expire"<<endl;
		}
	protected:
		BulkBackHandle* t_;
};

class BulkBackHandle
{
	private:
		Timer _execTime;
	public:
		BulkBackHandle():running_(0){}
		virtual void handle(){};
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
