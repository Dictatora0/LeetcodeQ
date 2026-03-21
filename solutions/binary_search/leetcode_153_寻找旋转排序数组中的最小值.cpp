/*
LeetCode 153. 寻找旋转排序数组中的最小值 (Find Minimum in Rotated Sorted Array)

题目概述 (Problem Summary)
-------------------------
已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。
例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
- 若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
- 若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]

注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]]。

给你一个元素值 互不相同 的数组 nums，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。
请你找出并返回数组中的 最小元素。

你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

关键约束 (Key Constraints)
-------------------------
- n == nums.length
- 1 <= n <= 5000
- -5000 <= nums[i] <= 5000
- nums 中的所有整数 互不相同
- nums 原来是一个升序排序的数组，并进行了 1 至 n 次旋转

示例 (Example)
-------------
输入：nums = [3,4,5,1,2]
输出：1
解释：原数组为 [1,2,3,4,5]，旋转 3 次得到输入数组

输入：nums = [4,5,6,7,0,1,2]
输出：0
解释：原数组为 [0,1,2,4,5,6,7]，旋转 4 次得到输入数组

输入：nums = [11,13,15,17]
输出：11
解释：原数组为 [11,13,15,17]，旋转 4 次（或 0 次）得到输入数组

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在旋转排序数组中找到最小值（即旋转点）

关键观察：
1. 旋转后的数组可以分为两段有序数组
   例如：[4,5,6,7,0,1,2] = [4,5,6,7] + [0,1,2]
2. 最小值就是第二段的第一个元素（旋转点）
3. 如果没有旋转，最小值就是第一个元素

核心问题：如何用二分查找定位旋转点？

关键技巧：比较 nums[mid] 与 nums[right]
- 如果 nums[mid] > nums[right]：
  说明 mid 在左半段（较大的部分），最小值在 mid 右侧
  例如：[4,5,6,7,0,1,2]，mid=7 > right=2

- 如果 nums[mid] <= nums[right]：
  说明 mid 在右半段（较小的部分）或数组未旋转，最小值在 mid 或 mid 左侧
  例如：[4,5,6,7,0,1,2]，mid=0 < right=2

为什么要与 nums[right] 比较，而不是 nums[left]？
- 与 nums[left] 比较无法确定最小值的位置
- 与 nums[right] 比较可以明确判断 mid 在哪一段
- 例如：[3,4,5,1,2]
  - mid=5, nums[mid] > nums[left]=3，但最小值可能在左边或右边，无法判断
  - mid=5, nums[mid] > nums[right]=2，可以确定最小值在右边

为什么循环条件是 left < right 而不是 left <= right？
- 我们要找的是最小值的位置（索引），不是判断是否存在
- 当 left == right 时，已经找到了最小值的位置
- 返回 left 或 right 都可以（它们相等）

根据这些观察，可以得到二分查找解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - Binary Search)

核心思想
--------
使用二分查找，通过比较 nums[mid] 与 nums[right] 来判断最小值的位置。

算法流程：
1. 初始化 left=0, right=n-1
2. 当 left < right 时循环：
   a. 计算 mid = left + (right - left) / 2
   b. 如果 nums[mid] > nums[right]：
      说明 mid 在左半段，最小值在右侧，left = mid + 1
   c. 否则：
      说明 mid 在右半段或未旋转，最小值在 mid 或左侧，right = mid
3. 返回 left（此时 left == right）

为什么这个算法正确？
- 每次都能排除一半的搜索空间
- 最终 left 和 right 会收敛到最小值的位置
- right = mid 而不是 mid - 1，因为 mid 可能就是最小值

复杂度分析
---------
时间复杂度：O(log n)，二分查找
空间复杂度：O(1)，只使用常数额外空间
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;

        // 循环条件是 left < right，不是 left <= right
        // 因为我们要找位置，当 left == right 时已经找到
        while (left < right) {
            int mid = left + (right - left) / 2;

            // 关键判断：比较 nums[mid] 与 nums[right]
            if (nums[mid] > nums[right]) {
                // mid 在左半段（较大的部分）
                // 最小值一定在 mid 右侧，所以 left = mid + 1
                left = mid + 1;
            } else {
                // nums[mid] <= nums[right]
                // mid 在右半段（较小的部分）或数组未旋转
                // 最小值可能是 mid 或在 mid 左侧，所以 right = mid
                right = mid;
            }
        }

        // 返回 left 或 right 都可以（此时它们相等）
        // 返回的是索引，如果要返回值，用 nums[left]
        return nums[left];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
示例 1：nums = [3,4,5,1,2]

第 1 轮：
- left=0, right=4
- mid=2, nums[mid]=5, nums[right]=2
- 5 > 2，说明 mid 在左半段，left = mid + 1 = 3

第 2 轮：
- left=3, right=4
- mid=3, nums[mid]=1, nums[right]=2
- 1 < 2，说明 mid 在右半段，right = mid = 3

第 3 轮：
- left=3, right=3
- 循环结束，返回 nums[3] = 1

示例 2：nums = [4,5,6,7,0,1,2]

第 1 轮：
- left=0, right=6
- mid=3, nums[mid]=7, nums[right]=2
- 7 > 2，left = 4

第 2 轮：
- left=4, right=6
- mid=5, nums[mid]=1, nums[right]=2
- 1 < 2，right = 5

第 3 轮：
- left=4, right=5
- mid=4, nums[mid]=0, nums[right]=1
- 0 < 1，right = 4

第 4 轮：
- left=4, right=4
- 循环结束，返回 nums[4] = 0

示例 3：nums = [11,13,15,17]（未旋转）

第 1 轮：
- left=0, right=3
- mid=1, nums[mid]=13, nums[right]=17
- 13 < 17，right = 1

第 2 轮：
- left=0, right=1
- mid=0, nums[mid]=11, nums[right]=13
- 11 < 13，right = 0

第 3 轮：
- left=0, right=0
- 循环结束，返回 nums[0] = 11
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 数组未旋转（已经有序）：[1,2,3,4,5]
   - 第一个元素就是最小值
   - 算法仍然正确，会收敛到 left=0

2. 只有一个元素：[1]
   - 直接返回该元素
   - left=0, right=0，循环不执行

3. 只有两个元素：[2,1]
   - 第 1 轮：mid=0, nums[0]=2 > nums[1]=1，left=1
   - 返回 nums[1]=1

4. 旋转一次：[5,1,2,3,4]
   - 最小值在第二个位置
   - 算法正确找到

5. 旋转 n 次（相当于未旋转）：[1,2,3,4,5]
   - 与情况 1 相同
*/

