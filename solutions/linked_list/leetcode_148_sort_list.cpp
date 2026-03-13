/*
LeetCode 148. 排序链表 (Sort List)

题目概述 (Problem Summary)
-------------------------
给你链表的头结点 head，请将其按升序排列并返回排序后的链表。

关键约束 (Key Constraints)
-------------------------
- 链表中节点的数目在范围 [0, 5 * 10^4] 内
- -10^5 <= Node.val <= 10^5

进阶要求：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？

示例 (Example)
-------------
输入：head = [4,2,1,3]
输出：[1,2,3,4]

输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

输入：head = []
输出：[]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对链表进行排序，要求 O(n log n) 时间复杂度

为什么这道题有难度？
1. 链表不支持随机访问，不能直接使用快速排序
2. 要求 O(n log n) 时间复杂度，排除冒泡、选择、插入排序
3. 进阶要求 O(1) 空间，不能转换为数组排序

关键观察：
1. 适合链表的 O(n log n) 排序算法：归并排序
2. 归并排序的核心：分治思想
   - 找到链表中点，分成两半
   - 递归排序左右两部分
   - 合并两个有序链表
3. 链表的归并排序比数组更自然，因为不需要额外空间来合并

归并排序的三个关键步骤：
1. 找中点：使用快慢指针
2. 递归排序：分别对左右两部分排序
3. 合并：合并两个有序链表

其他可能的解法：
- 转换为数组 + 快速排序：O(n log n) 时间，O(n) 空间
- 堆排序：不适合链表
- 快速排序：链表版本复杂，且最坏情况 O(n^2)

根据这些观察，可以得到几种典型解法：
1. 归并排序（递归）- O(n log n) 时间，O(log n) 递归栈空间
2. 归并排序（迭代）- O(n log n) 时间，O(1) 空间（满足进阶要求）
3. 转换为数组排序 - O(n log n) 时间，O(n) 空间（不推荐）
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
方法一：我的原始解法 - 归并排序（递归）(Approach 1: My Original Solution - Merge Sort Recursive)

核心思想
--------
使用归并排序对链表进行排序。归并排序是最适合链表的排序算法，因为：
1. 时间复杂度稳定在 O(n log n)
2. 不需要随机访问
3. 合并操作天然适合链表

算法流程：
1. 基础情况：如果链表为空或只有一个节点，直接返回
2. 找到链表的中点（使用快慢指针）
3. 将链表从中点断开，分成左右两部分
4. 递归排序左右两部分
5. 合并两个有序链表

关键子函数：
1. findMid(head)：找到链表中点并断开
   - 使用快慢指针
   - slow 每次走一步，fast 每次走两步
   - 当 fast 到达末尾时，slow 在中点
   - 需要记录 slow 的前一个节点，用于断开链表

2. merge(l1, l2)：合并两个有序链表
   - 使用虚拟头节点简化操作
   - 比较两个链表的节点，选择较小的连接
   - 最后连接剩余部分

为什么使用归并排序？
- 归并排序的分治思想天然适合链表
- 不需要随机访问，只需要顺序遍历
- 合并操作只需要调整指针，不需要额外空间
- 时间复杂度稳定在 O(n log n)

复杂度分析
---------
时间复杂度：O(n log n)
- 递归树的高度为 log n
- 每层需要遍历所有 n 个节点（找中点 + 合并）
- 总时间：O(n) * O(log n) = O(n log n)

空间复杂度：O(log n)
- 递归调用栈的深度为 log n
- 每次递归只使用常数空间

其中：
n = 链表节点数
*/
class Solution {
public:
    // 合并两个有序链表
    // 时间复杂度：O(n + m)，n 和 m 是两个链表的长度
    // 空间复杂度：O(1)
    ListNode* merge(ListNode* l1, ListNode* l2) {
        // 使用虚拟头节点简化边界处理
        ListNode dummy(0);  // 虚拟头节点
        ListNode* tail = &dummy;  // tail 指向已排序部分的尾节点

        // 比较两个链表的节点，选择较小的连接到结果链表
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;  // 连接 l1 的节点
                l1 = l1->next;    // l1 向前移动
            } else {
                tail->next = l2;  // 连接 l2 的节点
                l2 = l2->next;    // l2 向前移动
            }
            tail = tail->next;  // tail 向前移动
        }

        // 连接剩余部分
        // 此时至少有一个链表已经遍历完
        // 将另一个链表的剩余部分直接连接到结果链表
        tail->next = l1 ? l1 : l2;

        return dummy.next;  // 返回真正的头节点
    }

    // 找链表中点（快慢指针）并断开链表
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    ListNode* findMid(ListNode* head) {
        ListNode* slow = head;      // 慢指针，每次走一步
        ListNode* fast = head;      // 快指针，每次走两步
        ListNode* prev = nullptr;   // 记录 slow 的前一个节点

        // 快慢指针找中点
        // 当 fast 到达末尾时，slow 在中点
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // 断开链表
        // prev 是左半部分的尾节点，将其 next 设为 null
        if (prev) {
            prev->next = nullptr;
        }

        // 返回右半部分的头节点（中点）
        return slow;
    }

    ListNode* sortList(ListNode* head) {
        // 基础情况：空链表或单节点链表已经有序
        if (!head || !head->next) {
            return head;
        }

        // 1. 找到中点并分割链表
        // 分割后：head 指向左半部分，mid 指向右半部分
        ListNode* mid = findMid(head);

        // 2. 递归排序左右两部分
        ListNode* left = sortList(head);  // 排序左半部分
        ListNode* right = sortList(mid);  // 排序右半部分

        // 3. 合并两个有序链表
        return merge(left, right);
    }
};

