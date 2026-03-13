/*
LeetCode 104. 二叉树的最大深度 (Maximum Depth of Binary Tree)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，返回其最大深度。

二叉树的最大深度是指从根节点到最远叶子节点的最长路径上的节点数。

关键约束 (Key Constraints)
-------------------------
- 树中节点的数量在 [0, 10^4] 范围内
- -100 <= Node.val <= 100

示例 (Example)
-------------
输入：root = [3,9,20,null,null,15,7]
输出：3

解释：
    3
   / \
  9  20
    /  \
   15   7
最长路径是 3 -> 20 -> 15（或 7），长度为 3。

输入：root = [1,null,2]
输出：2

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 计算从根节点到最远叶子节点的路径长度

关键观察：
1. 树的深度 = max(左子树深度, 右子树深度) + 1
2. 这是一个典型的递归定义
3. 也可以用层序遍历（BFS）统计层数

根据这些观察，可以得到几种典型解法：
1. 递归 DFS - 最简洁直观
2. 迭代 BFS（层序遍历）- 统计层数
3. 迭代 DFS（使用栈）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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
方法一：递归 DFS (Approach 1: Recursive DFS)

核心思想
--------
使用递归计算树的深度。
树的深度 = max(左子树深度, 右子树深度) + 1

算法流程：
1. 递归终止条件：如果节点为空，深度为 0
2. 递归计算左子树的深度
3. 递归计算右子树的深度
4. 返回 max(左子树深度, 右子树深度) + 1

为什么要 +1？
- 因为当前节点本身也算一层
- 空节点深度为 0，单节点深度为 1

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(h)
- 递归调用栈的深度为树的高度 h
- 最坏情况（链状树）：O(n)
- 最好情况（平衡树）：O(log n)

其中：
n = 节点数量
h = 树的高度
*/
class Solution_Recursive {
public:
    int maxDepth(TreeNode* root) {
        // 递归终止条件：空节点深度为 0
        if (!root) return 0;

        // 递归计算左右子树的深度
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);

        // 当前树的深度 = 较深的子树深度 + 1（当前节点）
        return max(leftDepth, rightDepth) + 1;
    }
};

/*
方法二：我的原始解法 - 迭代 BFS (层序遍历) (Approach 2: My Original Solution - Iterative BFS)

核心思想
--------
使用队列进行层序遍历，统计树的层数。
每遍历完一层，深度 +1。

算法流程：
1. 如果根节点为空，返回 0
2. 将根节点加入队列，初始化深度为 0
3. 当队列不为空时：
   a. 记录当前层的节点数 size
   b. 遍历当前层的所有节点：
      - 取出节点
      - 将其左右子节点加入队列
   c. 完成一层遍历后，深度 +1
4. 返回深度

为什么要记录 size？
- 因为需要区分不同的层
- size 表示当前层有多少个节点
- 遍历完 size 个节点后，当前层结束，进入下一层

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(w)
- w 是树的最大宽度（某一层的最大节点数）
- 队列中最多存储一层的节点
- 最坏情况：O(n)（完全二叉树的最后一层）
*/
class Solution {
public:
    int maxDepth(TreeNode* root) {
        // 空树深度为 0
        if (!root) return 0;

        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;  // 记录深度

        while (!q.empty()) {
            int size = q.size();  // 当前层的节点数

            // 遍历当前层的所有节点
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();

                // 将下一层的节点加入队列
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            depth++;  // 完成一层遍历，深度 +1
        }

        return depth;
    }
};

/*
方法三：迭代 DFS (使用栈) (Approach 3: Iterative DFS with Stack)

核心思想
--------
使用栈模拟递归过程，同时记录每个节点的深度。

算法流程：
1. 使用栈存储 (节点, 深度) 对
2. 初始化最大深度为 0
3. 将根节点和深度 1 入栈
4. 当栈不为空时：
   a. 取出栈顶元素 (node, depth)
   b. 更新最大深度
   c. 将左右子节点和深度 depth+1 入栈
5. 返回最大深度

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(h)
*/
class Solution_DFS_Stack {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;

        stack<pair<TreeNode*, int>> stk;
        stk.push({root, 1});
        int maxDepth = 0;

        while (!stk.empty()) {
            auto [node, depth] = stk.top();
            stk.pop();

            // 更新最大深度
            maxDepth = max(maxDepth, depth);

            // 将子节点和深度入栈
            if (node->left) stk.push({node->left, depth + 1});
            if (node->right) stk.push({node->right, depth + 1});
        }

        return maxDepth;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例树：
    3
   / \
  9  20
    /  \
   15   7

方法一（递归）的执行过程：
1. maxDepth(3)
   - maxDepth(9) → 1（叶子节点）
   - maxDepth(20)
     - maxDepth(15) → 1
     - maxDepth(7) → 1
     - 返回 max(1, 1) + 1 = 2
   - 返回 max(1, 2) + 1 = 3

方法二（BFS）的执行过程：
1. 初始：queue = [3], depth = 0
2. 第 1 层：处理节点 3，queue = [9, 20], depth = 1
3. 第 2 层：处理节点 9, 20，queue = [15, 7], depth = 2
4. 第 3 层：处理节点 15, 7，queue = [], depth = 3
5. 返回 depth = 3
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归 DFS
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码最简洁，逻辑最清晰
- 缺点：递归深度受限于栈空间

方法二：迭代 BFS
- 时间复杂度：O(n)
- 空间复杂度：O(w)
- 优点：直观理解为"统计层数"，避免递归
- 缺点：需要额外的队列空间

方法三：迭代 DFS
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：避免递归，使用栈模拟
- 缺点：代码稍复杂

推荐使用方法一（递归），代码最简洁。
如果需要避免递归，推荐方法二（BFS），更直观。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：root = nullptr，深度为 0
2. 只有根节点：深度为 1
3. 链状树（退化为链表）：深度 = 节点数
4. 完全二叉树：深度 = log(n) + 1
5. 只有左子树或只有右子树：深度 = 较长的那一边
*/

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    cout << "测试用例 1 - 深度: " << solution.maxDepth(root1) << " (期望: 3)" << endl;

    // 测试用例 2：链状树
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);

    cout << "测试用例 2 - 深度: " << solution.maxDepth(root2) << " (期望: 2)" << endl;

    // 测试用例 3：单节点
    TreeNode* root3 = new TreeNode(0);
    cout << "测试用例 3 - 深度: " << solution.maxDepth(root3) << " (期望: 1)" << endl;

    // 测试用例 4：空树
    cout << "测试用例 4 - 深度: " << solution.maxDepth(nullptr) << " (期望: 0)" << endl;

    // 测试递归方法
    Solution_Recursive sol_rec;
    cout << "\n使用递归方法 - 测试用例 1: " << sol_rec.maxDepth(root1) << " (期望: 3)" << endl;

    return 0;
}
