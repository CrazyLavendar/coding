
#include <iostream>
using namespace std;

void nonRepeat(int * arr, int n){
    int mask = 0;
    for(int i = 0; i< n ; i++){
        mask ^= * (arr+i); 
    }
    cout << mask << endl;
}

int main(){
    int n = 7;
    // int arr[7] = {1,1,2,2,3,4,4};

    int *arr = (int *) malloc(n * sizeof(int));
    *arr = 1; 
    *(arr + 1) = 1;
    *(arr + 2) = 2;
    *(arr + 3) = 2;
    *(arr + 4) = 3;
    *(arr + 5) = 4;
    *(arr + 6) = 4;

    nonRepeat(arr, n);
    delete arr;

    
    return 0;
}