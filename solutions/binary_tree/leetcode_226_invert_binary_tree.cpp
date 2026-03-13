/*
LeetCode 226. 翻转二叉树 (Invert Binary Tree)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，翻转这棵二叉树，并返回其根节点。

翻转的定义：将每个节点的左右子树交换位置。

关键约束 (Key Constraints)
-------------------------
- 树中节点数目范围在 [0, 100] 内
- -100 <= Node.val <= 100

示例 (Example)
-------------
输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]

解释：
原始树：
     4
   /   \
  2     7
 / \   / \
1   3 6   9

翻转后：
     4
   /   \
  7     2
 / \   / \
9   6 3   1

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对二叉树的每个节点，交换其左右子树

关键观察：
1. 这是一个典型的递归问题
2. 对于每个节点，只需要交换其左右子节点
3. 然后递归地翻转左右子树
4. 可以使用 DFS（递归或迭代）或 BFS 实现

根据这些观察，可以得到几种典型解法：
1. 递归 DFS（后序遍历）- 最简洁
2. 递归 DFS（前序遍历）
3. 迭代 BFS（层序遍历）
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
方法一：我的原始解法 - 递归 DFS (后序遍历) (Approach 1: My Original Solution - Recursive DFS)

核心思想
--------
使用递归的方式，先翻转左右子树，然后交换当前节点的左右子节点。
这是一种后序遍历的思路：先处理子树，再处理当前节点。

算法流程：
1. 递归终止条件：如果节点为空，返回 nullptr
2. 递归翻转左子树，得到翻转后的左子树根节点
3. 递归翻转右子树，得到翻转后的右子树根节点
4. 交换当前节点的左右子节点
5. 返回当前节点

为什么这样做是正确的？
- 递归保证了从叶子节点开始，逐层向上翻转
- 每个节点的左右子树都已经被正确翻转
- 最后只需要交换当前节点的左右指针即可

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
    TreeNode* invertTree(TreeNode* root) {
        // 递归终止条件：空节点直接返回
        if (!root) return nullptr;

        // 递归翻转左右子树
        // 先处理子问题，再处理当前问题（后序遍历思想）
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        // 交换当前节点的左右子树
        // 此时 left 和 right 已经是翻转后的子树
        root->left = right;
        root->right = left;

        // 返回当前节点（作为翻转后的子树根节点）
        return root;
    }
};

/*
方法二：递归 DFS (前序遍历) (Approach 2: Recursive DFS - Preorder)

核心思想
--------
先交换当前节点的左右子节点，然后递归翻转左右子树。
这是一种前序遍历的思路：先处理当前节点，再处理子树。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(h)

与方法一的区别：
- 方法一是后序遍历（先递归，后交换）
- 方法二是前序遍历（先交换，后递归）
- 两种方法都是正确的，只是处理顺序不同
*/
class Solution_Preorder {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        // 先交换当前节点的左右子节点
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;

        // 再递归翻转左右子树
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};

/*
方法三：迭代 BFS (层序遍历) (Approach 3: Iterative BFS)

核心思想
--------
使用队列进行层序遍历，对每个节点交换其左右子节点。

算法流程：
1. 将根节点加入队列
2. 当队列不为空时：
   a. 取出队首节点
   b. 交换该节点的左右子节点
   c. 将左右子节点（如果存在）加入队列
3. 返回根节点

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(w)
- w 是树的最大宽度（某一层的最大节点数）
- 最坏情况：O(n)（完全二叉树的最后一层）
*/
class Solution_BFS {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            // 交换当前节点的左右子节点
            TreeNode* temp = node->left;
            node->left = node->right;
            node->right = temp;

            // 将子节点加入队列
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return root;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
原始树：
     4
   /   \
  2     7
 / \   / \
1   3 6   9

使用递归方法（后序遍历）的执行过程：

1. invertTree(4)
   - invertTree(2)
     - invertTree(1) → 返回 1
     - invertTree(3) → 返回 3
     - 交换：2 的左右变为 [3, 1]
     - 返回 2
   - invertTree(7)
     - invertTree(6) → 返回 6
     - invertTree(9) → 返回 9
     - 交换：7 的左右变为 [9, 6]
     - 返回 7
   - 交换：4 的左右变为 [7, 2]
   - 返回 4

最终结果：
     4
   /   \
  7     2
 / \   / \
9   6 3   1
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归 DFS（后序）
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码简洁，逻辑清晰
- 缺点：递归深度受限于栈空间

方法二：递归 DFS（前序）
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：与方法一类似
- 缺点：与方法一类似

方法三：迭代 BFS
- 时间复杂度：O(n)
- 空间复杂度：O(w)
- 优点：避免递归，不受栈深度限制
- 缺点：需要额外的队列空间

三种方法时间复杂度相同，空间复杂度略有差异。
递归方法更简洁，迭代方法更安全（避免栈溢出）。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：root = nullptr，直接返回 nullptr
2. 只有根节点：无需交换，直接返回
3. 只有左子树或只有右子树：交换后一边为空
4. 完全二叉树：所有节点都需要交换
5. 链状树（退化为链表）：递归深度最大
*/

// 辅助函数：层序遍历打印树（用于测试）
void printTree(TreeNode* root) {
    if (!root) {
        cout << "空树" << endl;
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->val << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
}

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    cout << "原始树（层序遍历）：" << endl;
    printTree(root);

    TreeNode* inverted = solution.invertTree(root);

    cout << "\n翻转后的树（层序遍历）：" << endl;
    printTree(inverted);
    cout << "期望：4 / 7 2 / 9 6 3 1" << endl;

    // 测试用例 2：只有根节点
    TreeNode* root2 = new TreeNode(1);
    TreeNode* inverted2 = solution.invertTree(root2);
    cout << "\n单节点树翻转后：" << inverted2->val << " (期望: 1)" << endl;

    return 0;
}
