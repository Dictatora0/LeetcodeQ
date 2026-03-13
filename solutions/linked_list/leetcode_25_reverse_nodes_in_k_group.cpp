/*
LeetCode 25. K 个一组翻转链表 (Reverse Nodes in k-Group)

题目概述 (Problem Summary)
-------------------------
给你链表的头节点 head，每 k 个节点一组进行翻转，请你返回修改后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，
那么请将最后剩余的节点保持原有顺序。

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

关键约束 (Key Constraints)
-------------------------
- 链表中的节点数目为 n
- 1 <= k <= n <= 5000
- 0 <= Node.val <= 1000

进阶要求：你可以设计一个只用 O(1) 额外内存空间的算法解决此问题吗？

示例 (Example)
-------------
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
解释：每 2 个节点一组翻转，最后剩余 1 个节点保持原样

输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]
解释：每 3 个节点一组翻转，最后剩余 2 个节点保持原样

输入：head = [1,2,3,4,5], k = 1
输出：[1,2,3,4,5]
解释：k = 1 时不需要翻转

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 将链表分成若干个长度为 k 的子链表，对每个子链表进行翻转
- 不足 k 个节点的部分保持原样

关键观察：
1. 这是链表翻转的进阶版本，需要分组翻转
2. 每组翻转后，需要正确连接前后部分
3. 需要先检查剩余节点数是否足够 k 个
4. 可以使用递归或迭代两种方式实现

递归思路：
1. 先检查从当前位置开始是否有 k 个节点
2. 如果有，翻转这 k 个节点
3. 递归处理剩余部分
4. 连接翻转后的部分和递归结果

迭代思路：
1. 使用虚拟头节点简化边界处理
2. 用指针标记每组的起始和结束位置
3. 逐组翻转并连接

根据这些观察，可以得到几种典型解法：
1. 递归法 - 代码简洁，O(n) 时间，O(n/k) 递归栈空间
2. 迭代法 - O(n) 时间，O(1) 空间
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;            // 节点存储的值
    ListNode *next;     // 指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}                    // 默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}               // 单参数构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}  // 双参数构造函数
};

/*
方法一：我的原始解法 - 递归法 (Approach 1: My Original Solution - Recursive)

核心思想
--------
使用递归的方式处理每一组 k 个节点：
1. 先检查是否有足够的 k 个节点
2. 如果有，翻转这 k 个节点
3. 递归处理剩余部分
4. 将翻转后的部分与递归结果连接

算法流程：
1. 边界检查：如果 head 为空或 k <= 1，直接返回
2. 检查从 head 开始是否有至少 k 个节点
   - 如果不足 k 个，保持原顺序，直接返回 head
3. 翻转前 k 个节点（标准链表翻转）
4. 递归处理剩余部分
5. 将原来的 head（翻转后变成尾节点）连接到递归结果
6. 返回翻转后的新头节点

为什么使用递归？
- 每组的处理逻辑相同，符合递归的特点
- 递归可以自然地处理"翻转 k 个 + 处理剩余部分"的逻辑
- 代码简洁易懂

翻转过程详解：
- 翻转前：1 -> 2 -> 3 -> 4 -> 5
- 翻转 k=3 个节点后：3 -> 2 -> 1，此时 1 的 next 指向 4
- prev 指向 3（新头），current 指向 4（剩余部分的头）
- 原来的 head（1）变成了尾节点

复杂度分析
---------
时间复杂度：O(n)
- n 是链表长度
- 每个节点被访问常数次（检查 + 翻转）

空间复杂度：O(n/k)
- 递归调用栈的深度为 n/k（链表被分成 n/k 组）
- 每次递归只使用常数空间

其中：
n = 链表长度
k = 每组节点数
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 边界情况：如果 head 为空或者 k <= 1，直接返回
        // k <= 1 时不需要翻转
        if (!head || k <= 1) {
            return head;
        }

        // 第一步：检查从当前 head 开始是否有至少 k 个节点
        ListNode* curr = head;
        for (int i = 0; i < k; i++) {
            if (!curr) {
                // 不足 k 个节点，保持原顺序，直接返回 head
                return head;
            }
            curr = curr->next;
        }

        // 第二步：翻转前 k 个节点
        // 使用标准的链表翻转算法
        ListNode* prev = nullptr;      // 前一个节点
        ListNode* current = head;      // 当前节点
        ListNode* next = nullptr;      // 下一个节点

        // 翻转 k 个节点
        // 循环结束后：
        // - prev 指向翻转后的新头节点（原来的第 k 个节点）
        // - current 指向第 k+1 个节点（剩余部分的头节点）
        // - head 指向翻转后的尾节点（原来的第 1 个节点）
        for (int i = 0; i < k; i++) {
            next = current->next;    // 保存下一个节点
            current->next = prev;    // 当前节点指向前一个节点（反转指针）
            prev = current;          // prev 向前移动
            current = next;          // current 向前移动
        }

        // 第三步：递归处理剩余的链表
        // 此时：
        // - prev 是翻转后的新头节点
        // - head 是翻转后的尾节点（原来的头节点）
        // - current 指向剩余未处理部分的头节点
        // 将翻转后的尾节点连接到递归处理后的剩余部分
        head->next = reverseKGroup(current, k);

        // 返回翻转后的头节点
        return prev;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：head = [1,2,3,4,5], k = 3

执行过程：
1. 第一次调用 reverseKGroup([1,2,3,4,5], 3)
   - 检查：有 5 个节点，足够 3 个，继续
   - 翻转前 3 个节点：
     * i=0: next=2, 1->null, prev=1, current=2
     * i=1: next=3, 2->1, prev=2, current=3
     * i=2: next=4, 3->2, prev=3, current=4
   - 翻转后：3 -> 2 -> 1，current=4
   - 递归调用 reverseKGroup([4,5], 3)

2. 第二次调用 reverseKGroup([4,5], 3)
   - 检查：只有 2 个节点，不足 3 个
   - 直接返回 [4,5]

3. 回到第一次调用
   - head(1)->next = [4,5]
   - 返回 prev(3)

最终结果：[3,2,1,4,5]

详细的指针变化：
初始：1 -> 2 -> 3 -> 4 -> 5

翻转前 3 个节点的过程：
- 开始：prev=null, current=1, next=null
- i=0: next=2, 1->null, prev=1, current=2
  状态：null <- 1    2 -> 3 -> 4 -> 5
- i=1: next=3, 2->1, prev=2, current=3
  状态：null <- 1 <- 2    3 -> 4 -> 5
- i=2: next=4, 3->2, prev=3, current=4
  状态：null <- 1 <- 2 <- 3    4 -> 5

翻转后：3 -> 2 -> 1 -> null，current=4
连接：1 -> reverseKGroup(4->5, 3) = 1 -> 4 -> 5
最终：3 -> 2 -> 1 -> 4 -> 5
*/

