/*
LeetCode 236. 二叉树的最近公共祖先 (Lowest Common Ancestor of a Binary Tree)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树，找到该树中两个指定节点的最近公共祖先。

最近公共祖先的定义：对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。

关键约束 (Key Constraints)
-------------------------
- 树中节点数目在范围 [2, 10^5] 内
- -10^9 <= Node.val <= 10^9
- 所有 Node.val 互不相同
- p != q
- p 和 q 均存在于给定的二叉树中

示例 (Example)
-------------
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3

输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5（一个节点可以是它自己的祖先）

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在二叉树中找到两个节点的最低公共祖先节点

关键观察：
1. 如果当前节点是 p 或 q，那么当前节点就是候选答案
2. 如果 p 和 q 分别在当前节点的左右子树中，当前节点就是 LCA
3. 如果 p 和 q 都在左子树，LCA 在左子树中
4. 如果 p 和 q 都在右子树，LCA 在右子树中

核心思想：
- 使用后序遍历（左右根）的递归思路
- 从底向上返回信息：是否找到 p 或 q
- 当左右子树都返回非空时，当前节点就是 LCA

为什么这个算法有效？
1. 递归终止条件：遇到 nullptr 返回 nullptr；遇到 p 或 q 返回当前节点
2. 递归过程：分别在左右子树中查找
3. 返回逻辑：
   - 如果左右都找到了（left && right），说明 p 和 q 分居两侧，当前节点是 LCA
   - 如果只有一侧找到，说明两个节点都在那一侧，返回那一侧的结果
   - 如果都没找到，返回 nullptr

根据这些观察，可以得到递归解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>

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
方法一：我的原始解法 (Approach 1: My Original Solution - Recursive DFS)

核心思想
--------
使用递归的后序遍历思路，从底向上返回信息。

算法流程：
1. 递归终止条件：
   - 如果当前节点为空，返回 nullptr
   - 如果当前节点是 p 或 q，返回当前节点
2. 递归左子树，得到 left 结果
3. 递归右子树，得到 right 结果
4. 根据 left 和 right 的情况判断：
   - 如果 left 和 right 都不为空，说明 p 和 q 分居当前节点两侧，当前节点是 LCA
   - 如果只有 left 不为空，说明 p 和 q 都在左子树，返回 left
   - 如果只有 right 不为空，说明 p 和 q 都在右子树，返回 right
   - 如果都为空，返回 nullptr

为什么这个算法正确？
- 后序遍历保证了从底向上处理
- 第一个同时在左右子树都找到目标的节点，就是最近公共祖先
- 如果某个节点本身是 p 或 q，它会被立即返回，阻止继续向下搜索

复杂度分析
---------
时间复杂度：O(n)，其中 n 是树中节点数，最坏情况需要遍历所有节点
空间复杂度：O(h)，其中 h 是树的高度，递归栈的深度
*/
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 递归终止条件：遇到空节点或目标节点
        if (!root || root == p || root == q) {
            return root;
        }

        // 在左子树中查找 p 和 q
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        // 在右子树中查找 p 和 q
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        // 如果左右子树都找到了，说明 p 和 q 分居当前节点两侧
        // 当前节点就是最近公共祖先
        if (left && right) {
            return root;
        }

        // 否则返回非空的那一侧
        // 如果 left 非空，说明 p 和 q 都在左子树，返回左子树的结果
        // 如果 right 非空，说明 p 和 q 都在右子树，返回右子树的结果
        // 如果都为空，返回 nullptr
        return left ? left : right;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
树结构：
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4

查找 p=5, q=1 的 LCA：

1. 从根节点 3 开始
2. 递归左子树（节点 5）：
   - 节点 5 == p，直接返回 5
3. 递归右子树（节点 1）：
   - 节点 1 == q，直接返回 1
4. 回到节点 3：left=5, right=1，都不为空
5. 返回节点 3（LCA）

查找 p=5, q=4 的 LCA：

1. 从根节点 3 开始
2. 递归左子树（节点 5）：
   - 节点 5 == p，直接返回 5
3. 递归右子树（节点 1）：
   - 继续递归，但找不到 p 或 q，返回 nullptr
4. 回到节点 3：left=5, right=nullptr
5. 返回 left（节点 5）

实际上，当递归到节点 5 时就返回了，因为 5 本身是 p。
虽然 q=4 在 5 的子树中，但由于 5 == p，递归提前终止。
这符合"一个节点可以是它自己的祖先"的定义。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. p 或 q 是另一个的祖先：返回祖先节点
2. p 和 q 在同一子树：返回子树中的 LCA
3. p 和 q 分居根节点两侧：返回根节点
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：递归 DFS
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码简洁，思路清晰
- 缺点：需要递归栈空间

其他可能的方法：
- 存储父节点路径：先找到从根到 p 和 q 的路径，然后找第一个公共节点
  时间 O(n)，空间 O(n)，需要额外存储空间
*/

// 辅助函数：构建二叉树（用于测试）
TreeNode* buildTree(const vector<int>& values, int index) {
    if (index >= values.size() || values[index] == -1) {
        return nullptr;
    }
    TreeNode* root = new TreeNode(values[index]);
    root->left = buildTree(values, 2 * index + 1);
    root->right = buildTree(values, 2 * index + 2);
    return root;
}

// 辅助函数：查找节点（用于测试）
TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    TreeNode* left = findNode(root->left, val);
    if (left) return left;
    return findNode(root->right, val);
}

int main() {
    Solution solution;

    // 测试用例 1：p 和 q 分居根节点两侧
    // 树结构：[3,5,1,6,2,0,8,null,null,7,4]
    vector<int> values1 = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    TreeNode* root1 = buildTree(values1, 0);
    TreeNode* p1 = findNode(root1, 5);
    TreeNode* q1 = findNode(root1, 1);
    TreeNode* lca1 = solution.lowestCommonAncestor(root1, p1, q1);
    cout << "测试用例 1 - 输出: " << lca1->val << " (期望: 3)" << endl;

    // 测试用例 2：p 是 q 的祖先
    TreeNode* p2 = findNode(root1, 5);
    TreeNode* q2 = findNode(root1, 4);
    TreeNode* lca2 = solution.lowestCommonAncestor(root1, p2, q2);
    cout << "测试用例 2 - 输出: " << lca2->val << " (期望: 5)" << endl;

    return 0;
}
