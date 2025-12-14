#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

struct data_{
    int a;
    // char pad[128];
    int b;
};

void helper(int* x){
    for(int i = 0; i < 100000000; i++)
        x++;
}

int main(){
    auto start_time = std::chrono::steady_clock::now();
    data_ d;
    d.a = 0;
    d.b = 0;
    thread a(helper, &d.a);
    thread b(helper, &d.b);

    a.join();
    b.join();

    auto end_time = std::chrono::steady_clock::now();

    auto duration = end_time - start_time;

    std::cout << "Operation took: " 
              << chrono::duration_cast<chrono::microseconds>(duration).count() 
              << " milliseconds." << std::endl;

    

    return 0;
}