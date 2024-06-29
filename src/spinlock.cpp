#include <spinlock.hpp>
#include <linux/futex.h>
#include <sys/syscall.h>

///////////////////////////////////////////////////////////////

TASSpinlock::TASSpinlock() {
	locked_.store(false);
}

void TASSpinlock::lock() {
	// backoff untill all others unlock
	while (locked_.exchange(true)) {
		// Backoff
	}

	/*	
		ASM prototype:
		mov		eax, locked_adress
		mov		ebx, 1

		wait:
			xchg  	[eax], ebx
			cmp		ebx, 0
			jnz		wait
	*/
}

void TASSpinlock::unlock() {
	locked_.store(false);
}

///////////////////////////////////////////////////////////////

TicketLock::TicketLock() {
	owner_ticket_.store(0);
	next_free_ticket_.store(0);
}

void TicketLock::lock() {
	size_t my_ticket = next_free_ticket_.fetch_add(1);

	while (my_ticket != owner_ticket_.load()) {
		// Backoff
	}
}

void TicketLock::unlock() {
	owner_ticket_.fetch_add(1);
}
