/*
LeetCode 98. 验证二叉搜索树 (Validate Binary Search Tree)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，判断其是否是一个有效的二叉搜索树。

有效二叉搜索树的定义：
- 节点的左子树只包含小于当前节点的数
- 节点的右子树只包含大于当前节点的数
- 所有左子树和右子树自身也必须是二叉搜索树

关键约束 (Key Constraints)
-------------------------
- 树中节点数目范围在 [1, 10^4] 内
- -2^31 <= Node.val <= 2^31 - 1

示例 (Example)
-------------
输入：root = [2,1,3]
输出：true

解释：
    2
   / \
  1   3

这是一个有效的二叉搜索树。

输入：root = [5,1,4,null,null,3,6]
输出：false

解释：
    5
   / \
  1   4
     / \
    3   6

根节点的值是 5，但是右子树节点 4 的值小于 5，不满足 BST 的定义。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 验证一棵树是否满足二叉搜索树的性质

关键观察：
1. 不能只比较当前节点与左右子节点的大小关系
2. 需要保证左子树的所有节点都小于当前节点，右子树的所有节点都大于当前节点
3. 可以为每个节点维护一个有效值范围 (min, max)
4. 二叉搜索树的中序遍历是严格递增的

常见错误：
- 只比较 root->val > root->left->val && root->val < root->right->val 是不够的
- 例如：[5,1,4,null,null,3,6]，节点 5 的右子树包含节点 3，3 < 5，不满足 BST

根据这些观察，可以得到几种典型解法：
1. 递归 + 范围检查 - 最直观
2. 中序遍历 + 递增检查 - 利用 BST 性质
*/

#include <iostream>
#include <vector>
#include <climits>
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
方法一：我的原始解法 - 递归 + 范围检查 (Approach 1: My Original Solution - Recursion with Range)

核心思想
--------
为每个节点维护一个有效值范围 (min, max)，递归验证每个节点是否在有效范围内。

算法流程：
1. 定义递归函数 isValidBST(root, min, max)：
   - root: 当前节点
   - min: 当前节点值的下界（不包含）
   - max: 当前节点值的上界（不包含）
2. 递归终止条件：如果节点为空，返回 true
3. 检查当前节点的值是否在 (min, max) 范围内
   - 如果不在，返回 false
4. 递归验证左子树：范围为 (min, root->val)
   - 左子树的所有节点必须小于当前节点
5. 递归验证右子树：范围为 (root->val, max)
   - 右子树的所有节点必须大于当前节点
6. 返回左右子树的验证结果

为什么需要范围检查？
- 不能只比较父节点和子节点的关系
- 需要保证整个子树的所有节点都满足范围约束
- 例如：节点 5 的右子树中的所有节点都必须大于 5

为什么使用 long long？
- 节点值的范围是 [-2^31, 2^31 - 1]
- 初始范围需要使用 LLONG_MIN 和 LLONG_MAX
- 避免边界情况（节点值为 INT_MIN 或 INT_MAX）

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
    // 递归验证 BST
    // root: 当前节点
    // min: 当前节点值的下界（不包含）
    // max: 当前节点值的上界（不包含）
    bool isValidBST(TreeNode* root, long long min = LLONG_MIN, long long max = LLONG_MAX) {
        // 递归终止条件：空节点是有效的 BST
        if (!root) {
            return true;
        }

        // 获取当前节点的值
        long long x = root->val;

        // 检查当前节点是否在有效范围内，并递归验证左右子树
        // 当前节点必须满足：min < x < max
        // 左子树的范围：(min, x)
        // 右子树的范围：(x, max)
        return min < x && x < max &&
               isValidBST(root->left, min, x) &&
               isValidBST(root->right, x, max);
    }
};

/*
方法二：中序遍历 + 递增检查 (Approach 2: Inorder Traversal with Increasing Check)

核心思想
--------
利用二叉搜索树的性质：中序遍历的结果是严格递增的。
在中序遍历过程中，检查当前节点是否大于前一个节点。

算法流程：
1. 维护一个变量 prev，记录中序遍历中前一个节点的值
2. 定义 inorder(root) 函数进行中序遍历：
   a. 递归终止条件：如果节点为空，返回 true
   b. 递归遍历左子树，如果返回 false，直接返回 false
   c. 检查当前节点是否大于 prev
      - 如果不大于，返回 false
      - 否则，更新 prev 为当前节点的值
   d. 递归遍历右子树，返回结果
3. 返回遍历结果

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(h)
- 递归调用栈的深度为树的高度
*/
class Solution_Inorder {
public:
    long long prev = LLONG_MIN;  // 记录前一个节点的值

