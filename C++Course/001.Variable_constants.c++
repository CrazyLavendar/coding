#include<iostream>
#include<climits>

using namespace std;
int main(){
    cout << " int max " << INT_MAX << endl;

    const int i1 = 10;
    //i = 2; // Error
    constexpr int i2 = 20;
    const int i3 = i1;
    constexpr int i4 = i2;


    static_assert(i1 < i2 , "assertion passed");

    return 0;
}