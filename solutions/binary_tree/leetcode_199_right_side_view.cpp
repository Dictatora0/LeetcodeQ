/*
LeetCode 199. 二叉树的右视图 (Binary Tree Right Side View)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

关键约束 (Key Constraints)
-------------------------
- 树中节点数目在范围 [0, 100] 内
- -100 <= Node.val <= 100

示例 (Example)
-------------
输入：root = [1,2,3,null,5,null,4]
输出：[1,3,4]

解释：
    1         <--- 看到 1
   / \
  2   3       <--- 看到 3
   \   \
    5   4     <--- 看到 4

从右侧看，能看到的节点是每一层最右边的节点。

输入：root = [1,null,3]
输出：[1,3]

输入：root = []
输出：[]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找到二叉树每一层最右边的节点

关键观察：
1. 右视图看到的是每一层最右边的节点
2. 可以使用层序遍历（BFS），取每一层的最后一个节点
3. 也可以使用 DFS，优先访问右子树，每层第一个访问的节点就是右视图的节点
4. DFS 方法需要记录当前深度，判断是否是该层第一个访问的节点

根据这些观察，可以得到几种典型解法：
1. DFS（优先右子树）- 最巧妙
2. BFS（层序遍历）- 最直观
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
方法一：我的原始解法 - DFS（优先右子树） (Approach 1: My Original Solution - DFS Right First)

核心思想
--------
使用 DFS 遍历树，优先访问右子树，然后访问左子树。
对于每一层，第一个访问到的节点就是右视图能看到的节点。

算法流程：
1. 维护一个结果数组 res
2. 定义 dfs(root, depth) 函数：
   - root: 当前节点
   - depth: 当前深度（从 0 开始）
3. 递归终止条件：如果节点为空，返回
4. 如果 res.size() == depth，说明这是该层第一个访问的节点
   - 将节点值加入 res
5. 先递归访问右子树（depth + 1）
6. 再递归访问左子树（depth + 1）

为什么优先访问右子树？
- 因为右视图看到的是每一层最右边的节点
- 优先访问右子树，保证每层第一个访问的节点是最右边的节点
- 如果右子树不存在，左子树的节点也会被看到

为什么用 res.size() == depth 判断？
- res.size() 表示已经记录了多少层
- depth 表示当前节点所在的层
- 如果 res.size() == depth，说明这一层还没有记录节点
- 由于优先访问右子树，第一个访问的节点一定是最右边的节点

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
class Solution {
public:
    // 结果数组：存储右视图的节点值
    vector<int> res;

    // DFS 遍历
    // root: 当前节点
    // depth: 当前深度（从 0 开始）
    void dfs(TreeNode* root, int depth) {
        // 递归终止条件：空节点
        if (!root) {
            return;
        }

        // 如果这是该层第一个访问的节点，加入结果
        // res.size() 表示已经记录了多少层
        // depth 表示当前节点所在的层
        if (res.size() == depth) {
            res.push_back(root->val);
        }

        // 优先访问右子树（关键！）
        dfs(root->right, depth + 1);

        // 再访问左子树
        dfs(root->left, depth + 1);
    }

    vector<int> rightSideView(TreeNode* root) {
        dfs(root, 0);  // 从根节点开始，深度为 0
        return res;
    }
};

/*
方法二：BFS（层序遍历） (Approach 2: BFS Level Order Traversal)

核心思想
--------
使用层序遍历，取每一层的最后一个节点。

算法流程：
1. 如果根节点为空，返回空数组
2. 创建结果数组 res 和队列 q
3. 将根节点加入队列
4. 当队列不为空时：
   a. 记录当前层的节点数 size
   b. 遍历当前层的所有节点
   c. 如果是该层的最后一个节点，加入结果数组
   d. 将左右子节点加入队列
5. 返回结果数组

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(w)
- w 是树的最大宽度（某一层的最大节点数）
- 队列中最多存储一层的节点
- 最坏情况：O(n)（完全二叉树的最后一层）
*/
class Solution_BFS {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();  // 当前层的节点数

            // 遍历当前层的所有节点
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

                // 如果是该层的最后一个节点，加入结果
                if (i == size - 1) {
                    res.push_back(node->val);
                }

                // 将左右子节点加入队列
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return res;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例树：
    1
   / \
  2   3
   \   \
    5   4

方法一（DFS 优先右子树）的执行过程：

初始：res = [], depth = 0

1. dfs(1, 0)
   - res.size() == 0 == depth，加入 1
   - res = [1]
   - dfs(3, 1)  // 优先右子树
     - res.size() == 1 == depth，加入 3
     - res = [1, 3]
     - dfs(4, 2)  // 优先右子树
       - res.size() == 2 == depth，加入 4
       - res = [1, 3, 4]
       - dfs(null, 3)  // 右子树
       - dfs(null, 3)  // 左子树
     - dfs(null, 2)  // 左子树
   - dfs(2, 1)  // 左子树
     - res.size() == 3 != 1，不加入（该层已有节点 3）
     - dfs(null, 2)  // 右子树
     - dfs(5, 2)  // 左子树
       - res.size() == 3 != 2，不加入（该层已有节点 4）
       - dfs(null, 3)  // 右子树
       - dfs(null, 3)  // 左子树

最终结果：[1, 3, 4]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：DFS（优先右子树）
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码简洁，空间效率高
- 缺点：需要理解优先右子树的含义

方法二：BFS（层序遍历）
- 时间复杂度：O(n)
- 空间复杂度：O(w)
- 优点：直观，符合"右视图"的定义
- 缺点：需要额外的队列空间

两种方法时间复杂度相同。
DFS 方法更简洁，空间效率更高，推荐使用方法一。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：root = nullptr，返回 []
2. 只有根节点：返回 [root->val]
3. 只有左子树：左子树的节点也会被看到
4. 只有右子树：只看到右子树的节点
5. 完全二叉树：每一层都能看到最右边的节点
6. 链状树（只有左子树）：每个节点都能被看到
*/

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->right = new TreeNode(5);
    root1->right->right = new TreeNode(4);

    vector<int> result1 = solution.rightSideView(root1);
    cout << "测试用例 1 - 右视图: ";
    for (int val : result1) {
        cout << val << " ";
    }
    cout << "(期望: 1 3 4)" << endl;

    // 测试用例 2：只有右子树
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(3);

    vector<int> result2 = solution.rightSideView(root2);
    cout << "测试用例 2 - 只有右子树: ";
    for (int val : result2) {
        cout << val << " ";
    }
    cout << "(期望: 1 3)" << endl;

    // 测试用例 3：空树
    vector<int> result3 = solution.rightSideView(nullptr);
    cout << "测试用例 3 - 空树: ";
    if (result3.empty()) {
        cout << "[]";
    }
    cout << " (期望: [])" << endl;

    // 测试用例 4：只有左子树
    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    root4->left->left = new TreeNode(3);

    vector<int> result4 = solution.rightSideView(root4);
    cout << "测试用例 4 - 只有左子树: ";
    for (int val : result4) {
        cout << val << " ";
    }
    cout << "(期望: 1 2 3)" << endl;

    // 测试用例 5：完全二叉树
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(2);
    root5->right = new TreeNode(3);
    root5->left->left = new TreeNode(4);
    root5->left->right = new TreeNode(5);
    root5->right->left = new TreeNode(6);
    root5->right->right = new TreeNode(7);

    vector<int> result5 = solution.rightSideView(root5);
    cout << "测试用例 5 - 完全二叉树: ";
    for (int val : result5) {
        cout << val << " ";
    }
    cout << "(期望: 1 3 7)" << endl;

    return 0;
}
