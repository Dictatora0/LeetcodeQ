/*
LeetCode 23. 合并 K 个升序链表 (Merge k Sorted Lists)

题目概述 (Problem Summary)
-------------------------
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。

关键约束 (Key Constraints)
-------------------------
- k == lists.length
- 0 <= k <= 10^4
- 0 <= lists[i].length <= 500
- -10^4 <= lists[i][j] <= 10^4
- lists[i] 按升序排列
- lists[i].length 的总和不超过 10^4

示例 (Example)
-------------
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到：
1->1->2->3->4->4->5->6

输入：lists = []
输出：[]

输入：lists = [[]]
输出：[]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 多路归并问题：将 k 个有序序列合并成一个有序序列
- 类似于归并排序的合并过程，但是有 k 路而不是 2 路

关键观察：
1. 每次需要从 k 个链表中选择当前最小的节点
2. 如果暴力比较，每次需要 O(k) 时间，总时间 O(nk)，n 是总节点数
3. 使用堆优化：每次从堆中取最小节点，时间降到 O(n log k)
4. 分治合并：两两合并，时间 O(n log k)

为什么用小顶堆？
- 需要快速找到 k 个链表头节点中的最小值
- 小顶堆的堆顶就是最小值，O(1) 时间
- 取出最小值后，将其下一个节点加入堆，O(log k) 时间
- 总时间：O(n log k)，n 是总节点数

堆的大小如何确定？
- 最多 k 个元素（每个链表的当前头节点）
- 实际大小 <= k（有些链表可能已经遍历完）

堆的变化过程示例（lists = [[1,4,5],[1,3,4],[2,6]]）：
初始：heap = [1(链表0), 1(链表1), 2(链表2)]（堆顶是 1）

取出 1(链表0)，加入 4(链表0)：
heap = [1(链表1), 2(链表2), 4(链表0)]

取出 1(链表1)，加入 3(链表1)：
heap = [2(链表2), 3(链表1), 4(链表0)]

取出 2(链表2)，加入 6(链表2)：
heap = [3(链表1), 4(链表0), 6(链表2)]

...依此类推

C++ priority_queue 存储链表节点
-------------------------------
1. 需要自定义比较器，比较节点的值
2. 存储节点指针：priority_queue<ListNode*, vector<ListNode*>, Compare>
3. 比较器：
   struct Compare {
       bool operator()(ListNode* a, ListNode* b) {
           return a->val > b->val;  // 小顶堆
       }
   };
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
方法一：小顶堆（优先队列）(Approach 1: Min Heap)

核心思想
--------
使用小顶堆维护 k 个链表的当前头节点，每次取出最小节点，将其下一个节点加入堆。

算法流程：
1. 将 k 个链表的头节点加入小顶堆
2. 创建哑节点（dummy node）作为结果链表的头
3. 循环直到堆为空：
   a. 取出堆顶节点（当前最小）
   b. 将该节点加入结果链表
   c. 如果该节点有下一个节点，将下一个节点加入堆
4. 返回结果链表

为什么这样做是对的？
- 堆顶始终是当前所有链表头节点中的最小值
- 每次取出最小值，保证结果链表有序
- 将下一个节点加入堆，继续维护堆的性质

复杂度分析
---------
时间复杂度：O(n log k)
- n 是所有链表的总节点数
- 每个节点都会入堆和出堆一次，每次操作 O(log k)
- 总时间：O(n log k)

空间复杂度：O(k)
- 堆的大小最多为 k（k 个链表的头节点）

其中：
n = 所有链表的总节点数
k = 链表的个数

优点：
- 时间复杂度优秀，O(n log k)
- 代码简洁，易于理解
- 适合 k 较大的情况

缺点：
- 需要额外的堆空间
*/
class Solution {
public:
    // 自定义比较器：小顶堆，值小的优先级高
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;  // 注意：返回 true 表示 a 优先级低于 b
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 创建小顶堆
        priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;

        // 将所有链表的头节点加入堆
        for (ListNode* head : lists) {
            if (head != nullptr) {  // 跳过空链表
                minHeap.push(head);
            }
        }

        // 创建哑节点，简化链表操作
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;

        // 循环直到堆为空
        while (!minHeap.empty()) {
            // 取出堆顶节点（当前最小）
            ListNode* minNode = minHeap.top();
            minHeap.pop();

            // 将该节点加入结果链表
            current->next = minNode;
            current = current->next;

            // 如果该节点有下一个节点，将下一个节点加入堆
            if (minNode->next != nullptr) {
                minHeap.push(minNode->next);
            }
        }

        // 返回结果链表（跳过哑节点）
        ListNode* result = dummy->next;
        delete dummy;  // 释放哑节点
        return result;
    }
};

