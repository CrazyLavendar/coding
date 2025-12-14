/*

Lowest Common Ancestor with Parent Pointers

Question
You are given two nodes p and q in a binary tree.
Each node has a pointer to its parent.

Find the Lowest Common Ancestor (LCA) of p and q.

Constraints
	•	Tree is not necessarily a BST
	•	You must use O(1) extra space
	•	Tree height can be large

Solution : lowestCommonAncestor(p ,q);

Follow-ups
	1.	How would this change if parent pointers were not available?
[Ans : ] If parent pointer not available, root Node must be provided and can be solved with only "lowestCommonAncestorWithRoot"
	2.	Can you solve it without computing depths?
[Ans : ] Current solution is already without computing depths
	3.	What if the tree is extremely skewed?
[Ans : ] Either p (or) q will be the answer in this case. Check p's child node is q (or) Check q's child node is p
*/

#include <iostream>
using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode *parent; // Root's parent is NULL
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestorWithRoot(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        if (root == NULL){
            return NULL;
        }
        else if (root == p){
            return root;
        }
        else if(root == q){
            return root;
        }
        else{
            TreeNode* left = lowestCommonAncestorWithRoot(root->left, p, q);
            TreeNode* right = lowestCommonAncestorWithRoot(root->right, p, q);

            if (left == NULL){
                return right;
            }
            else if(right == NULL){
                return left;
            }
            else{
                return root;
            }
        }
    }


    TreeNode*  findRoot(TreeNode* root){
        if(root == NULL){
            return root;
        }
        else{
            return findRoot(root->parent);
        }

    }


    TreeNode* lowestCommonAncestor(TreeNode* p, TreeNode* q) {
        TreeNode* root = findRoot(p); // p and q must have same root., else input is wrong
        return lowestCommonAncestorWithRoot(root, p, q);
    }
};
