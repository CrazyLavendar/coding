#include<iostream>
using namespace std;
#define mysizeof(type) ((char*)(&type+1) - (char*)&type)

struct A{
    int x;
    bool b;
    float f;
};

template<typename T>
int t_mysizeOf(T a){
    return ((char*)(&a+1) - (char*)(&a));
};


int main(){
    int x;
    cout << mysizeof(x) <<endl;
    cout << &x <<endl;
    cout << &x+1 <<endl;
    cout << t_mysizeOf(x) << endl;

    A a1;
    cout << sizeof(a1) << endl;
    cout << mysizeof(a1) << endl;     
    cout << t_mysizeOf(a1) << endl;  
    return 0;
}