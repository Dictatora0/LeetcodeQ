/*
 * LeetCode 108. Sorted Array To Bst
 * 练习：请在此文件中实现你的解法
 */

#include <iostream>
#include <vector>
#include <queue>
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
    TreeNode* dfs(vector<int>& nums, int left, int right) {
        // TODO: 在此实现
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // TODO: 在此实现
    }

};

int main() {
    // TODO: 添加测试用例
    return 0;
}
