#include<iostream>
using namespace std;

int conditionalSum(int a, int b, int (*ptr)(int)){ // --> callback function
    a = (*ptr)(a);
    b = (*ptr)(b);
    return a+b;
}

int square(int x){
    return x*x;
}
int cube(int x){
    return x*x*x;
}



int main(){
    cout << conditionalSum(2,3,&square) << endl; 
    cout << conditionalSum(2,3,&cube) << endl; 

    return 0;
}
