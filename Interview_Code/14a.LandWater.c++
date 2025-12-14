/*
[16/12/2025, 6:47:53 PM] Swetha Vimal: Q1
[16/12/2025, 6:47:55 PM] Swetha Vimal: Question
You are given a 2D grid of characters '1' (land) and '0' (water).
An island is formed by connecting adjacent lands horizontally or vertically.
Write a function that returns the number of islands in the grid.
Constraints
Grid size can be up to 2000 × 2000
You must modify the grid in place or use O(1) extra space (excluding recursion stack)
Follow-ups (asked often)
How would your solution change if diagonal connections were allowed?
[ans : ] Use "int dirs[4][2] = {{-1,0}, {0,-1}, {1, 0}, {0,1}, {-1,1}, {1,-1}, {-1,-1}, {1,1}}; "
Can you solve it iteratively (no recursion)?
[ans : ] Use BFS and queue to track
How would you parallelize island counting?
Yes, we can use threads.
*/

#include<iostream>
#include<vector>

using namespace std;

int dirs[4][2] = {{-1,0}, {0,-1}, {1, 0}, {0,1}};

void dfs(vector<vector<int>>& grid, int i, int j, int m, int n){
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0 || grid[i][j] == 2)
        return;

    grid[i][j] = 2;

    for(auto& dir : dirs){
        dfs(grid, dir[0] + i, dir[1] + j, m, n);
    }
}

int numIslands(vector<vector<int>>& grid){
    if(grid.size() == 0 || grid[0].size() == 0)
        return 0;
    int m = grid.size(), n = grid[0].size();
    int islands = 0;
    for(int i = 0; i < m ; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 1){
                islands++;
                dfs(grid, i , j, m, n);
            }
        }
    }
    return islands;
}

int main(){
    vector<vector<int>> grid = {
        {1,0,1,1},
        {1,0,1,1},
        {0,0,0,0},
        {1,1,1,1}
    };
    cout << numIslands(grid) << endl;
}