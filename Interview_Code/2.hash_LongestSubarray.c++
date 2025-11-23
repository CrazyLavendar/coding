/*
Find the Length of the Longest Subarray With Sum Divisible by K
You are given an integer array nums and an integer k.
Return the length of the longest contiguous subarray whose sum is divisible by k.
Example
Input: nums = [2, 3, -1, 4, 2], k = 3
Output: 3
*/

#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int LongestSubarray(vector<int>& arr, int k){
    int res = 0;
    int size = arr.size();
    unordered_map<int, int> map_;
    map_[0] = -1;
    int curr = 0;
    for(int i = 0 ; i < size; i++){
        curr += arr[i];
        int mod_k = ((curr % k) + k) % k;
        if(map_.count(mod_k) > 0){
            res = max(res, i - map_[mod_k]);
        }
        else{
            map_[mod_k] = i;
        }
    }
    return res;
}

int main()
{
    vector<int> q = {2, 3, -1, 4, 2};
    cout << LongestSubarray(q, 3) << endl;

    q = {3,3,3,3,1,2,3,1};
    cout << LongestSubarray(q, 3) << endl;

    q = {3,3,3,3,1,2,3,1, 1};
    cout << LongestSubarray(q, 2) << endl;

    q = {1,1,1,1};
    cout << LongestSubarray(q, 5) << endl;

    q = {2, 3, -5, 2, 3};
    cout << LongestSubarray(q, 3) << endl;

    return 0;
}