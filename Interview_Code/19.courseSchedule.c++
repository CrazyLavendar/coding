/*
Course Schedule with Recovery Order + Validation

You are given:
	•	An integer n representing the number of courses labeled 0 to n-1
	•	A list of prerequisite pairs prerequisites, where
prerequisites[i] = [a, b] means course b must be completed before course a

Tasks
	1.	Determine whether it is possible to finish all courses
	2.	If possible, return one valid order of courses
	3.	If not possible, return an empty list
	4.	Detect and report cycles

Constraints
	•	1 ≤ n ≤ 10⁵
	•	0 ≤ prerequisites.length ≤ 2 × 10⁵
	•	Must run in O(V + E)
	•	Use topological sort

⸻

Example 1

Input:
n = 4
prerequisites = [[1,0],[2,0],[3,1],[3,2]]

Output:
[0,2,1,3]   // or [0,1,2,3]

Example 2 (Cycle)

Input:
n = 2
prerequisites = [[0,1],[1,0]]

Output:
[]


⸻

Follow-ups Interviewers Ask
	1.	Why does a cycle make completion impossible?
[Ans] : It creates a cycling dedpendency for courses. If A-> B, B->A forms cycle. Both cannot be completed.
	2.	BFS (Kahn’s algorithm) vs DFS — which is safer for large graphs?
[Ans]: BFS can be better, DFS may cause stack overflow for very large graph;
	3.	How would you modify this to return the minimum number of semesters?
[Ans] : All dependent course present in DFS stack can be made for one semester. Semesters can be planned accordingly.
	4.	How does this problem relate to Alien Dictionary?
[Ans] : Both expects to do topological sort to find ordering.
	5.	What changes if multiple valid orders exist?
[Ans] : DFS can be started wih different course and multiple orders can be found,
Alternatively, with BFS if multiple courses are in queue at a time, different decision can be taken to get different orders.

*/
#include<iostream>
#include<vector>

using namespace std;

bool cycle = false;

void dfs(vector<vector<int>>& adj, int n, int node, vector<int>& res, vector<int>& vis)
{
   if(cycle)
      return;

   if(vis[node] == 1)
   {
       cycle = true;
       return;
   }
   else if (vis[node] == 2)
   {
      return;
   }

   vis[node] = 1;

 
   for(int v : adj[node])
   {
	dfs(adj, n, v, res, vis);
   }

   res.push_back(node);

   vis[node] = 2;
}

void schedule(vector<vector<int>>& prerequisites, int n, vector<int>& res)
{
   vector<vector<int>> adj(n);
   for(auto& edge : prerequisites)
   {
	adj[edge[0]].push_back(edge[1]);
   }
   vector<int> vis(n);
   for(int i = 0; i < n; i++)
   {
	dfs(adj, n, i, res, vis);
   }

   if (cycle)
   	res =  {};
   
} 

int main(){

   vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
   vector<int> res;
   schedule(prerequisites, 4, res);

  for(int x : res)
  {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}


