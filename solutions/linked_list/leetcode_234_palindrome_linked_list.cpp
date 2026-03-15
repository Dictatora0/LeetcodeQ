/*
LeetCode 234. 回文链表 (Palindrome Linked List)

题目概述 (Problem Summary)
-------------------------
给定一个单链表的头节点 head，请判断该链表是否为回文链表。

如果是，返回 true；否则，返回 false。

回文：正着读和反着读都一样，例如 1->2->2->1 是回文，1->2->3->4 不是回文。

关键约束 (Key Constraints)
-------------------------
- 链表中节点数目在范围 [1, 10^5] 内
- 0 <= Node.val <= 9

进阶要求：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

示例 (Example)
-------------
示例 1：
输入：head = [1,2,2,1]
输出：true
解释：链表是回文的

示例 2：
输入：head = [1,2]
输出：false
解释：链表不是回文的

示例 3：
输入：head = [1,2,3,2,1]
输出：true
解释：链表是回文的

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 判断链表是否对称（前半部分和后半部分反转后是否相同）

关键观察：
1. 回文的特点：正着读和反着读都一样
2. 对于链表：前半部分和后半部分反转后应该相同
3. 如何找到链表的中间位置？使用快慢指针
4. 如何比较前后两部分？反转后半部分，然后逐个比较

为什么使用快慢指针？
- 快慢指针可以一次遍历找到链表中点
- 慢指针到达中点时，快指针到达末尾
- 然后反转后半部分，与前半部分比较

算法流程（O(1) 空间解法）：
1. 使用快慢指针找到链表中点
2. 反转后半部分链表
3. 比较前半部分和反转后的后半部分
4. （可选）恢复链表结构
5. 返回比较结果

快慢指针找中点 + 反转后半部分图解：

奇数长度：[1,2,3,2,1]
  1 -> 2 -> 3 -> 2 -> 1 -> nullptr
  s,f

  1 -> 2 -> 3 -> 2 -> 1 -> nullptr
       s         f

  1 -> 2 -> 3 -> 2 -> 1 -> nullptr
            s              f (fast->next == nullptr，停止)

  slow 在中点 3，反转后半部分（从 slow->next 开始）：
  前半部分：1 -> 2 -> 3
  后半部分：1 -> 2（反转后）

  比较：1==1, 2==2，是回文

偶数长度：[1,2,2,1]
  1 -> 2 -> 2 -> 1 -> nullptr
  s,f

  1 -> 2 -> 2 -> 1 -> nullptr
       s         f

  1 -> 2 -> 2 -> 1 -> nullptr
            s         f (fast == nullptr，停止)

  slow 在第二个 2，反转后半部分（从 slow 开始）：
  前半部分：1 -> 2
  后半部分：1 -> 2（反转后）

  比较：1==1, 2==2，是回文

根据这些观察，可以得到几种典型解法：
1. 快慢指针 + 反转后半部分 - O(n) 时间，O(1) 空间（最优解）
2. 递归 - O(n) 时间，O(n) 空间（递归栈）
3. 数组辅助 - O(n) 时间，O(n) 空间（将链表存入数组）
*/

#include <iostream>
#include <vector>
#include <stack>

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
方法一：快慢指针 + 反转后半部分（O(1) 空间）(Approach 1: Fast-Slow Pointers + Reverse)

核心思想
--------
使用快慢指针找到链表中点，反转后半部分链表，然后比较前后两部分。

算法流程：
1. 使用快慢指针找到链表中点
   - slow 每次走 1 步，fast 每次走 2 步
   - 当 fast 到达末尾时，slow 在中点

2. 反转后半部分链表
   - 从 slow 开始反转（偶数长度）或从 slow->next 开始（奇数长度）
   - 使用三指针法反转链表

3. 比较前半部分和反转后的后半部分
   - 两个指针分别从头和反转后的后半部分开始
   - 逐个比较节点值

4. （可选）恢复链表结构
   - 再次反转后半部分，恢复原链表

5. 返回比较结果

复杂度分析
---------
时间复杂度：O(n)
- 找中点：O(n/2)
- 反转后半部分：O(n/2)
- 比较：O(n/2)
- 总共：O(n)