/*
方法二：转换为数组 + 快速排序 (Approach 2: Convert to Array + Quick Sort)

核心思想
--------
将链表转换为数组，使用快速排序，然后将排序后的值写回链表。

算法流程：
1. 遍历链表，将所有值存入数组
2. 对数组进行快速排序
3. 再次遍历链表，将排序后的值写回

优点：
- 代码简单，易于实现
- 可以使用任何数组排序算法

缺点：
- 需要 O(n) 额外空间
- 不符合进阶要求

复杂度分析
---------
时间复杂度：O(n log n)
- 遍历链表：O(n)
- 快速排序：O(n log n)
- 写回链表：O(n)
- 总计：O(n log n)

空间复杂度：O(n)
- 数组占用 O(n) 空间
- 快速排序递归栈：O(log n)
- 总计：O(n)

注：这个方法在原文件中被注释掉了，说明作者最终选择了更优的归并排序方案
*/
class Solution_Array {
public:
    // 快速排序的分区函数
    int partition(vector<int>& nums, int low, int high) {
        int pivot = nums[high]; // 选取最后一个元素作为基准
        int i = low - 1;        // i 指向"小于基准值"区域的末尾

        for (int j = low; j < high; ++j) {
            // 如果当前元素小于基准值
            if (nums[j] < pivot) {
                i++;
                swap(nums[i], nums[j]); // 把它交换到"小于区域"里去
            }
        }
        // 最后把基准值放到它正确的位置（i+1）
        swap(nums[i + 1], nums[high]);
        return i + 1; // 返回基准值的最终索引
    }

    // 快速排序递归主函数
    void quickSort(vector<int>& nums, int low, int high) {
        if (low < high) {
            // 1. 获取基准值的位置
            int pi = partition(nums, low, high);

            // 2. 递归排序基准值左边的子数组
            quickSort(nums, low, pi - 1);

            // 3. 递归排序基准值右边的子数组
            quickSort(nums, pi + 1, high);
        }
    }

