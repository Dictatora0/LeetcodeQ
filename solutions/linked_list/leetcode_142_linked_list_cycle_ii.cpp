/*
LeetCode 142. 环形链表 II (Linked List Cycle II)

题目概述 (Problem Summary)
-------------------------
给定一个链表的头节点 head，返回链表开始入环的第一个节点。如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。

注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
不允许修改链表。

关键约束 (Key Constraints)
-------------------------
- 链表中节点的数目范围在 [0, 10^4]
- -10^5 <= Node.val <= 10^5
- pos 为 -1 或者链表中的一个有效索引

进阶要求：你是否可以使用 O(1) 空间解决此题？

示例 (Example)
-------------
示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点

示例 2：
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点

示例 3：
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 不仅要检测链表是否有环，还要找到环的入口节点

关键观察：
1. 首先需要判断链表是否有环（使用快慢指针）
2. 如果有环，如何找到环的入口？

数学推导（核心）：
假设：
- 链表头到环入口的距离为 a
- 环入口到快慢指针相遇点的距离为 b
- 相遇点到环入口的距离为 c
- 环的长度为 b + c

链表结构：
  head -> ... -> 环入口 -> ... -> 相遇点 -> ... -> 环入口
  |<---- a ---->|<-- b -->|<-- c -->|

当快慢指针相遇时：
- 慢指针走过的距离：a + b
- 快指针走过的距离：a + b + n(b + c)，其中 n 是快指针在环内多走的圈数
- 因为快指针速度是慢指针的 2 倍：2(a + b) = a + b + n(b + c)

化简：
  2a + 2b = a + b + n(b + c)
  a + b = n(b + c)
  a = n(b + c) - b
  a = (n-1)(b + c) + c

关键结论：
当 n = 1 时（快指针在环内只多走了一圈）：
  a = c

这意味着：
- 从链表头到环入口的距离 = 从相遇点到环入口的距离
- 因此，让一个指针从头开始，另一个从相遇点开始，同时每次走 1 步
- 它们会在环入口相遇！

根据这些观察，可以得到几种典型解法：
1. 快慢指针 + 数学推导 - O(n) 时间，O(1) 空间（最优解）
2. 哈希表 - O(n) 时间，O(n) 空间（直观但空间复杂度高）
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
方法一：快慢指针 + 数学推导（经典解法）(Approach 1: Fast-Slow Pointers with Math)

核心思想
--------
分两个阶段：
1. 第一阶段：使用快慢指针检测是否有环，并找到相遇点
2. 第二阶段：一个指针从头开始，另一个从相遇点开始，同时每次走 1 步，相遇点即为环入口

算法流程：
1. 初始化快慢指针，都从头节点开始
2. 快指针每次走 2 步，慢指针每次走 1 步
3. 如果快指针到达末尾，说明无环，返回 nullptr
4. 如果快慢指针相遇，说明有环
5. 将一个指针重置到头节点，另一个保持在相遇点
6. 两个指针同时每次走 1 步，相遇点即为环入口

数学原理图解：

链表结构：
  1 -> 2 -> 3 -> 4 -> 5 -> 6
            ^              |
            |______________|

  a = 2（头到环入口：1->2->3）
  b = 2（环入口到相遇点：3->4->5）
  c = 2（相遇点到环入口：5->6->3）

第一阶段（检测环并找相遇点）：
- 慢指针走：a + b = 2 + 2 = 4 步
- 快指针走：a + b + (b + c) = 2 + 2 + 4 = 8 步
- 在节点 5 相遇

第二阶段（找环入口）：
- ptr1 从头开始：1 -> 2 -> 3
- ptr2 从相遇点开始：5 -> 6 -> 3
- 在节点 3（环入口）相遇

复杂度分析
---------
时间复杂度：O(n)
- 第一阶段：快慢指针检测环，最多 n 步
- 第二阶段：找环入口，最多 n 步
- 总共 O(n)

空间复杂度：O(1)
- 只使用了常数个指针变量

其中：
n = 链表节点总数
*/
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // 边界情况：空链表或只有一个节点
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }

        // 第一阶段：使用快慢指针检测环
        ListNode* slow = head;
        ListNode* fast = head;

        // 找到快慢指针的相遇点
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;        // 慢指针走 1 步
            fast = fast->next->next;  // 快指针走 2 步

            // 如果相遇，说明有环
            if (slow == fast) {
                // 第二阶段：找环的入口
                // 一个指针从头开始，另一个从相遇点开始
                ListNode* ptr1 = head;
                ListNode* ptr2 = slow;  // 或 fast，因为此时 slow == fast

                // 两个指针同时每次走 1 步
                while (ptr1 != ptr2) {
                    ptr1 = ptr1->next;
                    ptr2 = ptr2->next;
                }

                // 相遇点即为环的入口
                return ptr1;
            }
        }

        // 快指针到达链表末尾，说明无环
        return nullptr;
    }
};

