/*
LeetCode 114. 二叉树展开为链表 (Flatten Binary Tree to Linked List)

题目概述 (Problem Summary)
-------------------------
给定一个二叉树的根节点 root，请将其展开为一个单链表：
- 展开后的单链表应该使用 TreeNode，其中 right 子指针指向链表中下一个节点，而左子指针始终为 null
- 展开后的单链表应该与二叉树的前序遍历顺序相同

关键约束 (Key Constraints)
-------------------------
- 树中节点数在范围 [0, 2000] 内
- -100 <= Node.val <= 100
- 要求原地展开，即不能创建新节点

示例 (Example)
-------------
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]

解释：
原始树：
    1
   / \
  2   5
 / \   \
3   4   6

展开后（前序遍历顺序）：
1 -> 2 -> 3 -> 4 -> 5 -> 6

表示为树结构：
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6

输入：root = []
输出：[]

输入：root = [0]
输出：[0]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 将二叉树按前序遍历的顺序重新连接成单链表

关键观察：
1. 前序遍历的顺序是：根 -> 左 -> 右
2. 展开后的链表顺序应该是前序遍历的顺序
3. 需要原地修改，不能创建新节点
4. 每个节点的 left 指针都要设为 null，right 指针指向下一个节点

根据这些观察，可以得到几种典型解法：
1. 逆前序遍历（右 -> 左 -> 根）+ 头插法 - 最巧妙
2. 前序遍历 + 记录前驱节点
3. 迭代方法（找前驱节点）
*/

#include <iostream>
#include <vector>
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
方法一：我的原始解法 - 逆前序遍历 + 头插法 (Approach 1: My Original Solution - Reverse Preorder)

核心思想
--------
使用逆前序遍历（右 -> 左 -> 根），配合头插法构建链表。

算法流程：
1. 维护一个全局变量 head，表示当前链表的头节点
2. 按照"右 -> 左 -> 根"的顺序递归遍历树（逆前序遍历）
3. 对于每个节点：
   a. 先递归处理右子树
   b. 再递归处理左子树
   c. 将当前节点的 left 设为 nullptr
   d. 将当前节点的 right 指向 head（头插法）
   e. 更新 head 为当前节点
4. 遍历结束后，head 指向展开后的链表头

为什么要逆前序遍历？
- 前序遍历顺序：根 -> 左 -> 右 = [1, 2, 3, 4, 5, 6]
- 逆前序遍历顺序：右 -> 左 -> 根 = [6, 5, 4, 3, 2, 1]
- 使用头插法，最后访问的节点会成为链表的头
- 逆序访问 + 头插法 = 正序链表

为什么这样做是正确的？
- 逆前序遍历保证了我们按照"6 -> 5 -> 4 -> 3 -> 2 -> 1"的顺序访问节点
- 每次将当前节点插入到链表头部
- 最终得到的链表顺序是"1 -> 2 -> 3 -> 4 -> 5 -> 6"

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
    // head: 当前链表的头节点
    TreeNode *head;

    void flatten(TreeNode *root) {
        // 递归终止条件：空节点
        if (!root) {
            return;
        }

        // 逆前序遍历：右 -> 左 -> 根
        flatten(root->right);  // 先处理右子树
        flatten(root->left);   // 再处理左子树

        // 处理当前节点（根）
        root->left = nullptr;   // 左子树设为 null
        root->right = head;     // 右子树指向当前链表头
        head = root;            // 更新链表头为当前节点（头插法）
    }
};

/*
方法二：前序遍历 + 记录前驱节点 (Approach 2: Preorder Traversal with Predecessor)

核心思想
--------
按照前序遍历的顺序访问节点，同时记录前一个访问的节点（前驱节点）。
将前驱节点的 right 指向当前节点。

算法流程：
1. 维护一个全局变量 prev，表示前一个访问的节点
2. 按照"根 -> 左 -> 右"的顺序递归遍历树（前序遍历）
3. 对于每个节点：
   a. 保存左右子节点（因为后续会修改）
   b. 如果 prev 存在，将 prev->right 指向当前节点，prev->left 设为 null
   c. 更新 prev 为当前节点
   d. 递归处理左子树
   e. 递归处理右子树

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(h)
*/
class Solution_Preorder {
public:
    TreeNode* prev = nullptr;

    void flatten(TreeNode* root) {
        if (!root) return;

        // 保存左右子节点（因为后续会修改）
        TreeNode* left = root->left;
        TreeNode* right = root->right;

        // 如果存在前驱节点，连接前驱节点和当前节点
        if (prev) {
            prev->left = nullptr;
            prev->right = root;
        }

        // 更新前驱节点
        prev = root;

        // 递归处理左右子树
        flatten(left);
        flatten(right);
    }
};

