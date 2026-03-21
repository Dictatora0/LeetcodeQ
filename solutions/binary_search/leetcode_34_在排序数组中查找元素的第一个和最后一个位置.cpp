/*
LeetCode 34. 在排序数组中查找元素的第一个和最后一个位置 (Find First and Last Position of Element in Sorted Array)

题目概述 (Problem Summary)
-------------------------
给你一个按照非递减顺序排列的整数数组 nums,和一个目标值 target。
请你找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target,返回 [-1, -1]。

要求:时间复杂度为 O(log n)

关键约束 (Key Constraints)
-------------------------
- 0 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9
- nums 是一个非递减数组
- -10^9 <= target <= 10^9

示例 (Example)
-------------
输入:nums = [5,7,7,8,8,10], target = 8
输出:[3,4]

输入:nums = [5,7,7,8,8,10], target = 6
输出:[-1,-1]

输入:nums = [], target = 0
输出:[-1,-1]

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题?
- 在有序数组中找到目标值的第一个和最后一个位置

关键观察:
1. 要求 O(log n) 时间复杂度,必须使用二分查找
2. 需要找两个位置:第一个位置和最后一个位置
3. 可以使用两次二分查找分别找到这两个位置

核心技巧:lowerBound 模式
- lowerBound(target):找到第一个 >= target 的位置
- lowerBound(target+1):找到第一个 >= target+1 的位置
- lowerBound(target+1) - 1 就是最后一个 == target 的位置

为什么 lowerBound(target+1) - 1 有效?
- lowerBound(target+1) 找到的是第一个 > target 的位置
- 它的前一个位置就是最后一个 <= target 的位置
- 如果这个位置的值等于 target,那就是最后一个 target 的位置

例如:nums = [5,7,7,8,8,10], target = 8
- lowerBound(8) = 3 (第一个 >= 8 的位置)
- lowerBound(9) = 5 (第一个 >= 9 的位置)
- lowerBound(9) - 1 = 4 (最后一个 8 的位置)

根据这些观察,可以得到二分查找解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一:我的原始解法 (Approach 1: My Original Solution - Two Binary Searches with lowerBound)

核心思想
--------
使用 lowerBound 模式进行两次二分查找:
1. 找到第一个 >= target 的位置(左边界)
2. 找到第一个 >= target+1 的位置,减 1 得到右边界

算法流程:
1. 实现 lowerBound 函数:
   - 找到第一个 >= target 的位置
   - 如果不存在,返回 nums.size()
2. 调用 lowerBound(target) 得到左边界
3. 检查左边界是否有效:
   - 如果 left == nums.size() 或 nums[left] != target,返回 [-1, -1]
4. 调用 lowerBound(target+1) - 1 得到右边界
5. 返回 [left, right]

lowerBound 的实现细节:
- 初始化 ans = nums.size()(表示未找到)
- 当 nums[mid] >= target 时:
  * 更新 ans = mid(记录候选位置)
  * right = mid - 1(继续向左搜索更小的位置)
- 当 nums[mid] < target 时:
  * left = mid + 1(向右搜索)

为什么这个算法正确?
- lowerBound 保证找到第一个 >= target 的位置
- lowerBound(target+1) - 1 保证找到最后一个 == target 的位置
- 两次二分查找,时间复杂度 O(log n)

复杂度分析
---------
时间复杂度:O(log n),两次二分查找
空间复杂度:O(1),只使用常数额外空间
*/
class Solution {
public:
    // lowerBound:找到第一个 >= target 的位置
    // 这是一个通用的二分查找模板,非常重要
    int lowerBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int ans = nums.size();  // 初始化为 nums.size(),表示未找到

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // 关键:当 nums[mid] >= target 时
            // 1. 记录当前位置为候选答案
            // 2. 继续向左搜索,看是否有更小的位置也满足条件
            if (nums[mid] >= target) {
                ans = mid;           // 更新答案
                right = mid - 1;     // 继续向左搜索
            } else {
                left = mid + 1;      // 向右搜索
            }
        }

        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        // 特殊情况:空数组
        if (nums.empty()) {
            return {-1, -1};
        }

        // 找到第一个 >= target 的位置(左边界)
        int left = lowerBound(nums, target);

        // 检查左边界是否有效
        // 1. left == nums.size():target 大于所有元素
        // 2. nums[left] != target:找到的位置不是 target
        if (left == nums.size() || nums[left] != target) {
            return {-1, -1};
        }

        // 找到第一个 >= target+1 的位置,减 1 得到右边界
        // 为什么这样有效?
        // - lowerBound(target+1) 找到第一个 > target 的位置
        // - 它的前一个位置就是最后一个 == target 的位置
        int right = lowerBound(nums, target + 1) - 1;

        return {left, right};
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [5,7,7,8,8,10], target = 8

