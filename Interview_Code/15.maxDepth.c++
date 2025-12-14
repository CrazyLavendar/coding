/*
You are given the root of a binary tree.
Return the maximum depth of the tree.

The maximum depth is the number of nodes along the longest path from the root down to the farthest leaf.

Constraints
	•	Tree can have up to 10⁶ nodes
	•	Tree may be skewed (linked-list-like)

Follow-ups (commonly asked)
	1.	How would you solve this iteratively (no recursion)?
[Ans] : Using level order traversal (BFS). Each level , I will add nodes from left/right in queue.
I will pop. Number of levels will be answer
	2.	How do you avoid stack overflow for very deep trees?
[Ans] :  queue size will be minimal for skewed trees, Using level order traversal (BFS) approach stack overflow can be eliminated
	3.	Can you compute max depth using BFS?
    Yes. Nodes can be added in queues for each level.
	4.	What changes if the tree is n-ary instead of binary?
Currently max is obtained with    
    int left = 1 + maxDepth(root->left);
    int right = 1 + maxDepth(root->right);
With n-ary, for loop can be run (i = 0 to i<n)
    max can be calculated for the loop instead of left and right.
*/

#include<iostream>
#include<vector>

using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
};


int maxDepth(Node* root){
    if (root == NULL)
        return 0;
    int left = 1 + maxDepth(root->left);
    int right = 1 + maxDepth(root->right);
    return max(left, right);
}

int main(){

    Node* root = new Node();
    root->val = 1;
    root->left = new Node();
    root->left->val = 2;
    root->right = new Node();
    root->right->val = 3;
    root->left->left = new Node();
    root->left->left->val = 4;
    root->left->right = new Node();
    root->left->right->val = 5;
    root->right->left = new Node();
    root->right->left->val = 6;
    cout << maxDepth(root) << endl;


    return 0;
}