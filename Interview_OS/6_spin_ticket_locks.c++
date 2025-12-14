/*
Problem (Implement a fair spinlock and compare with naive spinlock):
Implement two locks in C++ (pseudocode OK):
NaiveSpinLock: simple atomic-test-and-set spinlock (busy-wait on a single atomic flag).
TicketLock: a ticket-based spinlock that guarantees FIFO fairness (each waiter takes a ticket and waits for its turn).
Provide these APIs:
class NaiveSpinLock {
  void lock();
  void unlock();
};

class TicketLock {
  void lock();
  void unlock();
};
Requirements & Deliverables:
Implement lock()/unlock() using std::atomic and explicit memory orders (explain which orders and why).
Ensure TicketLock provides FIFO fairness and bounded waiting.
Ensure unlock() has minimal overhead and avoids unnecessary cache-line thrashing.
Prove / Argue Correctness:
Show why TicketLock is free from starvation and provides FIFO service.
Show that NaiveSpinLock can starve threads and cause unfair scheduling.
Performance & Contention Analysis:
Explain the cache-coherency implications of both locks under high contention (thundering herd, cache-line bouncing).
Provide microbenchmarks you would run to compare:
low contention, moderate contention, and high contention.
critical section durations (short vs long).
varying numbers of threads and NUMA placements.
Explain expected results and why (e.g., ticket lock scales better under fairness; naive may be faster for extremely short critical sections with low contention).
Advanced Follow-ups (interviewer):
Modify TicketLock to support priorities (e.g., real-time threads get priority) — how do you avoid unbounded priority inversion?
Implement an adaptive lock that switches between spinning and blocking (futex/wait) depending on contention and critical-section length — design the heuristic.
Discuss weak fairness vs strong fairness and how you would simulate/measure fairness in practice.
*/

#include<iostream>
#include<memory>
#include<atomic>
#include<thread>
using namespace std;

class Lock{
public:
  virtual void lock () = 0;
  virtual void unlock () = 0;
private:
};

class NaiveSpinLock : Lock {
public:
  void lock();
  void unlock();
private:
 atomic<int> mylock{1};  // 1->unlocked, 0 -> locked
};

class TicketLock : Lock{
public:
  void lock();
  void unlock();
private:
  atomic<int> curr_ticket{0};
  atomic<int> next_ticket{0};
};

void TicketLock::lock(){
    int curr_ticket_local = curr_ticket.fetch_add(1, memory_order_release);
    while(true){
        if(curr_ticket_local == next_ticket.load(memory_order_acquire)){
            break;
        }
    }
};

void TicketLock::unlock(){
    next_ticket.fetch_add(1, memory_order_release);
};

void NaiveSpinLock::lock(){
    while(true){
        int curr = mylock.load(memory_order_relaxed);
        if(mylock.compare_exchange_weak(curr, 0, memory_order_acquire, memory_order_relaxed)){
            break;
        }else{
            this_thread::yield();
        }
    }
};

void NaiveSpinLock::unlock(){
    mylock.store(1, memory_order_release);
};


int main(){
    return 0;
}