#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
int val = 0;
mutex m,n;
void fun(){
    for(int i = 0; i <= 1000000; i++){
        if(try_lock(m,n)){
            val++;
            m.unlock();
            n.unlock();
        } 
    }
}

int main(){

    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();

    cout << val << endl;

    return 0;
}