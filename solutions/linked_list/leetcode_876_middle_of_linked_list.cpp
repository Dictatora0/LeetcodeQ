/*
LeetCode 876. 链表的中间结点 (Middle of the Linked List)

题目概述 (Problem Summary)
-------------------------
给定一个头结点为 head 的非空单链表，返回链表的中间结点。

如果有两个中间结点，则返回第二个中间结点。

关键约束 (Key Constraints)
-------------------------
- 给定链表的结点数介于 1 和 100 之间
- 1 <= Node.val <= 100

示例 (Example)
-------------
示例 1：
输入：[1,2,3,4,5]
输出：此列表中的结点 3（序列化形式：[3,4,5]）
解释：返回的结点值为 3。注意，我们返回了一个 ListNode 类型的对象 ans，
     这样：ans.val = 3, ans.next.val = 4, ans.next.next.val = 5,
     ans.next.next.next = NULL

示例 2：
输入：[1,2,3,4,5,6]
输出：此列表中的结点 4（序列化形式：[4,5,6]）
解释：由于该列表有两个中间结点，值分别为 3 和 4，我们返回第二个结点

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在不知道链表长度的情况下，找到链表的中间节点

关键观察：
1. 如果知道链表长度 n，中间节点就是第 n/2 + 1 个节点（向上取整）
2. 但题目要求高效解法，最好一次遍历
3. 可以使用快慢指针技巧：
   - 慢指针每次走 1 步
   - 快指针每次走 2 步
   - 当快指针到达链表末尾时，慢指针正好在中间位置

为什么快慢指针能找到中间节点？
- 快指针速度是慢指针的 2 倍
- 当快指针走完整个链表时，慢指针走了一半
- 因此慢指针正好在中间位置

奇偶长度的处理：
- 奇数长度（如 5 个节点）：
  - 快指针：0 -> 2 -> 4（到达末尾）
  - 慢指针：0 -> 1 -> 2（中间节点）

- 偶数长度（如 6 个节点）：
  - 快指针：0 -> 2 -> 4 -> 6（超出末尾，fast->next == nullptr）
  - 慢指针：0 -> 1 -> 2 -> 3（第二个中间节点）

根据这些观察，可以得到几种典型解法：
1. 快慢指针 - O(n) 时间，O(1) 空间（最优解）
2. 两次遍历 - O(n) 时间，O(1) 空间（先求长度，再找中间）
3. 数组辅助 - O(n) 时间，O(n) 空间（将链表存入数组）
*/

#include <iostream>
#include <vector>

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
方法一：快慢指针（一次遍历）(Approach 1: Fast-Slow Pointers - One Pass)

核心思想
--------
使用快慢指针，慢指针每次走 1 步，快指针每次走 2 步。
当快指针到达链表末尾时，慢指针正好在中间位置。

算法流程：
1. 初始化快慢指针，都指向头节点
2. 循环移动指针：
   - slow 每次走 1 步：slow = slow->next
   - fast 每次走 2 步：fast = fast->next->next
3. 循环条件：fast != nullptr && fast->next != nullptr
4. 循环结束时，slow 指向中间节点

快慢指针找中间节点原理图解：

奇数长度（5 个节点）：
  1 -> 2 -> 3 -> 4 -> 5 -> nullptr
  s,f

  1 -> 2 -> 3 -> 4 -> 5 -> nullptr
       s         f

  1 -> 2 -> 3 -> 4 -> 5 -> nullptr
            s              f (fast->next == nullptr，停止)

  返回 slow = 3（中间节点）

偶数长度（6 个节点）：
  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr
  s,f

  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr
       s         f

  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr
            s              f

  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr
                 s                   f (fast == nullptr，停止)

  返回 slow = 4（第二个中间节点）

复杂度分析
---------
时间复杂度：O(n)
- 只需要遍历链表一次
- 快指针走 n/2 步，慢指针走 n/2 步

空间复杂度：O(1)
- 只使用了两个指针变量

其中：
n = 链表节点总数
*/
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // 边界情况：空链表（题目保证非空，但为了代码健壮性）
        if (head == nullptr) {
            return nullptr;
        }

        // 初始化快慢指针，都指向头节点
        ListNode* slow = head;  // 慢指针，每次走 1 步
        ListNode* fast = head;  // 快指针，每次走 2 步

        // 循环条件：快指针及其下一个节点不为空
        // fast != nullptr：处理偶数长度
        // fast->next != nullptr：处理奇数长度
        while (fast != nullptr && fast->next != nullptr) {
            // 慢指针走 1 步
            slow = slow->next;

            // 快指针走 2 步
            fast = fast->next->next;
        }

        // 循环结束时，slow 指向中间节点
        return slow;
    }
};

