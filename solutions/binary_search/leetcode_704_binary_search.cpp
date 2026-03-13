/*
LeetCode 704. 二分查找 (Binary Search)

题目概述 (Problem Summary)
-------------------------
给定一个升序排序的整数数组 nums 和一个目标值 target，
如果 target 存在于数组中，返回其下标，否则返回 -1。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^4
- -10^4 <= nums[i], target <= 10^4
- nums 按升序排序

示例 (Example)
-------------
输入：nums = [-1,0,3,5,9,12], target = 9
输出：4
解释：9 出现在索引 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在有序数组中快速定位目标值

关键观察：
1. 有序数组可以使用二分查找
2. 每次比较中点与目标值，缩小搜索区间一半
3. 迭代与递归两种实现方式

根据这些观察，可以得到两种典型解法：
1. 迭代二分
2. 递归二分
*/

#include <iostream>
#include <vector>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用迭代二分查找，在闭区间 [left, right] 中缩小范围。

算法流程：
1. 初始化 left=0, right=n-1
2. 计算 mid
3. 若 nums[mid] == target 返回 mid
4. 否则根据大小关系缩小区间

复杂度分析
---------
时间复杂度：O(log n)
空间复杂度：O(1)
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Recursive)

优化思路
--------
使用递归方式实现二分查找，逻辑更直观。

复杂度分析
---------
时间复杂度：O(log n)
空间复杂度：O(log n)
*/
class Solution_Optimized {
public:
    int search(vector<int>& nums, int target) {
        return dfs(nums, target, 0, static_cast<int>(nums.size()) - 1);
    }

private:
    int dfs(const vector<int>& nums, int target, int left, int right) {
        if (left > right) return -1;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) return dfs(nums, target, mid + 1, right);
        return dfs(nums, target, left, mid - 1);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [-1,0,3,5,9,12], target = 9

left=0, right=5, mid=2 -> nums[2]=3 < 9
left=3, right=5, mid=4 -> nums[4]=9 命中
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：迭代二分
- 时间复杂度：O(log n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：逻辑需要手动维护区间

方法二：递归二分
- 时间复杂度：O(log n)
- 空间复杂度：O(log n)
- 优点：逻辑简洁
- 缺点：递归栈消耗空间
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 数组长度为 1
2. 目标值不存在
3. 目标值在边界位置
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    int target1 = 9;
    cout << "测试用例 1 - 输出: " << solution.search(nums1, target1)
         << " (期望: 4)" << endl;

    // 测试用例 2
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    int target2 = 2;
    cout << "测试用例 2 - 输出: " << solution.search(nums2, target2)
         << " (期望: -1)" << endl;

    return 0;
}