/*
方法二：分治合并 (Approach 2: Divide and Conquer)

核心思想
--------
类似归并排序，将 k 个链表两两合并，直到只剩一个链表。

算法流程：
1. 如果链表数组为空，返回 nullptr
2. 如果只有一个链表，直接返回
3. 将链表数组分成两半
4. 递归合并左半部分和右半部分
5. 合并两个有序链表

为什么这样做是对的？
- 两两合并，每次将问题规模减半
- 最终所有链表都会被合并成一个有序链表
- 类似归并排序的思想

复杂度分析
---------
时间复杂度：O(n log k)
- 合并两个链表：O(n1 + n2)
- 总共有 log k 层合并
- 每层合并的总节点数是 n
- 总时间：O(n log k)

空间复杂度：O(log k)
- 递归调用栈的深度

优点：
- 时间复杂度优秀，O(n log k)
- 不需要额外的堆空间
- 递归实现简洁

缺点：
- 需要递归调用栈
- 代码稍复杂
*/
class Solution_DivideConquer {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return merge(lists, 0, lists.size() - 1);
    }

private:
    // 合并 lists[left...right] 的所有链表
    ListNode* merge(vector<ListNode*>& lists, int left, int right) {
        if (left == right) {
            // 只有一个链表，直接返回
            return lists[left];
        }

        if (left > right) {
            return nullptr;
        }

        // 分治：将链表数组分成两半
        int mid = left + (right - left) / 2;
        ListNode* l1 = merge(lists, left, mid);
        ListNode* l2 = merge(lists, mid + 1, right);

        // 合并两个有序链表
        return mergeTwoLists(l1, l2);
    }

    // 合并两个有序链表
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }

        // 连接剩余节点
        current->next = (l1 != nullptr) ? l1 : l2;

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

/*
方法三：顺序合并 (Approach 3: Sequential Merge)

核心思想
--------
依次合并链表：先合并前两个，再合并结果和第三个，依此类推。

算法流程：
1. 初始化结果链表为 nullptr
2. 遍历所有链表：
   - 将当前链表与结果链表合并
   - 更新结果链表
3. 返回结果链表

复杂度分析
---------
时间复杂度：O(nk)
- 第 1 次合并：n1 + n2
- 第 2 次合并：(n1 + n2) + n3
- ...
- 第 k-1 次合并：(n1 + ... + n(k-1)) + nk
- 总时间：O(nk)

空间复杂度：O(1)
- 只需要常数额外空间

优点：
- 实现简单
- 空间复杂度低

缺点：
- 时间复杂度高，O(nk)
- 不适合 k 较大的情况
*/
class Solution_Sequential {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* result = nullptr;

        // 依次合并每个链表
        for (ListNode* list : lists) {
            result = mergeTwoLists(result, list);
        }

        return result;
    }

private:
    // 合并两个有序链表
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }

        current->next = (l1 != nullptr) ? l1 : l2;

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

/*
三种方法对比 (Comparison)
------------------------
方法一：小顶堆
- 时间复杂度：O(n log k)
- 空间复杂度：O(k)
- 适用场景：k 较大，需要高效合并
- 优点：时间复杂度优秀，代码简洁
- 缺点：需要额外的堆空间

方法二：分治合并
- 时间复杂度：O(n log k)
- 空间复杂度：O(log k)
- 适用场景：k 较大，递归实现
- 优点：时间复杂度优秀，空间效率高
- 缺点：递归实现稍复杂

方法三：顺序合并
- 时间复杂度：O(nk)
- 空间复杂度：O(1)
- 适用场景：k 较小，实现简单
- 优点：实现简单，空间效率最高
- 缺点：时间复杂度高

推荐方案：
- 面试中：方法一（小顶堆）最常用，易于理解和实现
- 追求空间效率：方法二（分治合并）
- k 很小：方法三（顺序合并）
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：lists = [[1,4,5],[1,3,4],[2,6]]

方法一：小顶堆
------------
初始化：
lists[0]: 1 -> 4 -> 5
lists[1]: 1 -> 3 -> 4
lists[2]: 2 -> 6

步骤 1：将所有头节点加入堆
minHeap = [1(链表0), 1(链表1), 2(链表2)]
堆顶：1(链表0) 或 1(链表1)（值相同，顺序不确定）

假设堆顶是 1(链表0)：
result: 1

步骤 2：取出 1(链表0)，加入 4(链表0)
minHeap = [1(链表1), 2(链表2), 4(链表0)]
堆顶：1(链表1)
result: 1 -> 1

步骤 3：取出 1(链表1)，加入 3(链表1)
minHeap = [2(链表2), 3(链表1), 4(链表0)]
堆顶：2(链表2)
result: 1 -> 1 -> 2

步骤 4：取出 2(链表2)，加入 6(链表2)
minHeap = [3(链表1), 4(链表0), 6(链表2)]
堆顶：3(链表1)
result: 1 -> 1 -> 2 -> 3

步骤 5：取出 3(链表1)，加入 4(链表1)
minHeap = [4(链表0), 4(链表1), 6(链表2)]
堆顶：4(链表0) 或 4(链表1)
result: 1 -> 1 -> 2 -> 3 -> 4

步骤 6：取出 4(链表0)，加入 5(链表0)
minHeap = [4(链表1), 5(链表0), 6(链表2)]
堆顶：4(链表1)
result: 1 -> 1 -> 2 -> 3 -> 4 -> 4

步骤 7：取出 4(链表1)，链表1 结束
minHeap = [5(链表0), 6(链表2)]
堆顶：5(链表0)
result: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5

步骤 8：取出 5(链表0)，链表0 结束
minHeap = [6(链表2)]
堆顶：6(链表2)
result: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

步骤 9：取出 6(链表2)，链表2 结束
minHeap = []
result: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

方法二：分治合并
--------------
初始：
lists[0]: 1 -> 4 -> 5
lists[1]: 1 -> 3 -> 4
lists[2]: 2 -> 6

第一层分治：
- 左半部分：lists[0..1]
- 右半部分：lists[2..2]

左半部分继续分治：
- 合并 lists[0] 和 lists[1]
- 结果：1 -> 1 -> 3 -> 4 -> 4 -> 5

右半部分：
- 只有 lists[2]：2 -> 6

最后合并：
- 合并 (1 -> 1 -> 3 -> 4 -> 4 -> 5) 和 (2 -> 6)
- 结果：1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空数组：
   - 输入：lists = []
   - 输出：nullptr

2. 只有一个空链表：
   - 输入：lists = [[]]
   - 输出：nullptr

3. 只有一个非空链表：
   - 输入：lists = [[1,2,3]]
   - 输出：1 -> 2 -> 3

4. 所有链表都为空：
   - 输入：lists = [[],[],[]]
   - 输出：nullptr

5. 链表长度差异很大：
   - 输入：lists = [[1],[1,2,3,4,5,6,7,8,9,10]]
   - 输出：1 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10

6. 包含负数：
   - 输入：lists = [[-2,-1],[0,1]]
   - 输出：-2 -> -1 -> 0 -> 1
*/