/*
方法二：两次遍历 (Approach 2: Two Pass)

核心思想
--------
第一次遍历求出链表长度，第二次遍历找到中间节点。

算法流程：
1. 第一次遍历：计算链表长度 n
2. 计算中间位置：mid = n / 2
3. 第二次遍历：从头节点走 mid 步，到达中间节点

复杂度分析
---------
时间复杂度：O(n)
- 第一次遍历：O(n)
- 第二次遍历：O(n/2)
- 总共：O(n)

空间复杂度：O(1)
- 只使用了常数个变量

其中：
n = 链表节点总数
*/
class Solution_TwoPass {
public:
    ListNode* middleNode(ListNode* head) {
        // 第一次遍历：计算链表长度
        int length = 0;
        ListNode* curr = head;
        while (curr != nullptr) {
            length++;
            curr = curr->next;
        }

        // 计算中间位置
        // 对于奇数长度，mid = length / 2（如 5/2 = 2，第 3 个节点）
        // 对于偶数长度，mid = length / 2（如 6/2 = 3，第 4 个节点）
        int mid = length / 2;

        // 第二次遍历：找到中间节点
        curr = head;
        for (int i = 0; i < mid; i++) {
            curr = curr->next;
        }

        return curr;
    }
};

/*
方法三：数组辅助 (Approach 3: Array Helper)

核心思想
--------
将链表节点存入数组，然后直接访问中间位置。

算法流程：
1. 遍历链表，将所有节点存入数组
2. 返回数组的中间元素：arr[arr.size() / 2]

复杂度分析
---------
时间复杂度：O(n)
- 遍历链表：O(n)
- 访问数组：O(1)

空间复杂度：O(n)
- 需要数组存储所有节点

其中：
n = 链表节点总数
*/
class Solution_Array {
public:
    ListNode* middleNode(ListNode* head) {
        // 将链表节点存入数组
        vector<ListNode*> arr;
        ListNode* curr = head;

        while (curr != nullptr) {
            arr.push_back(curr);
            curr = curr->next;
        }

        // 返回中间节点
        // 对于奇数长度：arr.size() / 2 是中间位置
        // 对于偶数长度：arr.size() / 2 是第二个中间位置
        return arr[arr.size() / 2];
    }
};

/*
快慢指针找中间节点模板代码 (Fast-Slow Pointer Template for Middle Node)
----------------------------------------------------------------------
这是找链表中间节点的标准模板，可以直接套用：

ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;        // 慢指针走 1 步
        fast = fast->next->next;  // 快指针走 2 步
    }

    return slow;  // 中间节点
}

关键点：
1. 初始化：slow 和 fast 都从 head 开始
2. 移动速度：slow 走 1 步，fast 走 2 步
3. 循环条件：fast != nullptr && fast->next != nullptr
4. 返回值：slow（中间节点）

变体：如果要返回第一个中间节点（偶数长度时）
- 可以在循环条件中调整，或者记录 slow 的前一个节点
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：head = [1,2,3,4,5]（奇数长度）

执行过程：
初始：slow = 1, fast = 1

第 1 次循环：
- slow = slow->next = 2
- fast = fast->next->next = 3
- fast != nullptr && fast->next != nullptr，继续

第 2 次循环：
- slow = slow->next = 3
- fast = fast->next->next = 5
- fast != nullptr && fast->next == nullptr，停止

返回 slow = 3（中间节点）

示例 2：head = [1,2,3,4,5,6]（偶数长度）

执行过程：
初始：slow = 1, fast = 1

第 1 次循环：
- slow = slow->next = 2
- fast = fast->next->next = 3
- fast != nullptr && fast->next != nullptr，继续

第 2 次循环：
- slow = slow->next = 3
- fast = fast->next->next = 5
- fast != nullptr && fast->next != nullptr，继续

第 3 次循环：
- slow = slow->next = 4
- fast = fast->next->next = nullptr
- fast == nullptr，停止

返回 slow = 4（第二个中间节点）

示例 3：head = [1]（单节点）

执行过程：
初始：slow = 1, fast = 1
- fast->next == nullptr，直接停止

返回 slow = 1（唯一节点）

示例 4：head = [1,2]（两个节点）

执行过程：
初始：slow = 1, fast = 1

第 1 次循环：
- slow = slow->next = 2
- fast = fast->next->next = nullptr
- fast == nullptr，停止

返回 slow = 2（第二个节点）
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：快慢指针（一次遍历）
- 时间复杂度：O(n)
- 空间复杂度：O(1) ✓ 最优
- 优点：一次遍历，空间效率高
- 缺点：需要理解快慢指针原理

方法二：两次遍历
- 时间复杂度：O(n)
- 空间复杂度：O(1) ✓ 最优
- 优点：思路直观，容易理解
- 缺点：需要遍历两次

方法三：数组辅助
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：最直观，可以随机访问
- 缺点：需要额外的数组空间

推荐使用方法一（快慢指针），这是找中间节点的经典算法。
*/