/*
方法三：迭代方法（找前驱节点） (Approach 3: Iterative with Predecessor)

核心思想
--------
对于每个节点，如果存在左子树，找到左子树的最右节点（前驱节点），
将右子树接到前驱节点的右边，然后将左子树移到右边。

算法流程：
1. 从根节点开始遍历
2. 对于每个节点：
   a. 如果左子树存在：
      - 找到左子树的最右节点 predecessor
      - 将右子树接到 predecessor 的右边
      - 将左子树移到右边
      - 将左子树设为 null
   b. 移动到右子节点
3. 重复直到遍历完所有节点

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(1)
- 只使用常数额外空间
*/
class Solution_Iterative {
public:
    void flatten(TreeNode* root) {
        TreeNode* curr = root;

        while (curr) {
            if (curr->left) {
                // 找到左子树的最右节点
                TreeNode* predecessor = curr->left;
                while (predecessor->right) {
                    predecessor = predecessor->right;
                }

                // 将右子树接到前驱节点的右边
                predecessor->right = curr->right;

                // 将左子树移到右边
                curr->right = curr->left;
                curr->left = nullptr;
            }

            // 移动到下一个节点
            curr = curr->right;
        }
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
原始树：
    1
   / \
  2   5
 / \   \
3   4   6

方法一（逆前序遍历）的执行过程：

初始：head = nullptr

1. flatten(1)
   - flatten(5)
     - flatten(6)
       - flatten(null)  // 右子树
       - flatten(null)  // 左子树
       - 6->left = null, 6->right = null, head = 6
     - flatten(null)  // 左子树
     - 5->left = null, 5->right = 6, head = 5
   - flatten(2)
     - flatten(4)
       - flatten(null)  // 右子树
       - flatten(null)  // 左子树
       - 4->left = null, 4->right = 5, head = 4
     - flatten(3)
       - flatten(null)  // 右子树
       - flatten(null)  // 左子树
       - 3->left = null, 3->right = 4, head = 3
     - 2->left = null, 2->right = 3, head = 2
   - 1->left = null, 1->right = 2, head = 1

最终结果：
1 -> 2 -> 3 -> 4 -> 5 -> 6
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：逆前序遍历 + 头插法
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：代码简洁，思路巧妙
- 缺点：需要理解逆前序遍历的含义

方法二：前序遍历 + 记录前驱
- 时间复杂度：O(n)
- 空间复杂度：O(h)
- 优点：思路直观，符合前序遍历的定义
- 缺点：需要保存左右子节点

方法三：迭代方法
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间复杂度最优，不使用递归
- 缺点：代码稍复杂

推荐使用方法一，代码最简洁。
如果要求 O(1) 空间，使用方法三。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空树：root = nullptr，直接返回
2. 只有根节点：无需修改
3. 只有左子树：将左子树移到右边
4. 只有右子树：无需修改
5. 链状树（已经是链表形式）：无需修改或只需将 left 设为 null
*/

// 辅助函数：打印展开后的链表
void printFlattenedTree(TreeNode* root) {
    TreeNode* curr = root;
    while (curr) {
        cout << curr->val;
        if (curr->right) cout << " -> ";
        if (curr->left) {
            cout << " [ERROR: left should be null]";
        }
        curr = curr->right;
    }
    cout << endl;
}

int main() {
    Solution solution;

    // 测试用例 1：示例中的树
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(5);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(4);
    root1->right->right = new TreeNode(6);

    cout << "测试用例 1 - 原始树: [1,2,5,3,4,null,6]" << endl;
    solution.flatten(root1);
    cout << "展开后: ";
    printFlattenedTree(root1);
    cout << "(期望: 1 -> 2 -> 3 -> 4 -> 5 -> 6)" << endl;

    // 测试用例 2：单节点
    TreeNode* root2 = new TreeNode(0);
    cout << "\n测试用例 2 - 单节点: [0]" << endl;
    solution.flatten(root2);
    cout << "展开后: ";
    printFlattenedTree(root2);
    cout << "(期望: 0)" << endl;

    // 测试用例 3：只有左子树
    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->left->left = new TreeNode(3);
    cout << "\n测试用例 3 - 只有左子树: [1,2,null,3]" << endl;
    solution.flatten(root3);
    cout << "展开后: ";
    printFlattenedTree(root3);
    cout << "(期望: 1 -> 2 -> 3)" << endl;

    // 测试用例 4：只有右子树
    TreeNode* root4 = new TreeNode(1);
    root4->right = new TreeNode(2);
    root4->right->right = new TreeNode(3);
    cout << "\n测试用例 4 - 只有右子树: [1,null,2,null,3]" << endl;
    solution.flatten(root4);
    cout << "展开后: ";
    printFlattenedTree(root4);
    cout << "(期望: 1 -> 2 -> 3)" << endl;

    return 0;
}
