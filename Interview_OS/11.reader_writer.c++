/*
Q2. RWLock — Implement Reader-Writer Lock (Hard)

Question

Implement a Reader-Writer Lock with the following properties:

Requirements
	•	Multiple readers can hold the lock simultaneously
	•	Writers must have exclusive access
	•	If a writer is waiting, new readers must block (writer-preference)
	•	Must use only:
	•	std::mutex
	•	std::condition_variable
	•	No busy waiting
	•	Must handle spurious wakeups
	•	No starvation

API

class RWLock {
public:
    void lock_read();
    void unlock_read();
    void lock_write();
    void unlock_write();
};

Follow-ups (very important)
	1.	What happens if readers are not blocked when a writer is waiting?
[ans] : Undefined behaviour. Readers may see incorrect data. Reader 1 and Reader 2 may see different data in same time.
	2.	How do you avoid writer starvation?
[ans] :    Current code is implemented with avoiding writer starvation. Using "writerWaiting = true; // indicating writer to give chance"
	3.	How is this different from a spin-based RW lock?
[ans] : Reader's thread will sleep when Writer is writing and viceversa. spin-based RW lock , readers will be spinning contionusly in CPU until writers complete. (Viceversa with writer thread). This can cause lot of contention.
	4.	Can this be downgraded from write → read safely?
[ans] : Yes, write to read is already safe in current code.
	5.	Where is RWLock preferred over mutex?
[ans] : When multiple readers can be allowed to read the data, 

⸻
*/

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

class RWLock {
public:
    void lock_read();
    void unlock_read();
    void lock_write();
    void unlock_write();
    RWLock(){
        r_count = 0;
        writerWaiting = false;
    }
private:
    int r_count; // number of readers count
    bool writerWaiting;
    mutex m;
    condition_variable cv_read, cv_write;
};

void RWLock::lock_read(){
    unique_lock<mutex> ul(m);
    cv_read.wait(ul, [&]{
        return writerWaiting == false; // if writer is waiting, readers should be fairness to allow writer to write
    });
    r_count++;
}
void RWLock::unlock_read(){
    unique_lock<mutex> m;
    r_count--;
    if(r_count == 0){
        cv_write.notify_one();
    }
}
void RWLock::lock_write(){
    unique_lock<mutex> ul(m);
    writerWaiting = true; // indicating writer to give chance
    cv_write.wait(ul, [&]{
        return r_count == 0;
    });
}

void RWLock::unlock_write(){
    unique_lock<mutex> m;
    writerWaiting = false;
    cv_read.notify_all();
}

int main(){

    return 0;
}