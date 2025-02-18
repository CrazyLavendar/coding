#include<iostream>
using namespace std;

int fun(int x){

    return x + 1;
}
int main(){
    cout << " function pointer " << endl;
    int i = 10;
    int (*p)(int) = fun;

    int j = (*p)(i);

    cout << " j "  << j<< endl;

    return 0;
}
