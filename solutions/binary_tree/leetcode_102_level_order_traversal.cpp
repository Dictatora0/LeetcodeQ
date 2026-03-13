/*
LeetCode 102. 二叉树的层序遍历 (Binary Tree Level Order Traversal)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，返回其节点值的层序遍历（即逐层地，从左到右访问所有节点）。

关键约束 (Key Constraints)
-------------------------
- 树中节点数目在范围 [0, 2000] 内
- -1000 <= Node.val <= 1000

示例 (Example)
-------------
输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]

解释：
    3
   / \
  9  20
    /  \
   15   7

层序遍历结果：
第 1 层：[3]
第 2 层：[9, 20]
第 3 层：[15, 7]

输入：root = [1]
输出：[[1]]

输入：root = []
输出：[]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 按层次遍历二叉树，将每一层的节点值收集到一个数组中

关键观察：
1. 层序遍历是典型的 BFS（广度优先搜索）问题
2. 需要区分不同的层，关键是记录每一层的节点数量
3. 使用队列来实现 BFS，先进先出保证了从左到右的顺序
4. 在处理每一层时，先记录当前队列的大小（即当前层的节点数）

根据这些观察，可以得到几种典型解法：
1. BFS + 队列（记录层大小）- 最常用
2. DFS + 递归（记录深度）- 另一种思路
*/

#include <iostream>
#include <vector>
#include <queue>
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
方法一：我的原始解法 - BFS + 队列 (Approach 1: My Original Solution - BFS with Queue)

核心思想
--------
使用队列进行层序遍历，关键是在处理每一层时，先记录当前层的节点数量。
这样可以确保每次只处理一层的节点，将它们的值收集到同一个数组中。

算法流程：
1. 如果根节点为空，返回空数组
2. 创建结果数组 ans 和队列 q
3. 将根节点加入队列
4. 当队列不为空时：
   a. 创建当前层的数组 t
   b. 记录当前层的节点数 size = q.size()（关键步骤！）
   c. 遍历 size 次（处理当前层的所有节点）：
      - 取出队首节点
      - 将节点值加入 t
      - 将左右子节点加入队列（为下一层做准备）
   d. 将当前层数组 t 加入结果数组 ans
5. 返回结果数组

为什么要先保存 size？
- 因为在遍历当前层时，会不断向队列中添加下一层的节点
- 如果直接用 q.size() 作为循环条件，会把下一层的节点也处理了
- 先保存 size，就能确保只处理当前层的节点

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(w)
- w 是树的最大宽度（某一层的最大节点数）
- 队列中最多存储一层的节点
- 最坏情况：O(n)（完全二叉树的最后一层）

其中：
n = 节点数量
w = 树的最大宽度
*/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        // 空树直接返回空数组
        if (!root) {
            return ans;
        }

        queue<TreeNode*> q;
        q.push(root);  // 将根节点加入队列

        while (!q.empty()) {
            vector<int> t;  // 存储当前层的节点值
            int size = q.size();  // 关键：先保存当前层的节点数

            // 遍历当前层的所有节点
            for (int i = 0; i < size; i++) {  // 使用固定值 size
                auto node = q.front();
                q.pop();
                t.push_back(node->val);  // 收集当前节点的值

                // 将下一层的节点加入队列
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            ans.push_back(t);  // 将当前层的结果加入答案
        }
        return ans;
    }
};

/*
方法二：DFS + 递归 (Approach 2: DFS with Recursion)

核心思想
--------
使用 DFS 遍历树，同时记录每个节点所在的深度（层数）。
根据深度将节点值添加到对应层的数组中。

算法流程：
1. 创建结果数组 ans
2. 定义 dfs(node, depth) 函数：
   a. 如果节点为空，返回
   b. 如果 depth == ans.size()，说明这是该层的第一个节点，创建新数组
   c. 将当前节点值加入 ans[depth]
   d. 递归处理左子树，depth + 1
   e. 递归处理右子树，depth + 1
3. 从根节点开始 DFS，初始深度为 0
4. 返回结果数组

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(h)
- 递归调用栈的深度为树的高度 h
- 最坏情况（链状树）：O(n)
- 最好情况（平衡树）：O(log n)
*/
class Solution_DFS {
public:
    vector<vector<int>> ans;

    void dfs(TreeNode* node, int depth) {
        if (!node) return;

        // 如果是该层的第一个节点，创建新数组
        if (depth == ans.size()) {
            ans.push_back(vector<int>());
        }

        // 将当前节点值加入对应层
        ans[depth].push_back(node->val);

        // 递归处理左右子树
        dfs(node->left, depth + 1);
        dfs(node->right, depth + 1);
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        dfs(root, 0);
        return ans;
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

方法一（BFS）的执行过程：

初始：queue = [3], ans = []

第 1 轮：
- size = 1, t = []
- 处理节点 3：t = [3], queue = [9, 20]
- ans = [[3]]

第 2 轮：
- size = 2, t = []
- 处理节点 9：t = [9], queue = [20]
- 处理节点 20：t = [9, 20], queue = [15, 7]
- ans = [[3], [9, 20]]

第 3 轮：
- size = 2, t = []
- 处理节点 15：t = [15], queue = [7]
- 处理节点 7：t = [15, 7], queue = []
- ans = [[3], [9, 20], [15, 7]]

返回：[[3], [9, 20], [15, 7]]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：BFS + 队列
- 时间复杂度：O(n)
- 空间复杂度：O(w)
- 优点：直观，符合层序遍历的定义
- 缺点：需要额外的队列空间

方法二：DFS + 递归
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码简洁，利用递归的深度信息
- 缺点：不太直观，需要理解深度与层的对应关系

两种方法时间复杂度相同。
BFS 更符合层序遍历的直观理解，推荐使用方法一。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：root = nullptr，返回 []
2. 只有根节点：返回 [[root->val]]
3. 只有左子树或只有右子树：正常处理
4. 完全二叉树：每一层都是满的
5. 链状树（退化为链表）：每一层只有一个节点
*/

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    vector<vector<int>> result1 = solution.levelOrder(root1);
    cout << "测试用例 1 - 层序遍历: ";
    for (const auto& level : result1) {
        cout << "[";
        for (int i = 0; i < level.size(); i++) {
            cout << level[i];
            if (i < level.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "(期望: [3] [9,20] [15,7])" << endl;

    // 测试用例 2：单节点
    TreeNode* root2 = new TreeNode(1);
    vector<vector<int>> result2 = solution.levelOrder(root2);
    cout << "测试用例 2 - 单节点: ";
    for (const auto& level : result2) {
        cout << "[";
        for (int i = 0; i < level.size(); i++) {
            cout << level[i];
            if (i < level.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "(期望: [1])" << endl;

    // 测试用例 3：空树
    vector<vector<int>> result3 = solution.levelOrder(nullptr);
    cout << "测试用例 3 - 空树: ";
    if (result3.empty()) {
        cout << "[]";
    }
    cout << " (期望: [])" << endl;

    // 测试用例 4：链状树
    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    root4->left->left = new TreeNode(3);
    vector<vector<int>> result4 = solution.levelOrder(root4);
    cout << "测试用例 4 - 链状树: ";
    for (const auto& level : result4) {
        cout << "[";
        for (int i = 0; i < level.size(); i++) {
            cout << level[i];
            if (i < level.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "(期望: [1] [2] [3])" << endl;

    return 0;
}
