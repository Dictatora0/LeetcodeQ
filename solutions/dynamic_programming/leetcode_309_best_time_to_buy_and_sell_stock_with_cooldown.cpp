/*
LeetCode 309. 最佳买卖股票时机含冷冻期 (Best Time to Buy and Sell Stock with Cooldown)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 prices，其中第 prices[i] 表示第 i 天的股票价格。

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）：

- 卖出股票后，你无法在第二天买入股票（即冷冻期为 1 天）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

关键约束 (Key Constraints)
-------------------------
- 1 <= prices.length <= 5000
- 0 <= prices[i] <= 1000
- 可以多次买卖，但卖出后有一天冷冻期

示例 (Example)
-------------
输入：prices = [1,2,3,0,2]
输出：3
解释：对应的交易状态为：[买入, 卖出, 冷冻期, 买入, 卖出]
     第 1 天买入，第 2 天卖出，利润 = 2-1 = 1
     第 3 天冷冻期
     第 4 天买入，第 5 天卖出，利润 = 2-0 = 2
     总利润 = 1 + 2 = 3

输入：prices = [1]
输出：0

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 可以多次买卖股票，但卖出后有一天冷冻期

关键观察：
1. 相比 122 题，增加了冷冻期的限制
2. 卖出后的第二天不能买入，必须冷冻一天
3. 需要区分"不持有"的两种状态：刚卖出 vs 冷冻期后

状态机模型：
```
      买入              卖出            冷冻期
持有 ────────> 不持有(卖出) ────────> 不持有(冷冻期后)
 ▲                                          │
 └──────────────────────────────────────────┘
              可以再次买入
```

DP 状态定义（方法一：3 个状态）：
- hold：当前持有股票的最大利润
- sold：当前不持有股票，且处于冷冻期（刚卖出）的最大利润
- rest：当前不持有股票，且不处于冷冻期的最大利润

状态转移方程：
- hold = max(hold, rest - prices[i])     // 保持持有 或 从冷冻期后买入
- sold = hold + prices[i]                // 今天卖出
- rest = max(rest, sold)                 // 保持冷冻期后 或 从冷冻期转移

注意：买入只能从 rest 状态转移，不能从 sold 状态转移（冷冻期限制）。

DP 状态定义（方法二：2 个状态）：
- dp[i][0]：第 i 天不持有股票的最大利润
- dp[i][1]：第 i 天持有股票的最大利润

状态转移方程：
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
- dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])  // 注意：从 i-2 转移

初始状态：
- dp[0][0] = 0
- dp[0][1] = -prices[0]
- dp[1][0] = max(0, -prices[0] + prices[1])
- dp[1][1] = max(-prices[0], -prices[1])

根据这些观察，可以得到几种典型解法：
1. DP（3 个状态）- 时间 O(n)，空间 O(1) ⭐ 推荐
2. DP（2 个状态，考虑 i-2）- 时间 O(n)，空间 O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
方法一：DP（3 个状态）(Approach 1: DP with 3 States)

核心思想
--------
定义三个状态：
- hold：持有股票
- sold：刚卖出股票（冷冻期）
- rest：冷冻期后（可以买入）

状态转移：
- hold = max(hold, rest - price)  // 保持持有 或 从 rest 买入
- sold = hold + price             // 今天卖出
- rest = max(rest, sold)          // 保持 rest 或 从 sold 转移

这是最直观、最优的解法！

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(1)
- 只使用 3 个变量
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // 初始化三个状态
        int hold = -prices[0];  // 持有股票
        int sold = 0;           // 刚卖出（冷冻期）
        int rest = 0;           // 冷冻期后

        for (int i = 1; i < n; i++) {
            int newHold = max(hold, rest - prices[i]);
            int newSold = hold + prices[i];
            int newRest = max(rest, sold);

            hold = newHold;
            sold = newSold;
            rest = newRest;
        }

        // 最后一天不持有股票的最大利润
        return max(sold, rest);
    }
};

/*
方法二：DP（2 个状态，考虑 i-2）(Approach 2: DP with 2 States and i-2)

核心思想
--------
定义两个状态：
- dp[i][0]：第 i 天不持有股票的最大利润
- dp[i][1]：第 i 天持有股票的最大利润

关键：买入时从 dp[i-2][0] 转移，而不是 dp[i-1][0]，这样就自动实现了冷冻期。

状态转移：
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
- dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(n)
- dp 数组，可优化到 O(1)
*/
class Solution_2States {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        if (n == 1) return 0;

        // dp[i][0]：第 i 天不持有股票的最大利润
        // dp[i][1]：第 i 天持有股票的最大利润
        vector<vector<int>> dp(n, vector<int>(2));

        // 初始状态
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[1][0] = max(0, prices[1] - prices[0]);
        dp[1][1] = max(-prices[0], -prices[1]);

        for (int i = 2; i < n; i++) {
            // 不持有：保持不持有 或 今天卖出
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);

            // 持有：保持持有 或 从 i-2 买入（冷冻期）
            dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i]);
        }

        return dp[n-1][0];
    }
};

/*
方法三：DP（空间优化）(Approach 3: DP with Space Optimization)

核心思想
--------
观察到 dp[i] 只依赖于 dp[i-1] 和 dp[i-2]，可以用变量代替数组。

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(1)
- 只使用常数个变量
*/
class Solution_Optimized {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        if (n == 1) return 0;

        // 状态变量
        int prevNotHold = 0;           // dp[i-2][0]
        int currNotHold = 0;           // dp[i-1][0]
        int hold = -prices[0];         // dp[i-1][1]

