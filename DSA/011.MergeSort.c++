#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& src, int l1, int r1, int l2, int r2){
    
    int size = (r1 - l1  +1) + (r2 - l2  +1);

    int curr = 0;
    int start = l1;

    vector<int> des(size);

    while (l1 <= r1 && l2 <=r2){
        if(src[l1] < src[l2]){
            des[curr++] = src[l1++];
        }
        else{
            des[curr++] = src[l2++];
        }
    }

    while(l1 <= r1){
        des[curr++] = src[l1++];
    }

    while(l2 <= r2){
        des[curr++] = src[l2++];
    }

    for(int x : des)
        src[start++] = x;

}

void mergesortAlgo(vector<int>& src, int l, int r){

if (l == r) {
    return;
}
    int mid = (l + r)/2;

mergesortAlgo(src, l, mid);        // <-- FIX #2
mergesortAlgo(src, mid+1, r);      // <-- FIX #3
merge(src,l, mid, mid+1, r);
}

void mergesort(vector<int>& arr){
    int n = arr.size();
    mergesortAlgo(arr, 0, n-1);
}


int main(){

    vector<int> arr = {5, 2, 2, 1, 6, 10, -1};

    mergesort(arr);

    for(int& i : arr){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}