步骤 1:查找左边界 lowerBound(8)
第 1 轮:
- left=0, right=5, mid=2
- nums[2]=7 < 8, left=3

第 2 轮:
- left=3, right=5, mid=4
- nums[4]=8 >= 8, ans=4, right=3

第 3 轮:
- left=3, right=3, mid=3
- nums[3]=8 >= 8, ans=3, right=2

第 4 轮:
- left=3, right=2, left > right
- 返回 ans=3

步骤 2:检查左边界
- left=3, nums[3]=8 == 8, 有效

步骤 3:查找右边界 lowerBound(9) - 1
第 1 轮:
- left=0, right=5, mid=2
- nums[2]=7 < 9, left=3

第 2 轮:
- left=3, right=5, mid=4
- nums[4]=8 < 9, left=5

第 3 轮:
- left=5, right=5, mid=5
- nums[5]=10 >= 9, ans=5, right=4

第 4 轮:
- left=5, right=4, left > right
- 返回 ans=5

right = 5 - 1 = 4

步骤 4:返回 [3, 4]

nums = [5,7,7,8,8,10], target = 6

步骤 1:查找左边界 lowerBound(6)
- 最终返回 ans=1 (第一个 >= 6 的位置是 7)

步骤 2:检查左边界
- left=1, nums[1]=7 != 6, 无效
- 返回 [-1, -1]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空数组:返回 [-1, -1]
2. target 不存在:返回 [-1, -1]
3. target 只出现一次:left == right
4. 整个数组都是 target:返回 [0, nums.size()-1]
5. target 小于最小值:lowerBound 返回 0,但 nums[0] != target
6. target 大于最大值:lowerBound 返回 nums.size()
*/

/*
关键点总结 (Key Points)
---------------------
1. lowerBound 模式是二分查找的重要变体
2. lowerBound(target):找第一个 >= target 的位置
3. lowerBound(target+1) - 1:找最后一个 == target 的位置
4. 为什么要用 ans = nums.size() 初始化?
   - 表示"未找到"的状态
   - 当 target 大于所有元素时,返回 nums.size()
5. 为什么 nums[mid] >= target 时要 right = mid - 1?
   - 因为我们要找"第一个"满足条件的位置
   - 即使 mid 满足条件,左边可能还有更小的位置也满足
6. lowerBound 的通用性:
   - 可以用于查找插入位置
   - 可以用于查找第一个满足条件的位置
   - 是 C++ STL lower_bound 的实现原理
*/

int main() {
    Solution solution;

    // 测试用例 1:目标存在多次
    vector<int> nums1 = {5, 7, 7, 8, 8, 10};
    int target1 = 8;
    vector<int> result1 = solution.searchRange(nums1, target1);
    cout << "测试用例 1 - 输出: [" << result1[0] << "," << result1[1] << "] (期望: [3,4])" << endl;

    // 测试用例 2:目标不存在
    vector<int> nums2 = {5, 7, 7, 8, 8, 10};
    int target2 = 6;
    vector<int> result2 = solution.searchRange(nums2, target2);
    cout << "测试用例 2 - 输出: [" << result2[0] << "," << result2[1] << "] (期望: [-1,-1])" << endl;

    // 测试用例 3:空数组
    vector<int> nums3 = {};
    int target3 = 0;
    vector<int> result3 = solution.searchRange(nums3, target3);
    cout << "测试用例 3 - 输出: [" << result3[0] << "," << result3[1] << "] (期望: [-1,-1])" << endl;

    // 测试用例 4:目标只出现一次
    vector<int> nums4 = {1, 2, 3, 4, 5};
    int target4 = 3;
    vector<int> result4 = solution.searchRange(nums4, target4);
    cout << "测试用例 4 - 输出: [" << result4[0] << "," << result4[1] << "] (期望: [2,2])" << endl;

    // 测试用例 5:整个数组都是目标
    vector<int> nums5 = {1, 1, 1, 1, 1};
    int target5 = 1;
    vector<int> result5 = solution.searchRange(nums5, target5);
    cout << "测试用例 5 - 输出: [" << result5[0] << "," << result5[1] << "] (期望: [0,4])" << endl;

    return 0;
}
