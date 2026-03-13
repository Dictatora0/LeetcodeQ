/*
LeetCode 24. 两两交换链表中的节点 (Swap Nodes in Pairs)

题目概述 (Problem Summary)
-------------------------
给定一个链表的头节点 head，两两交换其中相邻的节点，并返回交换后链表的头节点。

必须在不修改节点内部的值的情况下完成本题（即只能进行节点交换）。

关键约束 (Key Constraints)
-------------------------
- 链表中节点的数目在范围 [0, 100] 内
- 0 <= Node.val <= 100

示例 (Example)
-------------
输入：head = [1,2,3,4]
输出：[2,1,4,3]
解释：
原链表：1 -> 2 -> 3 -> 4
交换后：2 -> 1 -> 4 -> 3

输入：head = []
输出：[]

输入：head = [1]
输出：[1]

输入：head = [1,2,3]
输出：[2,1,3]
解释：最后一个节点没有配对，保持不变

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 将链表中每相邻的两个节点进行交换，不能修改节点的值

关键观察：
1. 这是一个指针操作问题，需要改变节点的 next 指针
2. 每次交换涉及 3 个指针的调整：
   - prev->next 指向第二个节点
   - 第一个节点的 next 指向第二个节点的 next
   - 第二个节点的 next 指向第一个节点
3. 使用虚拟头节点可以简化边界情况的处理
4. 可以用递归或迭代实现

根据这些观察，可以得到几种典型解法：
1. 迭代 + 虚拟头节点 - 最直观
2. 递归 - 代码简洁
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
方法一：我的原始解法 - 迭代 + 虚拟头节点 (Approach 1: My Original Solution - Iterative with Dummy)

核心思想
--------
使用虚拟头节点简化边界处理，通过迭代的方式逐对交换节点。

算法流程：
1. 创建虚拟头节点 dummy，dummy->next = head
2. 初始化 prev 指针指向 dummy
3. 当还有至少两个节点可以交换时：
   a. 记录当前节点 cur 和下一个节点 sub
   b. 执行交换：
      - prev->next = sub
      - cur->next = sub->next
      - sub->next = cur
   c. 移动 prev 到下一对节点的前一个位置（即当前的 cur）
4. 返回 dummy->next（新的头节点）

交换过程图示：
交换前：prev -> cur -> sub -> next
交换后：prev -> sub -> cur -> next

为什么使用虚拟头节点？
- 统一处理头节点和其他节点的交换
- 避免特殊判断第一对节点的情况

复杂度分析
---------
时间复杂度：O(n)
- 遍历链表一次，每个节点访问常数次

空间复杂度：O(1)
- 只使用了常数个指针变量

其中：
n = 链表长度
*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // 边界情况：空链表或只有一个节点，无需交换
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // 创建虚拟头节点，dummy->next 指向原头节点
        ListNode* dummy = new ListNode();
        dummy->next = head;

        // prev 指向待交换节点对的前一个节点（初始为 dummy）
        ListNode* prev = dummy;

        // 只要还有至少两个节点可以交换，就继续
        // 条件：prev->next 和 prev->next->next 都不为空
        while (prev->next != nullptr && prev->next->next != nullptr) {
            ListNode* cur = prev->next;        // 当前节点（第一个要交换的节点）
            ListNode* sub = prev->next->next;  // 后方节点（第二个要交换的节点）

            // 执行交换：prev -> cur -> sub -> next
            // 变成：prev -> sub -> cur -> next
            prev->next = sub;       // prev 指向 sub
            cur->next = sub->next;  // cur 指向 sub 的下一个节点
            sub->next = cur;        // sub 指向 cur

            // prev 移动到下一对节点的前一个位置（即当前的 cur）
            // 因为 cur 现在在 sub 后面，是下一对节点的前一个节点
            prev = cur;
        }

        // 返回新的头节点（dummy->next 可能已改变）
        ListNode* newHead = dummy->next;
        delete dummy;  // 释放虚拟节点
        return newHead;
    }
};

/*
方法二：递归 (Approach 2: Recursive)

核心思想
--------
将问题分解为：交换前两个节点 + 递归处理剩余链表。

算法流程：
1. 递归终止条件：如果链表为空或只有一个节点，返回 head
2. 记录第一个节点 first 和第二个节点 second
3. first->next = swapPairs(second->next)  // 递归处理剩余部分
4. second->next = first  // 交换前两个节点
5. 返回 second（新的头节点）

递归思路：
- 每次递归处理两个节点的交换
- 将剩余部分的处理交给递归调用
- 最后拼接起来

复杂度分析
---------
时间复杂度：O(n)
- 每个节点访问一次

空间复杂度：O(n)
- 递归调用栈的深度为 n/2，即 O(n)
*/
class Solution_Recursive {
public:
    ListNode* swapPairs(ListNode* head) {
        // 递归终止条件：空链表或只有一个节点
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // 记录前两个节点
        ListNode* first = head;
        ListNode* second = head->next;

        // 递归处理剩余部分，并连接到 first 后面
        first->next = swapPairs(second->next);

        // 交换前两个节点
        second->next = first;

        // 返回新的头节点（原来的第二个节点）
        return second;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：head = [1,2,3,4]

方法一（迭代）的执行过程：
1. 初始化：dummy -> 1 -> 2 -> 3 -> 4
   prev = dummy

2. 第一次交换（交换 1 和 2）：
   - cur = 1, sub = 2
   - 执行交换：
     * prev->next = 2
     * cur->next = 3
     * sub->next = 1
   - 结果：dummy -> 2 -> 1 -> 3 -> 4
   - prev = 1

3. 第二次交换（交换 3 和 4）：
   - cur = 3, sub = 4
   - 执行交换：
     * prev->next = 4
     * cur->next = nullptr
     * sub->next = 3
   - 结果：dummy -> 2 -> 1 -> 4 -> 3
   - prev = 3

4. 循环结束（prev->next->next == nullptr）
5. 返回 dummy->next = 2

最终结果：[2,1,4,3]

方法二（递归）的执行过程：
1. swapPairs([1,2,3,4])
   - first = 1, second = 2
   - first->next = swapPairs([3,4])
     - first = 3, second = 4
     - first->next = swapPairs([]) = nullptr
     - second->next = first
     - 返回 4 -> 3
   - first->next = 4 -> 3，即 1 -> 4 -> 3
   - second->next = first，即 2 -> 1 -> 4 -> 3
   - 返回 2

最终结果：[2,1,4,3]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：迭代 + 虚拟头节点
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间效率高，不使用递归栈
- 缺点：代码稍长，需要仔细处理指针

方法二：递归
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：代码简洁，逻辑清晰
- 缺点：使用递归栈，空间开销较大

推荐使用方法一（迭代），空间效率更高。
如果追求代码简洁，可以使用方法二（递归）。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空链表：直接返回 nullptr
2. 只有一个节点：无需交换，返回原节点
3. 奇数个节点：最后一个节点不交换
4. 偶数个节点：所有节点都参与交换
5. 两个节点：交换后返回第二个节点
*/

// 辅助函数：创建链表
ListNode* createList(vector<int>& vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* curr = head;
    for (int i = 1; i < vals.size(); i++) {
        curr->next = new ListNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    ListNode* curr = head;
    cout << "[";
    while (curr) {
        cout << curr->val;
        if (curr->next) cout << ",";
        curr = curr->next;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // 测试用例 1：偶数个节点
    vector<int> vals1 = {1, 2, 3, 4};
    ListNode* head1 = createList(vals1);
    cout << "测试用例 1 - 原链表: ";
    printList(head1);
    head1 = solution.swapPairs(head1);
    cout << "交换后: ";
    printList(head1);
    cout << "期望: [2,1,4,3]" << endl << endl;

    // 测试用例 2：奇数个节点
    vector<int> vals2 = {1, 2, 3};
    ListNode* head2 = createList(vals2);
    cout << "测试用例 2 - 原链表: ";
    printList(head2);
    head2 = solution.swapPairs(head2);
    cout << "交换后: ";
    printList(head2);
    cout << "期望: [2,1,3]" << endl << endl;

    // 测试用例 3：单节点
    vector<int> vals3 = {1};
    ListNode* head3 = createList(vals3);
    cout << "测试用例 3 - 原链表: ";
    printList(head3);
    head3 = solution.swapPairs(head3);
    cout << "交换后: ";
    printList(head3);
    cout << "期望: [1]" << endl << endl;

    // 测试用例 4：空链表
    ListNode* head4 = nullptr;
    cout << "测试用例 4 - 原链表: []" << endl;
    head4 = solution.swapPairs(head4);
    cout << "交换后: ";
    printList(head4);
    cout << "期望: []" << endl;

    return 0;
}
