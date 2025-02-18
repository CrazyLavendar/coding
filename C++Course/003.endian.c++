#include<iostream>
using namespace std;

int main(){
    int i = 0x1234567;
    char *p = (char*)&i;
    cout << hex << (int)*p << endl;
    cout << hex << (int)*(p+1) << endl;
    cout << hex << (int)*(p+2) << endl;
    cout << hex << (int)*(p+3) << endl;
    return 0;
}
