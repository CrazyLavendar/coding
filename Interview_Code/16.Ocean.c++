/*
You are given an m × n matrix of heights representing an island.
The Pacific Ocean touches the left and top edges, and the Atlantic Ocean touches the right and bottom edges.

Water can flow from a cell to another only if the destination cell has height ≤ current cell.

Return all coordinates from which water can flow to both the Pacific and Atlantic oceans.

Constraints
	•	1 ≤ m, n ≤ 200
	•	Must run in O(m × n)
	•	No extra space proportional to the number of paths

Follow-ups (commonly asked)
	1.	Why do we start DFS/BFS from the ocean borders instead of each cell?
     [ans : ] Can be started from each cell also, then time complexity will be (m * n * m * n);
	2.	How would you solve this using BFS instead of DFS?
     [ans : ] Add each (i, j) in queue. Traverse to next nearest row/col with similar condition check and visited check.
	3.	What changes if diagonal flow is allowed?
    [ans : ] Use "int dirs[8][2] = {{-1,0}, {0,-1}, {1, 0}, {0,1}, {-1,1}, {1,-1}, {-1,-1}, {1,1}}; "
	4.	Can this be parallelized?
     [ans : ]Yes. Currently mark=1 :: Pacific, mark=2::atlantic, mark=3/4= common. 
    pacific and atlantic can be parallelized. With union find we can get common coordinates.
*/

#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int dirs[4][2] = {{-1,0}, {0,-1}, {1, 0}, {0, 1}};

void dfs(vector<vector<int>>& islands, vector<vector<int>>& vis, int i, int j, int m, int n, int mark, int prevHeight){
    if(i < 0 || j < 0 || i == m || j == n || vis[i][j] == mark  || vis[i][j] == 4)
        return;

    if (islands[i][j] < prevHeight){
        return;
    }

    if(vis[i][j] == 0){
        vis[i][j] = mark;
    }
    else if (vis[i][j] == 3){
        vis[i][j] = 4; // again revisit
    }
    else{
        vis[i][j] = 3; // one time visit
        return;
    }

    for(auto dir : dirs){
        dfs(islands, vis, i + dir[0], j + dir[1], m, n , mark, islands[i][j]);
    }
}

vector<vector<int>> commonFlow(vector<vector<int>>& islands){
    int m = islands.size(), n = islands[0].size();
    vector<vector<int>> vis(m, vector<int>(n, 0));
    // vis[0][n-1] = 3;
    // vis[m-1][0] = 3;

    for(int col = 0; col < n; col++){
        dfs(islands, vis, 0, col, m, n, 1, -1);
    }
    for(int row = 0; row < m; row++){
        dfs(islands, vis, row, 0, m, n, 1, -1);
    }
    for(int col = 0; col < n; col++){
        dfs(islands, vis, m-1, col, m, n, 2, -1);
    }
    for(int row = 0; row < m; row++){
        dfs(islands, vis, row, n-1, m, n, 2, -1);
    }
    
    vector<vector<int>> res;

    for(int i = 0 ; i < m ; i++){
        for(int j = 0; j < n; j++){
            if(vis[i][j] >= 3){
                res.push_back({i, j});
            }
        }
    }

    return res;

}

int main(){

    vector<vector<int>> islands = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};
    vector<vector<int>> res = commonFlow(islands);

    for(auto row : res){
        cout << row[0] << " " << row[1] << endl;
    }

    return 0;
}