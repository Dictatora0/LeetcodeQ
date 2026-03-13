/*
LeetCode 230. 二叉搜索树中第K小的元素 (Kth Smallest Element in a BST)

题目概述 (Problem Summary)
-------------------------
给定一个二叉搜索树的根节点 root 和一个整数 k，请返回树中第 k 小的元素（从 1 开始计数）。

关键约束 (Key Constraints)
-------------------------
- 树中节点数为 n
- 1 <= k <= n <= 10^4
- 0 <= Node.val <= 10^4

示例 (Example)
-------------
输入：root = [3,1,4,null,2], k = 1
输出：1

解释：
    3
   / \
  1   4
   \
    2

中序遍历：[1, 2, 3, 4]
第 1 小的元素是 1

输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3

解释：
      5
     / \
    3   6
   / \
  2   4
 /
1

中序遍历：[1, 2, 3, 4, 5, 6]
第 3 小的元素是 3

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在二叉搜索树中找到第 k 小的元素

关键观察：
1. 二叉搜索树的性质：左子树 < 根节点 < 右子树
2. 二叉搜索树的中序遍历是有序的（升序）
3. 中序遍历的第 k 个元素就是第 k 小的元素
4. 可以在中序遍历过程中计数，找到第 k 个元素后立即返回

根据这些观察，可以得到几种典型解法：
1. 中序遍历 + 计数 - 最直观
2. 中序遍历 + 数组存储 - 最简单但空间复杂度高
3. 迭代中序遍历 + 栈 - 避免递归
*/

#include <iostream>
#include <vector>
#include <stack>
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
方法一：我的原始解法 - 中序遍历 + 计数 (Approach 1: My Original Solution - Inorder with Counter)

核心思想
--------
使用中序遍历（左 -> 根 -> 右）遍历二叉搜索树，同时计数。
当计数等于 k 时，当前节点就是第 k 小的元素。

算法流程：
1. 维护两个成员变量：
   - res: 存储结果
   - count: 记录当前访问的节点数
2. 定义 inorder(root, k) 函数进行中序遍历：
   a. 递归终止条件：如果节点为空，返回
   b. 递归遍历左子树
   c. 访问当前节点：
      - count++
      - 如果 count == k，记录当前节点的值
   d. 递归遍历右子树
3. 返回结果

为什么中序遍历是有序的？
- 二叉搜索树的性质：左子树的所有节点 < 根节点 < 右子树的所有节点
- 中序遍历顺序：左 -> 根 -> 右
- 因此中序遍历的结果是升序的

复杂度分析
---------
时间复杂度：O(n)
- 最坏情况需要遍历所有节点（k = n）
- 平均情况：O(k + h)，其中 h 是树的高度

空间复杂度：O(h)
- 递归调用栈的深度为树的高度 h
- 最坏情况（链状树）：O(n)
- 最好情况（平衡树）：O(log n)

其中：
n = 节点数量
h = 树的高度
k = 目标位置
*/
class Solution {
public:
    int res;      // 存储结果
    int count = 0; // 记录当前访问的节点数

    // 中序遍历
    // root: 当前节点
    // k: 目标位置
    void inorder(TreeNode* root, int k) {
        // 递归终止条件：空节点
        if (!root) {
            return;
        }

        // 中序遍历：左 -> 根 -> 右
        inorder(root->left, k);  // 先遍历左子树

        // 访问当前节点
        count++;  // 计数加 1
        if (count == k) {
            res = root->val;  // 找到第 k 小的元素
        }

        inorder(root->right, k);  // 再遍历右子树
    }

    int kthSmallest(TreeNode* root, int k) {
        inorder(root, k);
        return res;
    }
};

/*
方法二：中序遍历 + 数组存储 (Approach 2: Inorder with Array)

核心思想
--------
先进行完整的中序遍历，将所有节点值存入数组，然后返回第 k 个元素。

算法流程：
1. 定义 inorder(root) 函数进行中序遍历
2. 将所有节点值按顺序存入数组
3. 返回数组的第 k-1 个元素（因为数组索引从 0 开始）

复杂度分析
---------
时间复杂度：O(n)
- 需要遍历所有节点

空间复杂度：O(n)
- 需要存储所有节点值
*/
class Solution_Array {
public:
    vector<int> arr;

    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        arr.push_back(root->val);
        inorder(root->right);
    }

    int kthSmallest(TreeNode* root, int k) {
        inorder(root);
        return arr[k - 1];  // 数组索引从 0 开始
    }
};

