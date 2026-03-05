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
    /**
     * 删除链表的倒数第 n 个节点
     * 使用双指针（快慢指针）技术
     * 
     * @param head 链表的头节点
     * @param n 要删除的倒数第 n 个位置（从 1 开始计数）
     * @return 删除节点后的链表头节点
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 边界情况：如果链表为空或只有一个节点，删除后返回空
        if(head == NULL || head->next == NULL){
            return NULL;
        }

        // 初始化两个指针：prev（慢指针）和 sub（快指针），都指向头节点
        ListNode* prev = head;
        ListNode* sub = head;

        // 让快指针 sub 先向前移动 n 步
        // 这样快慢指针之间就保持了 n 个节点的距离
        for (int i = 0; i < n; i++){
            sub = sub->next;
        }

        // 特殊情况：如果快指针已经到达链表末尾（sub == NULL）
        // 说明要删除的是头节点（倒数第 n 个节点就是第一个节点）
        if(sub == NULL){
            ListNode* dummy = new ListNode();  // 创建虚拟头节点
            dummy->next = head->next;          // 虚拟节点指向原头节点的下一个节点
            return dummy->next;                // 返回新的头节点（原第二个节点）
        }

        // 同时移动快慢指针，直到快指针到达链表的最后一个节点
        // 此时慢指针 prev 指向要删除节点的前一个节点
        while(sub->next != NULL){
            sub = sub->next;
            prev = prev->next;
        }

        // 执行删除操作
        ListNode* temp = prev->next;    // temp 指向要删除的节点
        prev->next = temp->next;        // 将前一个节点的 next 指向要删除节点的下一个节点
        delete temp ;                    // 释放内存

        return head;  // 返回原链表头节点（因为删除的不是头节点）
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    // 例如：创建链表 [1,2,3,4,5]，删除倒数第 2 个节点，应该得到 [1,2,3,5]

    cout << INT_MIN << endl;  // 输出整数最小值（测试代码）
    
    return 0;
}