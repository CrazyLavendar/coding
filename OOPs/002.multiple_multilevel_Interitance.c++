#include<iostream>

using namespace std;


class A{
public:
    int A_;
    A(){
        A_ = 1;
    }
};

class B{
public:
    int B_;
    int A_;
    B (){
        B_ = 2;
    }
};

class C : A, public B{ /// --------> Multiple Inheritance
public:
    int getC(){
        return A::A_ + B_;
    };
};

class D : public C{ ///------------> multi level inheritance
public:
    int getD(){
        return B_;
        // return A_; //-------> cannot access
    }
};

int main(){
    C c;
    cout << c.getC() << endl;

    D d;
    cout << d.getD() << endl;
    return 0;
}