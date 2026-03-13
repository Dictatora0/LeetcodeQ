/*
LeetCode 198. 打家劫舍 (House Robber)

题目概述 (Problem Summary)
-------------------------
一排房屋存放着非负金额，不能抢相邻的房屋。
给定数组 nums，返回能抢到的最大金额。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 100
- 0 <= nums[i] <= 400

示例 (Example)
-------------
输入：nums = [1,2,3,1]
输出：4
解释：抢 1 号和 3 号房屋，金额 1 + 3 = 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在不相邻约束下选取最大总和

关键观察：
1. 抢第 i 个房屋，则不能抢 i-1
2. dp[i] 表示抢到第 i 个房屋时的最大金额
3. 状态转移：dp[i] = max(dp[i-1], dp[i-2] + nums[i])

根据这些观察，可以得到两种典型解法：
1. 动态规划
2. 状态压缩（滚动变量）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用 dp 数组记录到当前位置的最大收益。

算法流程：
1. dp[0] = nums[0]
2. dp[1] = max(nums[0], nums[1])
3. dp[i] = max(dp[i-1], dp[i-2] + nums[i])

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 1) return nums[0];

        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - State Compression)

优化思路
--------
只保留前两项状态，用两个变量滚动更新。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int rob(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 1) return nums[0];

        int prev2 = nums[0];
        int prev1 = max(nums[0], nums[1]);

        for (int i = 2; i < n; ++i) {
            int cur = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [2,7,9,3,1]

dp[0]=2
dp[1]=max(2,7)=7
dp[2]=max(7,2+9)=11
dp[3]=max(11,7+3)=11
dp[4]=max(11,11+1)=12
结果 12
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：DP 数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：直观易理解
- 缺点：多余空间

方法二：滚动变量
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：不容易回溯路径
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个房屋：返回 nums[0]
2. 只有两个房屋：返回较大值
3. 所有金额为 0：结果为 0
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "测试用例 1 - 输出: " << solution.rob(nums1)
         << " (期望: 4)" << endl;

    // 测试用例 2
    vector<int> nums2 = {2, 7, 9, 3, 1};
    cout << "测试用例 2 - 输出: " << solution.rob(nums2)
         << " (期望: 12)" << endl;

    return 0;
}
