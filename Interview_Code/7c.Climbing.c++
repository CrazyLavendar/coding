/*
Q1. Minimum Jumps With Forbidden Indexes
You are given an integer array nums, where nums[i] represents the maximum jump length from index i, and a set forbidden containing indexes you are not allowed to land on.
Return the minimum number of jumps needed to reach the last index, or -1 if it is impossible.
*/

#include<iostream>
#include<vector>
using namespace std;

vector<int> dp;
int rec(vector<int>& nums, int pos){
if(pos >= nums.size() - 1) return 0;    // when we reach end, return 0 denoting no more jumps required
if(dp[pos] != 1e9) return dp[pos];    // number of jumps from pos to end is already calculated, so just return it
// explore all possible jump sizes from current position. Store & return min jumps required
for(int j = 1; j <= nums[pos]; j++)
    dp[pos] = min(dp[pos], 1 + rec(nums, pos + j));        
return dp[pos];
}

int minimumJumps(vector<int>& arr, vector<int>& f){
    int n = arr.size();
    for(int x : f){
        if(x < n)
            arr[x] = 0; // invalidate the jumps
    }
    dp.resize(n, 1e9);

    int ans = rec(arr, 0);

    return ans == 1e9 ? -1 : ans;
}

int main(){
    vector<int> arr = {1, 4, 3, 2, 6, 7};
    vector<int> forbidden = {2,4}; // 2nd index shouldn't jump
    cout << minimumJumps(arr, forbidden);
    return 0;
}