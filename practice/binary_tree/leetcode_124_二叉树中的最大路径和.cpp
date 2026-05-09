/*
 * LeetCode 124. 二叉树中的最大路径和
 * 练习：请在此文件中实现你的解法
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
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
    int dfs(TreeNode *root) {
        // TODO: 在此实现
    }

    int maxPathSum(TreeNode *root) {
        // TODO: 在此实现
    }

};

int main() {
    // TODO: 添加测试用例
    return 0;
}
