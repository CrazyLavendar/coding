#include<iostream>
using namespace std;



class Base{
    int x;    
public:

    Base(int x):x{x}{}
    ~Base(){
        cout << " destruct " << endl;
    }

    // friend void fun2(Base &);
    // friend class F;
};

class F : public Base{

public:
    F(){
         Base b(10);
         int b = 10;
         fun(b);
         
         
    }

    // void fun(Base  &obj){
    // cout << obj.x << endl;  
    // }

    void 
};


int main(){

    F f;

    return 0;
}
