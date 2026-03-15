/*
LeetCode 141. 环形链表 (Linked List Cycle)

题目概述 (Problem Summary)
-------------------------
给定一个链表的头节点 head，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
注意：pos 不作为参数进行传递。仅仅是为了标识链表的实际情况。

如果链表中存在环，则返回 true。否则，返回 false。

关键约束 (Key Constraints)
-------------------------
- 链表中节点的数目范围是 [0, 10^4]
- -10^5 <= Node.val <= 10^5
- pos 为 -1 或者链表中的一个有效索引

进阶要求：你能用 O(1)（即常量）内存解决此问题吗？

示例 (Example)
-------------
示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点（值为 2）

示例 2：
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点（值为 1）

示例 3：
输入：head = [1], pos = -1
输出：false
解释：链表中没有环

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 检测链表中是否存在环（循环）

关键观察：
1. 如果链表有环，遍历时会无限循环，永远不会到达 nullptr
2. 如果链表无环，遍历时最终会到达链表末尾（nullptr）
3. 如何在有限时间内判断是否有环？

为什么使用快慢指针？
- 想象在环形跑道上，两个人以不同速度跑步
- 快的人最终会追上慢的人（套圈）
- 如果不是环形跑道，快的人会先到达终点

快慢指针原理：
1. 慢指针每次走 1 步，快指针每次走 2 步
2. 如果链表无环，快指针会先到达链表末尾（nullptr）
3. 如果链表有环，快指针会在环内追上慢指针
4. 为什么一定能追上？
   - 快指针进入环后，每次循环都会缩短与慢指针的距离 1 步
   - 最终距离会变为 0，即相遇

根据这些观察，可以得到几种典型解法：
1. 快慢指针 - O(n) 时间，O(1) 空间（最优解）
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
方法一：快慢指针（经典解法）(Approach 1: Fast-Slow Pointers - Floyd's Cycle Detection)

核心思想
--------
使用两个指针，慢指针每次走 1 步，快指针每次走 2 步。
如果链表有环，快指针最终会追上慢指针（在环内相遇）。
如果链表无环，快指针会先到达链表末尾。

算法流程：
1. 初始化慢指针 slow 和快指针 fast，都指向头节点
2. 循环移动指针：
   - slow 每次走 1 步：slow = slow->next
   - fast 每次走 2 步：fast = fast->next->next
3. 判断条件：
   - 如果 fast 或 fast->next 为空，说明到达链表末尾，无环
   - 如果 slow == fast，说明两指针相遇，有环

快慢指针相遇原理图解：

无环情况：
  1 -> 2 -> 3 -> 4 -> nullptr
  s,f

  1 -> 2 -> 3 -> 4 -> nullptr
       s    f

  1 -> 2 -> 3 -> 4 -> nullptr
            s         f (到达末尾，无环)

有环情况：
  1 -> 2 -> 3 -> 4
       ^         |
       |_________|

  初始：slow = 1, fast = 1
  第1步：slow = 2, fast = 3
  第2步：slow = 3, fast = 2
  第3步：slow = 4, fast = 4（相遇！）

为什么快指针一定能追上慢指针？
- 当慢指针进入环时，快指针已经在环内
- 假设此时快慢指针距离为 d（d < 环的长度）
- 每次移动，快指针比慢指针多走 1 步，距离缩短 1
- 经过 d 次移动后，距离变为 0，即相遇

复杂度分析
---------
时间复杂度：O(n)
- 无环情况：快指针走到链表末尾，最多走 n/2 步
- 有环情况：
  - 慢指针走到环入口需要 k 步（k < n）
  - 在环内相遇最多需要环的长度步数
  - 总共最多 n 步

空间复杂度：O(1)
- 只使用了两个指针变量

其中：
n = 链表节点总数
*/
class Solution {
public:
    bool hasCycle(ListNode *head) {
        // 边界情况：空链表或只有一个节点
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        // 初始化快慢指针
        ListNode* slow = head;  // 慢指针，每次走 1 步
        ListNode* fast = head;  // 快指针，每次走 2 步

        // 循环条件：快指针及其下一个节点不为空
        // 为什么要检查 fast->next？
        // 因为 fast 要走两步，需要确保 fast->next 存在
        while (fast != nullptr && fast->next != nullptr) {
            // 慢指针走 1 步
            slow = slow->next;

            // 快指针走 2 步
            fast = fast->next->next;

            // 如果快慢指针相遇，说明有环
            if (slow == fast) {
                return true;
            }
        }

        // 快指针到达链表末尾，说明无环
        return false;
    }
};