/*
特殊情况处理 (Edge Cases)
------------------------
1. 单节点：head = [1]
   - fast->next == nullptr，直接返回 head
   - 结果：[1]

2. 两个节点：head = [1,2]
   - 第一次循环后 fast == nullptr
   - slow = 2（第二个节点）
   - 结果：[2]

3. 奇数长度：head = [1,2,3,4,5]
   - 返回正中间的节点（节点 3）
   - 结果：[3,4,5]

4. 偶数长度：head = [1,2,3,4,5,6]
   - 返回第二个中间节点（节点 4）
   - 结果：[4,5,6]

5. 大量节点：head = [1,2,...,100]
   - 快慢指针依然高效
   - 时间复杂度 O(n)，空间复杂度 O(1)

循环条件的重要性：
- fast != nullptr：处理偶数长度，防止 fast 为空时访问 fast->next
- fast->next != nullptr：处理奇数长度，防止 fast->next 为空时访问 fast->next->next
- 两个条件缺一不可
*/

/*
奇偶长度的详细分析
----------------
为什么偶数长度返回第二个中间节点？

这取决于循环条件和初始化：
- 初始化：slow = head, fast = head
- 循环条件：fast != nullptr && fast->next != nullptr

对于偶数长度 n：
- 快指针走 n/2 次后，fast == nullptr
- 慢指针走 n/2 次后，slow 在第 n/2 + 1 个位置
- 例如 n = 6：slow 在第 4 个位置（第二个中间节点）

如果要返回第一个中间节点（偶数长度时）：
方法 1：调整初始化
  ListNode* slow = head;
  ListNode* fast = head->next;  // fast 从第二个节点开始

方法 2：记录前一个节点
  ListNode* prev = nullptr;
  ListNode* slow = head;
  ListNode* fast = head;

  while (fast != nullptr && fast->next != nullptr) {
      prev = slow;
      slow = slow->next;
      fast = fast->next->next;
  }

  // 如果是偶数长度，返回 prev
  return (fast == nullptr) ? prev : slow;
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

    // 测试用例 1：奇数长度
    cout << "测试用例 1：奇数长度" << endl;
    vector<int> vals1 = {1, 2, 3, 4, 5};
    ListNode* head1 = createList(vals1);
    cout << "原链表: ";
    printList(head1);
    ListNode* result1 = solution.middleNode(head1);
    cout << "中间节点开始: ";
    printList(result1);
    cout << "期望: [3,4,5]" << endl << endl;

    // 测试用例 2：偶数长度
    cout << "测试用例 2：偶数长度" << endl;
    vector<int> vals2 = {1, 2, 3, 4, 5, 6};
    ListNode* head2 = createList(vals2);
    cout << "原链表: ";
    printList(head2);
    ListNode* result2 = solution.middleNode(head2);
    cout << "中间节点开始: ";
    printList(result2);
    cout << "期望: [4,5,6]" << endl << endl;

    // 测试用例 3：单节点
    cout << "测试用例 3：单节点" << endl;
    vector<int> vals3 = {1};
    ListNode* head3 = createList(vals3);
    cout << "原链表: ";
    printList(head3);
    ListNode* result3 = solution.middleNode(head3);
    cout << "中间节点开始: ";
    printList(result3);
    cout << "期望: [1]" << endl << endl;

    // 测试用例 4：两个节点
    cout << "测试用例 4：两个节点" << endl;
    vector<int> vals4 = {1, 2};
    ListNode* head4 = createList(vals4);
    cout << "原链表: ";
    printList(head4);
    ListNode* result4 = solution.middleNode(head4);
    cout << "中间节点开始: ";
    printList(result4);
    cout << "期望: [2]" << endl;

    return 0;
}
