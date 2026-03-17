/*
LeetCode 4. 寻找两个正序数组的中位数 (Median of Two Sorted Arrays)

题目概述 (Problem Summary)
-------------------------
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
请你找出并返回这两个正序数组的中位数。

算法的时间复杂度应该为 O(log (m+n))。

关键约束 (Key Constraints)
-------------------------
- nums1.length == m
- nums2.length == n
- 0 <= m <= 1000
- 0 <= n <= 1000
- 1 <= m + n <= 2000
- -10^6 <= nums1[i], nums2[i] <= 10^6

示例 (Example)
-------------
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3]，中位数 2

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4]，中位数 (2 + 3) / 2 = 2.5

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在两个有序数组中找到中位数，要求 O(log(m+n)) 时间复杂度

关键观察：
1. O(log(m+n)) 提示使用二分查找
2. 中位数将数组分为两部分，左边 ≤ 右边
3. 可以在较短的数组上进行二分查找
4. 通过分割线将两个数组分为左右两部分
5. 满足条件：左边最大值 ≤ 右边最小值

根据这些观察，可以得到几种典型解法：
1. 二分查找（最优，O(log(min(m,n)))）
2. 归并排序（O(m+n)，不满足时间要求）
3. 双指针（O(m+n)，不满足时间要求）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
方法一：我的原始解法 - 二分查找 (Approach 1: Binary Search)

核心思想
--------
在较短的数组上进行二分查找，找到合适的分割位置。
使分割后左边所有元素 ≤ 右边所有元素。

算法流程：
1. 确保 nums1 是较短的数组（优化二分查找）
2. 在 nums1 上进行二分查找，寻找分割位置 i
3. 根据 i 计算 nums2 的分割位置 j = (m + n + 1) / 2 - i
4. 检查分割是否有效：
   - nums1[i-1] <= nums2[j]
   - nums2[j-1] <= nums1[i]
5. 如果有效，计算中位数：
   - 奇数个元素：max(左边最大值)
   - 偶数个元素：(max(左边最大值) + min(右边最小值)) / 2
6. 如果无效，调整二分查找范围

分割示例：
nums1: [1, 3, 5, 7]    i = 2
       左边: [1, 3]  |  右边: [5, 7]

nums2: [2, 4, 6, 8, 10]    j = 3
       左边: [2, 4, 6]  |  右边: [8, 10]

合并后的左边: [1, 2, 3, 4, 6]
合并后的右边: [5, 7, 8, 10]

检查条件：
- nums1[i-1] = 3 <= nums2[j] = 8 ✓
- nums2[j-1] = 6 <= nums1[i] = 5 ✗

需要调整 i

为什么在较短数组上二分？
- 减少二分查找的次数
- 时间复杂度 O(log(min(m,n)))

为什么 j = (m + n + 1) / 2 - i？
- 保证左边元素个数 = 右边元素个数（或多1个）
- (m + n + 1) / 2 确保奇数时左边多1个

复杂度分析
---------
时间复杂度：O(log(min(m, n)))
- 在较短数组上二分查找

空间复杂度：O(1)
- 只使用常数个变量

其中：
m = nums1.length
n = nums2.length
*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();

        // 确保 nums1 是较短的数组
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }

        // 在 nums1 上进行二分查找
        int left = 0, right = m;

        while (left <= right) {
            // nums1 的分割位置
            int i = left + (right - left) / 2;
            // nums2 的分割位置
            int j = (m + n + 1) / 2 - i;

            // nums1 左边的最大值
            int nums1LeftMax  = (i == 0) ? INT_MIN : nums1[i - 1];
            // nums1 右边的最小值
            int nums1RightMin = (i == m) ? INT_MAX : nums1[i];
            // nums2 左边的最大值
            int nums2LeftMax  = (j == 0) ? INT_MIN : nums2[j - 1];
            // nums2 右边的最小值
            int nums2RightMin = (j == n) ? INT_MAX : nums2[j];

            // 检查分割是否有效
            if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin) {
                // 找到了正确的分割位置
                if ((m + n) % 2 == 1) {
                    // 奇数个元素，返回左边最大值
                    return max(nums1LeftMax, nums2LeftMax);
                } else {
                    // 偶数个元素，返回左边最大值和右边最小值的平均
                    return ((long long)max(nums1LeftMax, nums2LeftMax)
                          + min(nums1RightMin, nums2RightMin)) / 2.0;
                }
            }
            // nums1 左边太大，需要减小 i
            else if (nums1LeftMax > nums2RightMin) {
                right = i - 1;
            }
            // nums1 左边太小，需要增大 i
            else {
                left = i + 1;
            }
        }

        return 0.0;
    }
};

/*
方法二：归并排序（不满足时间要求）(Approach 2: Merge Sort)

核心思想
--------
合并两个有序数组，然后找中位数。

算法流程：
1. 使用双指针合并两个数组
2. 找到中位数位置
3. 返回中位数

复杂度分析
---------
时间复杂度：O(m + n)
- 需要遍历两个数组

空间复杂度：O(m + n)
- 需要额外数组存储合并结果

不满足题目要求的 O(log(m+n))
*/
class Solution_Merge {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> merged;
        int i = 0, j = 0;

        // 合并两个数组
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                merged.push_back(nums1[i++]);
            } else {
                merged.push_back(nums2[j++]);
            }
        }

        // 添加剩余元素
        while (i < nums1.size()) {
            merged.push_back(nums1[i++]);
        }
        while (j < nums2.size()) {
            merged.push_back(nums2[j++]);
        }

        // 计算中位数
        int n = merged.size();
        if (n % 2 == 1) {
            return merged[n / 2];
        } else {
            return (merged[n / 2 - 1] + merged[n / 2]) / 2.0;
        }
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：nums1 = [1, 3], nums2 = [2]

