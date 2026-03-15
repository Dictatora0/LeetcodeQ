/*
LeetCode 714. 买卖股票的最佳时机含手续费 (Best Time to Buy and Sell Stock with Transaction Fee)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 prices，其中 prices[i] 表示第 i 天的股票价格；整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

关键约束 (Key Constraints)
-------------------------
- 1 <= prices.length <= 5 * 10^4
- 1 <= prices[i] < 5 * 10^4
- 0 <= fee < 5 * 10^4
- 可以多次买卖，但每次交易需要支付手续费

示例 (Example)
-------------
输入：prices = [1,3,2,8,4,9], fee = 2
输出：8
解释：能够达到的最大利润：
     在此处买入 prices[0] = 1
     在此处卖出 prices[3] = 8
     在此处买入 prices[4] = 4
     在此处卖出 prices[5] = 9
     总利润：((8 - 1) - 2) + ((9 - 4) - 2) = 8

输入：prices = [1,3,7,5,10,3], fee = 3
输出：6

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 可以多次买卖股票，但每次交易需要支付手续费

关键观察：
1. 相比 122 题，增加了手续费的限制
2. 手续费可以在买入时扣除，也可以在卖出时扣除
3. 本质上是 122 题的变种，只需要在状态转移时考虑手续费

状态机模型：
```
      买入(-fee)        卖出
  ┌────────────┐    ┌────────┐
  │            ▼    │        ▼
未持有 ──────────> 持有 ──────> 未持有
  ▲                            │
  └────────────────────────────┘
         可以循环多次
```

DP 状态定义：
- dp[i][0]：第 i 天不持有股票的最大利润
- dp[i][1]：第 i 天持有股票的最大利润

状态转移方程（手续费在卖出时扣除）：
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee)  // 保持不持有 或 今天卖出（扣除手续费）
- dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])        // 保持持有 或 今天买入

状态转移方程（手续费在买入时扣除）：
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])        // 保持不持有 或 今天卖出
- dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)  // 保持持有 或 今天买入（扣除手续费）

两种方式等价，本题采用在卖出时扣除手续费。

初始状态：
- dp[0][0] = 0
- dp[0][1] = -prices[0]

根据这些观察，可以得到几种典型解法：
1. DP（状态机）- 时间 O(n)，空间 O(1) ⭐ 推荐
2. 贪心 - 时间 O(n)，空间 O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：DP（状态机）(Approach 1: DP with State Machine)

核心思想
--------
使用动态规划，定义两个状态：持有股票和不持有股票。
在卖出时扣除手续费。

状态定义：
- hold：持有股票的最大利润
- notHold：不持有股票的最大利润

状态转移：
- notHold = max(notHold, hold + price - fee)  // 保持不持有 或 今天卖出（扣除手续费）
- hold = max(hold, notHold - price)           // 保持持有 或 今天买入

这是最直观、最优的解法！

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(1)
- 只使用两个变量
*/
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n == 0) return 0;

        // 初始化状态
        int hold = -prices[0];  // 持有股票
        int notHold = 0;        // 不持有股票

        for (int i = 1; i < n; i++) {
            int newNotHold = max(notHold, hold + prices[i] - fee);
            int newHold = max(hold, notHold - prices[i]);

            notHold = newNotHold;
            hold = newHold;
        }

        return notHold;
    }
};

/*
方法二：DP（数组）(Approach 2: DP with Array)

核心思想
--------
使用二维数组存储每一天的状态。

状态定义：
- dp[i][0]：第 i 天不持有股票的最大利润
- dp[i][1]：第 i 天持有股票的最大利润

状态转移：
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee)
- dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(n)
- dp 数组，可优化到 O(1)
*/
class Solution_Array {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n == 0) return 0;

        // dp[i][0]：第 i 天不持有股票的最大利润
        // dp[i][1]：第 i 天持有股票的最大利润
        vector<vector<int>> dp(n, vector<int>(2));

        // 初始状态
        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        for (int i = 1; i < n; i++) {
            // 不持有：保持不持有 或 今天卖出（扣除手续费）
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee);

            // 持有：保持持有 或 今天买入
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        }

        return dp[n-1][0];
    }
};

