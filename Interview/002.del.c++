#include<iostream>
using namespace std;

class Base{
public:
    int n;
    Base(){
        cout << "creating base" << endl;
    }
    ~Base(){
        cout << "deleting base" << endl;
    }
};

int main(){

    Base *b = new Base[5];
    b[0].n = 0;
     b[1].n = 1;
    delete[] b;
    return 0;
}