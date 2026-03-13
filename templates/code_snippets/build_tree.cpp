
/*
二叉树构建工具
使用层序数组构建二叉树，-1 表示空节点
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(const vector<int>& data) {
    if (data.empty() || data[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(data[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < (int)data.size()) {
        TreeNode* node = q.front(); q.pop();
        if (i < (int)data.size() && data[i] != -1) {
            node->left = new TreeNode(data[i]);
            q.push(node->left);
        }
        i++;
        if (i < (int)data.size() && data[i] != -1) {
            node->right = new TreeNode(data[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

int main() {
    vector<int> data = {1, 2, 3, -1, 4};
    TreeNode* root = buildTree(data);
    cout << (root ? root->val : -1) << endl;
    return 0;
}
