#include<iostream>
#include<atomic>
using namespace std;


class TicketLock
{
public:
    void lock(){
        // return old value
        int my_ticket_ = next_ticket.fetch_add(1, memory_order_relaxed);
        while(my_ticket_ != now_serving.load(memory_order_acquire));
        // allow
    }

    void unlock(){
        now_serving.fetch_add(1, memory_order_release);
    }
private:
    atomic<int> next_ticket{0};
    atomic<int> now_serving{0};
};
int main(){
    return 0;
}

/**
 T1 -> 1  
 my_ticket_ = 1, now_serving = 0
 1 != 0


 * 
 */