/*
方法三：贪心（Approach 3: Greedy)

核心思想
--------
维护一个"最低买入价格"（考虑手续费），每次遇到更高的价格就卖出。

算法流程：
1. 初始化 buy = prices[0]（买入价格）
2. 遍历每一天：
   - 如果 prices[i] < buy，更新 buy = prices[i]（找到更低的买入价格）
   - 如果 prices[i] > buy + fee，卖出获利，更新 buy = prices[i] - fee
     （为什么是 prices[i] - fee？因为如果后面还有更高的价格，可以继续卖出）

这个贪心策略的正确性：
- 如果后面价格更高，相当于没有卖出，继续持有
- 如果后面价格更低，已经获利了结

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(1)
- 只使用常数个变量
*/
class Solution_Greedy {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n == 0) return 0;

        int buy = prices[0];  // 买入价格
        int profit = 0;       // 总利润

        for (int i = 1; i < n; i++) {
            if (prices[i] < buy) {
                // 找到更低的买入价格
                buy = prices[i];
            } else if (prices[i] > buy + fee) {
                // 卖出获利
                profit += prices[i] - buy - fee;
                // 更新买入价格（为了后续可能的更高价格）
                buy = prices[i] - fee;
            }
        }

        return profit;
    }
};

/*
手续费的处理方式 (Handling Transaction Fee)
-----------------------------------------
方式一：在卖出时扣除手续费（推荐）
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee)
- dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])

方式二：在买入时扣除手续费
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
- dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)

两种方式等价，但在卖出时扣除更直观。
*/

/*
状态机图解 (State Machine Diagram)
---------------------------------
```
状态转移图：

      买入(-price)              卖出(+price-fee)
  ┌──────────────────┐      ┌──────────────────┐
  │                  ▼      │                  ▼
未持有 ────────────> 持有 ────────────────────> 未持有
(notHold)           (hold)                    (notHold)
  ▲                                              │
  │                                              │
  └──────────────────────────────────────────────┘
              可以循环多次

状态说明：
- notHold：不持有股票，利润为累计利润
- hold：持有股票，利润为累计利润减去买入价格

状态转移：
- notHold -> hold：买入股票，notHold - price
- hold -> notHold：卖出股票，hold + price - fee
- notHold -> notHold：保持不持有
- hold -> hold：保持持有
```

状态转移方程：
notHold = max(notHold, hold + price - fee)
hold = max(hold, notHold - price)
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：prices = [1,3,2,8,4,9], fee = 2

方法一（DP）：
初始：hold=-1, notHold=0

i=1, price=3:
  newNotHold = max(0, -1+3-2) = 0
  newHold = max(-1, 0-3) = -1
  hold=-1, notHold=0

i=2, price=2:
  newNotHold = max(0, -1+2-2) = 0
  newHold = max(-1, 0-2) = -1
  hold=-1, notHold=0

i=3, price=8:
  newNotHold = max(0, -1+8-2) = 5
  newHold = max(-1, 0-8) = -1
  hold=-1, notHold=5

i=4, price=4:
  newNotHold = max(5, -1+4-2) = 5
  newHold = max(-1, 5-4) = 1
  hold=1, notHold=5

i=5, price=9:
  newNotHold = max(5, 1+9-2) = 8
  newHold = max(1, 5-9) = 1
  hold=1, notHold=8

返回 notHold = 8

状态变化表：
天数  价格  hold  notHold  说明
 0     1    -1      0      初始买入
 1     3    -1      0      不卖（手续费太高）
 2     2    -1      0      不卖
 3     8    -1      5      卖出获利 5
 4     4     1      5      再次买入
 5     9     1      8      卖出获利 8

交易过程：
- 第 0 天买入（价格 1）
- 第 3 天卖出（价格 8），利润 = 8-1-2 = 5
- 第 4 天买入（价格 4）
- 第 5 天卖出（价格 9），利润 = 9-4-2 = 3
- 总利润 = 5 + 3 = 8
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：DP（状态机）⭐ 推荐
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：代码简洁，易于理解
- 缺点：无

方法二：DP（数组）
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：状态转移清晰
- 缺点：空间未优化

方法三：贪心
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优，思路巧妙
- 缺点：不够直观，难以理解

推荐使用方法一，代码简洁且易于理解。
*/

