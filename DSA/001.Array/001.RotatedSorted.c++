#include<iostream>
using namespace std;

int pivot(int *arr, int start, int end){


    int mid = (start + end) /2;

    if(arr[start] <= arr[mid] && arr[mid] <= arr[end]){ // already sorted
        return start;
    }
    else if(arr[mid] > arr[mid+1]){
        return mid+1;
    }
    else if(arr[start] > arr[mid])
        pivot(arr,  start , mid);
    else 
        pivot(arr, mid, end);
    
    
    // return -1;
}

int main(){

    int arr[] = {1,2,3,4,5,6};

    cout << pivot(arr, 0 , 5);

    
    return 0;
}