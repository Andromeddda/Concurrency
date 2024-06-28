#ifndef HEADER_GUARD_SPINLOCK_HPP
#define HEADER_GUARD_SPINLOCK_HPP

#include <atomic>
#include <iostream>

// Test-And-Set spinlock ~ atomic.exchange()
class TASSpinlock {
public:
	TASSpinlock();
	TASSpinlock(const TASSpinlock& other) = delete;

	void Lock();
	void Unlock();
private:
	std::atomic<bool> locked_;
};


class TicketLock {
public:
	TicketLock();
	TicketLock(const TicketLock& other) = delete;

	void Lock();
	void Unlock();
private:
	std::atomic<size_t> owner_ticket_;
	std::atomic<size_t> next_free_ticket_;
};

#endif // HEADER_GUARD_SPINLOCK_HPP