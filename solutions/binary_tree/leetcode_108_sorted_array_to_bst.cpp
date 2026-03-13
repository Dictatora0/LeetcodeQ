/*
LeetCode 108. 将有序数组转换为二叉搜索树 (Convert Sorted Array to Binary Search Tree)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 nums，其中元素已按升序排列，请将其转换为一棵高度平衡的二叉搜索树。

高度平衡二叉树是指一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^4
- -10^4 <= nums[i] <= 10^4
- nums 按严格递增顺序排列

示例 (Example)
-------------
输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]

解释：[0,-10,5,null,-3,null,9] 也是一个有效答案。
    0              0
   / \            / \
 -3   9        -10   5
 /   /           \    \
-10  5           -3    9

输入：nums = [1,3]
输出：[3,1] 或 [1,null,3]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 将有序数组转换为高度平衡的二叉搜索树

关键观察：
1. 二叉搜索树的中序遍历是有序的
2. 要构造高度平衡的 BST，应该选择中间元素作为根节点
3. 中间元素左边的所有元素构成左子树，右边的所有元素构成右子树
4. 递归地对左右子数组应用相同的逻辑
5. 这样构造出的树，左右子树的节点数最多相差 1，保证了高度平衡

为什么选择中间元素？
- 选择中间元素可以保证左右子树的大小尽可能接近
- 这样构造出的树高度最小，满足平衡条件

根据这些观察，可以得到递归解法：
1. 选择数组中间元素作为根节点
2. 递归构造左右子树
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
方法一：我的原始解法 - 递归（中序遍历） (Approach 1: My Original Solution - Recursion)

核心思想
--------
使用递归构造平衡二叉搜索树，每次选择中间元素作为根节点。

算法流程：
1. 定义递归函数 dfs(nums, left, right)：
   - left, right：当前子数组的左右边界（左闭右开）
2. 递归终止条件：如果 left == right，返回 nullptr（空区间）
3. 计算中间位置：mid = left + (right - left) / 2
   - 使用 (right - left) / 2 避免溢出
   - 如果元素个数是偶数，选择中间偏左的元素
4. 创建根节点，值为 nums[mid]
5. 递归构造左子树：dfs(nums, left, mid)
6. 递归构造右子树：dfs(nums, mid + 1, right)
7. 返回根节点

为什么使用左闭右开区间？
- 统一边界处理，避免边界条件的混淆
- left == right 表示空区间，逻辑清晰

复杂度分析
---------
时间复杂度：O(n)
- 每个元素访问一次，创建一个节点

空间复杂度：O(log n)
- 递归调用栈的深度为树的高度
- 平衡二叉树的高度为 O(log n)

其中：
n = 数组长度
*/
class Solution {
public:
    // 递归构造平衡二叉搜索树
    // nums: 有序数组
    // left: 左边界（包含）
    // right: 右边界（不包含）
    TreeNode* dfs(vector<int>& nums, int left, int right) {
        // 递归终止条件：空区间
        if (left == right) {
            return nullptr;
        }

        // 选择中间元素作为根节点
        // 如果元素个数是偶数，选择中间偏左的元素
        int mid = left + (right - left) / 2;

        // 创建根节点，并递归构造左右子树
        // 使用构造函数的第三个重载：TreeNode(val, left, right)
        return new TreeNode(nums[mid],
                            dfs(nums, left, mid),      // 左子树：[left, mid)
                            dfs(nums, mid + 1, right)); // 右子树：[mid+1, right)
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 从整个数组开始构造
        // 使用左闭右开区间 [0, nums.size())
        return dfs(nums, 0, nums.size());
    }
};

