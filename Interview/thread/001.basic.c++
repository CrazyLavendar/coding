#include<iostream>
#include<thread>
#include<chrono>
#include<ctime>
using namespace std;
using namespace chrono;

typedef unsigned long long ULL;
ULL evenRes = 0, oddRes = 0;
void funOdd(ULL start , ULL end){
    evenRes = 0;
    for(int i= start; i < end ; i++){
        if((i & 1) == 0)
            evenRes += i;
    }
}

void funEven(ULL start , ULL end){
    oddRes = 0;
    for(int i= start; i < end ; i++){
        if((i & 1) == 1)
            oddRes += i;
    }
}

int main(){

    ULL start = 0 , end = 10000000000;

    auto start_time = system_clock::now();
    funEven(start, end);
    funOdd(start, end);


    auto end_time = system_clock::now();
    // cout << evenRes << endl;
    // cout << oddRes << endl;

    auto duration = duration_cast<microseconds> (end_time - start_time);
    cout << duration.count() << endl;

    start_time = system_clock::now();   
    thread t1(funEven, start, end);
    thread t2(funOdd, start, end);
    t1.join();
    t2.join();
    end_time = system_clock::now();
    duration = duration_cast<microseconds> (end_time - start_time);
    cout << duration.count() << endl;

    
    return 0;
}