        for (int i = 1; i < n; i++) {
            int newNotHold = max(currNotHold, hold + prices[i]);
            int newHold = max(hold, prevNotHold - prices[i]);

            prevNotHold = currNotHold;
            currNotHold = newNotHold;
            hold = newHold;
        }

        return currNotHold;
    }
};

/*
状态机图解 (State Machine Diagram)
---------------------------------
```
状态转移图：

    ┌─────────────────────────────────┐
    │                                 │
    ▼                                 │
  rest ──────buy──────> hold ──────sell──────> sold
(冷冻期后)              (持有)              (刚卖出)
    ▲                                 │
    │                                 │
    └─────────cooldown─────────────────┘

状态说明：
- rest：不持有股票，且不在冷冻期（可以买入）
- hold：持有股票
- sold：刚卖出股票（冷冻期，不能买入）

状态转移：
- rest -> hold：买入股票
- hold -> sold：卖出股票
- sold -> rest：冷冻期结束
- rest -> rest：保持不持有
- hold -> hold：保持持有
```

状态转移方程：
hold = max(hold, rest - price)
sold = hold + price
rest = max(rest, sold)
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：prices = [1,2,3,0,2]

方法一（3 个状态）：
初始：hold=-1, sold=0, rest=0

i=1, price=2:
  newHold = max(-1, 0-2) = -1
  newSold = -1+2 = 1
  newRest = max(0, 0) = 0
  hold=-1, sold=1, rest=0

i=2, price=3:
  newHold = max(-1, 0-3) = -1
  newSold = -1+3 = 2
  newRest = max(0, 1) = 1
  hold=-1, sold=2, rest=1

i=3, price=0:
  newHold = max(-1, 1-0) = 1
  newSold = 1+0 = 1
  newRest = max(1, 2) = 2
  hold=1, sold=1, rest=2

i=4, price=2:
  newHold = max(1, 2-2) = 1
  newSold = 1+2 = 3
  newRest = max(2, 1) = 2
  hold=1, sold=3, rest=2

返回 max(sold, rest) = max(3, 2) = 3

状态变化表：
天数  价格  hold  sold  rest  说明
 0     1    -1     0     0    初始买入
 1     2    -1     1     0    卖出获利 1
 2     3    -1     2     1    卖出获利 2（或保持）
 3     0     1     1     2    从 rest 买入
 4     2     1     3     2    卖出获利 3

交易过程：
- 第 0 天买入（价格 1）
- 第 1 天卖出（价格 2），利润 1
- 第 2 天冷冻期
- 第 3 天买入（价格 0）
- 第 4 天卖出（价格 2），利润 2
- 总利润 = 1 + 2 = 3
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：3 个状态 ⭐ 推荐
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：状态清晰，易于理解
- 缺点：需要理解三个状态的含义

方法二：2 个状态（考虑 i-2）
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：状态少，通用性强
- 缺点：空间未优化

方法三：空间优化
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：需要维护 i-2 的状态

推荐使用方法一，状态清晰且代码简洁。
*/

/*
关键要点 (Key Points)
-------------------
1. 冷冻期的本质：卖出后的第二天不能买入
2. 状态设计：区分"刚卖出"和"冷冻期后"
3. 状态转移：买入只能从 rest 状态转移
4. 最终答案：max(sold, rest)，因为最后一天可能刚卖出或已冷冻
5. 空间优化：只需要维护前一天和前两天的状态
*/

/*
常见错误 (Common Mistakes)
------------------------
1. 忘记冷冻期限制：买入时从 dp[i-1][0] 转移而不是 dp[i-2][0]
2. 状态定义不清：没有区分"刚卖出"和"冷冻期后"
3. 最终答案错误：只返回 sold 或只返回 rest
4. 初始化错误：没有正确处理前两天的状态
*/

/*
与其他股票问题的对比 (Comparison with Other Stock Problems)
--------------------------------------------------------
121 题（k=1）：
- 状态：hold, notHold
- 买入：hold = max(hold, -price)

122 题（k=∞）：
- 状态：hold, notHold
- 买入：hold = max(hold, notHold - price)

123 题（k=2）：
- 状态：buy1, sell1, buy2, sell2
- 买入：buy1 = max(buy1, -price), buy2 = max(buy2, sell1 - price)

309 题（k=∞，有冷冻期）：
- 状态：hold, sold, rest
- 买入：hold = max(hold, rest - price)  // 只能从 rest 买入

714 题（k=∞，有手续费）：
- 状态：hold, notHold
- 卖出：notHold = max(notHold, hold + price - fee)  // 卖出时扣除手续费
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> prices1 = {1, 2, 3, 0, 2};
    cout << "测试用例 1: [1,2,3,0,2]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices1) << endl;
    cout << "期望: 3" << endl << endl;

    // 测试用例 2
    vector<int> prices2 = {1};
    cout << "测试用例 2: [1]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices2) << endl;
    cout << "期望: 0" << endl << endl;

    // 测试用例 3
    vector<int> prices3 = {1, 2, 4};
    cout << "测试用例 3: [1,2,4]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices3) << endl;
    cout << "期望: 3" << endl << endl;

    // 测试用例 4
    vector<int> prices4 = {2, 1, 4, 5, 2, 9, 7};
    cout << "测试用例 4: [2,1,4,5,2,9,7]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices4) << endl;
    cout << "期望: 11" << endl << endl;

    return 0;
}
