// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex m;
condition_variable cv;

void odd(){
    for(;;){
        
    }
    
    // std::cout << "odd" << std::endl;
}

void even(){
    for(;;){
        
    }
    //  std::cout << "even" << std::endl;
}

int main() {
    // Write C++ code here
    // std::cout << "Hello world!";
    
    thread t1(odd);
    thread t2(even);
    
    t1.join();
    t2.join();

    return 0;
}