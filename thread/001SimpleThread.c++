#include<iostream>
#include<ctime>
#include<thread>
using namespace std;
typedef unsigned long long ull;
ull oddSum = 0, evenSum = 0;

void findOdd(ull start, ull end){
  for(int i = start ; i<= end ; i++)
    if((i&1) == 1)
        oddSum += i;  
}
void findEven(ull start, ull end){
      for(int i = start ; i<= end ; i++)
        if((i&1) == 0)
        evenSum += i;  
}


int main(){

    auto timeStart = time(NULL);

    void(* funOdd)(ull, ull) = &findOdd;
    void(* funEven)(ull, ull) = &findEven;

    thread t1(funOdd, 0 , 19000000000);
    thread t2(funEven, 0 , 19000000000);
    // findOdd(0, 19000000000);
    // findEven(0, 19000000000);
    t1.join();
    t2.join();
    auto timeEnd = time(NULL);



    cout << "oddSum : " << oddSum <<  "\nevenSum  : " << evenSum << endl;
    cout << "time taken = " << timeEnd - timeStart << endl;
    return 0;
}