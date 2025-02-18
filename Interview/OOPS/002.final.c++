#include<iostream>
using namespace std;

class Base{
    public:
    virtual void fun()  {             /////////// virtual needed
        cout << "I am Base" << endl; 
    };

};
class Derived : public Base{        //// can't inherit
    public:
    void fun()                 
    {
        cout << "I am Derived " <<  " " << endl; 
    }

};

int main(){
    Base *b = new Derived(); ////////// polymorphism
    b->fun();
    return 0;
} 
