#include<iostream>
#include<atomic>
#include<mutex>
#include<semaphore>
#include<thread>
using namespace std;

class AtomicSpinLock{
    atomic<bool> flag{false};

    // basic spin lock
    void lock(){
        while(flag.exchange(true, memory_order_acquire));
    }

    // CAS
    void CASLock(){
        while(true){
            bool expected = false;
            if (flag.compare_exchange_weak(expected, true, memory_order_acquire, memory_order_relaxed)){
                break;
            }
        }
    }

    void unlock(){
        flag.store(false, memory_order_release);
    }
};

class MutexSpinLock{
    mutex m;

    void lock(){
        m.lock();
    }
    void unlock(){
        m.unlock();
    }
};

class SemaphoreSpinLock{
    binary_semaphore semaphore{1};
    void lock(){
        semaphore.acquire();
    }
    void unlock(){
        semaphore.release();
    }
};

int main(){
    return 0;
}