/*
常见错误 (Common Mistakes)
------------------------
1. 错误：使用 left <= right 作为循环条件
   - 会导致死循环或越界
   - 正确：使用 left < right

2. 错误：比较 nums[mid] 与 nums[left]
   - 无法准确判断最小值的位置
   - 正确：比较 nums[mid] 与 nums[right]

3. 错误：当 nums[mid] <= nums[right] 时，right = mid - 1
   - 可能会跳过最小值
   - 正确：right = mid（因为 mid 可能就是最小值）

4. 错误：返回 left 而不是 nums[left]
   - 题目要求返回最小值，不是索引
   - 正确：返回 nums[left]
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：二分查找（推荐）
- 时间复杂度：O(log n)
- 空间复杂度：O(1)
- 优点：满足题目要求，效率高
- 缺点：需要理解旋转数组的性质

方法二：线性扫描（不推荐）
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：简单直观
- 缺点：不满足题目的 O(log n) 要求
*/

int main() {
    Solution solution;

    // 测试用例 1：旋转数组
    vector<int> nums1 = {3, 4, 5, 1, 2};
    int result1 = solution.findMin(nums1);
    cout << "测试用例 1 - 输出: " << result1 << " (期望: 1)" << endl;

    // 测试用例 2：旋转数组
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    int result2 = solution.findMin(nums2);
    cout << "测试用例 2 - 输出: " << result2 << " (期望: 0)" << endl;

    // 测试用例 3：未旋转数组
    vector<int> nums3 = {11, 13, 15, 17};
    int result3 = solution.findMin(nums3);
    cout << "测试用例 3 - 输出: " << result3 << " (期望: 11)" << endl;

    // 测试用例 4：只有两个元素
    vector<int> nums4 = {2, 1};
    int result4 = solution.findMin(nums4);
    cout << "测试用例 4 - 输出: " << result4 << " (期望: 1)" << endl;

    // 测试用例 5：只有一个元素
    vector<int> nums5 = {1};
    int result5 = solution.findMin(nums5);
    cout << "测试用例 5 - 输出: " << result5 << " (期望: 1)" << endl;

    return 0;
}