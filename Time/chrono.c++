#include<iostream>
#include<chrono>
#include<thread>

using namespace std;

int main(){
    auto time1 = chrono::system_clock::now();
    this_thread::sleep_for(2000ms);
    auto time2 = chrono::system_clock::now();

    auto time_taken = time2 - time1;

    cout << chrono::duration_cast<chrono::milliseconds>(time_taken).count() << endl;

    return 0;
}