#include<stdio.h>

int* val(){
    static int x = 5;
    static int* p = &x;
    return p;
}

int main(void){
    int x = *val();
    printf("%d", x);
    return 0;
}