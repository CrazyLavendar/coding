#include<iostream>

int main(){

    int n = 12345; //1010 -> 0101 ->5
    int rev = 0;
    while(n > 0){
        rev = (rev << 1) + (n & 1);
        n >>= 1;
    }
    std::cout << rev << std::endl;

    std::cout << log2(8) << std::endl;
    return 0;
}