/*
方法二：哈希表 (Approach 2: Hash Set)

核心思想
--------
遍历链表，用哈希表记录访问过的节点。
如果遇到已访问过的节点，说明有环。
如果遍历到链表末尾，说明无环。

算法流程：
1. 创建哈希集合 visited
2. 从头节点开始遍历链表
3. 对于每个节点：
   - 如果节点已在 visited 中，返回 true（有环）
   - 否则将节点加入 visited
4. 如果遍历到 nullptr，返回 false（无环）

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
    bool hasCycle(ListNode *head) {
        // 使用哈希集合记录访问过的节点
        unordered_set<ListNode*> visited;

        // 遍历链表
        ListNode* curr = head;
        while (curr != nullptr) {
            // 如果当前节点已访问过，说明有环
            if (visited.count(curr)) {
                return true;
            }

            // 将当前节点加入已访问集合
            visited.insert(curr);

            // 移动到下一个节点
            curr = curr->next;
        }

        // 遍历到链表末尾，说明无环
        return false;
    }
};

/*
快慢指针模板代码 (Fast-Slow Pointer Template)
------------------------------------------
这是检测链表环的标准模板，可以直接套用：

bool hasCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return false;
    }

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;        // 慢指针走 1 步
        fast = fast->next->next;  // 快指针走 2 步

        if (slow == fast) {       // 相遇则有环
            return true;
        }
    }

    return false;  // 快指针到达末尾，无环
}

关键点：
1. 初始化：slow 和 fast 都从 head 开始
2. 移动速度：slow 走 1 步，fast 走 2 步
3. 循环条件：fast != nullptr && fast->next != nullptr
4. 相遇判断：slow == fast
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：head = [3,2,0,-4], pos = 1（有环）

链表结构：
  3 -> 2 -> 0 -> -4
       ^          |
       |__________|

执行过程：
初始：slow = 3, fast = 3

第 1 次循环：
- slow = slow->next = 2
- fast = fast->next->next = 0
- slow != fast，继续

第 2 次循环：
- slow = slow->next = 0
- fast = fast->next->next = 2
- slow != fast，继续

第 3 次循环：
- slow = slow->next = -4
- fast = fast->next->next = -4
- slow == fast，返回 true（有环）

示例 2：head = [1,2], pos = -1（无环）

链表结构：
  1 -> 2 -> nullptr

执行过程：
初始：slow = 1, fast = 1

第 1 次循环：
- slow = slow->next = 2
- fast = fast->next->next = nullptr
- fast == nullptr，退出循环

返回 false（无环）

示例 3：head = [1], pos = -1（单节点无环）

链表结构：
  1 -> nullptr

边界检查：
- head->next == nullptr
- 直接返回 false（无环）
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：快慢指针
- 时间复杂度：O(n)
- 空间复杂度：O(1) ✓ 最优
- 优点：空间效率高，满足进阶要求
- 缺点：需要理解快慢指针原理

方法二：哈希表
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：思路直观，容易理解
- 缺点：需要额外的哈希表空间

推荐使用方法一（快慢指针），这是检测链表环的经典算法。
*/

/*
特殊情况处理 (Edge Cases)
------------------------
1. 空链表：head == nullptr
   - 返回 false

2. 单节点无环：head->next == nullptr
   - 返回 false

3. 单节点有环：节点指向自己
   - 快慢指针会在第一次循环后相遇
   - 返回 true

4. 两节点有环：1 -> 2 -> 1
   - 快慢指针会相遇
   - 返回 true

5. 环在链表开头：第一个节点就是环的入口
   - 正常检测，返回 true

6. 环在链表末尾：最后几个节点形成环
   - 正常检测，返回 true

边界条件检查的重要性：
- 必须检查 fast != nullptr && fast->next != nullptr
- 如果只检查 fast != nullptr，当 fast->next 为空时，
  执行 fast->next->next 会导致空指针异常
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
    }

    return nodes[0];
}

// 辅助函数：打印链表（仅打印前 n 个节点，避免无限循环）
void printList(ListNode* head, int maxNodes = 10) {
    ListNode* curr = head;
    cout << "[";
    int count = 0;
    while (curr && count < maxNodes) {
        cout << curr->val;
        if (curr->next && count < maxNodes - 1) cout << ",";
        curr = curr->next;
        count++;
    }
    if (curr) cout << "...";
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // 测试用例 1：有环，环在中间
    cout << "测试用例 1：有环，pos = 1" << endl;
    vector<int> vals1 = {3, 2, 0, -4};
    ListNode* head1 = createCycleList(vals1, 1);
    cout << "链表: [3,2,0,-4], pos = 1" << endl;
    cout << "结果: " << (solution.hasCycle(head1) ? "true" : "false") << endl;
    cout << "期望: true" << endl << endl;

    // 测试用例 2：有环，环在开头
    cout << "测试用例 2：有环，pos = 0" << endl;
    vector<int> vals2 = {1, 2};
    ListNode* head2 = createCycleList(vals2, 0);
    cout << "链表: [1,2], pos = 0" << endl;
    cout << "结果: " << (solution.hasCycle(head2) ? "true" : "false") << endl;
    cout << "期望: true" << endl << endl;

    // 测试用例 3：无环
    cout << "测试用例 3：无环，pos = -1" << endl;
    vector<int> vals3 = {1};
    ListNode* head3 = createCycleList(vals3, -1);
    cout << "链表: [1], pos = -1" << endl;
    cout << "结果: " << (solution.hasCycle(head3) ? "true" : "false") << endl;
    cout << "期望: false" << endl << endl;

    // 测试用例 4：空链表
    cout << "测试用例 4：空链表" << endl;
    ListNode* head4 = nullptr;
    cout << "链表: [], pos = -1" << endl;
    cout << "结果: " << (solution.hasCycle(head4) ? "true" : "false") << endl;
    cout << "期望: false" << endl << endl;

    // 测试用例 5：单节点有环
    cout << "测试用例 5：单节点有环，pos = 0" << endl;
    vector<int> vals5 = {1};
    ListNode* head5 = createCycleList(vals5, 0);
    cout << "链表: [1], pos = 0" << endl;
    cout << "结果: " << (solution.hasCycle(head5) ? "true" : "false") << endl;
    cout << "期望: true" << endl;

    return 0;
}

