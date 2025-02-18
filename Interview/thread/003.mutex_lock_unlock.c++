#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

timed_mutex m; /// Timed mutex
int amount;
void fun(){
    for(int i = 0 ; i< 2000000; i++){
        // if(m.try_lock()) // --------> not strict
        // if(m.try_lock_for(chrono::milliseconds(1))) // strict with time 
        m.lock(); // very strict
        amount++;
        m.unlock();
    }
}

int main(){
    thread t1 (fun);
    thread t2 (fun);

    t1.join();
    t2.join();

    cout << amount << endl;
    return 0;
}