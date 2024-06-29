#include <broken_mutex.hpp>

/////////////////////////////////////////////////////////////////////////////////////

/*
	Safety [+]
	Assume both threads are in between of lock() and unlock() calls.
	It means, that want_ = {true, true} and both thread passed the loop.

	Liveness [-]
	There is a case, when both threads store(true) and wait for eachother to unlock

*/

BrokenMutex1::BrokenMutex1() {
	// when mutex created, nobody holds it
	want_[0].store(false);
	want_[1].store(false);
}

void BrokenMutex1::lock(size_t index) {
	want_[index].store(true); // caller takes the mutex

	// Skip if other thread does not want to hold the mutex
	// Wait otherwise
	while(want_[1 - index].load()) {
		// Backoff
	}
	owner_ = index; // Take the mutex
}

void BrokenMutex1::unlock() {
	want_[owner_].store(false);
}

////////////////////////////////////////////////////////////////////////////////////

/*
	Safety [+]
	Assume both threads are in between of lock() and unlock() calls.
	It means, that both saw victim_ that is different to theis indecies

	Liveness [-]
	Progress exist only if there is two thread. Only one thread will never take the mutex.

*/

void BrokenMutex2::lock(size_t index) {
	victim_.store(index);
	while (index == victim_.load()) {
		// Backoff
	}
}

void BrokenMutex2::unlock() { }


////////////////////////////////////////////////////////////////////////////////////

/*
	Safety [+]
	A thread can be between lock() and unlock() only when want_[i] == true.
	That means want_ = {true, true}.
	Since both while conditions was false, neither of thread was the victim.
	Thus, a contradiction 

	Liveness [+]
	Assume both threads are waiting for eachother. 
	That means want = {true, true} and both index1 == victim and index2 == victim.
	Thus, a contradiction

*/

PetersonMutex::PetersonMutex() {
	want_[0].store(false);
	want_[1].store(false);
}

void PetersonMutex::lock(size_t index) {
	want_[index].store(true);
	victim_.store(index);

	// Wait if other thread want mutex AND we called lock() the last (we are the victim)
	// Skip if other thread doesn't want the mutex
	// Skip if other thread want the mutex, but called lock() later
	while ((want_[1-index].load()) && (index == victim_.load())) {
		// Backoff
	}
	owner_ = index; // Take the mutex
}

void PetersonMutex::unlock() {
	want_[owner_].store(false);
}


