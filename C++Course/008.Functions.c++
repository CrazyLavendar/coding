#include <iostream>
using namespace std;

void fun(int x, int z, int y = 1){ // default argument
    cout << x + y  << endl;
}

void fun (double x , double y){ // function , method, operand overloading
    cout << x + y  << endl;
}

void operator+(int a, double b){
    cout << a + b  << endl;
}

int main(){

    fun(10, 20);
    fun(10.0,20.1);
    return 0;
}