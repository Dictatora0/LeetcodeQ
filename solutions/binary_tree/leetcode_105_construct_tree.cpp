/*
LeetCode 105. 从前序与中序遍历序列构造二叉树 (Construct Binary Tree from Preorder and Inorder Traversal)

题目概述 (Problem Summary)
-------------------------
给定两个整数数组 preorder 和 inorder，其中 preorder 是二叉树的前序遍历，inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

关键约束 (Key Constraints)
-------------------------
- 1 <= preorder.length <= 3000
- inorder.length == preorder.length
- -3000 <= preorder[i], inorder[i] <= 3000
- preorder 和 inorder 均无重复元素
- inorder 均出现在 preorder 中
- preorder 保证为二叉树的前序遍历序列
- inorder 保证为二叉树的中序遍历序列

示例 (Example)
-------------
输入：preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出：[3,9,20,null,null,15,7]

解释：
    3
   / \
  9  20
    /  \
   15   7

前序遍历：根 -> 左 -> 右 = [3, 9, 20, 15, 7]
中序遍历：左 -> 根 -> 右 = [9, 3, 15, 20, 7]

输入：preorder = [-1], inorder = [-1]
输出：[-1]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 利用前序和中序遍历的特性，递归地构造二叉树

关键观察：
1. 前序遍历的第一个元素一定是根节点
2. 在中序遍历中找到根节点的位置，可以将数组分为左子树和右子树
3. 中序遍历中，根节点左边的所有元素属于左子树，右边的所有元素属于右子树
4. 根据左子树的大小，可以在前序遍历中划分出左子树和右子树的范围
5. 递归地对左右子树应用相同的逻辑

前序和中序遍历的特点：
- 前序遍历：根 -> 左 -> 右
- 中序遍历：左 -> 根 -> 右

根据这些观察，可以得到递归解法：
1. 使用哈希表优化中序遍历中根节点位置的查找
2. 递归构造左右子树
*/

#include <iostream>
#include <vector>
#include <unordered_map>
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
方法一：我的原始解法 - 递归 + 哈希表 (Approach 1: My Original Solution - Recursion with HashMap)

核心思想
--------
使用递归构造二叉树，利用哈希表快速定位根节点在中序遍历中的位置。

算法流程：
1. 预处理：将中序遍历的值和索引存入哈希表 pos
   - 这样可以 O(1) 时间找到根节点在中序遍历中的位置
2. 定义递归函数 build(preorder, pl, pr, inorder, il, ir)：
   - pl, pr：前序遍历的左右边界
   - il, ir：中序遍历的左右边界
3. 递归终止条件：如果 pl > pr 或 il > ir，返回 nullptr
4. 从前序遍历的第一个元素 preorder[pl] 获取根节点的值
5. 在中序遍历中找到根节点的位置 k = pos[rootVal]
6. 计算左子树的大小：leftSize = k - il
7. 递归构造左子树：
   - 前序范围：[pl + 1, pl + leftSize]
   - 中序范围：[il, k - 1]
8. 递归构造右子树：
   - 前序范围：[pl + leftSize + 1, pr]
   - 中序范围：[k + 1, ir]
9. 返回根节点

为什么这样划分是正确的？
- 前序遍历：[根节点][左子树][右子树]
- 中序遍历：[左子树][根节点][右子树]
- 左子树的大小在前序和中序中是相同的
- 根据左子树的大小，可以在前序遍历中准确划分左右子树

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次
- 哈希表查找是 O(1)

空间复杂度：O(n)
- 哈希表存储 n 个元素：O(n)
- 递归调用栈深度为树的高度：O(h)
- 总空间：O(n)

其中：
n = 节点数量
h = 树的高度
*/
class Solution {
public:
    // 哈希表：存储中序遍历中每个值的索引位置
    unordered_map<int, int> pos;

