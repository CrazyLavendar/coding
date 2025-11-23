#include<iostream>
#include<thread>
#include <unistd.h>
#include <atomic>
using namespace std;


class Fun{
    public:
        void f(){
            // static int x = 1;
            static atomic<int> x = atomic<int>(1);
            // atomic_init(&x , 1);
            cout << x << endl;
            x++;
        }

        
};

int main(){

    Fun* f1 = new Fun();
    Fun* f2 = new Fun();
    
    // f1->f();
    // f2->f();

    thread t1(&Fun::f, f1);
    usleep(500);
    thread t2(&Fun::f, f2);
    t1.join();
    t2.join();


    delete f1;
    delete f2;
    return 0;
}