#include<iostream>
#include<thread>
#include<mutex>
#include<ctime>
#include<chrono>
#include<unistd.h>
using namespace std;
// typedef time_t time;

// using namespace std::chrono_literals;

time_t T = 5;
int Count = 0;
std::timed_mutex m;
void fun(int i){

    if(m.try_lock_for(std::chrono::seconds(2))){   
        Count++;
        // this_thread::sleep_for(std::chrono::seconds(1));
        sleep(1);
        cout << " count updated by thread " << i << " count : " << Count << endl;
        m.unlock();
    }else{
        cout << "thread " << i << " is not entered " << endl;
    }

}

int main(){
    thread t1(fun, 1);
    thread t2(fun, 2);

    t1.join();
    t2.join();
    return 0;
}