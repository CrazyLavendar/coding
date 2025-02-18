#include<iostream>
int main(){
    int n = 150;
    int msb = 0;
    while(n  > 0){
        n = n >> 1;
        msb++;
        std::cout << n << std::endl;
    }
    std::cout << msb << std::endl;
    n = 150;
    std::cout << ceil(log2(n)) << std::endl;
    return 0;
}