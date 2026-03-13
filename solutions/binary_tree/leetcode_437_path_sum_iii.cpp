/*
LeetCode 437. 路径总和 III (Path Sum III)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root 和一个整数 targetSum，求该二叉树里节点值之和等于 targetSum 的路径数量。

路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

关键约束 (Key Constraints)
-------------------------
- 二叉树的节点个数范围是 [0, 1000]
- -10^9 <= Node.val <= 10^9
- -1000 <= targetSum <= 1000
- 节点值可以为负数，这是关键约束

示例 (Example)
-------------
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条：
1. 5 -> 3
2. 5 -> 2 -> 1
3. -3 -> 11

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 统计所有可能的向下路径中，路径和等于 targetSum 的数量
- 路径可以从任意节点开始，到任意节点结束

关键观察：
1. 如果用暴力方法，需要枚举所有可能的起点和终点，时间复杂度 O(n^2)
2. 路径和问题可以转化为"前缀和"问题
3. 如果从根到当前节点的路径和为 curSum，从根到某个祖先节点的路径和为 prevSum
   那么从祖先节点到当前节点的路径和就是 curSum - prevSum
4. 如果 curSum - prevSum = targetSum，即 prevSum = curSum - targetSum
   说明存在一条满足条件的路径

根据这些观察，可以得到两种典型解法：
1. 暴力 DFS：对每个节点作为起点，向下搜索所有路径 - O(n^2)
2. 前缀和 + 哈希表优化：一次 DFS 遍历，用哈希表记录前缀和出现次数 - O(n)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

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
方法一：我的原始解法 - 前缀和 + 哈希表 (Approach 1: My Original Solution - Prefix Sum + HashMap)

核心思想
--------
使用前缀和的思想，配合哈希表记录从根节点到当前节点路径上所有前缀和出现的次数。

算法流程：
1. 维护一个哈希表 prefix，key 是前缀和，value 是该前缀和出现的次数
2. 初始化 prefix[0] = 1，表示空路径的和为 0（重要！用于处理从根节点开始的路径）
3. DFS 遍历树，对于每个节点：
   a. 计算从根到当前节点的累计和 curSum
   b. 查找 prefix 中是否存在 (curSum - target)
      - 如果存在，说明有 prefix[curSum - target] 条路径满足条件
   c. 将当前 curSum 加入 prefix 中
   d. 递归处理左右子树
   e. 回溯：将 curSum 从 prefix 中移除（因为回到父节点后，当前路径不再有效）

为什么需要回溯？
- 因为我们只统计"向下"的路径
- 当从左子树返回到父节点，准备进入右子树时，左子树的前缀和不应该影响右子树的计算
- 所以需要在递归返回前，将当前节点的前缀和计数减 1

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次
- 哈希表的插入、查找、删除操作都是 O(1)

空间复杂度：O(n)
- 哈希表最多存储 O(n) 个前缀和
- 递归调用栈深度为树的高度，最坏情况 O(n)

其中：
n = 节点数量
*/
class Solution {
public:
    // prefix: 哈希表，记录从根节点到当前路径上，每个前缀和出现的次数
    unordered_map<long, long> prefix;

    // result: 记录满足条件的路径总数
    int result = 0;

    // DFS 遍历二叉树
    // node: 当前访问的节点
    // curSum: 从根节点到当前节点的路径和
    // target: 目标和
    void dfs(TreeNode* node, long curSum, int target) {
        if (!node) {
            return;  // 空节点，直接返回
        }

        // 计算从根节点到当前节点的累计和
        curSum += node->val;

        // 查找是否存在前缀和为 (curSum - target) 的路径
        // 如果存在，说明从那个前缀和的位置到当前节点的路径和为 target
        if (prefix.count(curSum - target)) {
            result += prefix[curSum - target];
        }

        // 将当前前缀和加入哈希表（或增加计数）
        prefix[curSum]++;

        // 递归处理左右子树
        dfs(node->left, curSum, target);
        dfs(node->right, curSum, target);

        // 回溯：从哈希表中移除当前前缀和
        // 因为回到父节点后，当前路径不再有效
        prefix[curSum]--;
    }

