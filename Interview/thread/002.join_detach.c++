#include<iostream>
#include<thread>
#include<chrono>
using namespace std;
using namespace chrono;

void fun(){
    this_thread::sleep_for(seconds(5));
    cout << " thread finished";
}

int main(){

    thread t (fun);
    // t.join();
    if(t.joinable()){
        cout << " thread is joinabke" << endl;
    }
    t.detach(); // --> thread started and detached  
    // t.join(); // -> once detahced you cannot join again


    return 0;
}
