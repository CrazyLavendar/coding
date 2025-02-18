#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;
mutex m;
condition_variable cv;
int val = 0;
void printEven(int Limit){
    while(val  < Limit){

        unique_lock<mutex> ul{m};
        cv.wait(ul, [] {
            return
                (val & 1) == 0? true : false;
        });

            cout << val << endl;
            val++;

        if((val & 1) == 1){
            cv.notify_one();
        }
        

    }
}

void printOdd(int Limit){
    while(val  < Limit){

        unique_lock<mutex> ul{m};
        cv.wait(ul, [] {
            return
                (val & 1) == 1? true : false;
        });

            cout << val << endl;
            val++;

        if((val & 1) == 0){
            cv.notify_one();
        }


    }
}

int main(){
    int Limit = 10;
    thread t1(printEven, Limit);
    thread t2(printOdd, Limit);
    t1.join();
    t2.join();
    return 0;
}