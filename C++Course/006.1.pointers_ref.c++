#include<iostream>
using namespace std;



void fun2(string *ptr){
    cout << "addr of ptr inside fun2: " << &ptr << endl;
    string name = "Vimal Kumar NITW";
    ptr = &name;
    cout << "addr of ptr inside fun2 after modify: " << ptr << endl;
}
void fun3(string &s){
    cout << "addr of string inside fun3: " << &s << endl;
    s = "Vimal Kumar Mtech";

}

int main(){
    // dereference pointers;

    string name = "Vimal";
    string * ptr = &name;


    fun2(ptr);
    cout << *ptr << endl;
    cout << name << endl;
    cout << "addr of ptr : " << ptr << endl;


    fun3(name);
    cout << *ptr << endl;
    cout << name << endl;
    cout << "addr of ptr : " << ptr << endl;
    return 0;
}
