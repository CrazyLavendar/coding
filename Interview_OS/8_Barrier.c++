/*
Question
Implement a reusable barrier for N threads using only:
std::mutex
std::condition_variable
Requirements
All threads must block at the barrier until exactly N threads arrive
Once released, the barrier must be reusable for the next phase
No busy-waiting
No lost wakeups
Must handle spurious wakeups correctly
Follow-ups (very important)
What bug occurs if you forget to reset the counter?
[Ans] : deadlock can occur
Why is a generation counter needed?
[Ans] : To reuse the barrier again
What happens if notify_one() is used instead of notify_all()?
[Ans] :Only one thread will wake-up, though other threads can get out from baarier
How does this compare to a spin-barrier?
[Ans] : Contention is less. Spin-barrier can have higher contention
*/

#include<iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
using namespace std;

class Barrier{
public:

    Barrier(int num_threads) : count{0}, num_threads{num_threads}, generation{0} {}

    void wait(){
        unique_lock<mutex> ul(m);
        int gen = generation;
        count++;
        
        if(count == num_threads){
            count = 0;
            generation++;
            cv.notify_all();
            return;
        }

        // Do task

        cv.wait(ul, [&]{
            return gen < generation;
        });
    }

private:

    int count;
    int generation;
    int num_threads;
    mutex m;
    condition_variable cv;
};

class SpinBarrier {
public:
    explicit SpinBarrier(int n)
        : num_threads(n),
          count(n),
          global_sense(false) {}

    void wait() {
        thread_local bool local_sense = false;
        local_sense = !local_sense;

        // Decrement arrival count
        if (count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            // Last thread
            count.store(num_threads, std::memory_order_relaxed);
            global_sense.store(local_sense, std::memory_order_release);
        } else {
            // Spin
            while (global_sense.load(std::memory_order_acquire) != local_sense) {
                std::this_thread::yield();  // optional backoff
            }
        }
    }

private:
    const int num_threads;
    std::atomic<int> count;
    std::atomic<bool> global_sense;
};
