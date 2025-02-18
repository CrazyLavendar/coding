#include<iostream>
using namespace std;

//Stack or Heap
int* pointerInt(){
    int xVal = 100;
    int *x;
    x = &xVal; // stack
    cout << "from pointerFun : " << x << endl;
    cout << "from pointerFun x vak: " << *x << endl;
    return x;
}

int* pointerHEAPInt(){
    int *x = new int;
    *x = 555; // heap
    cout << "from pointerFun : " << x << endl;
    cout << "from pointerFun x vak: " << *x << endl;
    return x;
}



int main(){
    int *x;

    if(true){
        int yVal = 200; // stack
        int *y;
        y = &yVal;
        cout << "from if : " << y << endl;
        x = y;
    }

    cout << "from main : " << x << endl; 
    cout << "from main value: " << *x << endl; //??? donnt know

    x = pointerInt();
    cout << "from main : " << x << endl;
    cout << "from main value: " << *x << endl; //??? donnt know 

    x = pointerHEAPInt();
    cout << "from main : " << x << endl;
    cout << "from main value: " << *x << endl; //We know

    delete x;


    int *arr = new int[5];


    if(true){
        int *arr2 = arr;
        arr2[20] = 222;
    }
    
    cout <<  arr[8] << endl;
    delete[] arr;
    

    return 0;
}