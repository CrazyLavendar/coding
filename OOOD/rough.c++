#include<iostream>
using namespace std;

class dummy{
    public:
    int x;
};

static dummy* d;


int main(){
    // = new dummy();
    cout << d->x << endl;
    return 0;
};