空间复杂度：O(1)
- 只使用了常数个指针变量

其中：
n = 链表节点总数
*/
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // 边界情况：空链表或只有一个节点
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        // 第一步：使用快慢指针找到链表中点
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 此时 slow 指向中点（奇数长度）或后半部分第一个节点（偶数长度）

        // 第二步：反转后半部分链表
        ListNode* secondHalf = reverseList(slow);

        // 第三步：比较前半部分和反转后的后半部分
        ListNode* p1 = head;           // 前半部分指针
        ListNode* p2 = secondHalf;     // 后半部分指针（已反转）
        bool result = true;

        while (p2 != nullptr) {  // 只需要遍历后半部分（较短或相等）
            if (p1->val != p2->val) {
                result = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // 第四步（可选）：恢复链表结构
        // 如果需要保持原链表不变，可以再次反转后半部分
        // reverseList(secondHalf);

        return result;
    }

private:
    // 辅助函数：反转链表
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;  // 保存下一个节点
            curr->next = prev;                // 反转指针
            prev = curr;                      // prev 前进
            curr = nextTemp;                  // curr 前进
        }

        return prev;  // prev 是新的头节点
    }
};

/*
方法二：递归 (Approach 2: Recursion)

核心思想
--------
使用递归到达链表末尾，然后在回溯过程中与前面的节点比较。

算法流程：
1. 使用递归到达链表末尾
2. 在回溯过程中，比较当前节点和对应的前面节点
3. 使用一个全局指针记录前面的节点位置

复杂度分析
---------
时间复杂度：O(n)
- 需要遍历整个链表

空间复杂度：O(n)
- 递归调用栈的深度为 n

其中：
n = 链表节点总数
*/
class Solution_Recursion {
private:
    ListNode* frontPointer;

public:
    bool isPalindrome(ListNode* head) {
        frontPointer = head;
        return recursivelyCheck(head);
    }

private:
    bool recursivelyCheck(ListNode* currentNode) {
        if (currentNode != nullptr) {
            // 递归到链表末尾
            if (!recursivelyCheck(currentNode->next)) {
                return false;
            }

            // 在回溯过程中比较
            if (currentNode->val != frontPointer->val) {
                return false;
            }

            // 前指针前进
            frontPointer = frontPointer->next;
        }

        return true;
    }
};

