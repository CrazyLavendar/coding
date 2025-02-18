#include<iostream>
using namespace std;


void change1(int &x){
    x = 11;
}

void change2(int *x){
    *x = 12;
}

void change3(int *x){
    int y = 50;
    x = &y;
}

void change4(int *x){
    int y1 = 50;
    int* y2 = &y1;
    x = y2;
}

void change5(int *x){
    int* y2 = x;
    *y2 = 52;
}

int main(){
    int x = 10;
    cout << x << endl;

    change1(x);
    cout << x << endl;

    change2(&x);
    cout << x << endl;

    change3(&x);
    cout << x << endl;

    change4(&x);
    cout << x << endl;

    change5(&x);
    cout << x << endl;


    return 0;
};