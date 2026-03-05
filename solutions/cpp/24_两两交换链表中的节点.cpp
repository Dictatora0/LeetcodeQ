#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // 为了使用 INT_MIN
using namespace std;

// 链表节点结构定义
struct ListNode {
    int val;            // 节点存储的值
    ListNode *next;     // 指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}                    // 默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}               // 单参数构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}  // 双参数构造函数
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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
        ListNode *prev = dummy;

        // 只要还有至少两个节点可以交换，就继续
        while(prev->next!= nullptr && prev->next->next != nullptr){
            ListNode *cur = prev->next; // 当前节点
            ListNode* sub = prev->next->next;// 后方节点

            // 执行交换：prev -> cur -> sub -> next
            // 变成：prev -> sub -> cur -> next
            prev->next = sub;
            cur->next = sub->next;
            sub->next = cur;

            // prev 移动到下一对节点的前一个位置（即当前的 cur）
            prev = cur;
        }

        // 返回新的头节点（dummy.next 可能已改变）
        return dummy->next;
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    // 例如：创建链表 [1,2,3,4,5]，删除倒数第 2 个节点，应该得到 [1,2,3,5]

    cout << INT_MIN << endl;  // 输出整数最小值（测试代码）
    
    return 0;
}