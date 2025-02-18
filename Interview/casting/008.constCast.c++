#include<iostream>
using namespace std;


int main(){
    cout << "const cast" << endl; 
    const int i1 = 10;
    const int *p1 = &i1;
    // *p1 = 11;
    cout << i1 <<  " " << *p1 << endl;
    int* p2 = const_cast<int *>(p1);
    *p2 = 12; // Undefined Behaviour
    
    cout << &i1 <<  " " << p1 << " " << p2<< endl;
    cout << i1 <<  " " << *p1 << " " << *p2<< endl;


    const int i2 = 100;
    int *p3 = const_cast<int*>(&i2);

    *p3 = 101; // Undefined Behaviour

    cout << &i2 <<  " " << p3 <<  endl;
    cout << i2 <<  " " << *p3 << endl;

    

    return 0;
}