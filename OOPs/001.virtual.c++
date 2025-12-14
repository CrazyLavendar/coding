#include<iostream>

using namespace std;

class A{
public:
    virtual void print(){
        cout << "I am from Class A" << endl;
    }

    void basic(){
        cout << "I am from Class A - Basic" << endl;
    }
    virtual ~A(){
        cout << "destructing A" << endl;
    }
};

class B : public A{
public:
    
    void print() override {
        cout << "I am from Class B" << endl;
    }
    void basic(){
        cout << "I am from Class B - Basic" << endl;
    }
    ~B(){
        cout << "destructing B" << endl;
    }
};

int main(){
    A *a = new B();
    a->print();
    delete a;
    return 0;
}