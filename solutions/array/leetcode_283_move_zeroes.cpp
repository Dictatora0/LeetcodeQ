/*
LeetCode 283. 移动零 (Move Zeroes)

题目概述 (Problem Summary)
-------------------------
给定一个数组 nums，将所有 0 移动到数组末尾，同时保持非零元素的相对顺序。
要求原地操作。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^4
- -2^31 <= nums[i] <= 2^31 - 1
- 需要原地修改

示例 (Example)
-------------
输入：nums = [0,1,0,3,12]
输出：[1,3,12,0,0]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 稳定地“过滤”掉 0，并将空位填 0

关键观察：
1. 快慢指针可以将非零元素按顺序前移
2. 剩余位置全部填 0 即可

根据这些观察，可以得到两种典型解法：
1. 快慢指针（一次遍历 + 填 0）
2. 交换法（遇到非零就与慢指针位置交换）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用快慢指针将所有非零元素按顺序写入数组前部，
最后将剩余位置填充为 0。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;
        for (int fast = 0; fast < static_cast<int>(nums.size()); ++fast) {
            if (nums[fast] != 0) {
                nums[slow++] = nums[fast];
            }
        }
        while (slow < static_cast<int>(nums.size())) {
            nums[slow++] = 0;
        }
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Swap In Place)

优化思路
--------
遇到非零元素时，与 slow 位置交换。
可以减少写入次数（当 fast==slow 时不做交换）。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;
        for (int fast = 0; fast < static_cast<int>(nums.size()); ++fast) {
            if (nums[fast] != 0) {
                if (slow != fast) {
                    swap(nums[slow], nums[fast]);
                }
                slow++;
            }
        }
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [0,1,0,3,12]

快慢指针：
写入非零 -> [1,3,12,3,12]
填 0 -> [1,3,12,0,0]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：覆盖 + 填 0
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：逻辑简单
- 缺点：可能多次写入

方法二：交换法
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：减少写入
- 缺点：实现稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全是 0：数组不变
2. 没有 0：数组不变
3. 只有一个元素
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {0, 1, 0, 3, 12};
    solution.moveZeroes(nums1);
    cout << "测试用例 1 - 输出: ";
    printVector(nums1);
    cout << " (期望: [1, 3, 12, 0, 0])" << endl;

    // 测试用例 2
    vector<int> nums2 = {0, 0, 1};
    solution.moveZeroes(nums2);
    cout << "测试用例 2 - 输出: ";
    printVector(nums2);
    cout << " (期望: [1, 0, 0])" << endl;

    return 0;
}
