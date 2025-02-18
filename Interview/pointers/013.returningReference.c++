#include <iostream>
 
using namespace std;


int& fun(){

    static int i = 10;

    return i;
}

int main()
{
    int& x = fun();

    cout << x << endl;

    return 0;
}