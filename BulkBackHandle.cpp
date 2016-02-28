#include "BulkBackHandle.h"

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
	_execTime.next(interval);
	return this->getNowTime();
}

/**
 * @brief next 
 * 下一个时间点
 * @return {double}
 */
double BulkBackHandle::next()
{
	_execTime.next();
	return this->getNowTime();
}

/**
 * @brief getNowTime 
 * 获得当前时间
 * @return 
 */
double BulkBackHandle::getNowTime()
{
	return _execTime.getTime();
}
