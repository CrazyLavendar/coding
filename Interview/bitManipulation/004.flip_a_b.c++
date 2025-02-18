#include<iostream>
using namespace std;

void flip(int a , int b){

    int m = ceil(log2(a)) , n = ceil(log2(b));
    int max = m > n ? m : n;
    int mask = 1;
    int flip =0;
    for(int i = 0; i <= max ; i++){
        if((mask & a) != (mask & b))
        flip++;
        mask = mask << 1;
    }

    cout << flip << endl;

}

int main(){

    flip(1, 2); // 01, 10
    flip(0, 15); // 0000, 1111
    flip(256, 255);// 100000000, 11111111

    return 0;
}