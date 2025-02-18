#include<iostream>
using namespace std;


void fun (int &x, int *y){
    x = x+1;
    *y = *y+1;
}

int main(){

    int i = 10;
    int *p = &i;
    int &r = i;

    cout << "address values of i, p , r  " <<  &i << " " << &p << "  " << &r << endl;

    r = 20;

    cout << " values of i, p , r  " <<  i << " " << *p << "  " << r << endl;

    i = 100 ; int j = 200;

    fun(i, &j);

    cout << " values of i, j , p , r  " <<  i << " " << j << " " << *p << "  " << r << endl;

}

