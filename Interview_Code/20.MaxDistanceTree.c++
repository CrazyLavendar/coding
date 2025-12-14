/*
Question

You are given the root of a binary tree.
Each node contains an integer value (can be negative).

A path is defined as any sequence of nodes where:
	•	Each adjacent pair has a parent-child relationship
	•	The path can start and end at any node
	•	The path must contain at least one node
	•	Nodes cannot be reused

Tasks
	1.	Return the maximum path sum
	2.	Return the actual path that produces this maximum sum

⸻

Example

        -10
        /  \
       9   20
          /  \
         15   7

Output

Max Path Sum = 42
Path = [15 → 20 → 7]


⸻

Constraints
	•	Number of nodes ≤ 10⁶
	•	Node values ∈ [-1000, 1000]
	•	Must run in O(n) time
	•	Extra space allowed only for recursion stack

⸻

Follow-ups Interviewers Love
	1.	Why can’t this be solved using simple root-to-leaf DP?
[Ans]: Max value, need not include the root value. Path can be from sub tree as well.
	2.	How do you handle all-negative trees?
[Ans]: Ans is min negative value of node from tree.
Handled with logic "res = max(res, mid);"
	3.	How would you modify this to return multiple max paths?
[Ans]:
Need to store stack recursion path in the same solution. 
return format : vector<vector<Node*>>
	4.	How would you do this iteratively?
[Ans]: With BFS, it could be complex. Time complexity could be greater than O(n)
For each node, left max , right max needs to be retrived.

	5.	What changes if the tree is n-ary?
[Ans]: Instead of left , right. For(loop of 1->n) should be the logic

*/

#include<iostream>

using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
};

int traversal(Node* root, int& res){

    if(root == NULL){
        return 0;
    }

    int left = traversal(root->left, res);
    int right = traversal(root->right, res);
    int mid = root->val;

    // res = max(res, curr);
    res = max(res, mid);
    res = max(res, left + mid),
    res = max(res, mid + right);
    res = max(res, left + mid + right);

    return max(left + mid, mid + right);
}

int maxSum(Node* root){
    int res = -1000000000;
    traversal(root, res);
    return res;
}

int main(){

    Node* head = new Node();
    head->val = -10;
    head->left = new Node();
    head->left->val = 9;
    head->right = new Node();
    head->right->val = 20;
    head->right->left = new Node();
    head->right->left->val = 15;
    head->right->right = new Node();
    head->right->right->val = 7;
    cout << maxSum(head) << endl;


    return 0;

}