#include<iostream>
using namespace std;

class Base{
int x;
public:
    Base(){}
    Base(int x) : x{x} {}

private:
    Base operator = ( Base &rhs){
        x  = rhs.x;
        return x;
    }
};

int main(){

    Base b1(5);
    Base b2(10);

    // b1 = b2; It wont work



    // cout << b1.x << endl;
    // cout << b2.x << endl;


    return 0;
}