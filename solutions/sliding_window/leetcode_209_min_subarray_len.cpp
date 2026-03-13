/*
LeetCode 209. 长度最小的子数组 (Minimum Size Subarray Sum)

题目概述 (Problem Summary)
-------------------------
给定一个正整数数组 nums 和一个正整数 target，
找出数组中满足其和 >= target 的最短连续子数组长度。
如果不存在，返回 0。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^5
- 1 <= target <= 10^9
- nums 全为正数（关键！）

示例 (Example)
-------------
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 的和为 7，长度为 2，最短

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在正整数数组中找一个最短连续区间，使其和至少为 target

关键观察：
1. nums 全为正数，窗口右移时和只增不减
2. 当窗口和达到 target 时，可以收缩左边界尝试缩短长度
3. 这正是滑动窗口的典型场景

根据这些观察，可以得到两种典型解法：
1. 滑动窗口（双指针）
2. 前缀和 + 二分查找
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用滑动窗口维护当前子数组的和。
右指针扩展窗口，直到窗口和 >= target，
再移动左指针缩小窗口并更新答案。

算法流程：
1. 初始化 left=0, sum=0, ans=INF
2. 右指针从 0 扫到 n-1，累计 sum
3. 当 sum >= target 时，更新最短长度并收缩左边界
4. 最终若 ans 未更新则返回 0

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int sum = 0;
        int ans = INT_MAX;

        for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
            sum += nums[right];

            while (sum >= target) {
                ans = min(ans, right - left + 1);
                sum -= nums[left];
                ++left;
            }
        }

        return ans == INT_MAX ? 0 : ans;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Prefix Sum + Binary Search)

优化思路
--------
使用前缀和数组，针对每个起点 i，
用二分查找寻找最小的 j 使得 prefix[j] - prefix[i] >= target。

为什么可行：
- 前缀和数组单调递增（因为 nums 全为正数）

复杂度分析
---------
时间复杂度：O(n log n)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        int ans = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int need = target + prefix[i];
            auto it = lower_bound(prefix.begin() + i + 1, prefix.end(), need);
            if (it != prefix.end()) {
                int j = static_cast<int>(it - prefix.begin());
                ans = min(ans, j - i);
            }
        }

        return ans == INT_MAX ? 0 : ans;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
target = 7, nums = [2,3,1,2,4,3]

窗口扩展：
right=0 sum=2
right=1 sum=5
right=2 sum=6
right=3 sum=8 >= 7，更新长度=4，收缩 left
left=1 sum=6
right=4 sum=10 >= 7，更新长度=4，收缩
left=2 sum=7，更新长度=3，再收缩
left=3 sum=6
right=5 sum=9 >= 7，更新长度=3，收缩
left=4 sum=7，更新长度=2 -> 最短
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：滑动窗口
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：线性时间，最优
- 缺点：依赖“全为正数”的约束

方法二：前缀和 + 二分
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：思路通用、便于理解
- 缺点：复杂度略高
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 无法达到 target：返回 0
2. 只有一个元素且满足：返回 1
3. 数组长度很大：滑动窗口依旧可用
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<int> nums1 = {2, 3, 1, 2, 4, 3};
    int target1 = 7;
    cout << "测试用例 1 - 输出: " << solution.minSubArrayLen(target1, nums1)
         << " (期望: 2)" << endl;

    // 测试用例 2
    vector<int> nums2 = {1, 4, 4};
    int target2 = 4;
    cout << "测试用例 2 - 输出: " << solution.minSubArrayLen(target2, nums2)
         << " (期望: 1)" << endl;

    // 测试用例 3
    vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1};
    int target3 = 11;
    cout << "测试用例 3 - 输出: " << solution.minSubArrayLen(target3, nums3)
         << " (期望: 0)" << endl;

    return 0;
}
