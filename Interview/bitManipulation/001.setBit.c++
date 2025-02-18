#include<iostream>
#include<stdio.h>
int main(){

    int start = 4, end = 8;

    int x = 0xAAAA;
            int mask = 1;
    for(int i = start ; i < end ; i++){

        if(i == start){
            mask = mask << start;
            std::cout << mask << std::endl;
        }

        // x |= mask; // set all to one
        x ^= mask; // toggle 
        mask = mask << 1;
    }

    std::cout << std::hex << x << std::endl;
    printf("%x\n", x);


    return 0;
}