#include<iostream>
#include<semaphore>
#include <queue>
#include <thread>
#include <unistd.h>

using namespace std;

binary_semaphore lock_(1);
int N = 10;

struct my_data{
    int val;
};

queue<int> q;
int id = 0;

void producer(){

    while(true){
       // cout << " producer produced " << endl;
       lock_.acquire();
        if(q.size() < N){
            usleep(1000000);
            q.push(++id);
            cout << " producer produced " << q.size() << " id : " << id << endl; 
        }
        lock_.release();
        this_thread::yield();
    }

}

void consumer(){

    while(true){
       // cout << " consumer consumed " << endl;
       lock_.acquire();
        if (!q.empty())
        {
            usleep(1000000);
            cout << " consumer consumed " << q.size() << " id : " << q.front() << endl; 
            q.pop();
        }
        lock_.release();
        this_thread::yield();
    }

}

int main(){


    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();

    return 0;
}