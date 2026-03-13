/*
LeetCode 138. 随机链表的复制 (Copy List with Random Pointer)

题目概述 (Problem Summary)
-------------------------
给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random，
该指针可以指向链表中的任何节点或空节点。

构造这个链表的深拷贝。深拷贝应该正好由 n 个全新节点组成，其中每个新节点的值
都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中
的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。
复制链表中的指针都不应指向原链表中的节点。

关键约束 (Key Constraints)
-------------------------
- 0 <= n <= 1000
- -10^4 <= Node.val <= 10^4
- Node.random 为 null 或指向链表中的节点

示例 (Example)
-------------
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
解释：
- 节点 0: val=7, random=null
- 节点 1: val=13, random=节点0
- 节点 2: val=11, random=节点4
- 节点 3: val=10, random=节点2
- 节点 4: val=1, random=节点0

输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]
解释：
- 节点 0: val=1, random=节点1
- 节点 1: val=2, random=节点1

输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 深拷贝一个带有随机指针的链表
- 关键难点：如何正确设置新节点的 random 指针

为什么这道题有难度？
1. 普通链表只需要按顺序复制 next 指针
2. 但 random 指针可能指向任意节点，包括还未创建的节点
3. 需要建立原节点和新节点之间的映射关系

关键观察：
1. 需要两次遍历：第一次创建节点，第二次设置指针
2. 需要一个数据结构来存储原节点到新节点的映射
3. 哈希表是最直观的选择：原节点 -> 新节点

解法思路：
方法一：哈希表法（推荐）
- 第一遍遍历：创建所有新节点，建立 原节点->新节点 的映射
- 第二遍遍历：根据映射关系设置 next 和 random 指针
- 时间 O(n)，空间 O(n)

方法二：原地修改法（进阶）
- 在每个原节点后面插入对应的新节点
- 设置新节点的 random 指针
- 拆分链表
- 时间 O(n)，空间 O(1)（不考虑返回值）

根据这些观察，可以得到几种典型解法：
1. 哈希表法 - 最直观，代码简洁，O(n) 时间和空间
2. 原地修改法 - 空间优化，O(1) 额外空间，但代码复杂
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Definition for a Node.
 */
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/*
方法一：我的原始解法 - 哈希表法 (Approach 1: My Original Solution - Hash Map)

核心思想
--------
使用哈希表存储原节点到新节点的映射关系，分两次遍历完成深拷贝：
1. 第一次遍历：创建所有新节点，建立映射
2. 第二次遍历：根据映射设置 next 和 random 指针

算法流程：
1. 边界检查：如果 head 为空，返回 nullptr
2. 第一次遍历：
   - 遍历原链表的每个节点
   - 为每个原节点创建对应的新节点（只复制 val）
   - 将 原节点->新节点 的映射存入哈希表
3. 第二次遍历：
   - 再次遍历原链表
   - 对每个原节点，通过哈希表找到对应的新节点
   - 设置新节点的 next：newNode->next = map[原节点->next]
   - 设置新节点的 random：newNode->random = map[原节点->random]
4. 返回新链表的头节点：map[head]

为什么需要两次遍历？
- 第一次遍历时，某些节点可能还未创建，无法设置 random 指针
- 第一次遍历后，所有节点都已创建，第二次遍历可以安全设置指针

哈希表的作用：
- 建立原节点和新节点的一一对应关系
- 通过原节点快速找到对应的新节点
- 处理 random 指针指向任意节点的情况

边界情况处理：
- 如果 current->next 为 null，map[null] 也是 null，正确
- 如果 current->random 为 null，map[null] 也是 null，正确

复杂度分析
---------
时间复杂度：O(n)
- 第一次遍历：O(n)，创建 n 个节点
- 第二次遍历：O(n)，设置 2n 个指针
- 总计：O(2n) = O(n)

空间复杂度：O(n)
- 哈希表存储 n 个键值对
- 不考虑返回的新链表占用的空间

其中：
n = 链表节点数
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // 边界情况：空链表
        if (head == nullptr) {
            return nullptr;
        }

        // 哈希表：原节点 -> 新节点
        // 用于建立原链表和新链表节点之间的映射关系
        unordered_map<Node*, Node*> nodeMap;

        // 第一遍遍历：创建所有新节点，建立映射关系
        // 此时只复制节点的值，不设置 next 和 random 指针
        Node* current = head;
        while (current) {
            // 为当前原节点创建对应的新节点
            nodeMap[current] = new Node(current->val);
            current = current->next;
        }

        // 第二遍遍历：设置新节点的 next 和 random 指针
        // 此时所有新节点都已创建，可以安全地设置指针
        current = head;
        while (current) {
            // 通过哈希表找到当前原节点对应的新节点
            Node* newNode = nodeMap[current];

            // 设置新节点的 next 指针
            // 如果 current->next 为 null，nodeMap[null] 也是 null（未定义的键返回默认值）
            newNode->next = nodeMap[current->next];

            // 设置新节点的 random 指针
            // 如果 current->random 为 null，nodeMap[null] 也是 null
            newNode->random = nodeMap[current->random];

            current = current->next;
        }

        // 返回新链表的头节点
        return nodeMap[head];
    }
};

/*
方法二：原地修改法 (Approach 2: Interweaving Nodes)

核心思想
--------
不使用额外的哈希表，而是在原链表中插入新节点，利用位置关系建立映射。

算法流程：
1. 第一步：在每个原节点后面插入对应的新节点
   原链表：1 -> 2 -> 3
   变成：1 -> 1' -> 2 -> 2' -> 3 -> 3'

2. 第二步：设置新节点的 random 指针
   对于原节点 A，其新节点 A' 在 A.next
   如果 A.random = B，则 A'.random = B.next（即 B'）

3. 第三步：拆分链表
   将交织的链表拆分成原链表和新链表

优点：
- 空间复杂度 O(1)（不考虑返回值）
- 巧妙利用位置关系代替哈希表

缺点：
- 代码复杂度较高
- 需要修改原链表（虽然最后会恢复）

复杂度分析
---------
时间复杂度：O(n)
- 三次遍历，每次 O(n)

空间复杂度：O(1)
- 只使用常数个指针变量
- 不考虑返回的新链表
*/
class Solution_Interweaving {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        // 第一步：在每个节点后面插入复制节点
        Node* curr = head;
        while (curr) {
            Node* newNode = new Node(curr->val);
            newNode->next = curr->next;
            curr->next = newNode;
            curr = newNode->next;
        }