/*
方法三：数组辅助 (Approach 3: Array Helper)

核心思想
--------
将链表值存入数组，然后使用双指针判断数组是否回文。

算法流程：
1. 遍历链表，将所有节点值存入数组
2. 使用双指针（左右）判断数组是否回文
   - left 从 0 开始，right 从 n-1 开始
   - 比较 arr[left] 和 arr[right]
   - 如果不相等，返回 false
   - left++, right--
3. 如果所有比较都相等，返回 true

复杂度分析
---------
时间复杂度：O(n)
- 遍历链表：O(n)
- 双指针比较：O(n/2)
- 总共：O(n)

空间复杂度：O(n)
- 需要数组存储所有节点值

其中：
n = 链表节点总数
*/
class Solution_Array {
public:
    bool isPalindrome(ListNode* head) {
        // 将链表值存入数组
        vector<int> vals;
        ListNode* curr = head;

        while (curr != nullptr) {
            vals.push_back(curr->val);
            curr = curr->next;
        }

        // 使用双指针判断数组是否回文
        int left = 0;
        int right = vals.size() - 1;

        while (left < right) {
            if (vals[left] != vals[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }
};

/*
方法四：栈辅助（比较前半部分和后半部分）(Approach 4: Stack Helper)

核心思想
--------
使用快慢指针找到中点，将前半部分压入栈，然后与后半部分比较。

算法流程：
1. 使用快慢指针遍历链表
2. 在慢指针移动过程中，将节点值压入栈
3. 当快指针到达末尾时，慢指针在中点
4. 从慢指针开始，与栈中元素比较（栈顶是前半部分的最后一个元素）

复杂度分析
---------
时间复杂度：O(n)
- 遍历链表一次

空间复杂度：O(n/2) = O(n)
- 栈存储前半部分节点值

其中：
n = 链表节点总数
*/
class Solution_Stack {
public:
    bool isPalindrome(ListNode* head) {
        stack<int> stk;
        ListNode* slow = head;
        ListNode* fast = head;

        // 快慢指针遍历，同时将前半部分压入栈
        while (fast != nullptr && fast->next != nullptr) {
            stk.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }

        // 如果是奇数长度，跳过中间节点
        if (fast != nullptr) {
            slow = slow->next;
        }

        // 比较后半部分和栈中元素
        while (slow != nullptr) {
            if (slow->val != stk.top()) {
                return false;
            }
            stk.pop();
            slow = slow->next;
        }

        return true;
    }
};

/*
快慢指针判断回文链表模板代码 (Fast-Slow Pointer Template for Palindrome)
----------------------------------------------------------------------
这是判断回文链表的标准模板（O(1) 空间）：

bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    // 第一步：找中点
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 第二步：反转后半部分
    ListNode* secondHalf = reverseList(slow);

    // 第三步：比较前后两部分
    ListNode* p1 = head;
    ListNode* p2 = secondHalf;

    while (p2 != nullptr) {
        if (p1->val != p2->val) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    return true;
}

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr != nullptr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

关键点：
1. 快慢指针找中点（slow 走 1 步，fast 走 2 步）
2. 反转后半部分链表
3. 比较前后两部分（只需比较后半部分长度）
4. O(n) 时间，O(1) 空间
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：head = [1,2,2,1]（偶数长度，回文）

第一步：找中点
初始：slow = 1, fast = 1

第 1 次循环：
- slow = 2（第一个）
- fast = 2（第二个）
- fast != nullptr && fast->next != nullptr，继续

第 2 次循环：
- slow = 2（第二个）
- fast = nullptr
- fast == nullptr，停止

slow 指向第二个 2

第二步：反转后半部分（从第二个 2 开始）
原链表：1 -> 2 -> 2 -> 1 -> nullptr
反转后：1 -> 2 -> nullptr, 1 -> 2 -> nullptr

第三步：比较
p1 = 1, p2 = 1（反转后的后半部分头）
- 1 == 1，继续
- p1 = 2, p2 = 2
- 2 == 2，继续
- p2 == nullptr，停止

返回 true（是回文）

示例 2：head = [1,2]（偶数长度，非回文）

第一步：找中点
初始：slow = 1, fast = 1

第 1 次循环：
- slow = 2
- fast = nullptr
- fast == nullptr，停止

slow 指向 2

第二步：反转后半部分（从 2 开始）
原链表：1 -> 2 -> nullptr
反转后：1 -> nullptr, 2 -> nullptr

第三步：比较
p1 = 1, p2 = 2
- 1 != 2，返回 false

返回 false（不是回文）

示例 3：head = [1,2,3,2,1]（奇数长度，回文）

第一步：找中点
slow 最终指向 3（中间节点）

第二步：反转后半部分（从 3 开始）
原链表：1 -> 2 -> 3 -> 2 -> 1 -> nullptr
反转后：1 -> 2 -> nullptr, 1 -> 2 -> 3 -> nullptr

第三步：比较
p1 从 1 开始，p2 从反转后的 1 开始
- 1 == 1，2 == 2，3 != 1？
- 实际上，反转后的后半部分是：1 -> 2 -> 3
- 比较时：p1 = 1,2,3，p2 = 1,2,3
- 但我们只比较到 p2 为空，所以会比较 1==1, 2==2
- 中间的 3 不需要比较（奇数长度的中点）

返回 true（是回文）
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：快慢指针 + 反转后半部分
- 时间复杂度：O(n) ✓ 最优
- 空间复杂度：O(1) ✓ 最优
- 优点：满足进阶要求，时间和空间都是最优
- 缺点：会修改链表结构（可以恢复）

方法二：递归
- 时间复杂度：O(n) ✓ 最优
- 空间复杂度：O(n)（递归栈）
- 优点：代码简洁优雅
- 缺点：空间复杂度不满足进阶要求

方法三：数组辅助
- 时间复杂度：O(n) ✓ 最优
- 空间复杂度：O(n)
- 优点：思路最直观，容易理解
- 缺点：空间复杂度不满足进阶要求

方法四：栈辅助
- 时间复杂度：O(n) ✓ 最优
- 空间复杂度：O(n/2) = O(n)
- 优点：比数组方法节省一半空间
- 缺点：空间复杂度仍不满足进阶要求

推荐使用方法一（快慢指针 + 反转），这是满足进阶要求的最优解。
*/

/*
特殊情况处理 (Edge Cases)
------------------------
1. 空链表：head == nullptr
   - 返回 true（空链表是回文）

2. 单节点：head = [1]
   - 返回 true（单节点是回文）

3. 两个节点相同：head = [1,1]
   - 返回 true

4. 两个节点不同：head = [1,2]
   - 返回 false

5. 奇数长度回文：head = [1,2,3,2,1]
   - 中间节点不需要比较
   - 返回 true

6. 偶数长度回文：head = [1,2,2,1]
   - 前后两部分长度相等
   - 返回 true

7. 奇数长度非回文：head = [1,2,3,4,5]
   - 返回 false

8. 偶数长度非回文：head = [1,2,3,4]
   - 返回 false

奇偶长度的处理：
- 奇数长度：slow 指向中间节点，反转时从 slow 或 slow->next 开始都可以
  - 因为中间节点不需要比较
- 偶数长度：slow 指向后半部分第一个节点，反转从 slow 开始
  - 前后两部分长度相等，都需要比较
*/

/*
为什么反转后半部分而不是前半部分？
--------------------------------
技术上两种方式都可以，但反转后半部分更常见：

优点：
1. 不需要额外记录前半部分的尾节点
2. 比较时从头节点开始，逻辑更清晰
3. 如果需要恢复链表，只需要再次反转后半部分

如果反转前半部分：
1. 需要记录前半部分的尾节点（用于比较）
2. 需要记录前半部分反转后的头节点
3. 恢复链表时需要再次反转前半部分并重新连接

因此，反转后半部分是更优雅的选择。
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

    // 测试用例 1：偶数长度回文
    cout << "测试用例 1：偶数长度回文" << endl;
    vector<int> vals1 = {1, 2, 2, 1};
    ListNode* head1 = createList(vals1);
    cout << "链表: ";
    printList(head1);
    cout << "结果: " << (solution.isPalindrome(head1) ? "true" : "false") << endl;
    cout << "期望: true" << endl << endl;

    // 测试用例 2：两个节点非回文
    cout << "测试用例 2：两个节点非回文" << endl;
    vector<int> vals2 = {1, 2};
    ListNode* head2 = createList(vals2);
    cout << "链表: ";
    printList(head2);
    cout << "结果: " << (solution.isPalindrome(head2) ? "true" : "false") << endl;
    cout << "期望: false" << endl << endl;

    // 测试用例 3：奇数长度回文
    cout << "测试用例 3：奇数长度回文" << endl;
    vector<int> vals3 = {1, 2, 3, 2, 1};
    ListNode* head3 = createList(vals3);
    cout << "链表: ";
    printList(head3);
    cout << "结果: " << (solution.isPalindrome(head3) ? "true" : "false") << endl;
    cout << "期望: true" << endl << endl;

    // 测试用例 4：单节点
    cout << "测试用例 4：单节点" << endl;
    vector<int> vals4 = {1};
    ListNode* head4 = createList(vals4);
    cout << "链表: ";
    printList(head4);
    cout << "结果: " << (solution.isPalindrome(head4) ? "true" : "false") << endl;
    cout << "期望: true" << endl << endl;

    // 测试用例 5：长链表非回文
    cout << "测试用例 5：长链表非回文" << endl;
    vector<int> vals5 = {1, 2, 3, 4, 5};
    ListNode* head5 = createList(vals5);
    cout << "链表: ";
    printList(head5);
    cout << "结果: " << (solution.isPalindrome(head5) ? "true" : "false") << endl;
    cout << "期望: false" << endl;

    return 0;
}
