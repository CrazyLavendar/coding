/*
Question

You are given the root of a Binary Search Tree (BST) and an integer k.

Return the k-th smallest element in the BST.

⸻

Example

Input:
       5
      / \
     3   6
    / \
   2   4
  /
 1

k = 3

Output:
3


⸻

Constraints
	•	Number of nodes ≤ 10⁵
	•	1 ≤ k ≤ number of nodes
	•	BST property holds
	•	Target time: O(n) (or better with optimization)
	•	Extra space: recursion stack allowed

*/



#include<iostream>

struct Node{
    int val;
    Node* left;
    Node* right;
};


void smallestKthElement(Node* root, int& res, int& k){

    if(root == NULL || k == 0){
        return;
    }

    smallestKthElement(root->left, res, k);
    // cout << res << " " << root->val
    k--;
    if(k == 0){
        res = root->val;
        return;
    }
    smallestKthElement(root->right, res, k);
}

using namespace std;

int main(){

    Node* root = new Node();
    root->val = 5;
    root->left = new Node();
    root->left->val = 3;
    root->right = new Node();
    root->right->val = 6;
    root->left->left = new Node();
    root->left->left->val = 2;
    root->left->right = new Node();
    root->left->right->val = 4;
    root->left->left->left = new Node();
    root->left->left->left->val = 1;

    // int len = 0;
    // findlen(root, len);
    // cout << len << endl;
    int res = -1;
    int k = 3;
    smallestKthElement(root, res, k);
    cout << res << endl;

    res = -1;
    k = 7;
    smallestKthElement(root, res, k);
    cout << res << endl;

    res = -1;
    k = 5;
    smallestKthElement(root, res, k);
    cout << res << endl;

    return 0;
}

