/*
Question
You are designing a high-performance in-memory key-value store that is accessed by multiple threads.
	•	Multiple threads frequently read data
	•	Writes are infrequent but must be exclusive

Using C++17 std::shared_mutex, answer the following:

⸻

Tasks
	1.	Explain the difference between:

std::shared_lock<std::shared_mutex>
std::unique_lock<std::shared_mutex>

[Ans:]
shared_lock allows multiple thread to access the critical section.
unique_lock will allow only one thread to access critical section.


	2.	Implement a thread-safe class that supports:

int get(int key);      // shared access
void put(int key, int value);  // exclusive access

Ans:
Implementing the code at last:

	3.	What happens if a writer is waiting and new readers keep arriving?
	•	Is starvation possible?
    Yes. Starvation is possible, but this can be avoided with writer preference by notifying the reader section not to allow further readers, since writer is waiting already.
	4.	When should shared_mutex NOT be used?
    For any exclusive access required (single ownership) shared_mutex should not be allowed with shared_lock.

⸻

Constraints
	•	No busy waiting
	•	Must be safe under high read contention
	•	Use only:
	•	std::shared_mutex
	•	std::shared_lock
	•	std::unique_lock

⸻

Follow-ups Interviewers Love
	•	How does shared_mutex differ from a reader-writer lock you implement manually?
[Ans:]
    Manual classic reader-writer involves exclusive lock for readers as well. Need to unlock reader's lock to allow other readers to enter critical section.
	•	Is std::shared_mutex fair?
[Ans:] No, fairness has to implemented seperately.
	•	What is std::shared_timed_mutex?
[Ans:] Can lock the mutex until spectic timeout
	•	How does this compare with lock-free read paths?
[Ans:] shared_mutex are wrapper over regular mutex to allow multiple threads to access critical section. It can be combined with condition variable. It can behave like non-busy waiting mechanism.. Where as lock-free involves busy-waiting (spin locks)
	•	Can shared locks be upgraded to exclusive locks safely?
[Ans:] No, might need to use upgrade_lock

*/

#include<iostream>
#include<shared_mutex>
#include<thread>
#include<condition_variable>
#include<map>

using namespace std;


class ThreadSafe{
    shared_mutex sm;
    //mutex sm;
    map<int, int> m;
    bool writer_wait;
    condition_variable_any cv;

    public:
    ThreadSafe(){
        writer_wait = false;
    }
    int get(int key)      // shared access
    {
        shared_lock<shared_mutex> sl(sm);
        cv.wait(sl, [&]{
            return !writer_wait;
        });
        return m[key];
    }
    void put(int key, int value)  // exclusive access
    {
        writer_wait = true;
        unique_lock<shared_mutex> ul(sm);
        m[key] = value;
        writer_wait = false;
        cv.notify_all();
    }

};

int main(){

    return 0;
}

