/*
LeetCode 543. 二叉树的直径 (Diameter of Binary Tree)

题目概述 (Problem Summary)
-------------------------
给定一棵二叉树，计算它的直径长度。
直径是任意两个节点之间最长路径的长度，路径长度以边数表示。
路径可以不经过根节点。

关键约束 (Key Constraints)
-------------------------
- 节点数范围：[1, 10^4]
- 节点值范围：[-100, 100]
- 直径长度按“边数”计算

示例 (Example)
-------------
输入：root = [1,2,3,4,5]
输出：3
解释：最长路径为 4 -> 2 -> 1 -> 3，包含 3 条边

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找到任意节点作为“拐点”时，左子树高度 + 右子树高度的最大值

关键观察：
1. 经过某个节点的最长路径长度 = 左子树高度 + 右子树高度
2. 直径是所有节点“经过该节点的最长路径长度”的最大值
3. 一次 DFS 就能同时得到子树高度与更新全局直径

根据这些观察，可以得到两种典型解法：
1. 原始实现（保留）：当前文件中的原始代码
2. DFS 高度计算：O(n) 一次遍历更新直径
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心说明
--------
以下为原始代码，保持实现不变，仅补充必要注释。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(h)
*/
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isMirror(root->left, root->right);
    }

private:
    bool isMirror(TreeNode* left, TreeNode* right) {
        if (!left && !right) return true;           // 两者都空
        if (!left || !right) return false;          // 一空一非空
        if (left->val != right->val) return false;  // 值不等

        // 递归：外侧 vs 外侧，内侧 vs 内侧
        return isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - DFS Height)

优化思路
--------
用一次 DFS 计算每个节点的高度，并在回溯时更新直径：
直径候选值 = leftHeight + rightHeight。

为什么更快：
- 每个节点只访问一次
- 避免重复计算路径长度

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(h)
*/
class Solution_Optimized {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;
        dfsHeight(root);
        return maxDiameter;
    }

private:
    int maxDiameter = 0;

    // 返回以当前节点为根的子树高度（节点数）
    int dfsHeight(TreeNode* node) {
        if (!node) return 0;

        int leftHeight = dfsHeight(node->left);
        int rightHeight = dfsHeight(node->right);

        // 更新直径：左右子树高度之和（边数）
        maxDiameter = max(maxDiameter, leftHeight + rightHeight);

        // 当前节点高度 = 1 + max(左高度, 右高度)
        return 1 + max(leftHeight, rightHeight);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
二叉树：
        1
       / \
      2   3
     / \
    4   5

以节点 1 为拐点的路径长度：
左高度 = 2（2->4 或 2->5）
右高度 = 1（3）
直径候选 = 2 + 1 = 3
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：原始实现
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 说明：保留原始代码供学习对比

方法二：DFS 高度计算
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：一次遍历即可获得直径
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个节点：直径为 0
2. 只有一条链：直径为节点数 - 1
3. 空树：返回 0
*/

int main() {
    // 测试用例 1
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    Solution_Optimized solution1;
    int result1 = solution1.diameterOfBinaryTree(root1);
    cout << "测试用例 1 - 直径: " << result1 << " (期望: 3)" << endl;

    // 测试用例 2：链式结构
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    root2->right->right = new TreeNode(3);
    root2->right->right->right = new TreeNode(4);

    int result2 = solution1.diameterOfBinaryTree(root2);
    cout << "测试用例 2 - 直径: " << result2 << " (期望: 3)" << endl;

    return 0;
}
