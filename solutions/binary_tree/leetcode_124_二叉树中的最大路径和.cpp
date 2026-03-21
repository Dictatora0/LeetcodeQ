/*
LeetCode 124. 二叉树中的最大路径和 (Binary Tree Maximum Path Sum)

题目概述 (Problem Summary)
-------------------------
路径被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。
同一个节点在一条路径序列中至多出现一次。该路径至少包含一个节点，且不一定经过根节点。

路径和是路径中各节点值的总和。

给定一个二叉树的根节点 root，返回其最大路径和。

关键约束 (Key Constraints)
-------------------------
- 树中节点数目范围是 [1, 3 * 10^4]
- -1000 <= Node.val <= 1000

示例 (Example)
-------------
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3，路径和为 2 + 1 + 3 = 6

输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7，路径和为 15 + 20 + 7 = 42

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在二叉树中找到一条路径，使得路径上所有节点值的和最大
- 路径可以从任意节点开始，到任意节点结束
- 关键难点：路径可以"拐弯"（经过某个节点后分叉到左右子树）

关键观察：
1. 对于任意节点，经过它的最大路径和 = 节点值 + 左子树贡献 + 右子树贡献
2. 但是，当前节点向上返回时，只能选择左子树或右子树的一条路径（不能拐弯）
3. 负数路径应该被剪枝（贡献为 0 比负数更好）

核心概念区分：
- "经过节点的路径"（Path through node）：可以同时包含左右子树，用于更新全局答案
  计算方式：root->val + left + right
- "从节点出发的路径"（Path from node）：只能选择一侧子树，用于向上返回
  计算方式：root->val + max(left, right)

为什么这个算法有效？
1. 使用后序遍历（左右根），确保处理当前节点时，左右子树的信息已知
2. 每个节点都尝试作为"拐点"，计算经过它的最大路径和
3. 向上返回时只返回单侧路径，保证路径的连续性
4. max(0, dfs(child)) 确保负数路径被剪枝

根据这些观察，可以得到树形 DP 解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

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
方法一：树形 DP + 后序遍历 (Approach 1: Tree DP with Post-order Traversal)

核心思想
--------
使用递归的后序遍历，每个节点维护两个信息：
1. 经过该节点的最大路径和（用于更新全局答案）
2. 从该节点出发的最大路径和（用于向上返回）

算法流程：
1. 递归终止条件：空节点返回 0
2. 递归计算左子树的最大贡献：left = max(0, dfs(root->left))
   - max(0, ...) 的作用：如果子树贡献为负，不如不选（剪枝）
3. 递归计算右子树的最大贡献：right = max(0, dfs(root->right))
4. 更新全局答案：ans = max(ans, root->val + left + right)
   - 这是"经过当前节点的路径"，可以同时包含左右子树
5. 向上返回：return root->val + max(left, right)
   - 这是"从当前节点出发的路径"，只能选择一侧子树

为什么要区分"经过节点"和"从节点出发"？
- 经过节点：当前节点作为路径的"拐点"，可以连接左右子树
  例如：左子树 -> 当前节点 -> 右子树
- 从节点出发：当前节点作为路径的一部分，向上延伸
  例如：祖先节点 -> 当前节点 -> 左子树（或右子树）
  不能同时选左右，否则路径会分叉

为什么使用 max(0, dfs(child))？
- 如果子树的最大路径和为负数，选择它会让总和变小
- 不如不选这个子树（贡献为 0），直接使用当前节点的值
- 例如：节点值 10，左子树贡献 -5，右子树贡献 3
  - 不剪枝：10 + (-5) + 3 = 8
  - 剪枝后：10 + 0 + 3 = 13（更优）

复杂度分析
---------
时间复杂度：O(n)，其中 n 是树中节点数，每个节点访问一次
空间复杂度：O(h)，其中 h 是树的高度，递归栈的深度
*/
class Solution {
public:
    int ans = INT_MIN;  // 全局答案，初始化为最小值（因为节点值可能为负）

