/*
LeetCode 94. 二叉树的中序遍历 (Binary Tree Inorder Traversal)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，返回它的中序遍历结果。
中序遍历顺序为：左子树 -> 根节点 -> 右子树。

关键约束 (Key Constraints)
-------------------------
- 节点数范围：[0, 100]
- 节点值范围：[-100, 100]

示例 (Example)
-------------
输入：root = [1,null,2,3]
输出：[1,3,2]
解释：
    1
     \
      2
     /
    3
中序遍历顺序：1 -> 3 -> 2

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 按固定顺序遍历二叉树的所有节点

关键观察：
1. 中序遍历是“左-根-右”的固定访问顺序
2. 递归天然符合树的结构，是最直观的写法
3. 迭代可以用显式栈模拟递归过程，避免递归栈

根据这些观察，可以得到两种典型解法：
1. 递归 DFS：代码简洁清晰
2. 迭代 + 栈：避免递归栈，适合深树
*/

#include <iostream>
#include <vector>
#include <stack>

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

核心思想
--------
使用递归进行中序遍历：先遍历左子树，再访问当前节点，最后遍历右子树。

算法流程：
1. 从根节点开始递归
2. 先遍历左子树
3. 将当前节点值加入结果
4. 再遍历右子树

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(h)

其中：
n = 节点数量
h = 树的高度（递归栈深度）
*/
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }

private:
    void inorderHelper(TreeNode* node, vector<int>& res) {
        if (node == nullptr) return;     // 空节点直接返回
        inorderHelper(node->left, res);  // 递归遍历左子树
        res.push_back(node->val);        // 访问当前节点
        inorderHelper(node->right, res); // 递归遍历右子树
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Iterative Stack)

优化思路
--------
使用显式栈模拟递归过程，避免递归栈，适用于深度较大的树。

算法流程：
1. 从根节点开始，不断向左入栈
2. 左节点为空时，弹出栈顶并访问
3. 转向右子树，重复上述过程

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(h)
*/
class Solution_Optimized {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {
                st.push(cur);           // 一直向左走，路径入栈
                cur = cur->left;
            }

            cur = st.top();             // 访问最左侧节点
            st.pop();
            result.push_back(cur->val); // 访问当前节点

            cur = cur->right;           // 转向右子树
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
二叉树：
    1
     \
      2
     /
    3

中序遍历顺序：
左 -> 根 -> 右
1 -> 3 -> 2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归 DFS
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码最简洁
- 缺点：深树可能导致递归栈过深

方法二：迭代 + 栈
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：避免递归栈
- 缺点：代码稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：返回空数组
2. 只有一个节点：返回单元素数组
3. 极度不平衡的树：递归深度或栈深度较大
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    // 测试用例 1
    // 树结构：1 -> null -> 2 -> left 3
    TreeNode* root1 = new TreeNode(1);
    root1->right = new TreeNode(2);
    root1->right->left = new TreeNode(3);

    Solution_Optimized solution1;
    vector<int> result1 = solution1.inorderTraversal(root1);
    cout << "测试用例 1 - 输出: ";
    printVector(result1);
    cout << " (期望: [1, 3, 2])" << endl;

    // 测试用例 2
    TreeNode* root2 = new TreeNode(2);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(3);

    vector<int> result2 = solution1.inorderTraversal(root2);
    cout << "测试用例 2 - 输出: ";
    printVector(result2);
    cout << " (期望: [1, 2, 3])" << endl;

    return 0;
}
