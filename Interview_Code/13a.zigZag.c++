/*
You are given the root of a binary tree.
Return the zigzag level order traversal of its nodes’ values
(i.e., left → right for level 0, right → left for level 1, alternating for each level).
Example
Input Tree:
        1
       / \
      2   3
     /  \     \
    4   5   6
Output
[
  [1],
  [3, 2],
  [4, 5, 6]
]
*/

#include<iostream>
#include<vector>

using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
};

int oldheight = -1;

void traversal(Node* root, int h, vector<vector<int>>& res){
    if(root ==NULL)
    return;

    // cout << root->val << "  " << h << endl;
    if (oldheight < h){
        oldheight++;
        vector<int> temp;
        res.push_back(temp);
    }
    if (h % 2 == 0){
        res[h].push_back(root->val);
    }
    else{
        res[h].insert(res[h].begin(), root->val);
    }
    traversal(root->left, h + 1, res);
    
    traversal(root->right, h + 1, res);
}

vector<vector<int>> zigZag(Node* root){
    vector<vector<int>> res;
    traversal (root, 0, res);
    return res;
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
    vector<vector<int>> res = zigZag(root);

    for(auto row : res){
        for(int x : row){
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}