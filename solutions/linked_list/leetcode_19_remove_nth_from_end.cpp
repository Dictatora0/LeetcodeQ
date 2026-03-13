/*
LeetCode 19. 删除链表的倒数第 N 个结点 (Remove Nth Node From End of List)

题目概述 (Problem Summary)
-------------------------
给定一个链表的头节点 head，删除链表的倒数第 n 个节点，并返回链表的头节点。

关键约束 (Key Constraints)
-------------------------
- 链表中节点的数目为 sz
- 1 <= sz <= 30
- 0 <= Node.val <= 100
- 1 <= n <= sz

进阶要求：能否用一趟扫描实现？

示例 (Example)
-------------
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
解释：删除倒数第 2 个节点（值为 4 的节点）

输入：head = [1], n = 1
输出：[]
解释：删除唯一的节点

输入：head = [1,2], n = 1
输出：[1]
解释：删除倒数第 1 个节点（值为 2 的节点）

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在不知道链表总长度的情况下，找到并删除倒数第 n 个节点

关键观察：
1. 如果知道链表长度 L，倒数第 n 个节点就是正数第 (L-n+1) 个节点
2. 但题目要求一趟扫描，不能先遍历一次求长度
3. 可以使用双指针（快慢指针）技巧：
   - 让快指针先走 n 步
   - 然后快慢指针同时移动
   - 当快指针到达末尾时，慢指针正好在倒数第 n 个节点的前一个位置
4. 需要处理删除头节点的特殊情况

根据这些观察，可以得到几种典型解法：
1. 双指针（快慢指针）- 一趟扫描，O(n) 时间
2. 两次遍历 - 先求长度，再删除，O(2n) 时间
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
方法一：我的原始解法 - 双指针（快慢指针）(Approach 1: My Original Solution - Two Pointers)

核心思想
--------
使用快慢指针，让快指针先走 n 步，然后两个指针同时移动。
当快指针到达链表末尾时，慢指针正好指向倒数第 n 个节点的前一个节点。

算法流程：
1. 初始化快慢指针都指向头节点
2. 让快指针先向前移动 n 步
3. 特殊情况：如果快指针已经为空，说明要删除的是头节点
4. 同时移动快慢指针，直到快指针到达最后一个节点
5. 此时慢指针指向要删除节点的前一个节点
6. 执行删除操作：prev->next = prev->next->next

为什么快指针先走 n 步？
- 这样可以保持快慢指针之间相距 n 个节点
- 当快指针到达末尾时，慢指针自然就在倒数第 n+1 个位置
- 即要删除节点的前一个位置

复杂度分析
---------
时间复杂度：O(L)
- L 是链表长度
- 只需要遍历一次链表

空间复杂度：O(1)
- 只使用了常数个指针变量

其中：
L = 链表长度
*/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 边界情况：空链表或只有一个节点且要删除它
        if (head == NULL || head->next == NULL) {
            return NULL;
        }

        // 初始化快慢指针，都指向头节点
        ListNode* prev = head;  // 慢指针
        ListNode* sub = head;   // 快指针

        // 让快指针先向前移动 n 步
        // 这样快慢指针之间就保持了 n 个节点的距离
        for (int i = 0; i < n; i++) {
            sub = sub->next;
        }

        // 特殊情况：如果快指针已经到达链表末尾（sub == NULL）
        // 说明要删除的是头节点（倒数第 n 个节点就是第一个节点）
        if (sub == NULL) {
            ListNode* dummy = new ListNode();  // 创建虚拟头节点
            dummy->next = head->next;          // 跳过原头节点
            return dummy->next;                // 返回新的头节点
        }

        // 同时移动快慢指针，直到快指针到达链表的最后一个节点
        // 循环结束时：
        // - sub 指向最后一个节点（sub->next == NULL）
        // - prev 指向倒数第 n+1 个节点（即要删除节点的前一个节点）
        while (sub->next != NULL) {
            sub = sub->next;
            prev = prev->next;
        }

        // 执行删除操作
        ListNode* temp = prev->next;  // temp 指向要删除的节点
        prev->next = temp->next;      // 跳过要删除的节点
        delete temp;                  // 释放内存

        return head;  // 返回原链表头节点
    }
};

