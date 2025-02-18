#include<iostream>
using namespace std;
int x  = 5;
void fun(int x){
    cout << "called fun with val "  << x << endl;
}

void wrapper(void (*f)(int x)){
        (*f)(x);
    }
int main(){

    void (*callBack)(int) = fun;

    void *x = (*callBack)(int);

    return 0;
}