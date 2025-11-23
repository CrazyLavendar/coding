#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

int LIMIT = 100;
mutex m,n;

void print_odd(){
    for(int i = 0 ; i < LIMIT; i++){
        m.lock();
        if(i%2 == 1){
            cout << " odd func  " << i << endl; 
        }
        n.unlock();
    }
}

void print_even(){
    for(int i = 0 ; i < LIMIT; i++){
        n.lock();
        if(i%2 == 0){
            cout << " even func  " << i << endl; 
        }
        m.unlock();
    }
}

int main(){

    thread t1(print_even);
    thread t2(print_odd);

    t1.join();
    t2.join();

    return 0;
}