/*
方法二：使用虚拟头节点优化 (Approach 2: Using Dummy Head)

核心思想
--------
使用虚拟头节点可以统一处理删除头节点和删除其他节点的情况。

算法流程：
1. 创建虚拟头节点 dummy，dummy->next = head
2. 初始化快慢指针都指向 dummy
3. 让快指针先走 n+1 步（注意是 n+1，因为从 dummy 开始）
4. 同时移动快慢指针，直到快指针为空
5. 此时慢指针指向要删除节点的前一个节点
6. 执行删除操作

优点：
- 不需要特殊处理删除头节点的情况
- 代码更简洁统一

复杂度分析
---------
时间复杂度：O(L)
空间复杂度：O(1)
*/
class Solution_DummyHead {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 创建虚拟头节点
        ListNode* dummy = new ListNode(0, head);

        // 初始化快慢指针，都指向虚拟头节点
        ListNode* slow = dummy;
        ListNode* fast = dummy;

        // 让快指针先走 n+1 步
        // 为什么是 n+1？因为我们从 dummy 开始，需要让 slow 停在要删除节点的前一个位置
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // 同时移动快慢指针，直到快指针为空
        while (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }

        // 此时 slow 指向要删除节点的前一个节点
        ListNode* toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete;

        // 返回新的头节点
        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：head = [1,2,3,4,5], n = 2

方法一的执行过程：
1. 初始化：prev = 1, sub = 1
2. 快指针先走 2 步：
   - sub = 2
   - sub = 3
   - 现在：prev = 1, sub = 3
3. 同时移动直到 sub->next == NULL：
   - prev = 2, sub = 4
   - prev = 3, sub = 5（sub->next == NULL，停止）
4. 此时 prev = 3，prev->next = 4（要删除的节点）
5. 执行删除：prev->next = 5
6. 结果：[1,2,3,5]

方法二（使用虚拟头节点）的执行过程：
1. 创建 dummy -> 1 -> 2 -> 3 -> 4 -> 5
2. 初始化：slow = dummy, fast = dummy
3. 快指针先走 3 步（n+1）：
   - fast = 1
   - fast = 2
   - fast = 3
4. 同时移动直到 fast == NULL：
   - slow = 1, fast = 4
   - slow = 2, fast = 5
   - slow = 3, fast = NULL（停止）
5. 此时 slow = 3，slow->next = 4（要删除的节点）
6. 执行删除：slow->next = 5
7. 返回 dummy->next = 1
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：双指针（原始解法）
- 时间复杂度：O(L)
- 空间复杂度：O(1)
- 优点：一趟扫描，效率高
- 缺点：需要特殊处理删除头节点的情况

方法二：使用虚拟头节点
- 时间复杂度：O(L)
- 空间复杂度：O(1)
- 优点：代码更简洁，统一处理所有情况
- 缺点：需要额外创建虚拟节点

两种方法时间和空间复杂度相同，方法二代码更简洁。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 删除头节点：n 等于链表长度
2. 删除尾节点：n = 1
3. 只有一个节点：删除后返回空链表
4. 只有两个节点：删除其中一个
5. n 等于链表长度：删除头节点
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

    // 测试用例 1：删除中间节点
    vector<int> vals1 = {1, 2, 3, 4, 5};
    ListNode* head1 = createList(vals1);
    cout << "测试用例 1 - 原链表: ";
    printList(head1);
    head1 = solution.removeNthFromEnd(head1, 2);
    cout << "删除倒数第 2 个节点后: ";
    printList(head1);
    cout << "期望: [1,2,3,5]" << endl << endl;

    // 测试用例 2：删除唯一节点
    vector<int> vals2 = {1};
    ListNode* head2 = createList(vals2);
    cout << "测试用例 2 - 原链表: ";
    printList(head2);
    head2 = solution.removeNthFromEnd(head2, 1);
    cout << "删除倒数第 1 个节点后: ";
    printList(head2);
    cout << "期望: []" << endl << endl;

    // 测试用例 3：删除头节点
    vector<int> vals3 = {1, 2};
    ListNode* head3 = createList(vals3);
    cout << "测试用例 3 - 原链表: ";
    printList(head3);
    head3 = solution.removeNthFromEnd(head3, 2);
    cout << "删除倒数第 2 个节点后: ";
    printList(head3);
    cout << "期望: [2]" << endl;

    return 0;
}