/*
方法二：递归（左闭右闭区间） (Approach 2: Recursion with Closed Interval)

核心思想
--------
与方法一相同，但使用左闭右闭区间。

算法流程：
1. 递归终止条件：left > right
2. 计算中间位置：mid = left + (right - left) / 2
3. 创建根节点，递归构造左右子树

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(log n)
*/
class Solution_ClosedInterval {
public:
    TreeNode* dfs(vector<int>& nums, int left, int right) {
        // 递归终止条件：左边界大于右边界
        if (left > right) {
            return nullptr;
        }

        // 选择中间元素作为根节点
        int mid = left + (right - left) / 2;

        // 创建根节点
        TreeNode* root = new TreeNode(nums[mid]);

        // 递归构造左右子树
        root->left = dfs(nums, left, mid - 1);      // 左子树：[left, mid-1]
        root->right = dfs(nums, mid + 1, right);    // 右子树：[mid+1, right]

        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return dfs(nums, 0, nums.size() - 1);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：nums = [-10, -3, 0, 5, 9]

构造过程（使用左闭右开区间）：

1. dfs(nums, 0, 5)
   - mid = 0 + (5 - 0) / 2 = 2
   - 根节点 = nums[2] = 0
   - 左子树：dfs(nums, 0, 2) → [-10, -3]
   - 右子树：dfs(nums, 3, 5) → [5, 9]

2. 构造左子树 dfs(nums, 0, 2)
   - mid = 0 + (2 - 0) / 2 = 1
   - 根节点 = nums[1] = -3
   - 左子树：dfs(nums, 0, 1) → [-10]
   - 右子树：dfs(nums, 2, 2) → nullptr

3. 构造 -3 的左子树 dfs(nums, 0, 1)
   - mid = 0 + (1 - 0) / 2 = 0
   - 根节点 = nums[0] = -10
   - 左子树：dfs(nums, 0, 0) → nullptr
   - 右子树：dfs(nums, 1, 1) → nullptr

4. 构造右子树 dfs(nums, 3, 5)
   - mid = 3 + (5 - 3) / 2 = 4
   - 根节点 = nums[4] = 9
   - 左子树：dfs(nums, 3, 4) → [5]
   - 右子树：dfs(nums, 5, 5) → nullptr

5. 构造 9 的左子树 dfs(nums, 3, 4)
   - mid = 3 + (4 - 3) / 2 = 3
   - 根节点 = nums[3] = 5
   - 左子树：dfs(nums, 3, 3) → nullptr
   - 右子树：dfs(nums, 4, 4) → nullptr

最终结果：
      0
     / \
   -3   9
   /   /
 -10  5
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归（左闭右开）
- 时间复杂度：O(n)
- 空间复杂度：O(log n)
- 优点：边界条件统一，left == right 表示空区间
- 缺点：需要理解左闭右开的含义

方法二：递归（左闭右闭）
- 时间复杂度：O(n)
- 空间复杂度：O(log n)
- 优点：更符合直觉，left > right 表示空区间
- 缺点：需要注意边界的 +1 和 -1

两种方法本质相同，只是区间表示方式不同。
推荐使用方法一（左闭右开），代码更简洁。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：nums = [1]，返回单节点树
2. 两个元素：nums = [1, 3]，选择中间偏左的元素作为根
3. 奇数个元素：中间元素唯一
4. 偶数个元素：选择中间偏左的元素（也可以选择中间偏右）
5. 负数元素：正常处理，不影响算法
*/

// 辅助函数：中序遍历打印树（用于验证 BST）
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// 辅助函数：计算树的高度
int getHeight(TreeNode* root) {
    if (!root) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// 辅助函数：检查是否是平衡二叉树
bool isBalanced(TreeNode* root) {
    if (!root) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if (abs(leftHeight - rightHeight) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

int main() {
    Solution solution;

    // 测试用例 1：示例中的数组
    vector<int> nums1 = {-10, -3, 0, 5, 9};
    TreeNode* root1 = solution.sortedArrayToBST(nums1);

    cout << "测试用例 1 - 数组: [-10, -3, 0, 5, 9]" << endl;
    cout << "中序遍历: ";
    printInorder(root1);
    cout << "(期望: -10 -3 0 5 9)" << endl;
    cout << "是否平衡: " << (isBalanced(root1) ? "是" : "否") << " (期望: 是)" << endl;
    cout << "树的高度: " << getHeight(root1) << endl;

    // 测试用例 2：两个元素
    vector<int> nums2 = {1, 3};
    TreeNode* root2 = solution.sortedArrayToBST(nums2);

    cout << "\n测试用例 2 - 数组: [1, 3]" << endl;
    cout << "中序遍历: ";
    printInorder(root2);
    cout << "(期望: 1 3)" << endl;
    cout << "是否平衡: " << (isBalanced(root2) ? "是" : "否") << " (期望: 是)" << endl;

    // 测试用例 3：单个元素
    vector<int> nums3 = {0};
    TreeNode* root3 = solution.sortedArrayToBST(nums3);

    cout << "\n测试用例 3 - 数组: [0]" << endl;
    cout << "中序遍历: ";
    printInorder(root3);
    cout << "(期望: 0)" << endl;
    cout << "是否平衡: " << (isBalanced(root3) ? "是" : "否") << " (期望: 是)" << endl;

    // 测试用例 4：较长数组
    vector<int> nums4 = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root4 = solution.sortedArrayToBST(nums4);

    cout << "\n测试用例 4 - 数组: [1, 2, 3, 4, 5, 6, 7]" << endl;
    cout << "中序遍历: ";
    printInorder(root4);
    cout << "(期望: 1 2 3 4 5 6 7)" << endl;
    cout << "是否平衡: " << (isBalanced(root4) ? "是" : "否") << " (期望: 是)" << endl;
    cout << "树的高度: " << getHeight(root4) << " (期望: 3)" << endl;

    return 0;
}
