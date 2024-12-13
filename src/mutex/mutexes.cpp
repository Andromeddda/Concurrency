#include "mutex/mutexes.hpp"
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/futex.h>

static int
futex(int *uaddr, int futex_op, uint32_t val,
     const struct timespec *timeout, uint32_t *uaddr2, uint32_t val3)
{
   return syscall(SYS_futex, uaddr, futex_op, val,
                  timeout, uaddr2, val3);
}


TASSpinlockMutex::TASSpinlockMutex() 
    : locked_(false) 
    {}

void TASSpinlockMutex::lock() 
{
    while (locked_.exchange(true)) 
    {}
}

void TASSpinlockMutex::unlock() 
{
    locked_.store(false);
}



TicketMutex::TicketMutex() 
    : owner_ticket_(0), next_free_ticket_(0)
    {}

void TicketMutex::lock() 
{
    size_t my_ticket = next_free_ticket_.fetch_add(1);
    while (my_ticket != owner_ticket_.load())  
    {}
}

void TicketMutex::unlock() {
    owner_ticket_.fetch_add(1);
}

FastMutex::FastMutex() : futex_word(0) {}

void FastMutex::lock() {
   while (futex_word.exchange(MUTEX_LOCKED) != MUTEX_FREE) {
      futex((int*)&futex_word, FUTEX_WAIT, MUTEX_LOCKED, NULL, NULL, 0);
   }
}

void FastMutex::unlock() {
   futex_word.store(MUTEX_FREE);
   futex((int*)&futex_word, FUTEX_WAKE, 1, NULL, NULL, 0);
}
