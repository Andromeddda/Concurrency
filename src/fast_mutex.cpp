#include <sys/syscall.h>
#include <unistd.h>
#include <linux/futex.h>

#include <errno.h>

#include <atomic>
#include <iostream>

#include <cstdlib>
#include <stdio.h>
#include <stdint.h>

#include <fast_mutex.hpp>

static int
futex(int *uaddr, int futex_op, uint32_t val,
     const struct timespec *timeout, uint32_t *uaddr2, uint32_t val3)
{
   return syscall(SYS_futex, uaddr, futex_op, val,
                  timeout, uaddr2, val3);
}

SmartMutex::SmartMutex() : futex_word(0) {}

void SmartMutex::lock() {
   while (futex_word.exchange(MUTEX_LOCKED) != MUTEX_FREE) {
      futex((int*)&futex_word, FUTEX_WAIT, MUTEX_LOCKED, NULL, NULL, 0);
   }
}

void SmartMutex::unlock() {
   futex_word.store(MUTEX_FREE);
   futex((int*)&futex_word, FUTEX_WAKE, 1, NULL, NULL, 0);
}