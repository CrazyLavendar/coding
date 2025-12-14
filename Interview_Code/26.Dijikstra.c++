/*
Question

You are given a weighted graph with non-negative edge weights.

Implement Dijkstra’s algorithm to find the shortest distance from a given source node to all other nodes.

Requirements
	•	Graph can be directed or undirected
	•	Edge weights are non-negative
	•	Use an efficient data structure to achieve optimal time complexity

Follow-ups Interviewers Commonly Ask
	1.	Why does Dijkstra fail with negative edge weights?
[Ans]: Dijiktra Algorithm may or mayn't give correct answer for negative edge weights. 
It is a greedy solution, once the node popped out from queue, recalculation wont be possible.
Negative edges may form cycle, and it can  be never ending loop.

	2.	What is the time complexity using:
[Ans]: form adj List + Push Edge in Queue and collect result for each edge. --> T.C = O (E + ElogV )
	•	Binary heap (priority queue)?
[Ans]:  O (E + ElogV )
	•	Adjacency matrix?
[Ans]: V^2 * LogV
	3.	How do you modify Dijkstra to return the actual shortest path, not just distance?
[Ans]: Store the visited vertices during heap pop
	4.	How is Dijkstra different from BFS?
[Ans]: Dijikstra uses priority queue, where as BFS uses genric queue structure.
	5.	When would you prefer Bellman–Ford over Dijkstra?
[Ans]: When distance don't have negative edges.
	6.	How does Dijkstra change for very large graphs (10⁶ nodes)?
[Ans]: Time complexity can increase., More time will take to compute single source shortest path
	7.	Can Dijkstra be made lock-free or parallel?
[Ans]: Dijikstra is for single running thread solution.
lock-free and parallelism is not helpful
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Node{
    int w; // weight
    int v; // next vertex
};

struct Compare{
    bool operator () (Node& a, Node& b){
        return a.w > b.w;
    }
};



class Solution {
  public:
    vector<int> dijkstra(int N, vector<vector<int>> &edges, int src) { // edges -> {u, v, distance}
        // Code here
        vector<vector<pair<int, int>>> adj(N);
        for(auto& e : edges){
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]}); // If directed edges, this can be removed
        }
        
        vector<int> res(N, 1e9); // assuming distance wont reach 1e9
        vector<int> vis(N);
        
        priority_queue<Node, vector<Node>, Compare> pq;
        pq.push({0, src});
        
        while(!pq.empty()){
            Node m = pq.top();
            // cout << m.w << " " << m.v << endl;
            pq.pop();
            
            if(res[m.v] > m.w)
                res[m.v] = m.w;
            
            if (vis[m.v] == 0){
                vis[m.v] = 1;
            }
            else{
                continue;
            }
            
            for(auto& p : adj[m.v]){
                Node n;
                n.v = p.first;
                n.w = p.second + m.w;
                if (vis[n.v] == 0)
                    pq.push(n);
            }
            
        }
        
        return res;
    }
};


/**
 * 
 * 
 
 00  01 02 03

 10  11 12 13

 * 
 */