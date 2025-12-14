/*
You are given:
A list of non-overlapping, sorted intervals intervals[i] = [start, end]
A new interval newInt = [a, b]
Insert newInt into the list and then merge all overlapping intervals.
Return the final merged list.
Example
intervals = [[1, 3], [6, 9]]
newInt = [2, 5]

Output:
[[1, 5], [6, 9]]
Follow-up (asked at Google)
What is the time complexity if intervals are stored:
(a) as an array
Answer: Insertion. O(n), Merge : O(n)
(b) as a balanced BST
Answer: Insertion. O(logn), Merge : O(n)
(c) in a skip list
Answer: Insertion. O(logN), Merge : O(n)
Which is optimal for frequent insert + merge operations?
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int binarySearch(vector<vector<int>>& arr, vector<int>& intrvl){

    // int left = 0, right = arr.size() - 1;
    // int res = -1;

    // while(left < right){
    //     int mid = (left + right) / 2;
    //     if (arr[mid][0] == intrvl[0]){
    //         res = mid;
    //         break;
    //     }
    //     if(arr[mid][0] <= intrvl[0]){
    //         res = mid + 1;
    //         left = mid + 1;
    //     }
    //     else{
    //         res = mid - 1;
    //         right = mid -1;
    //     }
    //     cout << "res : " << res << endl;
    // }

    // return res;

    int l=0, r=arr.size(); // note r = size
    while (l < r) {
        int m = l + (r - l)/2;
        if (arr[m][0] < intrvl[0]) l = m+1;
        else r = m;
    }
    return l; // insertion index
}
vector<vector<int>> merge(vector<vector<int>>& arr){
    // sort(arr.begin(), arr.end(), [&](auto& a, auto b){
    // if(a[0] == b[0])
    //     return a[1] < b[1];
    // else
    //     return a[0] < b[0];
    // });

    vector<vector<int>> res;
    int i = 1;
    int start = arr[0][0], end = arr[0][1];
    for(; i < arr.size(); i++){
        auto& curr = arr[i];
        if(start == curr[0]){
            if(curr[1] == end || curr[1] <= end){
                // continue;
            }
            if(curr[1] > end){
                end = curr[1];
                // continue;
            }
            // cout << " should not execute 1 " << endl;
        }
        // inner 
        else if(curr[1] <= end){
            // do nothing
            // continue;
        }
        else if(end >= curr[0] && end <= curr[1] ){
            end = curr[1];
        }
        // completely diff
        else if(end < curr[0]){
            res.push_back({start, end});
            start = curr[0];
            end   = curr[1];
        }
        else{
            // cout << " should not execute 2" << endl;
        }
        // cout << "start : "<<  start << " end:  " << end << endl;
    }
    res.push_back({start, end});
    return res;
}

vector<vector<int>>& mergeIntervals(vector<vector<int>>& arr, vector<int>& intrvl){
    int pivot = binarySearch(arr, intrvl);
    arr.insert(arr.begin() + pivot, intrvl);
    arr = merge(arr);
    return arr;
}

int main(){
    vector<vector<int>> arr = {{1, 3}, {6, 9}};
    vector<int> intevl = {2,5};
    mergeIntervals(arr, intevl);

    for(auto x : arr){
        cout <<  x[0] << " " << x[1]  << ",  ";
    }
    cout << endl;

    return 0;
}