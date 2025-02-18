#include<iostream>
#include<mutex>
#include<chrono>
#include<thread>
using namespace std;

mutex m1;
mutex m2;

void thread1() {
    m1.lock();
    // this_thread::sleep_for(std::chrono::seconds(2)); //--> create deadlock
    m2.lock();
    cout << "thread 1 critical section" << endl;
    m2.unlock();
    m1.unlock();
}

void thread2() {
    m2.lock();
    m1.lock();
    cout << "thread 2 critical section" << endl;
    m1.unlock();
    m2.unlock();
}

int main(){

    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();


    return 0 ;
}