#include<iostream>
using namespace std;

void isPower(int n){
    if((n & (n-1)) == 0){
        cout << n << " is power of 2" << endl;
    }
    else{
        cout << n << " is not power of 2" << endl;
    }
}

int main(){

    isPower(256);
    isPower(155);

    
    return 0;
}

