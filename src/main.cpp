#include <iostream>
#include <vector>

#include <mutex>
#include <thread>
#include <atomic>

#include <fast_mutex.hpp>	// Mutexes with syscalls
#include <spinlock.hpp>		// Spinlocks
#include <broken_mutex.hpp> // Peterson mutex for two threads

using namespace std;

#define MUTEX_ON
typedef TicketLock mutex_t;

using namespace std;
mutex_t guardian = mutex_t();
int x = 0;

void increment() {
	#ifdef MUTEX_ON
	guardian.lock();
	#endif

	for (int i = 0; i < 100; i++) {
		x = x + 1;
	}

	#ifdef MUTEX_ON
	guardian.unlock();
	#endif
}

int go() {
	auto threads = vector<thread>();

	for (int i = 0; i < 100; i++) {
		threads.push_back(thread(increment));
	}

	for (int i = 0; i < 100; i++) {
		threads[i].join();
	}
	return x;
}

int main(void) {

	int i = 0;
	int fails = 0;
	while (i < 1000) {
		int ret = go();
		if (ret != 10000) {
			cout << "Fail: " << i << '\n';
			fails++;
		}
		x = 0;
		i++;
	}

	cout << "Total fails: " << fails << '\n';

	return 0;
}