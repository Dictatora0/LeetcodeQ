/*
 * LeetCode 105. Construct Tree
 * 练习：请在此文件中实现你的解法
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* build(vector<int>& preorder, int pl, int pr,
                    vector<int>& inorder, int il, int ir) {
        // TODO: 在此实现
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // TODO: 在此实现
    }

};

int main() {
    // TODO: 添加测试用例
    return 0;
}
