#include <spinlock.hpp>

///////////////////////////////////////////////////////////////

TASSpinlock::TASSpinlock() {
	locked_.store(false);
}

void TASSpinlock::Lock() {
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



void TASSpinlock::Unlock() {
	locked_.store(false);
}

///////////////////////////////////////////////////////////////

TicketLock::TicketLock() {
	owner_ticket_.store(0);
	next_free_ticket_.store(0);
}

void TicketLock::Lock() {
	size_t my_ticket = next_free_ticket_.fetch_add(1);

	while (my_ticket != owner_ticket_.load()) {
		// Backoff
	}
}

void TicketLock::Unlock() {
	owner_ticket_.fetch_add(1);
}