/*
方法二：哈希表 (Approach 2: Hash Set)

核心思想
--------
遍历链表，用哈希表记录访问过的节点。
第一个重复访问的节点就是环的入口。

算法流程：
1. 创建哈希集合 visited
2. 从头节点开始遍历链表
3. 对于每个节点：
   - 如果节点已在 visited 中，返回该节点（环入口）
   - 否则将节点加入 visited
4. 如果遍历到 nullptr，返回 nullptr（无环）

复杂度分析
---------
时间复杂度：O(n)
- 需要遍历链表中的每个节点一次

空间复杂度：O(n)
- 需要哈希表存储所有访问过的节点

其中：
n = 链表节点总数
*/
class Solution_HashSet {
public:
    ListNode *detectCycle(ListNode *head) {
        // 使用哈希集合记录访问过的节点
        unordered_set<ListNode*> visited;

        // 遍历链表
        ListNode* curr = head;
        while (curr != nullptr) {
            // 如果当前节点已访问过，说明这是环的入口
            if (visited.count(curr)) {
                return curr;
            }

            // 将当前节点加入已访问集合
            visited.insert(curr);

            // 移动到下一个节点
            curr = curr->next;
        }

        // 遍历到链表末尾，说明无环
        return nullptr;
    }
};

/*
快慢指针找环入口模板代码 (Fast-Slow Pointer Template for Cycle Entry)
--------------------------------------------------------------------
这是找链表环入口的标准模板，可以直接套用：

ListNode *detectCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    // 第一阶段：检测环并找相遇点
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            // 第二阶段：找环入口
            ListNode* ptr1 = head;
            ListNode* ptr2 = slow;

            while (ptr1 != ptr2) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }

            return ptr1;  // 环入口
        }
    }

    return nullptr;  // 无环
}

关键点：
1. 第一阶段：快慢指针检测环（slow 走 1 步，fast 走 2 步）
2. 第二阶段：两指针同时走 1 步找入口（一个从头，一个从相遇点）
3. 数学原理：a = c（头到入口 = 相遇点到入口）
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：head = [3,2,0,-4], pos = 1

链表结构：
  3 -> 2 -> 0 -> -4
       ^          |
       |__________|

  a = 1（3 -> 2）
  b = 1（2 -> 0）
  c = 2（0 -> -4 -> 2）

第一阶段：检测环
初始：slow = 3, fast = 3

第 1 次循环：
- slow = 2, fast = 0
- slow != fast，继续

第 2 次循环：
- slow = 0, fast = 2
- slow != fast，继续

第 3 次循环：
- slow = -4, fast = -4
- slow == fast，相遇！相遇点是 -4

第二阶段：找环入口
- ptr1 = 3（从头开始）
- ptr2 = -4（从相遇点开始）

第 1 次循环：
- ptr1 = 2
- ptr2 = 2
- ptr1 == ptr2，找到环入口！

返回节点 2（索引为 1）

验证数学公式：
- a = 1（3 -> 2）
- c = 2（-4 -> 2，在环内走 2 步）
- 实际上 c = 2 步到达入口，但因为环的特性，
  从 -4 走 2 步：-4 -> 2 -> 0，然后 ptr1 从 3 走 1 步到 2
  它们在入口 2 相遇

示例 2：head = [1,2], pos = 0

链表结构：
  1 -> 2
  ^    |
  |____|

  a = 0（头节点就是环入口）
  b = 1（1 -> 2）
  c = 1（2 -> 1）

第一阶段：
- 快慢指针会在环内相遇

第二阶段：
- ptr1 从头开始（节点 1）
- ptr2 从相遇点开始
- 因为 a = 0，ptr1 已经在环入口
- ptr2 走 c 步也会到达环入口
- 它们在节点 1 相遇

返回节点 1（索引为 0）
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：快慢指针 + 数学推导
- 时间复杂度：O(n)
- 空间复杂度：O(1) ✓ 最优
- 优点：空间效率高，满足进阶要求
- 缺点：需要理解数学推导

方法二：哈希表
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：思路直观，容易理解
- 缺点：需要额外的哈希表空间

推荐使用方法一（快慢指针），这是找环入口的经典算法。
*/

