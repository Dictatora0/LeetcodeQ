/*
LeetCode 33. 搜索旋转排序数组 (Search in Rotated Sorted Array)

题目概述 (Problem Summary)
-------------------------
整数数组 nums 按升序排列,数组中的值互不相同。

在传递给函数之前,nums 在预先未知的某个下标 k(0 <= k < nums.length)上进行了旋转,
使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]。

例如,[0,1,2,4,5,6,7] 在下标 3 处旋转后可能变为 [4,5,6,7,0,1,2]。

给你旋转后的数组 nums 和一个整数 target,如果 nums 中存在这个目标值 target,
则返回它的下标,否则返回 -1。

要求:时间复杂度为 O(log n)

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 5000
- -10^4 <= nums[i] <= 10^4
- nums 中的每个值都独一无二
- 题目数据保证 nums 在预先未知的某个下标上进行了旋转
- -10^4 <= target <= 10^4

示例 (Example)
-------------
输入:nums = [4,5,6,7,0,1,2], target = 0
输出:4

输入:nums = [4,5,6,7,0,1,2], target = 3
输出:-1

输入:nums = [1], target = 0
输出:-1

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题?
- 在旋转排序数组中查找目标值,要求 O(log n) 时间复杂度

关键观察:
1. 虽然整个数组不是有序的,但可以分为两段有序的子数组
2. 对于任意位置 mid,至少有一半是有序的
3. 可以利用有序的那一半来判断 target 是否在其中
4. 如果 target 在有序的那一半,就在那一半继续二分查找
5. 否则,在另一半继续二分查找

核心技巧:判断哪一半是有序的
- 如果 nums[left] <= nums[mid],说明左半部分有序
- 否则,右半部分有序

为什么这个判断有效?
- 旋转数组的特点:一定有一半是完全有序的
- 例如 [4,5,6,7,0,1,2]:
  - mid=3 时,nums[0]=4 <= nums[3]=7,左半部分 [4,5,6,7] 有序
  - mid=5 时,nums[4]=0 < nums[5]=1 但 nums[0]=4 > nums[5]=1,右半部分相对有序

根据这些观察,可以得到二分查找解法。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一:我的原始解法 (Approach 1: My Original Solution - Binary Search on Rotated Array)

核心思想
--------
使用二分查找,关键是判断哪一半是有序的,然后判断 target 是否在有序的那一半。

算法流程:
1. 初始化 left=0, right=nums.size()-1
2. 当 left <= right 时循环:
   a. 计算 mid = left + (right - left) / 2
   b. 如果 nums[mid] == target,返回 mid
   c. 判断哪一半是有序的:
      - 如果 nums[left] <= nums[mid],左半部分有序:
        * 如果 nums[left] <= target < nums[mid],target 在左半部分,right = mid - 1
        * 否则,target 在右半部分,left = mid + 1
      - 否则,右半部分有序:
        * 如果 nums[mid] < target <= nums[right],target 在右半部分,left = mid + 1
        * 否则,target 在左半部分,right = mid - 1
3. 循环结束后返回 -1

为什么这个算法正确?
- 每次都能确定 target 在哪一半,缩小搜索范围
- 利用了旋转数组"至少有一半有序"的特性
- 标准二分查找保证了 O(log n) 的时间复杂度

复杂度分析
---------
时间复杂度:O(log n),二分查找
空间复杂度:O(1),只使用常数额外空间
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // 找到目标值,直接返回
            if (nums[mid] == target) {
                return mid;
            }

            // 关键:判断哪一半是有序的
            // 情况1:左半部分 [left, mid] 是有序的
            if (nums[left] <= nums[mid]) {
                // 判断 target 是否在有序的左半部分中
                // 注意:nums[left] <= target < nums[mid]
                // 不能包含 nums[mid],因为已经判断过 nums[mid] != target
                if (nums[left] <= target && target < nums[mid]) {
                    // target 在左半部分,缩小右边界
                    right = mid - 1;
                } else {
                    // target 在右半部分,缩小左边界
                    left = mid + 1;
                }
            }
            // 情况2:右半部分 [mid, right] 是有序的
            else {
                // 判断 target 是否在有序的右半部分中
                // 注意:nums[mid] < target <= nums[right]
                if (nums[mid] < target && target <= nums[right]) {
                    // target 在右半部分,缩小左边界
                    left = mid + 1;
                } else {
                    // target 在左半部分,缩小右边界
                    right = mid - 1;
                }
            }
        }

        // 未找到目标值
        return -1;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [4,5,6,7,0,1,2], target = 0

第 1 轮:
- left=0, right=6, mid=3
- nums[mid]=7 != 0
- nums[0]=4 <= nums[3]=7,左半部分有序
- target=0 不在 [4,7) 范围内,搜索右半部分
- left=4

第 2 轮:
- left=4, right=6, mid=5
- nums[mid]=1 != 0
- nums[4]=0 > nums[5]=1,右半部分有序
- target=0 不在 (1,2] 范围内,搜索左半部分
- right=4

第 3 轮:
- left=4, right=4, mid=4
- nums[mid]=0 == 0
- 返回 4

nums = [4,5,6,7,0,1,2], target = 3

第 1 轮:
- left=0, right=6, mid=3
- nums[mid]=7 != 3
- nums[0]=4 <= nums[3]=7,左半部分有序
- target=3 不在 [4,7) 范围内,搜索右半部分
- left=4

第 2 轮:
- left=4, right=6, mid=5
- nums[mid]=1 != 3
- nums[4]=0 > nums[5]=1,右半部分有序
- target=3 不在 (1,2] 范围内,搜索左半部分
- right=4

第 3 轮:
- left=4, right=4, mid=4
- nums[mid]=0 != 3
- nums[4]=0 <= nums[4]=0,左半部分有序
- target=3 不在 [0,0) 范围内,搜索右半部分
- left=5

第 4 轮:
- left=5, right=4, left > right
- 返回 -1
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 数组长度为 1:直接比较
2. 数组未旋转(k=0):退化为标准二分查找
3. target 是最小值或最大值:正常处理
4. target 不存在:返回 -1
*/