使用方法一（二分查找）：

初始状态：
- m = 2, n = 1
- nums1 较短，在 nums1 上二分
- left = 0, right = 2

第 1 次循环：
- i = 1, j = (2 + 1 + 1) / 2 - 1 = 1
- nums1LeftMax = nums1[0] = 1
- nums1RightMin = nums1[1] = 3
- nums2LeftMax = nums2[0] = 2
- nums2RightMin = INT_MAX

检查条件：
- nums1LeftMax (1) <= nums2RightMin (INT_MAX) ✓
- nums2LeftMax (2) <= nums1RightMin (3) ✓

找到正确分割：
- 总元素个数 = 3（奇数）
- 返回 max(1, 2) = 2

结果：2.0

---

输入：nums1 = [1, 2], nums2 = [3, 4]

初始状态：
- m = 2, n = 2
- left = 0, right = 2

第 1 次循环：
- i = 1, j = (2 + 2 + 1) / 2 - 1 = 1
- nums1LeftMax = 1, nums1RightMin = 2
- nums2LeftMax = 3, nums2RightMin = 4

检查条件：
- nums1LeftMax (1) <= nums2RightMin (4) ✓
- nums2LeftMax (3) <= nums1RightMin (2) ✗

nums2LeftMax > nums1RightMin，需要增大 i
- left = 2

第 2 次循环：
- i = 2, j = (2 + 2 + 1) / 2 - 2 = 0
- nums1LeftMax = 2, nums1RightMin = INT_MAX
- nums2LeftMax = INT_MIN, nums2RightMin = 3

检查条件：
- nums1LeftMax (2) <= nums2RightMin (3) ✓
- nums2LeftMax (INT_MIN) <= nums1RightMin (INT_MAX) ✓

找到正确分割：
- 总元素个数 = 4（偶数）
- 返回 (max(2, INT_MIN) + min(INT_MAX, 3)) / 2.0
- 返回 (2 + 3) / 2.0 = 2.5

结果：2.5
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二分查找
- 时间复杂度：O(log(min(m, n)))
- 空间复杂度：O(1)
- 优点：满足题目要求，最优解
- 缺点：理解和实现较复杂

方法二：归并排序
- 时间复杂度：O(m + n)
- 空间复杂度：O(m + n)
- 优点：简单直观
- 缺点：不满足题目的时间要求

方法一是唯一满足 O(log(m+n)) 的解法。
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 一个数组为空：nums1 = [], nums2 = [1]
   - 返回 nums2 的中位数

2. 两个数组长度相同：nums1 = [1, 2], nums2 = [3, 4]
   - 正常处理

3. 一个数组只有一个元素：nums1 = [1], nums2 = [2, 3]
   - 正常处理

4. 所有元素相同：nums1 = [1, 1], nums2 = [1, 1]
   - 返回 1.0

5. 负数：nums1 = [-2, -1], nums2 = [3]
   - 返回 -1.0

6. 奇数个元素：nums1 = [1], nums2 = [2, 3]
   - 返回 2.0

7. 偶数个元素：nums1 = [1, 2], nums2 = [3, 4]
   - 返回 2.5
*/

int main() {
    Solution solution;

    // 测试用例 1：基本情况
    vector<int> nums1_1 = {1, 3};
    vector<int> nums2_1 = {2};
    cout << "测试用例 1: [1,3] 和 [2] -> "
         << solution.findMedianSortedArrays(nums1_1, nums2_1)
         << " (期望: 2.0)" << endl;

    // 测试用例 2：偶数个元素
    vector<int> nums1_2 = {1, 2};
    vector<int> nums2_2 = {3, 4};
    cout << "测试用例 2: [1,2] 和 [3,4] -> "
         << solution.findMedianSortedArrays(nums1_2, nums2_2)
         << " (期望: 2.5)" << endl;

    // 测试用例 3：一个数组为空
    vector<int> nums1_3 = {};
    vector<int> nums2_3 = {1};
    cout << "测试用例 3: [] 和 [1] -> "
         << solution.findMedianSortedArrays(nums1_3, nums2_3)
         << " (期望: 1.0)" << endl;

    // 测试用例 4：负数
    vector<int> nums1_4 = {-2, -1};
    vector<int> nums2_4 = {3};
    cout << "测试用例 4: [-2,-1] 和 [3] -> "
         << solution.findMedianSortedArrays(nums1_4, nums2_4)
         << " (期望: -1.0)" << endl;

    // 测试用例 5：长度差异大
    vector<int> nums1_5 = {1};
    vector<int> nums2_5 = {2, 3, 4, 5, 6};
    cout << "测试用例 5: [1] 和 [2,3,4,5,6] -> "
         << solution.findMedianSortedArrays(nums1_5, nums2_5)
         << " (期望: 3.5)" << endl;

    return 0;
}

/*
关键要点总结
-----------
1. 二分查找的关键是找到正确的分割位置
2. 在较短数组上二分可以优化时间复杂度
3. 分割条件：左边最大值 ≤ 右边最小值
4. 注意处理边界情况（数组为空、索引越界）
5. 中位数的计算分奇偶两种情况
6. 使用 INT_MIN 和 INT_MAX 处理边界

二分查找的本质：
- 不是在值域上二分，而是在分割位置上二分
- 通过调整分割位置，使左右两边满足条件

相关题目
-------
- LeetCode 295: 数据流的中位数
- LeetCode 480: 滑动窗口中位数
- LeetCode 719: 找出第 K 小的数对距离
- LeetCode 786: 第 K 个最小的素数分数
- LeetCode 878: 第 N 个神奇数字
*/