    int pathSum(TreeNode* root, int targetSum) {
        // 初始化：前缀和为 0 的路径有 1 条（空路径）
        // 这样可以正确处理从根节点开始的路径
        prefix[0] = 1;

        // 从根节点开始 DFS
        dfs(root, 0, targetSum);

        return result;
    }
};

/*
方法二：暴力 DFS (Approach 2: Brute Force DFS)

核心思想
--------
对每个节点作为起点，向下搜索所有可能的路径，统计路径和等于 target 的数量。

算法流程：
1. 外层 DFS：遍历每个节点作为路径起点
2. 内层 DFS：从当前起点向下搜索，累加路径和，统计满足条件的路径

复杂度分析
---------
时间复杂度：O(n^2)
- 外层遍历 n 个节点
- 对每个节点，内层最多遍历 n 个节点

空间复杂度：O(h)
- 递归调用栈深度为树的高度 h

这种方法简单直观，但效率较低，适合作为对比学习。
*/
class Solution_BruteForce {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;

        // 以当前节点为起点的路径数 + 左子树的路径数 + 右子树的路径数
        return countPaths(root, targetSum)
             + pathSum(root->left, targetSum)
             + pathSum(root->right, targetSum);
    }

private:
    // 计算以 node 为起点，向下的路径中，和为 targetSum 的路径数量
    int countPaths(TreeNode* node, long targetSum) {
        if (!node) return 0;

        int count = 0;
        if (node->val == targetSum) {
            count = 1;  // 当前节点自己就是一条路径
        }

        // 继续向下搜索
        count += countPaths(node->left, targetSum - node->val);
        count += countPaths(node->right, targetSum - node->val);

        return count;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
二叉树：
        10
       /  \
      5   -3
     / \    \
    3   2   11
   / \   \
  3  -2   1

target = 8

使用前缀和方法的执行过程：

初始：prefix = {0: 1}

访问 10：curSum = 10
  - 查找 prefix[10-8=2]，不存在
  - prefix = {0:1, 10:1}

访问 5：curSum = 15
  - 查找 prefix[15-8=7]，不存在
  - prefix = {0:1, 10:1, 15:1}

访问 3：curSum = 18
  - 查找 prefix[18-8=10]，存在！count += 1（路径：5->3）
  - prefix = {0:1, 10:1, 15:1, 18:1}

...以此类推

最终找到 3 条路径：
1. 5 -> 3
2. 5 -> 2 -> 1
3. -3 -> 11
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：前缀和 + 哈希表
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：效率高，一次遍历解决问题
- 缺点：需要额外的哈希表空间，需要理解前缀和思想

方法二：暴力 DFS
- 时间复杂度：O(n^2)
- 空间复杂度：O(h)
- 优点：思路简单直观，容易理解
- 缺点：效率低，存在大量重复计算

优化方案避免了重复计算路径和，将时间复杂度从 O(n^2) 降低到 O(n)。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：root = null，返回 0
2. 只有一个节点：判断该节点值是否等于 target
3. 存在负数节点：前缀和可能出现相同值，需要用计数而不是布尔值
4. target 为 0：需要正确处理，prefix[0] = 1 的初始化很关键
5. 路径和溢出：使用 long 类型防止溢出
*/

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->right->right = new TreeNode(11);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right->right = new TreeNode(1);

    int result = solution.pathSum(root, 8);
    cout << "测试用例 1 - 路径数量: " << result << " (期望: 3)" << endl;

    // 测试用例 2：简单情况
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);

    int result2 = solution.pathSum(root2, 3);
    cout << "测试用例 2 - 路径数量: " << result2 << " (期望: 2)" << endl;
    // 路径：[3] 和 [1,2]

    return 0;
}