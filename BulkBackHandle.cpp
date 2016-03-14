#include "BulkBackHandle.h"

/**
 * @brief expire 
 * handle function
 */
void BulkBackHandleTimer::expire(Event*)
{
	t_->handle();
	t_->timeout();
}

/**
 * @brief start 
 */
void BulkBackHandle::start()
{
	running_ = 1;
	double t = next();
	timer_.sched(t);
}

/**
 * @brief stop 
 */
void BulkBackHandle::stop()
{
	running_ = 0;
}

/**
 * @brief timeout 
 */
void BulkBackHandle::timeout()
{
	if (running_) {
		double t = next();
		timer_.resched(t);
	} 
}

/**
 * @brief next 
 * 下一个时间点
 * @param {double} interval
 * @return {double}
 */
double BulkBackHandle::next(double interval)
{
	Timer::next(interval);
	return getNowTime();
}

/**
 * @brief next 
 * 下一个时间点
 * @return {double}
 */
double BulkBackHandle::next()
{
	Timer::next();
	return getNowTime();
}

/**
 * @brief getNowTime 
 * 获得当前时间
 * @return 
 */
double BulkBackHandle::getNowTime()
{
	return Timer::getTime();
}
