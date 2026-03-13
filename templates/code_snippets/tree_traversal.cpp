
/*
树遍历代码片段
包含：前序、中序、后序
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void preorder(TreeNode* node, vector<int>& out) {
    if (!node) return;
    out.push_back(node->val);
    preorder(node->left, out);
    preorder(node->right, out);
}

void inorder(TreeNode* node, vector<int>& out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->val);
    inorder(node->right, out);
}

void postorder(TreeNode* node, vector<int>& out) {
    if (!node) return;
    postorder(node->left, out);
    postorder(node->right, out);
    out.push_back(node->val);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    vector<int> out;
    preorder(root, out);
    cout << "preorder size = " << out.size() << endl;
    return 0;
}