/*
方法三：迭代中序遍历 + 栈 (Approach 3: Iterative Inorder with Stack)

核心思想
--------
使用栈模拟中序遍历的递归过程，避免递归调用。

算法流程：
1. 创建栈 stk
2. 从根节点开始，不断将左子节点入栈
3. 当栈不为空时：
   a. 弹出栈顶节点
   b. 计数加 1
   c. 如果计数等于 k，返回当前节点的值
   d. 将当前节点的右子节点及其所有左子节点入栈
4. 重复直到找到第 k 小的元素

复杂度分析
---------
时间复杂度：O(k + h)
- 只需要遍历到第 k 个节点

空间复杂度：O(h)
- 栈的最大深度为树的高度
*/
class Solution_Iterative {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        TreeNode* curr = root;
        int count = 0;

        while (curr || !stk.empty()) {
            // 将所有左子节点入栈
            while (curr) {
                stk.push(curr);
                curr = curr->left;
            }

            // 弹出栈顶节点（当前最小的未访问节点）
            curr = stk.top();
            stk.pop();

            // 计数加 1
            count++;
            if (count == k) {
                return curr->val;  // 找到第 k 小的元素
            }

            // 转向右子树
            curr = curr->right;
        }

        return -1;  // 不会到达这里（题目保证 k 有效）
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例树：
    3
   / \
  1   4
   \
    2

k = 1

方法一（中序遍历 + 计数）的执行过程：

初始：count = 0, res = 0

1. inorder(3, 1)
   - inorder(1, 1)  // 左子树
     - inorder(null, 1)  // 左子树
     - count = 1, count == k，res = 1  // 访问节点 1
     - inorder(2, 1)  // 右子树
       - inorder(null, 1)  // 左子树
       - count = 2  // 访问节点 2
       - inorder(null, 1)  // 右子树
   - count = 3  // 访问节点 3
   - inorder(4, 1)  // 右子树
     - inorder(null, 1)  // 左子树
     - count = 4  // 访问节点 4
     - inorder(null, 1)  // 右子树

中序遍历顺序：1 -> 2 -> 3 -> 4
第 1 小的元素：1
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：中序遍历 + 计数
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码简洁，空间效率高
- 缺点：需要遍历完整棵树（即使找到结果）

方法二：中序遍历 + 数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：代码最简单
- 缺点：空间复杂度高，需要存储所有节点

方法三：迭代中序遍历
- 时间复杂度：O(k + h)
- 空间复杂度：O(h)
- 优点：找到结果后立即返回，效率最高
- 缺点：代码稍复杂

推荐使用方法一，代码简洁且效率较高。
如果需要最优时间复杂度，使用方法三。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. k = 1：返回最小的元素（最左边的节点）
2. k = n：返回最大的元素（最右边的节点）
3. 只有根节点：k = 1，返回根节点的值
4. 链状树（只有左子树）：中序遍历从下到上
5. 链状树（只有右子树）：中序遍历从上到下
*/

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(4);
    root1->left->right = new TreeNode(2);

    cout << "测试用例 1 - 第 1 小的元素: " << solution.kthSmallest(root1, 1)
         << " (期望: 1)" << endl;

    // 重置 count（因为是成员变量）
    solution.count = 0;
    cout << "测试用例 1 - 第 2 小的元素: " << solution.kthSmallest(root1, 2)
         << " (期望: 2)" << endl;

    solution.count = 0;
    cout << "测试用例 1 - 第 3 小的元素: " << solution.kthSmallest(root1, 3)
         << " (期望: 3)" << endl;

    // 测试用例 2：较大的树
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(6);
    root2->left->left = new TreeNode(2);
    root2->left->right = new TreeNode(4);
    root2->left->left->left = new TreeNode(1);

    solution.count = 0;
    cout << "\n测试用例 2 - 第 3 小的元素: " << solution.kthSmallest(root2, 3)
         << " (期望: 3)" << endl;

    solution.count = 0;
    cout << "测试用例 2 - 第 1 小的元素: " << solution.kthSmallest(root2, 1)
         << " (期望: 1)" << endl;

    solution.count = 0;
    cout << "测试用例 2 - 第 6 小的元素: " << solution.kthSmallest(root2, 6)
         << " (期望: 6)" << endl;

    // 测试用例 3：单节点
    TreeNode* root3 = new TreeNode(1);
    solution.count = 0;
    cout << "\n测试用例 3 - 单节点，第 1 小的元素: " << solution.kthSmallest(root3, 1)
         << " (期望: 1)" << endl;

    return 0;
}
