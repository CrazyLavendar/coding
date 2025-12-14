/*
You are implementing a multi-threaded producer-consumer system in C++ using std::atomic:

#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

std::atomic<bool> ready{false};
int data = 0;

void producer() {
    data = 42;                               // (A)
    ready.store(true, std::memory_order_release);  // (B)
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) { // (C)
        // spin
    }
    std::cout << data << std::endl;          // (D)
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}


⸻

🔹 Tasks:
	1.	Explain why memory_order_release on store and memory_order_acquire on load are needed.
(B) memory_order_release , (C) memory_order_acquire  are needed for ordering the instructions.
(D)  data  can be 42 or 0 without proper order of execution.
(D) can be executed first. Compiler or Processor can change the order due to optimization changes.

	2.	What could happen if memory_order_relaxed is used for both store and load?
It just enables atomicity. Still order of instructions can be jumbled.
memory_order_acquire & memory_order_release / memory_order_seq_cst is needed for ordering  the instruction. 
	3.	Can data = 42; be reordered after ready.store(true) by the compiler or CPU?
No, ready.store(true) means,  memory_order_seq_cst by default. hence reordering not possible, it is very strict compared to acquire or release.

	4.	How do acquire/release semantics ensure proper synchronization?
After acquire : all the instruction before must not be reordered after acquire.
After release: all the instructions after release must not be reordered before release.
	5.	(Follow-up) How does this differ from using a mutex?

lock free is non-blocking synchronization. It wont block other threads by default.
But spin (while loop) can do busy waiting until the expected ordering met.
lock-free can be complex, But if performance needed and Critical section is smaller, lock-free datastructure is preferred.


*/