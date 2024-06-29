#ifndef HEADER_GUARD_FAST_MUTEX_HPP
#define HEADER_GUARD_FAST_MUTEX_HPP

#include <iostream>
#include <atomic>

#define MUTEX_LOCKED 1
#define MUTEX_FREE 0

class SmartMutex {
public:
	SmartMutex();
	SmartMutex(const SmartMutex& other) = delete;

	void lock();
	void unlock();
private:
	std::atomic<int> futex_word;
};

#endif