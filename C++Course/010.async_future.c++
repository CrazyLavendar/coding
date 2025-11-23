#include<iostream>
#include<future>
#include<chrono>
#include<thread>
// #include<promise>

using namespace std;

int CS(int a){
    this_thread::sleep_for(chrono::seconds(2));
    cout << "CS" << endl;
    return a+1;
}

int main(){

    // future<int> result = async(CS, 5);

    // cout << "running async " << endl;

    // cout << result.get() << endl; // wait until CS complete

    // // thread
    // thread t1(CS, 5);

    future<int> result = promise(CS, 5);

    cout << "running async " << endl;

    cout << result.get() << endl; // wait until CS complete

    return 0;
}
