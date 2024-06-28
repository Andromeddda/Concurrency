#ifndef HEADER_GUARD_BROKEN_MUTEX_HPP
#define HEADER_GUARD_BROKEN_MUTEX_HPP

#include <iostream>
#include <atomic>

// SAFEFY 	[+]
// LIVENESS [-]
class BrokenMutex1 {
public:
	// Default constructor
	BrokenMutex1();

	// Mutex is not copyable
	BrokenMutex1(const BrokenMutex1& other) = delete;

	void Lock(size_t index);
	void Unlock();

private:
	std::atomic<bool> want_[2];
	size_t owner_;
};

// SAFEFY 	[+]
// LIVENESS [-]
class BrokenMutex2 {
public:
	// Default constructor
	BrokenMutex2() = default;

	// Mutex is not copyable
	BrokenMutex2(const BrokenMutex1& other) = delete;

	void Lock(size_t index);
	void Unlock();

private:
	std::atomic<size_t> victim_;
};


// SAFEFY 	[+]
// LIVENESS [+]
class PetersonMutex {
public:
	// Default constructor
	PetersonMutex();

	// Mutex is not copyable
	PetersonMutex(const BrokenMutex1& other) = delete;

	void Lock(size_t index);
	void Unlock();

private:
	std::atomic<bool> want_[2];
	std::atomic<size_t> victim_;
	size_t owner_;
};

#endif // HEADER_GUARD_BROKEN_MUTEX_HPP