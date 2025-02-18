#include<stdio.h>

int main(){


    struct {
    char a;
    char b;
    int i;
    char c;

    }__attribute__((packed)) something;

    
    printf("%lu", sizeof(something));
    return 0;
}