/*
关键要点 (Key Points)
-------------------
1. 手续费的处理：在卖出时扣除（或在买入时扣除）
2. 状态定义：与 122 题相同，只是多了手续费
3. 贪心策略：维护最低买入价格，考虑手续费
4. 优化技巧：buy = prices[i] - fee（为后续更高价格做准备）
5. 与 122 题的区别：只是在状态转移时多了 fee
*/

/*
常见错误 (Common Mistakes)
------------------------
1. 手续费扣除两次：在买入和卖出时都扣除
2. 贪心策略错误：没有正确更新 buy 的值
3. 忘记考虑手续费：直接使用 122 题的代码
4. 状态转移错误：在错误的地方扣除手续费
*/

/*
与其他股票问题的对比 (Comparison with Other Stock Problems)
--------------------------------------------------------
121 题（k=1）：
- 买入：hold = max(hold, -price)
- 卖出：notHold = max(notHold, hold + price)

122 题（k=∞）：
- 买入：hold = max(hold, notHold - price)
- 卖出：notHold = max(notHold, hold + price)

309 题（k=∞，有冷冻期）：
- 买入：hold = max(hold, rest - price)  // 只能从 rest 买入
- 卖出：sold = hold + price

714 题（k=∞，有手续费）：
- 买入：hold = max(hold, notHold - price)
- 卖出：notHold = max(notHold, hold + price - fee)  // 卖出时扣除手续费
*/

/*
股票问题总结 (Stock Problems Summary)
-----------------------------------
通用框架：
dp[i][k][0]：第 i 天，最多进行 k 次交易，当前不持有股票的最大利润
dp[i][k][1]：第 i 天，最多进行 k 次交易，当前持有股票的最大利润

状态转移：
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

特殊情况：
- 121 题：k=1
- 122 题：k=∞
- 123 题：k=2
- 188 题：k=任意值
- 309 题：k=∞，有冷冻期
- 714 题：k=∞，有手续费

所有股票问题都可以用这个框架解决！
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> prices1 = {1, 3, 2, 8, 4, 9};
    int fee1 = 2;
    cout << "测试用例 1: prices=[1,3,2,8,4,9], fee=2" << endl;
    cout << "最大利润: " << solution.maxProfit(prices1, fee1) << endl;
    cout << "期望: 8" << endl << endl;

    // 测试用例 2
    vector<int> prices2 = {1, 3, 7, 5, 10, 3};
    int fee2 = 3;
    cout << "测试用例 2: prices=[1,3,7,5,10,3], fee=3" << endl;
    cout << "最大利润: " << solution.maxProfit(prices2, fee2) << endl;
    cout << "期望: 6" << endl << endl;

    // 测试用例 3
    vector<int> prices3 = {1, 2, 3, 4, 5};
    int fee3 = 1;
    cout << "测试用例 3: prices=[1,2,3,4,5], fee=1" << endl;
    cout << "最大利润: " << solution.maxProfit(prices3, fee3) << endl;
    cout << "期望: 3" << endl << endl;

    // 测试用例 4
    vector<int> prices4 = {9, 8, 7, 1, 2};
    int fee4 = 3;
    cout << "测试用例 4: prices=[9,8,7,1,2], fee=3" << endl;
    cout << "最大利润: " << solution.maxProfit(prices4, fee4) << endl;
    cout << "期望: 0" << endl << endl;

    return 0;
}