/*
特殊情况处理 (Edge Cases)
------------------------
1. 空链表：head == nullptr
   - 返回 nullptr

2. 单节点无环：head->next == nullptr
   - 返回 nullptr

3. 单节点有环：节点指向自己
   - 第一阶段：快慢指针在第一次循环后相遇
   - 第二阶段：ptr1 从头开始就是环入口，ptr2 也在环入口
   - 返回该节点

4. 两节点有环：1 -> 2 -> 1
   - 正常检测，返回环入口

5. 环在链表开头：第一个节点就是环的入口（a = 0）
   - ptr1 从头开始就在环入口
   - ptr2 从相遇点走 c 步到达环入口
   - 因为 a = c = 0（当 a = 0 时，c 也等于环长度的倍数）
   - 返回头节点

6. 整个链表都是环：所有节点都在环内
   - a = 0，头节点就是环入口
   - 返回头节点

数学推导的通用性：
- 公式 a = c 在所有情况下都成立
- 包括 a = 0（环在开头）的特殊情况
*/

/*
为什么 a = c？深入理解
---------------------
设：
- 链表头到环入口距离：a
- 环入口到相遇点距离：b
- 相遇点到环入口距离：c
- 环长度：L = b + c

相遇时：
- 慢指针走了：a + b
- 快指针走了：a + b + nL（n 是快指针比慢指针多走的圈数）

因为快指针速度是慢指针的 2 倍：
  2(a + b) = a + b + nL
  a + b = nL
  a = nL - b
  a = n(b + c) - b
  a = nb + nc - b
  a = (n-1)b + b + nc - b
  a = (n-1)b + nc
  a = (n-1)(b + c) + c
  a = (n-1)L + c

当 n = 1 时（最常见的情况）：
  a = c

当 n > 1 时：
  a = (n-1)L + c
  这意味着从相遇点走 a 步，等于走 (n-1) 圈再走 c 步
  最终还是会到达环入口

因此，无论 n 是多少，从头和从相遇点同时走，都会在环入口相遇！
*/

// 辅助函数：创建带环的链表
ListNode* createCycleList(vector<int>& vals, int pos) {
    if (vals.empty()) return nullptr;

    // 创建链表节点
    vector<ListNode*> nodes;
    for (int val : vals) {
        nodes.push_back(new ListNode(val));
    }

    // 连接节点
    for (int i = 0; i < nodes.size() - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }

    // 创建环
    if (pos >= 0 && pos < nodes.size()) {
        nodes[nodes.size() - 1]->next = nodes[pos];
        return nodes[0];  // 返回头节点
    }

    return nodes[0];
}

// 辅助函数：获取节点在链表中的索引
int getNodeIndex(ListNode* head, ListNode* target) {
    if (target == nullptr) return -1;

    ListNode* curr = head;
    int index = 0;
    unordered_set<ListNode*> visited;

    while (curr != nullptr) {
        if (curr == target) {
            return index;
        }
        if (visited.count(curr)) {
            break;  // 避免无限循环
        }
        visited.insert(curr);
        curr = curr->next;
        index++;
    }

    return -1;
}

int main() {
    Solution solution;

    // 测试用例 1：有环，环在中间
    cout << "测试用例 1：有环，pos = 1" << endl;
    vector<int> vals1 = {3, 2, 0, -4};
    ListNode* head1 = createCycleList(vals1, 1);
    ListNode* result1 = solution.detectCycle(head1);
    cout << "链表: [3,2,0,-4], pos = 1" << endl;
    cout << "结果索引: " << getNodeIndex(head1, result1) << endl;
    cout << "期望索引: 1" << endl << endl;

    // 测试用例 2：有环，环在开头
    cout << "测试用例 2：有环，pos = 0" << endl;
    vector<int> vals2 = {1, 2};
    ListNode* head2 = createCycleList(vals2, 0);
    ListNode* result2 = solution.detectCycle(head2);
    cout << "链表: [1,2], pos = 0" << endl;
    cout << "结果索引: " << getNodeIndex(head2, result2) << endl;
    cout << "期望索引: 0" << endl << endl;

    // 测试用例 3：无环
    cout << "测试用例 3：无环，pos = -1" << endl;
    vector<int> vals3 = {1};
    ListNode* head3 = createCycleList(vals3, -1);
    ListNode* result3 = solution.detectCycle(head3);
    cout << "链表: [1], pos = -1" << endl;
    cout << "结果: " << (result3 == nullptr ? "nullptr" : "有环") << endl;
    cout << "期望: nullptr" << endl << endl;

    // 测试用例 4：单节点有环
    cout << "测试用例 4：单节点有环，pos = 0" << endl;
    vector<int> vals4 = {1};
    ListNode* head4 = createCycleList(vals4, 0);
    ListNode* result4 = solution.detectCycle(head4);
    cout << "链表: [1], pos = 0" << endl;
    cout << "结果索引: " << getNodeIndex(head4, result4) << endl;
    cout << "期望索引: 0" << endl;

    return 0;
}