/*
关键点总结 (Key Points)
---------------------
1. 旋转数组的特性:至少有一半是有序的
2. 判断有序的方法:nums[left] <= nums[mid]
3. 在有序的一半中判断 target 是否存在
4. 注意边界条件:
   - 左半部分有序时:nums[left] <= target < nums[mid]
   - 右半部分有序时:nums[mid] < target <= nums[right]
5. 为什么要用 < 和 <=:
   - nums[mid] 已经判断过不等于 target,所以不能包含
   - nums[left] 和 nums[right] 还没判断过,所以要包含
*/

int main() {
    Solution solution;

    // 测试用例 1:目标存在
    vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    int result1 = solution.search(nums1, target1);
    cout << "测试用例 1 - 输出: " << result1 << " (期望: 4)" << endl;

    // 测试用例 2:目标不存在
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    int result2 = solution.search(nums2, target2);
    cout << "测试用例 2 - 输出: " << result2 << " (期望: -1)" << endl;

    // 测试用例 3:单元素数组
    vector<int> nums3 = {1};
    int target3 = 0;
    int result3 = solution.search(nums3, target3);
    cout << "测试用例 3 - 输出: " << result3 << " (期望: -1)" << endl;

    // 测试用例 4:未旋转数组
    vector<int> nums4 = {1, 2, 3, 4, 5};
    int target4 = 3;
    int result4 = solution.search(nums4, target4);
    cout << "测试用例 4 - 输出: " << result4 << " (期望: 2)" << endl;

    // 测试用例 5:目标是最小值
    vector<int> nums5 = {4, 5, 6, 7, 0, 1, 2};
    int target5 = 0;
    int result5 = solution.search(nums5, target5);
    cout << "测试用例 5 - 输出: " << result5 << " (期望: 4)" << endl;

    return 0;
}
