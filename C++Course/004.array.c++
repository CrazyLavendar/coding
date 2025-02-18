#include<iostream>
using namespace std;
const int size_ = 2;
void print(int *arr, int n ){
    cout << sizeof(arr) << endl;
};

void print2(int arr[size_][size_], int x, int y ){
    cout << sizeof(arr) << endl;
};

int main(){
    
    int arr[] = {1,2,3,4,5};
    cout << arr << endl;
    cout << (arr + 1) << endl;
    cout << (arr + 2) << endl;
        cout << *arr << endl;
    cout << *(arr + 1) << endl;
    cout << *(arr + 2) << endl;
    int *p = arr;
    cout << sizeof(arr) << endl;
    print(arr,(sizeof(arr)/sizeof(int)));

    int arr2[size_][size_] = { {1,2} , {3,4}};

    cout << sizeof(arr2) << endl;
    print2(arr2,(sizeof(arr2)/sizeof(arr2[0])),(sizeof(arr2[0])/sizeof(int)) );

    return 0;
}