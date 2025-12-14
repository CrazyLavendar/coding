/*
Q. Implement a lock-free counter using both compare_exchange (CAS) and fetch_add. Explain the difference.
You must design a class LockFreeCounter with two increment functions:
class LockFreeCounter {
private:
    std::atomic<int> value;

public:
    LockFreeCounter() : value(0) {}

    void inc_CAS();       // increment using compare_exchange_weak or strong
    void inc_fetch_add(); // increment using atomic fetch_add()

    int get() const;
};
Requirements
inc_CAS() must implement increment using a CAS loop.
inc_fetch_add() must increment using a single atomic fetch_add().
Explain during the interview:
When CAS is preferred
When fetch_add is preferred
Performance and contention differences
Why CAS may loop (spinning) under high concurrency

*/
#include<iostream>
#include<atomic>

using namespace std;

class LockFreeCounter{
public:
    LockFreeCounter() : value(0) {}

    // void inc_CAS();       // increment using compare_exchange_weak or strong
    // void inc_fetch_add(); // increment using atomic fetch_add()
    // int get() const;

    void inc_CAS(){
        int curr_val = value.load(memory_order_relaxed);
        while(true){
            int next_val = curr_val + 1;
            if(value.compare_exchange_weak(curr_val, next_val, memory_order_acquire, memory_order_relaxed)){
                break;
            }
        }

    }
    void inc_fetch_add(){
        int old_value = value.fetch_add(1,memory_order_relaxed);
    }

    int get() const{
        return value.load(memory_order_relaxed);
    }

private:
    std::atomic<int> value;

};

int main(){

    LockFreeCounter l;
    
    for(int i = 0; i < 100; i++){
        l.inc_CAS();
    }
    for(int i = 0; i < 100; i++){
        l.inc_fetch_add();
    }
    cout << l.get() << endl;


    return 0;
}