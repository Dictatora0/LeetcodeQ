
/*
算法名称：双指针 Two Pointers

算法核心思想
-----------
使用两个指针协同移动来缩小搜索空间，
常见模式包括“左右夹逼”和“快慢指针”。

思路要点
-------
- 左右指针常用于有序数组
- 快慢指针常用于原地修改或检测环
- 指针移动方向必须保证区间收缩

什么时候使用
-----------
适用场景：
- 有序数组中的两数之和
- 去重/删除元素
- 环检测（快慢指针）

常见算法变体
-----------
1) 左右指针（有序数组）
2) 快慢指针（删除/去重）
3) 快慢指针（环检测）
4) 双指针反转字符串

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)

ASCII 示例
---------
nums = [1,2,3,4], target=5
l=0,r=3 -> 1+4=5

典型题目扩展
-----------
- 167 Two Sum II
- 26 Remove Duplicates from Sorted Array
- 283 Move Zeroes
- 19 Remove Nth Node From End

可直接使用的代码模板
------------------
见下方 TwoPointers_Template

常见错误
--------
- 指针更新方向错误
- 边界条件遗漏
*/

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

class TwoPointers_Template {
public:
    // 有序数组两数之和
    bool twoSumSorted(vector<int>& nums, int target) {
        int l = 0, r = static_cast<int>(nums.size()) - 1;
        while (l < r) {
            int sum = nums[l] + nums[r];
            if (sum == target) return true;
            if (sum < target) l++; else r--;
        }
        return false;
    }

    // 快慢指针：移除指定值
    int removeVal(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < (int)nums.size(); ++fast) {
            if (nums[fast] != val) nums[slow++] = nums[fast];
        }
        return slow;
    }

    // 快慢指针：移除有序数组重复元素
    int removeDuplicatesSorted(vector<int>& nums) {
        if (nums.empty()) return 0;
        int slow = 1;
        for (int fast = 1; fast < (int)nums.size(); ++fast) {
            if (nums[fast] != nums[fast - 1]) nums[slow++] = nums[fast];
        }
        return slow;
    }

    // 快慢指针：判断链表是否有环
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

    // 左右指针：反转字符串
    void reverseString(vector<char>& s) {
        int l = 0, r = (int)s.size() - 1;
        while (l < r) {
            swap(s[l], s[r]);
            l++; r--;
        }
    }
};

int main() {
    TwoPointers_Template solver;
    vector<int> nums = {1,2,3,4};
    cout << boolalpha << solver.twoSumSorted(nums, 5) << endl;
    vector<int> nums2 = {3,2,2,3};
    cout << "new len = " << solver.removeVal(nums2, 3) << endl;
    return 0;
}
