/*
LeetCode 213. House Robber II (打家劫舍 II)

题目概述 (Problem Summary)
-------------------------
房屋围成一个环，不能抢相邻房屋。
求在不触发警报的前提下可抢到的最大金额。

和 LC 198 的区别：
- LC 198 是线性数组
- LC 213 首尾相邻，多了环约束

关键词
------
- 线性 DP
- 环形拆分
- 状态压缩

算法思路 (Algorithm Thinking)
----------------------------
环形的关键冲突是“第 0 间”和“第 n-1 间”不能同时抢。

因此答案只能来自两种互斥情况：
1. 不抢最后一间：在区间 [0..n-2] 做 LC 198
2. 不抢第一间：在区间 [1..n-1] 做 LC 198

最终答案：
max(robLinear(0, n-2), robLinear(1, n-1))

线性子问题（LC 198）转移：
- dp[i] = max(dp[i-1], dp[i-2] + nums[i])
- 用 prev2/prev1 做 O(1) 状态压缩

常见变体
--------
1. LeetCode 198 打家劫舍：线性版本
2. LeetCode 337 打家劫舍 III：树形 DP（树上选/不选）
3. 需要恢复具体抢劫路径：额外记录决策数组

面试追问
--------
Q1: 为什么拆两段就覆盖所有情况？
A1: 因为首尾冲突，合法解必然落在“去头”或“去尾”之一。

Q2: 两段会不会重复统计？
A2: 会有交集但不影响，取最大值即可。

Q3: n=1 怎么办？
A3: 直接返回 nums[0]，否则两段区间会非法。

Q4: 复杂度是多少？
A4: 时间 O(n)，空间 O(1)。
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        if (n == 1) return nums[0];
        return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }

private:
    int robLinear(const vector<int>& nums, int left, int right) {
        int prev2 = 0;  // dp[i-2]
        int prev1 = 0;  // dp[i-1]

        for (int i = left; i <= right; ++i) {
            int cur = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

/*
示例推演
--------
nums = [2,3,2]
- 方案 A: [2,3] -> 最大 3
- 方案 B: [3,2] -> 最大 3
答案 3

nums = [1,2,3,1]
- 方案 A: [1,2,3] -> 最大 4
- 方案 B: [2,3,1] -> 最大 3
答案 4

易错点
------
1. 忘记 n=1 特判
2. 把两段写成 [0..n-1] 与 [1..n-1]（第一段错误）
3. 线性 DP 初始状态设置混乱
*/

int main() {
    Solution sol;

    {
        vector<int> nums = {2, 3, 2};
        assert(sol.rob(nums) == 3);
    }
    {
        vector<int> nums = {1, 2, 3, 1};
        assert(sol.rob(nums) == 4);
    }
    {
        vector<int> nums = {1, 2, 3};
        assert(sol.rob(nums) == 3);
    }
    {
        vector<int> nums = {5};
        assert(sol.rob(nums) == 5);
    }

    cout << "LeetCode 213 tests passed.\n";
    return 0;
}