/*
方法二：迭代法 (Approach 2: Iterative)

核心思想
--------
使用迭代的方式，逐组处理每 k 个节点。
使用虚拟头节点简化边界处理。

算法流程：
1. 创建虚拟头节点 dummy
2. 使用 prevGroupEnd 指针标记上一组的尾节点
3. 对每一组：
   - 检查是否有 k 个节点
   - 如果有，翻转这 k 个节点
   - 连接上一组和当前组
   - 更新 prevGroupEnd
4. 返回 dummy->next

优点：
- 空间复杂度 O(1)，不使用递归栈
- 更符合迭代思维

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_Iterative {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k <= 1) {
            return head;
        }

        // 创建虚拟头节点
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        // prevGroupEnd 指向上一组的尾节点
        ListNode* prevGroupEnd = dummy;

        while (true) {
            // 检查是否还有 k 个节点
            ListNode* kthNode = prevGroupEnd;
            for (int i = 0; i < k; i++) {
                kthNode = kthNode->next;
                if (!kthNode) {
                    // 不足 k 个节点，结束
                    return dummy->next;
                }
            }

            // 记录下一组的头节点
            ListNode* nextGroupHead = kthNode->next;

            // 翻转当前组
            ListNode* prev = nextGroupHead;
            ListNode* curr = prevGroupEnd->next;
            while (curr != nextGroupHead) {
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            // 连接上一组和当前组
            ListNode* currentGroupHead = prevGroupEnd->next;
            prevGroupEnd->next = kthNode;
            prevGroupEnd = currentGroupHead;
        }
    }
};

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：递归法
- 时间复杂度：O(n)
- 空间复杂度：O(n/k) - 递归栈
- 优点：代码简洁，逻辑清晰
- 缺点：使用递归栈空间

方法二：迭代法
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间效率更高，满足进阶要求
- 缺点：代码相对复杂

如果面试要求 O(1) 空间，使用方法二；否则方法一更简洁。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. k = 1：不需要翻转，直接返回原链表
2. k 等于链表长度：翻转整个链表
3. 链表长度小于 k：保持原样
4. 链表长度是 k 的整数倍：所有节点都被翻转
5. 只有一个节点：无论 k 是多少，都返回原节点
6. 空链表：返回 null
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

    // 测试用例 1：k = 2，链表长度为奇数
    vector<int> vals1 = {1, 2, 3, 4, 5};
    ListNode* head1 = createList(vals1);
    cout << "测试用例 1 - 原链表: ";
    printList(head1);
    head1 = solution.reverseKGroup(head1, 2);
    cout << "每 2 个节点翻转后: ";
    printList(head1);
    cout << "期望: [2,1,4,3,5]" << endl << endl;

    // 测试用例 2：k = 3，有剩余节点
    vector<int> vals2 = {1, 2, 3, 4, 5};
    ListNode* head2 = createList(vals2);
    cout << "测试用例 2 - 原链表: ";
    printList(head2);
    head2 = solution.reverseKGroup(head2, 3);
    cout << "每 3 个节点翻转后: ";
    printList(head2);
    cout << "期望: [3,2,1,4,5]" << endl << endl;

    // 测试用例 3：k = 1，不翻转
    vector<int> vals3 = {1, 2, 3, 4, 5};
    ListNode* head3 = createList(vals3);
    cout << "测试用例 3 - 原链表: ";
    printList(head3);
    head3 = solution.reverseKGroup(head3, 1);
    cout << "每 1 个节点翻转后: ";
    printList(head3);
    cout << "期望: [1,2,3,4,5]" << endl << endl;

    // 测试用例 4：k 等于链表长度
    vector<int> vals4 = {1, 2, 3};
    ListNode* head4 = createList(vals4);
    cout << "测试用例 4 - 原链表: ";
    printList(head4);
    head4 = solution.reverseKGroup(head4, 3);
    cout << "每 3 个节点翻转后: ";
    printList(head4);
    cout << "期望: [3,2,1]" << endl << endl;

    // 测试用例 5：k 大于链表长度
    vector<int> vals5 = {1, 2};
    ListNode* head5 = createList(vals5);
    cout << "测试用例 5 - 原链表: ";
    printList(head5);
    head5 = solution.reverseKGroup(head5, 3);
    cout << "每 3 个节点翻转后: ";
    printList(head5);
    cout << "期望: [1,2]" << endl;

    return 0;
}
