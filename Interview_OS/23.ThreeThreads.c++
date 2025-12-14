/*
A → B → C → A → B → C ...
*/

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

class Solution{

public:

Solution(int N) : N(N){
    curr = 0;
    start_a = true;
    start_b = false;
    start_c = false;
}

void printA(){
    while(true){
        unique_lock<mutex> ul(m);
        cv_a.wait(ul, [&]{
            return start_a;
        });
        if(curr == N){
            start_b = true;
            cv_b.notify_one();
            break;
        }
        cout << "A" << endl;
        start_a = false;
        start_b = true;
        cv_b.notify_one();
    }
}

void printB(){
    while(true){
        unique_lock<mutex> ul(m);
        cv_b.wait(ul, [&]{
            return start_b;
        });
        if(curr == N){
            start_c = true;
            cv_c.notify_one();
            break;
        }
        cout << "B" << endl;
        start_b = false;
        start_c = true;
        cv_c.notify_one();
    }
}

void printC(){
    while(true){
        unique_lock<mutex> ul(m);
        cv_c.wait(ul, [&]{
            return start_c;
        });
        if(curr == N){
            start_a = true;
            cv_a.notify_one();
            break;
        }
        cout << "C" << endl;
        start_c = false;
        start_a = true;
        curr++;
        cv_a.notify_one();
    }
}

private:
int N;
int curr;
mutex m;
condition_variable cv_a, cv_b, cv_c;
bool start_a, start_b, start_c;
};

int main(){

    Solution instance(2);

    thread t1(&Solution::printA, &instance);
    thread t2(&Solution::printB, &instance);
    thread t3(&Solution::printC, &instance);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}