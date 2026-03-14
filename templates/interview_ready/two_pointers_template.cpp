/*
 * ============================================================================
 * 双指针算法 - 面试必备完整模板
 * Two Pointers Algorithm - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 双指针是一种简单而高效的技巧，通过维护两个指针在数组/字符串上移动，
 * 将 O(n²) 的暴力解法优化到 O(n)。
 *
 * 【通俗解释】
 * 想象你用两只手指指着数组：
 * - 对撞指针：左右手从两端向中间移动
 * - 快慢指针：右手走得快，左手走得慢
 * - 同向指针：两只手同方向移动，但速度不同
 *
 * 【为什么有效】
 * 1. 减少搜索空间：每次移动都排除一部分不可能的解
 * 2. 单次遍历：通常只需要 O(n) 时间
 * 3. 原地操作：空间复杂度 O(1)
 *
 * 【与其他算法对比】
 * - vs 滑动窗口：双指针更通用，窗口是双指针的特例
 * - vs 二分查找：双指针不要求有序（某些情况）
 * - vs 哈希表：双指针空间复杂度更低
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别双指针题目】
 *
 * ✅ 关键词识别：
 * 1. "有序数组" + "查找/删除" - 90% 是对撞指针
 * 2. "链表" + "环/中点/倒数第K个" - 快慢指针
 * 3. "原地" + "删除/移动" - 同向双指针
 * 4. "两数之和" + "有序" - 对撞指针
 * 5. "回文" - 对撞指针
 *
 * ✅ 题目特征：
 * - 数组已排序或可以排序
 * - 要求原地操作
 * - 需要找两个元素的关系
 * - 链表相关问题
 *
 * ❌ 不适合双指针：
 * - 需要记录所有子数组
 * - 无序且不能排序
 * - 需要回溯
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：对撞指针（最常用）
// 适用场景：有序数组，从两端向中间查找
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// ============================================================================

class CollisionPointers {
public:
    // 两数之和 - 有序数组
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum == target) {
                return {left, right};
            } else if (sum < target) {
                left++;   // 和太小，左指针右移
            } else {
                right--;  // 和太大，右指针左移
            }
        }

        return {-1, -1};
    }

    // 判断回文串
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }
};

// ============================================================================
// 模板 2：快慢指针（链表专用）
// 适用场景：链表环检测、找中点、倒数第K个节点
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// ============================================================================

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class FastSlowPointers {
public:
    // 检测链表是否有环
    bool hasCycle(ListNode* head) {
        if (!head || !head->next) return false;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            slow = slow->next;        // 慢指针走一步
            fast = fast->next->next;  // 快指针走两步

            if (slow == fast) {
                return true;  // 相遇说明有环
            }
        }

        return false;
    }

    // 找链表中点
    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;  // slow 指向中点
    }

    // 找倒数第 k 个节点
    ListNode* findKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head;
        ListNode* slow = head;

        // fast 先走 k 步
        for (int i = 0; i < k; i++) {
            if (!fast) return nullptr;
            fast = fast->next;
        }

        // 一起走，fast 到末尾时 slow 在倒数第 k 个
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};

// ============================================================================
// 模板 3：同向双指针（原地操作）
// 适用场景：原地删除、移动元素
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// ============================================================================

class SameDirectionPointers {
public:
    // 删除数组中的指定元素
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;  // 慢指针：下一个有效元素的位置

        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
        }

        return slow;  // 新数组长度
    }

    // 移动零到末尾
    void moveZeroes(vector<int>& nums) {
        int slow = 0;  // 下一个非零元素的位置

        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != 0) {
                swap(nums[slow], nums[fast]);
                slow++;
            }
        }
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：三数之和
// LeetCode 15: 3Sum
// ============================================================================

class Solution_ThreeSum {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 3) return result;

        // 1. 排序
        sort(nums.begin(), nums.end());

        // 2. 固定第一个数，用双指针找另外两个数
        for (int i = 0; i < n - 2; i++) {
            // 跳过重复元素
            if (i > 0 && nums[i] == nums[i-1]) continue;

            // 优化：如果最小的数都大于0，后面不可能有解
            if (nums[i] > 0) break;

            int left = i + 1, right = n - 1;
            int target = -nums[i];

            while (left < right) {
                int sum = nums[left] + nums[right];

                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // 跳过重复元素
                    while (left < right && nums[left] == nums[left+1]) left++;
                    while (left < right && nums[right] == nums[right-1]) right--;

                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return result;
    }
};

// ============================================================================
// 变体 2：盛最多水的容器
// LeetCode 11: Container With Most Water
// ============================================================================

class Solution_MaxArea {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;

        while (left < right) {
            // 计算当前容量
            int h = min(height[left], height[right]);
            int w = right - left;
            maxWater = max(maxWater, h * w);

            // 移动较矮的那一边（贪心）
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxWater;
    }
};

// ============================================================================
// 变体 3：删除有序数组中的重复项
// LeetCode 26: Remove Duplicates from Sorted Array
// ============================================================================

class Solution_RemoveDuplicates {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int slow = 0;  // 慢指针：不重复元素的末尾

        for (int fast = 1; fast < nums.size(); fast++) {
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }

        return slow + 1;
    }
};

// ============================================================================
// 变体 4：反转字符串
// LeetCode 344: Reverse String
// ============================================================================

class Solution_ReverseString {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};

// ============================================================================
// 变体 5：环形链表 II（找环的入口）
// LeetCode 142: Linked List Cycle II
// ============================================================================

class Solution_DetectCycle {
public:
    ListNode* detectCycle(ListNode* head) {
        if (!head || !head->next) return nullptr;

        // 1. 快慢指针找相遇点
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                // 2. 找环的入口
                ListNode* ptr = head;
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }

        return nullptr;
    }
};

/*
 * ============================================================================
 * 第五部分：面试技巧
 * ============================================================================
 */