    int dfs(TreeNode *root) {
        // 递归终止条件：空节点贡献为 0
        if (!root) {
            return 0;
        }

        // 递归计算左子树的最大贡献
        // max(0, ...) 的作用：如果左子树贡献为负，不如不选（剪枝）
        // 这样可以避免负数路径拖累总和
        int left = max(0, dfs(root->left));

        // 递归计算右子树的最大贡献
        // 同样，负数贡献被剪枝为 0
        int right = max(0, dfs(root->right));

        // 计算"经过当前节点的路径和"
        // 这条路径可以同时包含左右子树：左子树 -> 当前节点 -> 右子树
        // 这是当前节点作为"拐点"时的最大路径和
        int current = root->val + left + right;

        // 更新全局最大路径和
        // 每个节点都尝试作为拐点，更新答案
        ans = max(ans, current);

        // 向上返回"从当前节点出发的最大路径和"
        // 只能选择左子树或右子树的一条路径（不能同时选，否则会分叉）
        // 返回值用于父节点计算其路径和
        // 为什么只能选一侧？因为路径不能分叉，向上延伸时只能走一条路
        return root->val + max(left, right);
    }

    int maxPathSum(TreeNode *root) {
        dfs(root);
        return ans;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：简单情况
树结构：
    1
   / \
  2   3

执行过程：
1. dfs(节点2)：
   - left = 0, right = 0
   - current = 2 + 0 + 0 = 2
   - ans = max(INT_MIN, 2) = 2
   - 返回 2 + max(0, 0) = 2

2. dfs(节点3)：
   - left = 0, right = 0
   - current = 3 + 0 + 0 = 3
   - ans = max(2, 3) = 3
   - 返回 3 + max(0, 0) = 3

3. dfs(节点1)：
   - left = max(0, 2) = 2
   - right = max(0, 3) = 3
   - current = 1 + 2 + 3 = 6
   - ans = max(3, 6) = 6
   - 返回 1 + max(2, 3) = 4

最终答案：6（路径 2 -> 1 -> 3）

示例 2：包含负数
树结构：
     -10
     /  \
    9   20
       /  \
      15   7

执行过程：
1. dfs(节点9)：
   - left = 0, right = 0
   - current = 9
   - ans = 9
   - 返回 9

2. dfs(节点15)：
   - left = 0, right = 0
   - current = 15
   - ans = max(9, 15) = 15
   - 返回 15

3. dfs(节点7)：
   - left = 0, right = 0
   - current = 7
   - ans = max(15, 7) = 15
   - 返回 7

4. dfs(节点20)：
   - left = max(0, 15) = 15
   - right = max(0, 7) = 7
   - current = 20 + 15 + 7 = 42
   - ans = max(15, 42) = 42
   - 返回 20 + max(15, 7) = 35

5. dfs(节点-10)：
   - left = max(0, 9) = 9
   - right = max(0, 35) = 35
   - current = -10 + 9 + 35 = 34
   - ans = max(42, 34) = 42
   - 返回 -10 + max(9, 35) = 25

最终答案：42（路径 15 -> 20 -> 7）

关键观察：
- 节点 -10 虽然是根节点，但不在最优路径上
- 最优路径在右子树中，不经过根节点
- max(0, ...) 确保了负数路径被剪枝

示例 3：全是负数
树结构：
    -3
   /
  -2

执行过程：
1. dfs(节点-2)：
   - left = 0, right = 0
   - current = -2
   - ans = -2
   - 返回 -2

2. dfs(节点-3)：
   - left = max(0, -2) = 0  // 负数被剪枝
   - right = 0
   - current = -3 + 0 + 0 = -3
   - ans = max(-2, -3) = -2
   - 返回 -3 + max(0, 0) = -3

最终答案：-2（单节点路径）

关键观察：
- 即使子树贡献为负，也会被剪枝为 0
- 但节点本身的值不会被剪枝（路径至少包含一个节点）
- 所以答案是 -2，而不是 -3 或 -5
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单节点树：直接返回节点值
2. 全是负数：返回最大的负数（单节点路径）
3. 链状树：退化为一维数组的最大子数组和
4. 完全二叉树：需要考虑所有可能的拐点
5. 左右子树贡献都为负：剪枝后只保留根节点
*/

/*
关键点总结 (Key Takeaways)
-------------------------
1. 为什么使用 max(0, dfs(child))？
   - 负数路径会拖累总和，不如不选
   - 剪枝负数贡献，保证路径和尽可能大

2. 为什么返回 root->val + max(left, right)？
   - 向上返回时，路径不能分叉
   - 只能选择左子树或右子树的一条路径
   - 这是"从节点出发的路径"，用于父节点计算

3. 为什么更新 ans 时使用 root->val + left + right？
   - 当前节点作为"拐点"，可以连接左右子树
   - 这是"经过节点的路径"，用于更新全局答案
   - 左子树 -> 当前节点 -> 右子树 形成完整路径

4. "经过节点的路径" vs "从节点出发的路径"
   - 经过节点：可以同时包含左右子树，用于更新答案
   - 从节点出发：只能选一侧子树，用于向上返回
   - 这是树形 DP 的核心技巧
*/

// 辅助函数：构建二叉树（用于测试）
TreeNode* buildTree(const vector<int>& values, int index) {
    if (index >= values.size() || values[index] == -1001) {  // 使用 -1001 表示 null
        return nullptr;
    }
    TreeNode* root = new TreeNode(values[index]);
    root->left = buildTree(values, 2 * index + 1);
    root->right = buildTree(values, 2 * index + 2);
    return root;
}

int main() {
    Solution solution;

    // 测试用例 1：正常情况，最优路径经过根节点
    // 树结构：[1,2,3]
    //     1
    //    / \
    //   2   3
    // 最优路径：2 -> 1 -> 3，路径和 = 6
    vector<int> values1 = {1, 2, 3};
    TreeNode* root1 = buildTree(values1, 0);
    int result1 = solution.maxPathSum(root1);
    cout << "测试用例 1 - 输出: " << result1 << " (期望: 6)" << endl;
    solution.ans = INT_MIN;  // 重置全局变量

    // 测试用例 2：包含负数，最优路径不经过根节点
    // 树结构：[-10,9,20,null,null,15,7]
    //      -10
    //      /  \
    //     9   20
    //        /  \
    //       15   7
    // 最优路径：15 -> 20 -> 7，路径和 = 42
    vector<int> values2 = {-10, 9, 20, -1001, -1001, 15, 7};
    TreeNode* root2 = buildTree(values2, 0);
    int result2 = solution.maxPathSum(root2);
    cout << "测试用例 2 - 输出: " << result2 << " (期望: 42)" << endl;
    solution.ans = INT_MIN;

    // 测试用例 3：单节点
    // 树结构：[-3]
    // 最优路径：-3，路径和 = -3
    vector<int> values3 = {-3};
    TreeNode* root3 = buildTree(values3, 0);
    int result3 = solution.maxPathSum(root3);
    cout << "测试用例 3 - 输出: " << result3 << " (期望: -3)" << endl;
    solution.ans = INT_MIN;

    // 测试用例 4：全是负数
    // 树结构：[-3,-2]
    //     -3
    //     /
    //   -2
    // 最优路径：-2（单节点），路径和 = -2
    vector<int> values4 = {-3, -2, -1001};
    TreeNode* root4 = buildTree(values4, 0);
    int result4 = solution.maxPathSum(root4);
    cout << "测试用例 4 - 输出: " << result4 << " (期望: -2)" << endl;
    solution.ans = INT_MIN;

    // 测试用例 5：链状树
    // 树结构：[2,-1,3]
    //     2
    //    / \
    //  -1   3
    // 最优路径：2 -> 3，路径和 = 5
    vector<int> values5 = {2, -1, 3};
    TreeNode* root5 = buildTree(values5, 0);
    int result5 = solution.maxPathSum(root5);
    cout << "测试用例 5 - 输出: " << result5 << " (期望: 5)" << endl;

    return 0;
}
