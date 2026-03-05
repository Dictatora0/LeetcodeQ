#include <iostream>
#include <vector>
#include <algorithm>

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 边界情况：如果 head 为空或者 k <= 1，直接返回
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
        ListNode* prev = nullptr;
        ListNode* current = head;
        ListNode* next = nullptr;
        
        // 标准的链表翻转，翻转 k 个节点
        for (int i = 0; i < k; i++) {
            next = current->next;    // 保存下一个节点
            current->next = prev;    // 当前节点指向前一个节点
            prev = current;          // prev 向前移动
            current = next;          // current 向前移动
        }
        
        // 第三步：递归处理剩余的链表
        // 此时 prev 是翻转后的新头节点，head 是翻转后的尾节点
        // current 指向剩余未处理部分的头节点
        head->next = reverseKGroup(current, k);
        
        // 返回翻转后的头节点
        return prev;
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    // 例如：创建链表 [1,2,3,4,5]，删除倒数第 2 个节点，应该得到 [1,2,3,5]

    cout << INT_MIN << endl;  // 输出整数最小值（测试代码）
    
    return 0;
}