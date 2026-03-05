#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
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

// class Solution {
// public:

//     // 分区函数：核心步骤
//     int partition(std::vector<int>& nums, int low, int high) {
//         int pivot = nums[high]; // 选取最后一个元素作为基准
//         int i = low - 1;        // i 指向"小于基准值"区域的末尾

//         for (int j = low; j < high; ++j) {
//             // 如果当前元素小于基准值
//             if (nums[j] < pivot) {
//                 i++; 
//                 std::swap(nums[i], nums[j]); // 把它交换到"小于区域"里去
//             }
//         }
//         // 最后把基准值放到它正确的位置（i+1）
//         std::swap(nums[i + 1], nums[high]);
//         return i + 1; // 返回基准值的最终索引
//     }

//     // 递归主函数
//     void quickSort(std::vector<int>& nums, int low, int high) {
//         if (low < high) {
//             // 1. 获取基准值的位置
//             int pi = partition(nums, low, high);

//             // 2. 递归排序基准值左边的子数组
//             quickSort(nums, low, pi - 1);

//             // 3. 递归排序基准值右边的子数组
//             quickSort(nums, pi + 1, high);
//         }
//     }
    

//     ListNode* sortList(ListNode* head) {
//         if(!head){
//             return nullptr;
//         }

//         vector<int> nums;
//         ListNode *current = head;

//         while(current){
//             nums.push_back(current->val);
//             current = current->next;
//         }

//         quickSort(nums, 0, nums.size() - 1);

//         current = head;

//         for (int i = 0; i < nums.size();i++){
//             current->val = nums[i];
//             current = current->next;
//         }

//         return head;
//     }
// };

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
    // 合并两个有序链表
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);  // 虚拟头节点
        ListNode* tail = &dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        // 连接剩余部分
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
    
    // 找链表中点（快慢指针）
    ListNode* findMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;
        
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // 断开链表
        if (prev) {
            prev->next = nullptr;
        }
        return slow;
    }
    
    ListNode* sortList(ListNode* head) {
        // 基础情况：空链表或单节点
        if (!head || !head->next) {
            return head;
        }
        
        // 1. 找到中点并分割链表
        ListNode* mid = findMid(head);
        
        // 2. 递归排序左右两部分
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);
        
        // 3. 合并两个有序链表
        return merge(left, right);
    }
};

int main() {
    Solution solution;
    
    // TODO: 添加测试用例
    // 例如：创建链表 [1,2,3,4,5]，删除倒数第 2 个节点，应该得到 [1,2,3,5]

    cout << INT_MIN << endl;  // 输出整数最小值（测试代码）
    
    return 0;
}