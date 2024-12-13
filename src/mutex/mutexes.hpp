#ifndef HEADER_GUARD_MUTEX_MUTEXES_HPP
#define HEADER_GUARD_MUTEX_MUTEXES_HPP

#include <atomic>
#include <cstdint>
#include <cstdio>

#define MUTEX_LOCKED 1
#define MUTEX_FREE 0

class AbstractMutex
{
public:
    AbstractMutex() {}
    AbstractMutex(const AbstractMutex& other) = delete;

    virtual void lock() = 0;
    virtual void unlock() = 0;
};


class TASSpinlockMutex : public AbstractMutex
{
public:
    TASSpinlockMutex();
    void lock() override;
    void unlock() override;
private:
    std::atomic<bool> locked_;
};


class TicketMutex : public AbstractMutex
{
public:
    TicketMutex();
    void lock() override;
    void unlock() override;
private:
    std::atomic<size_t> owner_ticket_;
    std::atomic<size_t> next_free_ticket_;
};


class FastMutex : public AbstractMutex
{
public:
    FastMutex();
    void lock() override;
    void unlock() override;
private:
    std::atomic<int> futex_word;
};




#endif // HEADER_GUARD_MUTEX_MUTEXES_HPP