        // 第二步：设置复制节点的 random 指针
        curr = head;
        while (curr) {
            if (curr->random) {
                // curr->next 是复制节点
                // curr->random->next 是 random 指向节点的复制节点
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        // 第三步：拆分链表
        Node* dummy = new Node(0);
        Node* copyCurr = dummy;
        curr = head;

        while (curr) {
            Node* copyNode = curr->next;
            copyCurr->next = copyNode;
            copyCurr = copyNode;

            // 恢复原链表
            curr->next = copyNode->next;
            curr = curr->next;
        }

        return dummy->next;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]

方法一（哈希表法）的执行过程：

第一次遍历（创建节点和映射）：
- current = 节点7，创建新节点7'，map[节点7] = 节点7'
- current = 节点13，创建新节点13'，map[节点13] = 节点13'
- current = 节点11，创建新节点11'，map[节点11] = 节点11'
- current = 节点10，创建新节点10'，map[节点10] = 节点10'
- current = 节点1，创建新节点1'，map[节点1] = 节点1'

此时哈希表：
{节点7 -> 节点7', 节点13 -> 节点13', 节点11 -> 节点11', 节点10 -> 节点10', 节点1 -> 节点1'}

第二次遍历（设置指针）：
- current = 节点7
  * newNode = 节点7'
  * newNode->next = map[节点13] = 节点13'
  * newNode->random = map[null] = null

- current = 节点13
  * newNode = 节点13'
  * newNode->next = map[节点11] = 节点11'
  * newNode->random = map[节点7] = 节点7'

- current = 节点11
  * newNode = 节点11'
  * newNode->next = map[节点10] = 节点10'
  * newNode->random = map[节点1] = 节点1'

- current = 节点10
  * newNode = 节点10'
  * newNode->next = map[节点1] = 节点1'
  * newNode->random = map[节点11] = 节点11'

- current = 节点1
  * newNode = 节点1'
  * newNode->next = map[null] = null
  * newNode->random = map[节点7] = 节点7'

最终结果：新链表 [[7,null],[13,0],[11,4],[10,2],[1,0]]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：哈希表法
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：代码简洁，逻辑清晰，易于理解
- 缺点：需要额外的哈希表空间

方法二：原地修改法
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间效率高，满足进阶要求
- 缺点：代码复杂，需要修改原链表（虽然最后恢复）

推荐使用方法一，除非面试明确要求 O(1) 空间。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空链表：返回 null
2. 只有一个节点：random 可能指向自己或 null
3. 所有节点的 random 都是 null：退化为普通链表复制
4. random 指针形成环：例如 A.random = B, B.random = A
5. random 指针都指向同一个节点：例如都指向头节点
6. random 指针指向自己：节点的 random 指向自己
*/

// 辅助函数：创建带 random 指针的链表
Node* createListWithRandom(vector<pair<int, int>>& data) {
    // data[i] = {val, randomIndex}
    // randomIndex = -1 表示 random 为 null
    if (data.empty()) return nullptr;

    vector<Node*> nodes;
    for (auto& p : data) {
        nodes.push_back(new Node(p.first));
    }

    for (int i = 0; i < nodes.size(); i++) {
        if (i < nodes.size() - 1) {
            nodes[i]->next = nodes[i + 1];
        }
        if (data[i].second != -1) {
            nodes[i]->random = nodes[data[i].second];
        }
    }

    return nodes[0];
}

// 辅助函数：打印带 random 指针的链表
void printListWithRandom(Node* head) {
    Node* curr = head;
    cout << "[";
    int index = 0;
    unordered_map<Node*, int> nodeIndex;

    // 先建立节点到索引的映射
    Node* temp = head;
    while (temp) {
        nodeIndex[temp] = index++;
        temp = temp->next;
    }

    // 打印链表
    while (curr) {
        cout << "[" << curr->val << ",";
        if (curr->random) {
            cout << nodeIndex[curr->random];
        } else {
            cout << "null";
        }
        cout << "]";
        if (curr->next) cout << ",";
        curr = curr->next;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // 测试用例 1：复杂的 random 指针
    vector<pair<int, int>> data1 = {{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    Node* head1 = createListWithRandom(data1);
    cout << "测试用例 1 - 原链表: ";
    printListWithRandom(head1);
    Node* copied1 = solution.copyRandomList(head1);
    cout << "复制后的链表: ";
    printListWithRandom(copied1);
    cout << "期望: [[7,null],[13,0],[11,4],[10,2],[1,0]]" << endl << endl;

    // 测试用例 2：random 指针指向自己
    vector<pair<int, int>> data2 = {{1, 1}, {2, 1}};
    Node* head2 = createListWithRandom(data2);
    cout << "测试用例 2 - 原链表: ";
    printListWithRandom(head2);
    Node* copied2 = solution.copyRandomList(head2);
    cout << "复制后的链表: ";
    printListWithRandom(copied2);
    cout << "期望: [[1,1],[2,1]]" << endl << endl;

    // 测试用例 3：所有 random 都是 null
    vector<pair<int, int>> data3 = {{3, -1}, {3, 0}, {3, -1}};
    Node* head3 = createListWithRandom(data3);
    cout << "测试用例 3 - 原链表: ";
    printListWithRandom(head3);
    Node* copied3 = solution.copyRandomList(head3);
    cout << "复制后的链表: ";
    printListWithRandom(copied3);
    cout << "期望: [[3,null],[3,0],[3,null]]" << endl << endl;

    // 测试用例 4：空链表
    Node* head4 = nullptr;
    cout << "测试用例 4 - 原链表: []" << endl;
    Node* copied4 = solution.copyRandomList(head4);
    cout << "复制后的链表: ";
    printListWithRandom(copied4);
    cout << "期望: []" << endl;

    return 0;
}
