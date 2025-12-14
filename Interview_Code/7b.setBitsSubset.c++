/*
Q2. Count Subsets With Odd Bitwise-OR Parity
Given an array of positive integers arr, 
return the number of non-empty subsets whose bitwise OR result contains an odd number of set bits.

1.  y
10. y
11. n
100 y
101 n
110 n
111 y


*/

#include<iostream>
#include<vector>

using namespace std;

bool oddSetBit(int n){
    int count = 0;
    while(n > 0){
        if(n & 1) count++;
        n >>= 1; 
    }
    return (count % 2);
}

int Solution(vector<int>& arr){
    int n = arr.size();
    int curr = 0;
    int res = 0;
    vector<int> prefixOR;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            curr = 0;
            for(int k = i; k <=j; k++){
                curr ^= arr[j];
            }
            if (oddSetBit(curr)) res++;
        }
    }
    return res;
}

int main(){
    vector<int> arr = {1, 2, 3};
    cout << Solution(arr) << endl;

    return 0;
}