#include <iostream>
 
using namespace std;


int* fun(){
    // with static
    // method 1
     static int arr[3] = {1,2,3};

    //without static
    // method 2
    // int *arr = static_cast<int*>(malloc(3 * sizeof(int)));
    // method 3 with new keyword
    // int *arr = new int[3];
    // *arr = 1;
    // *(arr + 1) = 2;
    // *(arr + 2) = 3;

       
    cout << sizeof(arr) << endl;


    return arr;
}

int main()
{

    int * arr = fun();

    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;

    // delete arr;

    return 0;
}