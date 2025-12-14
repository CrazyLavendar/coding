#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>
#include<unistd.h>

using namespace std;

mutex m;
condition_variable cv;
struct image{
    int id;
    int data;
};
queue<image> q;
int id = 0;
int max_q = 10;

// consumer
void app(){
    while(true){
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{
            return !q.empty();
        });
        cout << "consuming from queue " << q.front().id << endl;
        q.pop();
        if (q.empty())
        {
            cv.notify_one();
        }
        usleep(500000);
    }
}

// producer
void sensor(){
    while(true){
        unique_lock <mutex>lock(m);
        if (q.size() == max_q){
            cv.wait(lock, []{
                return (q.size() == 0);
            });
        }
        usleep(1000000);
        image img = {++id, 0};
        q.push(img);
        cout << "pushed into queue for id " << q.back().id << endl;

        if(q.size() > 0){
            cv.notify_one();
        }
    }
}

int main(){

    thread t1(app);
    thread t2(sensor);

    t1.join();
    t2.join();

    return 0;
}