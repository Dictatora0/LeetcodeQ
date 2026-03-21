/*
LeetCode 300. 最长递增子序列 (Longest Increasing Subsequence)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 nums，找到其中最长严格递增子序列的长度。
子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 2500
- -10^4 <= nums[i] <= 10^4

示例 (Example)
-------------
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，长度为 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在数组中找到最长的严格递增子序列

关键观察：
1. dp[i] 表示以 nums[i] 结尾的最长递增子序列长度
2. 对于每个位置 i，需要检查所有 j < i 的位置
3. 如果 nums[i] > nums[j]，则可以接在 j 后面
4. 状态转移：dp[i] = max(dp[i], dp[j] + 1)，其中 j < i 且 nums[j] < nums[i]

根据这些观察，可以得到两种典型解法：
1. 动态规划 O(n²)
2. 动态规划 + 二分查找 O(n log n)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：动态规划 (Approach 1: Dynamic Programming)

核心思想
--------
使用 dp[i] 记录以 nums[i] 结尾的最长递增子序列长度。

状态定义：
dp[i] = 以 nums[i] 结尾的最长递增子序列的长度

状态转移方程：
dp[i] = max(dp[j] + 1)，其中 0 <= j < i 且 nums[j] < nums[i]
如果没有这样的 j，则 dp[i] = 1

初始状态：
dp[i] = 1（每个元素自身可以构成长度为 1 的子序列）

算法流程：
1. 初始化 dp 数组，所有元素为 1
2. 双重循环：外层遍历 i，内层遍历 j < i
3. 如果 nums[i] > nums[j]，更新 dp[i] = max(dp[i], dp[j] + 1)
4. 返回 dp 数组中的最大值

复杂度分析
---------
时间复杂度：O(n²) - 双重循环
空间复杂度：O(n) - dp 数组
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        int ans = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }

        return ans;
    }
};

/*
方法二：动态规划 + 二分查找 (Approach 2: DP with Binary Search)

优化思路
--------
维护一个数组 tails，其中 tails[i] 表示长度为 i+1 的递增子序列的最小末尾元素。
遍历 nums，对于每个元素：
- 如果它大于 tails 中所有元素，追加到 tails 末尾
- 否则，用二分查找找到第一个大于等于它的位置并替换

关键洞察：
- tails 数组始终保持递增
- 可以用二分查找优化查找过程

复杂度分析
---------
时间复杂度：O(n log n) - n 次遍历，每次二分查找 O(log n)
空间复杂度：O(n) - tails 数组
*/
class Solution_Optimized {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;

        for (int num : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), num);
            if (it == tails.end()) {
                tails.push_back(num);
            } else {
                *it = num;
            }
        }

        return tails.size();
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [10,9,2,5,3,7,101,18]

方法一：动态规划
初始：dp = [1,1,1,1,1,1,1,1]

i=1, nums[1]=9:
  j=0: 9 < 10, 不更新
  dp[1]=1

i=2, nums[2]=2:
  j=0: 2 < 10, 不更新
  j=1: 2 < 9, 不更新
  dp[2]=1

i=3, nums[3]=5:
  j=0: 5 < 10, 不更新
  j=1: 5 < 9, 不更新
  j=2: 5 > 2, dp[3]=max(1,1+1)=2
  dp[3]=2

i=4, nums[4]=3:
  j=0: 3 < 10, 不更新
  j=1: 3 < 9, 不更新
  j=2: 3 > 2, dp[4]=max(1,1+1)=2
  j=3: 3 < 5, 不更新
  dp[4]=2

i=5, nums[5]=7:
  j=0: 7 < 10, 不更新
  j=1: 7 < 9, 不更新
  j=2: 7 > 2, dp[5]=max(1,1+1)=2
  j=3: 7 > 5, dp[5]=max(2,2+1)=3
  j=4: 7 > 3, dp[5]=max(3,2+1)=3
  dp[5]=3

i=6, nums[6]=101:
  j=5: 101 > 7, dp[6]=max(1,3+1)=4
  dp[6]=4

i=7, nums[7]=18:
  j=5: 18 > 7, dp[7]=max(1,3+1)=4
  dp[7]=4

最终 dp = [1,1,1,2,2,3,4,4]
答案：4

方法二：二分查找
tails = []
num=10: tails=[10]
num=9:  lower_bound(9)=10, 替换 tails=[9]
num=2:  lower_bound(2)=9, 替换 tails=[2]
num=5:  lower_bound(5)=end, 追加 tails=[2,5]
num=3:  lower_bound(3)=5, 替换 tails=[2,3]
num=7:  lower_bound(7)=end, 追加 tails=[2,3,7]
num=101: lower_bound(101)=end, 追加 tails=[2,3,7,101]
num=18: lower_bound(18)=101, 替换 tails=[2,3,7,18]

答案：tails.size() = 4
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：动态规划
- 时间复杂度：O(n²)
- 空间复杂度：O(n)
- 优点：直观易理解，可以回溯具体序列
- 缺点：时间复杂度较高

方法二：DP + 二分查找
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：时间复杂度最优
- 缺点：不容易回溯具体序列
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：返回 1
2. 全部递增：返回 n
3. 全部递减：返回 1
4. 有重复元素：严格递增，不能包含相等元素
*/

int main() {
    Solution solution;
    Solution_Optimized solution_opt;

    // 测试用例 1
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "测试用例 1 - 方法一输出: " << solution.lengthOfLIS(nums1)
         << " (期望: 4)" << endl;
    cout << "测试用例 1 - 方法二输出: " << solution_opt.lengthOfLIS(nums1)
         << " (期望: 4)" << endl;

    // 测试用例 2
    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "测试用例 2 - 方法一输出: " << solution.lengthOfLIS(nums2)
         << " (期望: 4)" << endl;
    cout << "测试用例 2 - 方法二输出: " << solution_opt.lengthOfLIS(nums2)
         << " (期望: 4)" << endl;

    // 测试用例 3
    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    cout << "测试用例 3 - 方法一输出: " << solution.lengthOfLIS(nums3)
         << " (期望: 1)" << endl;
    cout << "测试用例 3 - 方法二输出: " << solution_opt.lengthOfLIS(nums3)
         << " (期望: 1)" << endl;

    return 0;
}

