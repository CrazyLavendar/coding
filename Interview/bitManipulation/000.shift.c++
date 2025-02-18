#include<iostream>
using namespace std;

int main(){

    int x = 15;
 
    int y = x << 2; // right shift --> multiplies by 2
    int z = x >> 2; // left shift --> divides by 2

    cout << y << endl;
    cout << z << endl;

    return 0;
}