    ListNode* sortList(ListNode* head) {
        if (!head) {
            return nullptr;
        }

        // 1. 将链表值存入数组
        vector<int> nums;
        ListNode* current = head;
        while (current) {
            nums.push_back(current->val);
            current = current->next;
        }

        // 2. 对数组进行快速排序
        quickSort(nums, 0, nums.size() - 1);

        // 3. 将排序后的值写回链表
        current = head;
        for (int i = 0; i < nums.size(); i++) {
            current->val = nums[i];
            current = current->next;
        }

        return head;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：head = [4,2,1,3]

方法一（归并排序）的执行过程：

第一层递归：sortList([4,2,1,3])
1. findMid：找到中点 1，断开为 [4,2] 和 [1,3]
2. 递归：left = sortList([4,2])，right = sortList([1,3])

第二层递归（左）：sortList([4,2])
1. findMid：找到中点 2，断开为 [4] 和 [2]
2. 递归：left = sortList([4])，right = sortList([2])
3. sortList([4]) 返回 [4]（单节点）
4. sortList([2]) 返回 [2]（单节点）
5. merge([4], [2]) 返回 [2,4]

第二层递归（右）：sortList([1,3])
1. findMid：找到中点 3，断开为 [1] 和 [3]
2. 递归：left = sortList([1])，right = sortList([3])
3. sortList([1]) 返回 [1]（单节点）
4. sortList([3]) 返回 [3]（单节点）
5. merge([1], [3]) 返回 [1,3]

回到第一层：
merge([2,4], [1,3])
- 比较 2 和 1：选 1，结果 [1]
- 比较 2 和 3：选 2，结果 [1,2]
- 比较 4 和 3：选 3，结果 [1,2,3]
- 连接剩余 4，结果 [1,2,3,4]

最终结果：[1,2,3,4]

findMid 的详细过程（以 [4,2,1,3] 为例）：
- 初始：slow=4, fast=4, prev=null
- 第一步：prev=4, slow=2, fast=1
- 第二步：prev=2, slow=1, fast=null（fast->next 不存在，停止）
- 断开：prev(2)->next = null
- 返回：slow(1)
- 结果：[4,2] 和 [1,3]

merge 的详细过程（以 [2,4] 和 [1,3] 为例）：
- dummy -> null, tail = dummy
- 比较 2 和 1：1 < 2，tail->next = 1, l2 = 3, tail = 1
  状态：dummy -> 1
- 比较 2 和 3：2 < 3，tail->next = 2, l1 = 4, tail = 2
  状态：dummy -> 1 -> 2
- 比较 4 和 3：3 < 4，tail->next = 3, l2 = null, tail = 3
  状态：dummy -> 1 -> 2 -> 3
- l2 为空，连接 l1：tail->next = 4
  状态：dummy -> 1 -> 2 -> 3 -> 4
- 返回 dummy->next = 1
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：归并排序（递归）
- 时间复杂度：O(n log n)
- 空间复杂度：O(log n) - 递归栈
- 优点：稳定排序，适合链表，代码清晰
- 缺点：使用递归栈空间

方法二：转换为数组 + 快速排序
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：代码简单，可以使用任何排序算法
- 缺点：需要额外数组空间，不符合进阶要求

方法三：归并排序（迭代）- 未实现
- 时间复杂度：O(n log n)
- 空间复杂度：O(1)
- 优点：满足进阶要求的 O(1) 空间
- 缺点：代码复杂度高

推荐使用方法一，代码清晰且效率高。如果面试要求 O(1) 空间，需要实现迭代版本的归并排序。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空链表：返回 null
2. 只有一个节点：直接返回
3. 两个节点：需要比较并排序
4. 所有节点值相同：返回原链表
5. 已经有序的链表：仍需 O(n log n) 时间
6. 逆序链表：最坏情况，但归并排序仍是 O(n log n)
7. 包含负数：正常排序
8. 包含重复值：稳定排序，保持相对顺序
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

    // 测试用例 1：普通无序链表
    vector<int> vals1 = {4, 2, 1, 3};
    ListNode* head1 = createList(vals1);
    cout << "测试用例 1 - 原链表: ";
    printList(head1);
    head1 = solution.sortList(head1);
    cout << "排序后: ";
    printList(head1);
    cout << "期望: [1,2,3,4]" << endl << endl;

    // 测试用例 2：包含负数
    vector<int> vals2 = {-1, 5, 3, 4, 0};
    ListNode* head2 = createList(vals2);
    cout << "测试用例 2 - 原链表: ";
    printList(head2);
    head2 = solution.sortList(head2);
    cout << "排序后: ";
    printList(head2);
    cout << "期望: [-1,0,3,4,5]" << endl << endl;

    // 测试用例 3：空链表
    vector<int> vals3 = {};
    ListNode* head3 = createList(vals3);
    cout << "测试用例 3 - 原链表: ";
    printList(head3);
    head3 = solution.sortList(head3);
    cout << "排序后: ";
    printList(head3);
    cout << "期望: []" << endl << endl;

    // 测试用例 4：单节点
    vector<int> vals4 = {1};
    ListNode* head4 = createList(vals4);
    cout << "测试用例 4 - 原链表: ";
    printList(head4);
    head4 = solution.sortList(head4);
    cout << "排序后: ";
    printList(head4);
    cout << "期望: [1]" << endl << endl;

    // 测试用例 5：已经有序
    vector<int> vals5 = {1, 2, 3, 4, 5};
    ListNode* head5 = createList(vals5);
    cout << "测试用例 5 - 原链表: ";
    printList(head5);
    head5 = solution.sortList(head5);
    cout << "排序后: ";
    printList(head5);
    cout << "期望: [1,2,3,4,5]" << endl << endl;

    // 测试用例 6：逆序
    vector<int> vals6 = {5, 4, 3, 2, 1};
    ListNode* head6 = createList(vals6);
    cout << "测试用例 6 - 原链表: ";
    printList(head6);
    head6 = solution.sortList(head6);
    cout << "排序后: ";
    printList(head6);
    cout << "期望: [1,2,3,4,5]" << endl;

    return 0;
}
