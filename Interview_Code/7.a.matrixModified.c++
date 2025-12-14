/*
Question
You are given an m × n matrix.
If any cell in the matrix is 0, set its entire row and column to 0.
Return the modified matrix.
Example
Input:
[
  [{, 2, 3],
  [{, 0, 6],
  [{, 8, 9]
]

Output:
[
  [1, 0, 3],
  [0, 0, 0],
  [7, 0, 9]
]
*/
#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

void Solution(vector<vector<int>>& matrix){
    unordered_set<int> row, col;
    int m = matrix.size(), n = matrix[0].size();
    for(int i = 0; i < m; i++){
        for(int j= 0; j <n; j++){
            if(matrix[i][j] == 0){
                row.insert(i);
                col.insert(j);
            }
        }
    }

    // each row make col = 0
    for(int r : row){
        for(int i = 0; i < n; i++){
            matrix[r][i] = 0;
        }
    }

    // each col make row = 0
    for(int c : col){
        for(int i = 0; i < m; i++){
            matrix[i][c] = 0;
        }
    }

}

int main(){

    vector<vector<int>> matrix = { 
  {1, 2, 3},
  {4, 0, 6},
  {7, 8, 9}};

   Solution(matrix);

   for(auto& row : matrix){
    for(auto& x : row)
        cout << x << " " ;
    cout << endl;
   }



    return 0;
}