    bool isValidBST(TreeNode* root) {
        if (!root) return true;

        // 中序遍历：左 -> 根 -> 右
        // 先遍历左子树
        if (!isValidBST(root->left)) {
            return false;
        }

        // 检查当前节点是否大于前一个节点
        if (root->val <= prev) {
            return false;
        }
        prev = root->val;  // 更新前一个节点的值

        // 遍历右子树
        return isValidBST(root->right);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：有效的 BST
    2
   / \
  1   3

方法一（递归 + 范围检查）的执行过程：

1. isValidBST(2, -∞, +∞)
   - 检查：-∞ < 2 < +∞，通过
   - isValidBST(1, -∞, 2)
     - 检查：-∞ < 1 < 2，通过
     - isValidBST(null, -∞, 1) → true
     - isValidBST(null, 1, 2) → true
     - 返回 true
   - isValidBST(3, 2, +∞)
     - 检查：2 < 3 < +∞，通过
     - isValidBST(null, 2, 3) → true
     - isValidBST(null, 3, +∞) → true
     - 返回 true
   - 返回 true

示例 2：无效的 BST
    5
   / \
  1   4
     / \
    3   6

方法一的执行过程：

1. isValidBST(5, -∞, +∞)
   - 检查：-∞ < 5 < +∞，通过
   - isValidBST(1, -∞, 5)
     - 检查：-∞ < 1 < 5，通过
     - 返回 true
   - isValidBST(4, 5, +∞)
     - 检查：5 < 4 < +∞，失败！（4 不大于 5）
     - 返回 false
   - 返回 false
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归 + 范围检查
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：逻辑清晰，直接验证 BST 的定义
- 缺点：需要理解范围传递的含义

方法二：中序遍历 + 递增检查
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：利用 BST 的性质，代码简洁
- 缺点：需要维护前一个节点的值

两种方法时间和空间复杂度相同。
方法一更直观，方法二更巧妙。
推荐使用方法一，逻辑更清晰。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有根节点：返回 true
2. 节点值为 INT_MIN 或 INT_MAX：需要使用 long long 避免溢出
3. 所有节点值相同：返回 false（BST 要求严格递增）
4. 链状树（只有左子树或只有右子树）：正常验证
5. 完全二叉树：正常验证
*/

int main() {
    Solution solution;

    // 测试用例 1：有效的 BST
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);

    cout << "测试用例 1 - [2,1,3]: "
         << (solution.isValidBST(root1) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 2：无效的 BST
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(3);
    root2->right->right = new TreeNode(6);

    cout << "测试用例 2 - [5,1,4,3,6]: "
         << (solution.isValidBST(root2) ? "true" : "false")
         << " (期望: false)" << endl;

    // 测试用例 3：单节点
    TreeNode* root3 = new TreeNode(1);
    cout << "测试用例 3 - [1]: "
         << (solution.isValidBST(root3) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 4：边界值
    TreeNode* root4 = new TreeNode(INT_MAX);
    cout << "测试用例 4 - [INT_MAX]: "
         << (solution.isValidBST(root4) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 5：重复值（无效）
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(1);
    cout << "测试用例 5 - [1,1]: "
         << (solution.isValidBST(root5) ? "true" : "false")
         << " (期望: false)" << endl;

    // 测试用例 6：较大的有效 BST
    TreeNode* root6 = new TreeNode(5);
    root6->left = new TreeNode(3);
    root6->right = new TreeNode(7);
    root6->left->left = new TreeNode(1);
    root6->left->right = new TreeNode(4);
    root6->right->left = new TreeNode(6);
    root6->right->right = new TreeNode(9);

    cout << "测试用例 6 - [5,3,7,1,4,6,9]: "
         << (solution.isValidBST(root6) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 7：左子树中有大于根的节点（无效）
    TreeNode* root7 = new TreeNode(5);
    root7->left = new TreeNode(4);
    root7->right = new TreeNode(6);
    root7->left->right = new TreeNode(6);  // 6 > 5，无效

    cout << "测试用例 7 - [5,4,6,null,6]: "
         << (solution.isValidBST(root7) ? "true" : "false")
         << " (期望: false)" << endl;

    return 0;
}