    // 递归构造二叉树
    // preorder: 前序遍历数组
    // pl, pr: 前序遍历的左右边界
    // inorder: 中序遍历数组
    // il, ir: 中序遍历的左右边界
    TreeNode* build(vector<int>& preorder, int pl, int pr,
                    vector<int>& inorder, int il, int ir) {

        // 递归终止条件：边界不合法
        if (pl > pr || il > ir) return nullptr;

        // 前序遍历的第一个元素是根节点
        int rootVal = preorder[pl];
        TreeNode* root = new TreeNode(rootVal);

        // 在中序遍历中找到根节点的位置
        int k = pos[rootVal];

        // 计算左子树的大小
        // k 是根节点在中序遍历中的位置
        // il 是中序遍历的左边界
        // 左子树的大小 = k - il
        int leftSize = k - il;

        // 递归构造左子树
        // 前序遍历：[pl + 1, pl + leftSize]
        // 中序遍历：[il, k - 1]
        root->left = build(preorder, pl + 1, pl + leftSize,
                           inorder, il, k - 1);

        // 递归构造右子树
        // 前序遍历：[pl + leftSize + 1, pr]
        // 中序遍历：[k + 1, ir]
        root->right = build(preorder, pl + leftSize + 1, pr,
                            inorder, k + 1, ir);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 预处理：将中序遍历的值和索引存入哈希表
        // 这样可以 O(1) 时间找到根节点在中序遍历中的位置
        for (int i = 0; i < inorder.size(); i++) {
            pos[inorder[i]] = i;
        }

        // 开始递归构造
        return build(preorder, 0, preorder.size() - 1,
                     inorder, 0, inorder.size() - 1);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：
preorder = [3, 9, 20, 15, 7]
inorder = [9, 3, 15, 20, 7]

构造过程：

1. 根节点 = 3（preorder[0]）
   - 在 inorder 中找到 3 的位置：k = 1
   - 左子树：inorder[0:0] = [9]
   - 右子树：inorder[2:4] = [15, 20, 7]
   - 左子树大小 = 1

2. 构造左子树：
   - preorder[1:1] = [9]
   - inorder[0:0] = [9]
   - 根节点 = 9，无左右子树

3. 构造右子树：
   - preorder[2:4] = [20, 15, 7]
   - inorder[2:4] = [15, 20, 7]
   - 根节点 = 20（preorder[2]）
   - 在 inorder 中找到 20 的位置：k = 3
   - 左子树：inorder[2:2] = [15]
   - 右子树：inorder[4:4] = [7]

4. 构造 20 的左子树：
   - 根节点 = 15，无左右子树

5. 构造 20 的右子树：
   - 根节点 = 7，无左右子树

最终结果：
    3
   / \
  9  20
    /  \
   15   7
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归 + 哈希表
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：代码清晰，效率高
- 缺点：需要额外的哈希表空间

如果不使用哈希表：
- 每次都在中序遍历中线性查找根节点位置
- 时间复杂度：O(n^2)（最坏情况）
- 空间复杂度：O(h)

使用哈希表优化后，将查找时间从 O(n) 降低到 O(1)，
总时间复杂度从 O(n^2) 降低到 O(n)。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个节点：preorder = [1], inorder = [1]
2. 链状树（只有左子树）：preorder = [1,2,3], inorder = [3,2,1]
3. 链状树（只有右子树）：preorder = [1,2,3], inorder = [1,2,3]
4. 完全二叉树：所有层都是满的
5. 负数节点：题目允许负数，哈希表可以正确处理
*/

// 辅助函数：前序遍历打印树（用于测试）
void printPreorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

// 辅助函数：中序遍历打印树（用于测试）
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    vector<int> preorder1 = {3, 9, 20, 15, 7};
    vector<int> inorder1 = {9, 3, 15, 20, 7};
    TreeNode* root1 = solution.buildTree(preorder1, inorder1);

    cout << "测试用例 1 - 构造的树:" << endl;
    cout << "前序遍历: ";
    printPreorder(root1);
    cout << "(期望: 3 9 20 15 7)" << endl;
    cout << "中序遍历: ";
    printInorder(root1);
    cout << "(期望: 9 3 15 20 7)" << endl;

    // 测试用例 2：单节点
    vector<int> preorder2 = {-1};
    vector<int> inorder2 = {-1};
    TreeNode* root2 = solution.buildTree(preorder2, inorder2);

    cout << "\n测试用例 2 - 单节点:" << endl;
    cout << "前序遍历: ";
    printPreorder(root2);
    cout << "(期望: -1)" << endl;

    // 测试用例 3：链状树（只有左子树）
    vector<int> preorder3 = {1, 2, 3};
    vector<int> inorder3 = {3, 2, 1};
    TreeNode* root3 = solution.buildTree(preorder3, inorder3);

    cout << "\n测试用例 3 - 链状树（只有左子树）:" << endl;
    cout << "前序遍历: ";
    printPreorder(root3);
    cout << "(期望: 1 2 3)" << endl;
    cout << "中序遍历: ";
    printInorder(root3);
    cout << "(期望: 3 2 1)" << endl;

    return 0;
}
