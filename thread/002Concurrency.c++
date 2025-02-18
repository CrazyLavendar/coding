#include<iostream>
#include<ctime>
#include<thread>
#include<unistd.h>
using namespace std;
void fun(int n){
    while (n--)
    {
        cout << n << endl;
    }
    
}


int main(){

    cout << " main start" << endl;
    thread t1(fun , 10);
    t1.detach();
    cout << " main end" << endl;
    sleep(3);
    return 0;
}