/*
堆的原理图解 (Heap Visualization)
--------------------------------
小顶堆（存储链表节点）的性质：
- 父节点的值 <= 子节点的值
- 堆顶是值最小的节点

示例：lists = [[1,4,5],[1,3,4],[2,6]]

初始堆（存储头节点）：
        1(链表0)
       /        \
   1(链表1)    2(链表2)

取出 1(链表0)，加入 4(链表0)：
        1(链表1)
       /        \
   2(链表2)    4(链表0)

取出 1(链表1)，加入 3(链表1)：
        2(链表2)
       /        \
   3(链表1)    4(链表0)

取出 2(链表2)，加入 6(链表2)：
        3(链表1)
       /        \
   4(链表0)    6(链表2)

...依此类推

堆的大小始终 <= k（链表的个数）
*/

// 辅助函数：创建链表
ListNode* createList(vector<int> values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    if (head == nullptr) {
        cout << "nullptr" << endl;
        return;
    }
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// 辅助函数：释放链表
void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Solution solution;

    // 测试用例 1：标准情况
    cout << "测试用例 1 - 标准情况" << endl;
    vector<ListNode*> lists1 = {
        createList({1, 4, 5}),
        createList({1, 3, 4}),
        createList({2, 6})
    };
    cout << "输入：" << endl;
    cout << "链表 0: "; printList(lists1[0]);
    cout << "链表 1: "; printList(lists1[1]);
    cout << "链表 2: "; printList(lists1[2]);
    ListNode* result1 = solution.mergeKLists(lists1);
    cout << "输出："; printList(result1);
    cout << "期望：1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6" << endl << endl;
    deleteList(result1);

    // 测试用例 2：空数组
    cout << "测试用例 2 - 空数组" << endl;
    vector<ListNode*> lists2 = {};
    ListNode* result2 = solution.mergeKLists(lists2);
    cout << "输出："; printList(result2);
    cout << "期望：nullptr" << endl << endl;

    // 测试用例 3：只有一个空链表
    cout << "测试用例 3 - 只有一个空链表" << endl;
    vector<ListNode*> lists3 = {nullptr};
    ListNode* result3 = solution.mergeKLists(lists3);
    cout << "输出："; printList(result3);
    cout << "期望：nullptr" << endl << endl;

    // 测试用例 4：只有一个非空链表
    cout << "测试用例 4 - 只有一个非空链表" << endl;
    vector<ListNode*> lists4 = {createList({1, 2, 3})};
    ListNode* result4 = solution.mergeKLists(lists4);
    cout << "输出："; printList(result4);
    cout << "期望：1 -> 2 -> 3" << endl << endl;
    deleteList(result4);

    // 测试用例 5：包含负数
    cout << "测试用例 5 - 包含负数" << endl;
    vector<ListNode*> lists5 = {
        createList({-2, -1}),
        createList({0, 1})
    };
    ListNode* result5 = solution.mergeKLists(lists5);
    cout << "输出："; printList(result5);
    cout << "期望：-2 -> -1 -> 0 -> 1" << endl;
    deleteList(result5);

    return 0;
}
