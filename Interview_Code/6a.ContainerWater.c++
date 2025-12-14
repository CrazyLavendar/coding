/*

You are given an array height[] where each element represents a vertical line on the x-axis.
Return two indices (i, j) such that the container formed between them holds the maximum amount of water, AND return that maximum water volume.
Example:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: indices = (1, 8), max_water = 49
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> Solution(vector<int>& heights){
    vector<int> res;
    int maxArea = 0, maxAreaL = -1, maxAreaR = -1;
    int l = 0, r = heights.size() - 1;
    while(l < r)
    {
        int minheight = min(heights[l] , heights[r]);
        if (maxArea < minheight * (r - l)){
            maxArea = minheight * (r - l);
            maxAreaL = l;
            maxAreaR = r;
        }

        if(heights[l] < heights[r])
            l++;
        else
            r--;
    }
    // cout << l << " " << r << " " << maxArea << endl;

    return {maxAreaL, maxAreaR, maxArea};
}

int main(){
    vector<int> arr = {1,8,6,2,5,4,8,3,7};
    vector<int> res = Solution(arr);
    cout << "indices " <<  res[0] << " , " << res [1] << " max_water : " << res[2] << endl;


    arr = {1, 1, 1};
    res = Solution(arr);
    cout << "indices " <<  res[0] << " , " << res [1] << " max_water : " << res[2] << endl;
    return 0;
}
