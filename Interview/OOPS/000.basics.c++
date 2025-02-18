#include<iostream>
using namespace std;

class Base {
    public:
    virtual void baseFun(){
        cout << "Base's Base fun" << endl;
    };
};

class child : public Base{
    public:
    void childFun(){
        cout << "Child fun" << endl;
    }

    
    void baseFun()
    override
    {
        cout << "Child's Base fun" << endl;
    }

};
int main(){

    Base* c = new Base();
    c->baseFun();


    
    return 0;
}