/*
 * 【如何向面试官解释思路】
 *
 * 1. 识别类型
 *    "这是一个有序数组问题，我可以用对撞指针优化..."
 *
 * 2. 说明指针移动规则
 *    "左指针从头开始，右指针从尾开始，根据和的大小决定移动哪个指针..."
 *
 * 3. 分析时间复杂度
 *    "每个指针最多移动 n 次，所以时间复杂度是 O(n)"
 *
 * 【常见追问】
 *
 * Q1: "为什么移动较小的指针？"
 * A1: "因为移动较大的指针只会让和更小，不可能找到更大的和"
 *
 * Q2: "如果数组无序怎么办？"
 * A2: "可以先排序，时间复杂度变成 O(nlogn)"
 *
 * Q3: "能否用哈希表？"
 * A3: "可以，但空间复杂度是 O(n)，双指针只需要 O(1)"
 */

/*
 * ============================================================================
 * 第六部分：易错点
 * ============================================================================
 */

/*
 * 【常见错误 1：边界条件】
 * ❌ while (left <= right)  // 回文判断时应该用 <
 * ✅ while (left < right)
 *
 * 【常见错误 2：忘记跳过重复元素】
 * ❌ 三数之和不去重，导致重复结果
 * ✅ while (left < right && nums[left] == nums[left+1]) left++;
 *
 * 【常见错误 3：快慢指针空指针】
 * ❌ while (fast->next)  // 可能空指针
 * ✅ while (fast && fast->next)
 */

/*
 * ============================================================================
 * 第七部分：复杂度分析
 * ============================================================================
 */

/*
 * 【时间复杂度】
 * - 对撞指针：O(n)
 * - 快慢指针：O(n)
 * - 同向双指针：O(n)
 * - 三数之和：O(n²)（外层循环 + 内层双指针）
 *
 * 【空间复杂度】
 * - 通常是 O(1)，原地操作
 */

/*
 * ============================================================================
 * 第八部分：真题实战
 * ============================================================================
 */

/*
 * ⭐ 简单
 * 1. LC 26: 删除有序数组中的重复项
 * 2. LC 27: 移除元素
 * 3. LC 283: 移动零
 * 4. LC 344: 反转字符串
 * 5. LC 125: 验证回文串
 *
 * ⭐⭐ 中等（高频）
 * 6. LC 15: 三数之和 ⭐⭐⭐⭐⭐
 * 7. LC 11: 盛最多水的容器 ⭐⭐⭐⭐⭐
 * 8. LC 142: 环形链表 II ⭐⭐⭐⭐
 * 9. LC 167: 两数之和 II ⭐⭐⭐⭐
 * 10. LC 16: 最接近的三数之和
 *
 * ⭐⭐⭐ 困难
 * 11. LC 42: 接雨水 ⭐⭐⭐⭐⭐
 * 12. LC 18: 四数之和
 */

/*
 * ============================================================================
 * 第九部分：完整示例
 * ============================================================================
 */

// 完整示例：三数之和
void testThreeSum() {
    Solution_ThreeSum sol;
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto result = sol.threeSum(nums);

    cout << "三数之和结果：" << endl;
    for (auto& triplet : result) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "]" << endl;
    }
}

/*
 * ============================================================================
 * 第十部分：速查表
 * ============================================================================
 */

/*
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │                      双指针算法速查表                                    │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * 【三种类型】
 * 1. 对撞指针：left=0, right=n-1, 向中间移动
 * 2. 快慢指针：slow走1步, fast走2步（链表）
 * 3. 同向指针：slow和fast同向，速度不同
 *
 * 【识别关键词】
 * ✓ 有序数组 → 对撞指针
 * ✓ 链表环/中点 → 快慢指针
 * ✓ 原地删除 → 同向指针
 *
 * 【时间复杂度】O(n)
 * 【空间复杂度】O(1)
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 15, LC 11
 * ⭐⭐⭐⭐ LC 142, LC 167
 */

int main() {
    testThreeSum();
    cout << "双指针算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o two_pointers two_pointers_template.cpp && ./two_pointers
 */
