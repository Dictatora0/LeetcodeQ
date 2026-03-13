/*
LeetCode 746. 使用最小花费爬楼梯 (Min Cost Climbing Stairs)

题目概述 (Problem Summary)
-------------------------
给定一个数组 cost，其中 cost[i] 表示踩在第 i 个台阶的花费。
可以从第 0 或第 1 个台阶开始，每次爬 1 或 2 个台阶。
求到达楼梯顶部的最小花费（顶部视为数组末尾之后的位置）。

关键约束 (Key Constraints)
-------------------------
- 2 <= cost.length <= 1000
- 0 <= cost[i] <= 999

示例 (Example)
-------------
输入：cost = [10,15,20]
输出：15
解释：从索引 1 开始，支付 15，直接到顶部

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 选择爬楼路线，累计最小花费

关键观察：
1. 到达台阶 i 的最小花费 = cost[i] + min(到达 i-1, 到达 i-2)
2. 顶部可以由最后两个台阶到达
3. 动态规划可以线性求解

根据这些观察，可以得到两种典型解法：
1. DP 数组
2. 滚动变量空间优化
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
dp[i] 表示到达第 i 个台阶的最小花费。
状态转移：dp[i] = cost[i] + min(dp[i-1], dp[i-2])。
答案为 min(dp[n-1], dp[n-2])。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = static_cast<int>(cost.size());
        vector<int> dp(n, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int i = 2; i < n; ++i) {
            dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
        }

        return min(dp[n - 1], dp[n - 2]);
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Rolling Variables)

优化思路
--------
只保留前两级的最小花费即可完成转移。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = static_cast<int>(cost.size());
        int prev2 = cost[0];
        int prev1 = cost[1];

        for (int i = 2; i < n; ++i) {
            int cur = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = cur;
        }

        return min(prev1, prev2);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
cost = [10, 15, 20]

dp[0]=10
dp[1]=15
dp[2]=20+min(10,15)=30
答案 min(dp[1], dp[2]) = 15
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：DP 数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：直观易懂
- 缺点：额外空间

方法二：滚动变量
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：不可回溯路径
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有两级台阶：直接取 min(cost[0], cost[1])
2. 花费均为 0：结果为 0
3. 大量台阶：滚动变量更节省空间
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<int> cost1 = {10, 15, 20};
    cout << "测试用例 1 - 输出: " << solution.minCostClimbingStairs(cost1)
         << " (期望: 15)" << endl;

    // 测试用例 2
    vector<int> cost2 = {1,100,1,1,1,100,1,1,100,1};
    cout << "测试用例 2 - 输出: " << solution.minCostClimbingStairs(cost2)
         << " (期望: 6)" << endl;

    return 0;
}
