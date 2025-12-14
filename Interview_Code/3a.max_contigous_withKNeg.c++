/*
You are given an integer array nums and an integer k.
Return the maximum possible sum of any contiguous subarray that contains at most k negative numbers.
Example:
nums = [4, -1, 2, -6, 3, -1, 5], k = 2  
Output: 8  
(One optimal subarray is [4, -1, 2, -6, 3, -1, 5] → contains exactly 2 negatives)
*/

#include<iostream>
#include<limits.h>
#include<vector>
#include<queue>

using namespace std;



int max_contigous_k_neg(vector<int>& arr, int k){

    int n = arr.size();
    int sum = 0;
    int res = INT_MIN;
    vector<int> prefixSum;
    for(int i =0; i< n; i++){
        sum += arr[i];
        prefixSum.push_back(sum);
    }

    sum = 0;
    
    queue<int> q;
    for(int i =0; i< n; i++){
        
        sum += arr[i];

        if(arr[i] < 0){
            if(q.size() < k){
                q.push(i);
            }
            else{
                int last_neg_ind = q.front();
                sum = prefixSum[i] - prefixSum[last_neg_ind];
                q.pop();
                q.push(i);
            }
        }


        res = max(res, sum);

        if(sum <= 0){
            sum = 0;
            // whatever it is. clear Q
            while (!q.empty()) {
                q.pop();
            }
        }
    }
    return res;

}

int main(){

    vector<int> arr = {4, -1, 2, -6, 3, -1, 5};
    cout << max_contigous_k_neg(arr, 2) << endl;

    arr = {2, -1, -1, 2, -1, 2};
    cout << max_contigous_k_neg(arr, 2) << endl;

    arr = {4, -1, 2, -6, 3, -1, 5};
    cout << max_contigous_k_neg(arr, 2) << endl;

    return 0;
}