#include<iostream>
using namespace std;

int main(){
    int a = 10, b = 20, c = 30, d = 40;


    // * int // ---> not possible
    const int * p = &a;
    int const * q = &b;
    int * const r = &c;

    // *p = 11; //  error
    p = &b;

    // *q = 21; // error
    q = &a;

    *r = 31;
    // r = &d; // error




    cout << *p << " " << *q << endl;

    return 0;
}