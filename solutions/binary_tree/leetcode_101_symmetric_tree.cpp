/*
LeetCode 101. 对称二叉树 (Symmetric Tree)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，检查它是否轴对称。

轴对称的定义：一棵树如果沿着中心线对折后，左右两部分完全重合，则称为对称树。

关键约束 (Key Constraints)
-------------------------
- 树中节点数目在范围 [1, 1000] 内
- -100 <= Node.val <= 100

示例 (Example)
-------------
输入：root = [1,2,2,3,4,4,3]
输出：true

解释：
    1
   / \
  2   2
 / \ / \
3  4 4  3
这棵树是对称的。

输入：root = [1,2,2,null,3,null,3]
输出：false

解释：
    1
   / \
  2   2
   \   \
    3   3
这棵树不对称（右侧的 3 位置不匹配）。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 判断一棵树是否关于根节点中心线对称

关键观察：
1. 对称意味着：左子树是右子树的镜像
2. 两棵树互为镜像的条件：
   - 它们的根节点值相同
   - 左树的左子树 和 右树的右子树 互为镜像
   - 左树的右子树 和 右树的左子树 互为镜像
3. 这是一个递归定义，可以用递归或迭代实现

根据这些观察，可以得到几种典型解法：
1. 递归：定义辅助函数判断两棵树是否互为镜像
2. 迭代（BFS）：使用队列，成对比较节点
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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
方法一：我的原始解法 - 递归 (Approach 1: My Original Solution - Recursive)

核心思想
--------
定义一个辅助函数 isMirror(left, right)，判断两棵树是否互为镜像。
对于根节点，判断其左子树和右子树是否互为镜像。

算法流程：
1. 如果根节点为空，返回 true（空树是对称的）
2. 调用 isMirror(root->left, root->right) 判断左右子树是否镜像

isMirror(left, right) 的逻辑：
1. 如果 left 和 right 都为空，返回 true（两个空树互为镜像）
2. 如果 left 和 right 有一个为空，返回 false（一空一非空，不对称）
3. 如果 left->val != right->val，返回 false（值不相等，不对称）
4. 递归判断：
   - left 的左子树 和 right 的右子树 是否镜像
   - left 的右子树 和 right 的左子树 是否镜像
   - 两者都为 true 才返回 true

为什么要比较 left->left 和 right->right？
- 因为对称意味着外侧对外侧，内侧对内侧
- 左树的左子树（外侧）应该和右树的右子树（外侧）镜像
- 左树的右子树（内侧）应该和右树的左子树（内侧）镜像

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
    bool isSymmetric(TreeNode* root) {
        // 空树是对称的
        if (!root) return true;

        // 判断左右子树是否互为镜像
        return isMirror(root->left, root->right);
    }

private:
    // 判断两棵树是否互为镜像
    bool isMirror(TreeNode* left, TreeNode* right) {
        // 情况 1：两者都为空，互为镜像
        if (!left && !right) return true;

        // 情况 2：一个为空，一个不为空，不对称
        if (!left || !right) return false;

        // 情况 3：值不相等，不对称
        if (left->val != right->val) return false;

        // 情况 4：递归判断子树
        // 外侧对外侧：left->left 和 right->right
        // 内侧对内侧：left->right 和 right->left
        return isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }
};

/*
方法二：迭代 BFS (Approach 2: Iterative BFS)

核心思想
--------
使用队列进行层序遍历，每次从队列中取出两个节点进行比较。
将需要比较的节点成对加入队列。

算法流程：
1. 初始化队列，将根节点的左右子节点加入队列
2. 当队列不为空时：
   a. 取出两个节点 node1 和 node2
   b. 如果都为空，继续下一轮
   c. 如果一个为空或值不相等，返回 false
   d. 将需要比较的子节点成对加入队列：
      - (node1->left, node2->right)
      - (node1->right, node2->left)
3. 遍历完成，返回 true

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(w)
- w 是树的最大宽度
- 队列中最多存储一层的节点
- 最坏情况：O(n)
*/
class Solution_Iterative {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;

        queue<TreeNode*> q;
        // 将左右子树的根节点加入队列
        q.push(root->left);
        q.push(root->right);

        while (!q.empty()) {
            // 每次取出两个节点进行比较
            TreeNode* node1 = q.front(); q.pop();
            TreeNode* node2 = q.front(); q.pop();

            // 两者都为空，继续
            if (!node1 && !node2) continue;

            // 一个为空或值不相等，不对称
            if (!node1 || !node2 || node1->val != node2->val) {
                return false;
            }

            // 将需要比较的子节点成对加入队列
            // 外侧对外侧
            q.push(node1->left);
            q.push(node2->right);

            // 内侧对内侧
            q.push(node1->right);
            q.push(node2->left);
        }

        return true;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：对称树
    1
   / \
  2   2
 / \ / \
3  4 4  3

递归过程：
1. isMirror(2, 2)
   - 值相等，继续递归
   - isMirror(3, 3) → true（外侧）
   - isMirror(4, 4) → true（内侧）
   - 返回 true

2. 结果：true

示例 2：非对称树
    1
   / \
  2   2
   \   \
    3   3

递归过程：
1. isMirror(2, 2)
   - 值相等，继续递归
   - isMirror(null, 3) → false（外侧不匹配）
   - 返回 false

2. 结果：false
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码简洁，逻辑清晰
- 缺点：递归深度受限于栈空间

方法二：迭代 BFS
- 时间复杂度：O(n)
- 空间复杂度：O(w)
- 优点：避免递归，不受栈深度限制
- 缺点：代码稍复杂，需要维护队列

两种方法时间复杂度相同，空间复杂度略有差异。
递归方法更简洁，迭代方法更安全（避免栈溢出）。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：返回 true
2. 只有根节点：返回 true（单节点树是对称的）
3. 只有左子树或只有右子树：返回 false
4. 完全对称的完全二叉树：返回 true
5. 值相同但结构不对称：返回 false
*/

int main() {
    Solution solution;

    // 测试用例 1：对称树
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(2);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(4);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(3);

    cout << "测试用例 1 - 对称树: " << (solution.isSymmetric(root1) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 2：非对称树
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->left->right = new TreeNode(3);
    root2->right->right = new TreeNode(3);

    cout << "测试用例 2 - 非对称树: " << (solution.isSymmetric(root2) ? "true" : "false")
         << " (期望: false)" << endl;

    // 测试用例 3：单节点
    TreeNode* root3 = new TreeNode(1);
    cout << "测试用例 3 - 单节点: " << (solution.isSymmetric(root3) ? "true" : "false")
         << " (期望: true)" << endl;

    return 0;
}
