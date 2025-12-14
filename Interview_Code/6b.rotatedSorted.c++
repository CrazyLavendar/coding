/*
Question
Given a rotated sorted array nums which may contain duplicates, and a target value t, return:
any valid index where nums[index] == t
return -1 if not present
Examples:
Input:
nums = [4,5,6,6,7,0,1,2,2]
t = 6
Output: 2   (or 3)

Input:
nums = [2,5,6,0,0,1,2], t = 3
Output: -1
*/

#include<iostream>
#include<vector>

using namespace std;

int getPivot(vector<int>& nums){
    int mid=0;
    int lo = 0, hi = nums.size() - 1;
    while(lo<hi){
        mid = (lo+hi)/2;
        // if value at mid index is equal to value at end index
        // reduce end index to left by 1
        // means we have to move left nums[hi-1] > nums[hi]
        // nums = [2,5,6,0,0,1,2] -- 6 > 0 -- return hi -- as it is separation point
        if(nums[mid]==nums[hi]){
            if(hi>0 && nums[hi-1]>nums[hi])return hi; //[1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1]
            hi = hi-1;
        } 
        else if(nums[mid] > nums[hi]){
            lo = mid+1;
        }
        else hi = mid;
    }
    return lo;
}

int bs(vector<int>& arr, int l , int r, int t){
    cout << l << " bs " << r << " " << t << endl;
    while(l <= r){
        int mid = l + (r - l) /2;
        if(arr[mid] == t){
            return mid;
        }
        else if(arr[mid] > t){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return -1;
}

int Solution(vector<int>& arr, int t){
    int pivot = getPivot(arr);
    int n = arr.size();

    // cout << " pivot " << pivot <<  " size " << n << endl;

    int res = -1;
    
    res =  bs(arr, pivot, n-1, t);

    if (res == -1)
    res = bs(arr, 0 , pivot -1, t);


    return res;

}

int main(){

    vector<int> arr;
    arr = {4,5,6,6,7,0,1,2,2};
    cout << "expect idx 2 or 3 -> got: " << Solution(arr, 6) << '\n';

    arr = {2,5,6,0,0,1,2};
    cout << "expect -1 -> got: " << Solution(arr, 3) << '\n';

    // failing examples from original code:
    arr = {1,2,3};
    cout << "expect 2 -> got: " << Solution(arr, 3) << '\n';

    arr = {2,3,4,5,1}; // rotated, only last element is 1
    cout << "expect 4 -> got: " << Solution(arr, 1) << '\n';

    // duplicates edgecases
    arr = {2,2,2,3,2,2};
    cout << "search 3 -> got: " << Solution(arr, 3) << '\n';
    return 0;
}