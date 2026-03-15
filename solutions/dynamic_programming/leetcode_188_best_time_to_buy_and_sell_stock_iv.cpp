/*
LeetCode 188. 买卖股票的最佳时机 IV (Best Time to Buy and Sell Stock IV)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 prices，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

关键约束 (Key Constraints)
-------------------------
- 1 <= k <= 100
- 1 <= prices.length <= 1000
- 0 <= prices[i] <= 1000
- 最多完成 k 笔交易

示例 (Example)
-------------
输入：k = 2, prices = [2,4,1]
输出：2
解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，利润 = 4-2 = 2。

输入：k = 2, prices = [3,2,6,5,0,3]
输出：7
解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出，利润 = 6-2 = 4。
     随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出，利润 = 3-0 = 3。
     总利润 = 4 + 3 = 7。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 最多完成 k 笔交易，求最大利润
- 这是股票买卖问题的通用版本

关键观察：
1. 这是 121、122、123 题的通用版本
2. 当 k >= n/2 时，等价于 122 题（无限次交易）
3. 需要追踪当前是第几次交易

状态机模型：
```
        买入1         卖出1         买入2         卖出2              买入k         卖出k
未持有 ────> 持有1 ────> 未持有 ────> 持有2 ────> 未持有 ... ────> 持有k ────> 未持有
(初始)                  (完成1次)              (完成2次)                      (完成k次)
```

DP 状态定义：
- buy[i]：第 i 次买入后的最大利润
- sell[i]：第 i 次卖出后的最大利润

状态转移方程：
- buy[i] = max(buy[i], sell[i-1] - prices[j])   // 第 i 次买入
- sell[i] = max(sell[i], buy[i] + prices[j])    // 第 i 次卖出

初始状态：
- buy[i] = -prices[0]  // 所有买入状态初始化为第一天买入
- sell[i] = 0          // 所有卖出状态初始化为 0

优化：
当 k >= n/2 时，可以进行无限次交易，退化为 122 题。

根据这些观察，可以得到几种典型解法：
1. DP（2k 个状态）- 时间 O(nk)，空间 O(k) ⭐ 推荐
2. DP（3 维数组）- 时间 O(nk)，空间 O(nk)
3. 贪心（k >= n/2 时）- 时间 O(n)，空间 O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
方法一：DP（2k 个状态）(Approach 1: DP with 2k States)

核心思想
--------
使用两个数组：
- buy[i]：第 i 次买入后的最大利润
- sell[i]：第 i 次卖出后的最大利润

对于每一天，更新所有的买入和卖出状态。

特殊优化：
当 k >= n/2 时，可以进行无限次交易，直接使用贪心算法。

这是最优解法！

复杂度分析
---------
时间复杂度：O(nk) 或 O(n)
- 一般情况：O(nk)
- k >= n/2 时：O(n)

空间复杂度：O(k)
- buy 和 sell 数组
*/
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        // 优化：当 k >= n/2 时，等价于无限次交易
        if (k >= n / 2) {
            return maxProfitUnlimited(prices);
        }

        // buy[i]：第 i 次买入后的最大利润
        // sell[i]：第 i 次卖出后的最大利润
        vector<int> buy(k + 1, INT_MIN);
        vector<int> sell(k + 1, 0);

        for (int price : prices) {
            // 从后往前更新，避免使用临时变量
            for (int i = k; i >= 1; i--) {
                sell[i] = max(sell[i], buy[i] + price);
                buy[i] = max(buy[i], sell[i-1] - price);
            }
        }

        return sell[k];
    }

private:
    // 无限次交易的贪心算法（122 题）
    int maxProfitUnlimited(vector<int>& prices) {
        int maxProfit = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i-1]) {
                maxProfit += prices[i] - prices[i-1];
            }
        }
        return maxProfit;
    }
};

/*
方法二：DP（3 维数组）(Approach 2: DP with 3D Array)

核心思想
--------
使用三维数组 dp[i][j][s]：
- i：第 i 天
- j：已完成的交易次数（0 到 k）
- s：是否持有股票（0 不持有，1 持有）

状态定义：
dp[i][j][0]：第 i 天，已完成 j 次交易，不持有股票的最大利润
dp[i][j][1]：第 i 天，已完成 j 次交易，持有股票的最大利润

状态转移：
dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j-1][1] + prices[i])
dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j][0] - prices[i])

注意：一次完整的交易是"买入 + 卖出"，这里我们在卖出时增加交易次数。

复杂度分析
---------
时间复杂度：O(nk)
- 遍历 n 天，每天更新 k 个状态

空间复杂度：O(nk)
- dp 数组，可优化到 O(k)
*/
class Solution_3D {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        // 优化：当 k >= n/2 时，等价于无限次交易
        if (k >= n / 2) {
            int maxProfit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i-1]) {
                    maxProfit += prices[i] - prices[i-1];
                }
            }
            return maxProfit;
        }

        // dp[i][j][0/1]：第 i 天，完成 j 次交易，不持有/持有股票的最大利润
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));

        // 初始状态
        for (int j = 0; j <= k; j++) {
            dp[0][j][0] = 0;
            dp[0][j][1] = -prices[0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                // 不持有：保持不持有 或 今天卖出
                dp[i][j][0] = dp[i-1][j][0];
                if (j > 0) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i-1][j-1][1] + prices[i]);
                }

                // 持有：保持持有 或 今天买入
                dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j][0] - prices[i]);
            }
        }

        // 返回最多完成 k 次交易，不持有股票的最大利润
        int maxProfit = 0;
        for (int j = 0; j <= k; j++) {
            maxProfit = max(maxProfit, dp[n-1][j][0]);
        }
        return maxProfit;
    }
};

/*
方法三：DP（空间优化）(Approach 3: DP with Space Optimization)

核心思想
--------
观察到 dp[i] 只依赖于 dp[i-1]，可以用滚动数组优化空间。

复杂度分析
---------
时间复杂度：O(nk)
- 遍历 n 天，每天更新 k 个状态

空间复杂度：O(k)
- 只使用两个一维数组
*/
class Solution_Optimized {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        // 优化：当 k >= n/2 时，等价于无限次交易
        if (k >= n / 2) {
            int maxProfit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i-1]) {
                    maxProfit += prices[i] - prices[i-1];
                }
            }
            return maxProfit;
        }

        // buy[j]：完成 j 次交易，持有股票的最大利润
        // sell[j]：完成 j 次交易，不持有股票的最大利润
        vector<int> buy(k + 1, INT_MIN);
        vector<int> sell(k + 1, 0);

        for (int price : prices) {
            for (int j = k; j >= 1; j--) {
                sell[j] = max(sell[j], buy[j] + price);
                buy[j] = max(buy[j], sell[j-1] - price);
            }
        }

        return sell[k];
    }
};

/*
股票问题通用模板 (General Stock Trading Template)
----------------------------------------------
这是所有股票买卖问题的通用框架！

状态定义：
dp[i][k][0]：第 i 天，最多进行 k 次交易，当前不持有股票的最大利润
dp[i][k][1]：第 i 天，最多进行 k 次交易，当前持有股票的最大利润

状态转移：
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

初始状态：
dp[0][k][0] = 0
dp[0][k][1] = -prices[0]

特殊情况：
- k = 1：LeetCode 121
- k = +∞：LeetCode 122
- k = 2：LeetCode 123
- k = 任意值：LeetCode 188（本题）
- 有冷冻期：LeetCode 309
- 有手续费：LeetCode 714
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：k = 2, prices = [3,2,6,5,0,3]

初始化：
buy = [INT_MIN, INT_MIN, INT_MIN]
sell = [0, 0, 0]

price = 3:
  j=2: sell[2] = max(0, INT_MIN+3) = 0
       buy[2] = max(INT_MIN, 0-3) = -3
  j=1: sell[1] = max(0, INT_MIN+3) = 0
       buy[1] = max(INT_MIN, 0-3) = -3

price = 2:
  j=2: sell[2] = max(0, -3+2) = 0
       buy[2] = max(-3, 0-2) = -2
  j=1: sell[1] = max(0, -3+2) = 0
       buy[1] = max(-3, 0-2) = -2

price = 6:
  j=2: sell[2] = max(0, -2+6) = 4
       buy[2] = max(-2, 4-6) = -2
  j=1: sell[1] = max(0, -2+6) = 4
       buy[1] = max(-2, 0-6) = -2

price = 5:
  j=2: sell[2] = max(4, -2+5) = 4
       buy[2] = max(-2, 4-5) = -1
  j=1: sell[1] = max(4, -2+5) = 4
       buy[1] = max(-2, 0-5) = -2

price = 0:
  j=2: sell[2] = max(4, -1+0) = 4
       buy[2] = max(-1, 4-0) = 4
  j=1: sell[1] = max(4, -2+0) = 4
       buy[1] = max(-2, 0-0) = 0

price = 3:
  j=2: sell[2] = max(4, 4+3) = 7
       buy[2] = max(4, 4-3) = 4
  j=1: sell[1] = max(4, 0+3) = 4
       buy[1] = max(0, 0-3) = 0

返回 sell[2] = 7

状态变化表：
价格  buy[1]  sell[1]  buy[2]  sell[2]
 3     -3       0       -3       0
 2     -2       0       -2       0
 6     -2       4       -2       4
 5     -2       4       -1       4
 0      0       4        4       4
 3      0       4        4       7
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：2k 个状态 ⭐ 推荐
- 时间复杂度：O(nk) 或 O(n)
- 空间复杂度：O(k)
- 优点：代码简洁，空间最优，有优化
- 缺点：需要理解状态含义

方法二：3 维数组
- 时间复杂度：O(nk)
- 空间复杂度：O(nk)
- 优点：状态转移清晰，通用性强
- 缺点：空间未优化

方法三：空间优化
- 时间复杂度：O(nk)
- 空间复杂度：O(k)
- 优点：空间最优
- 缺点：与方法一类似

推荐使用方法一，代码简洁且效率最高。
*/

/*
关键要点 (Key Points)
-------------------
1. 通用模板：适用于所有股票买卖问题
2. 状态定义：buy[i] 和 sell[i] 表示第 i 次交易的状态
3. 优化：k >= n/2 时退化为无限次交易
4. 更新顺序：从后往前更新，避免覆盖
5. 初始化：buy 初始化为 INT_MIN，sell 初始化为 0
*/

/*
常见错误 (Common Mistakes)
------------------------
1. 忘记优化 k >= n/2 的情况：会导致超时或超内存
2. 状态更新顺序错误：应该从后往前更新
3. 初始化错误：buy 应该初始化为 INT_MIN
4. 交易次数定义不清：买入+卖出算一次完整交易
*/

int main() {
    Solution solution;

    // 测试用例 1
    int k1 = 2;
    vector<int> prices1 = {2, 4, 1};
    cout << "测试用例 1: k=2, prices=[2,4,1]" << endl;
    cout << "最大利润: " << solution.maxProfit(k1, prices1) << endl;
    cout << "期望: 2" << endl << endl;

    // 测试用例 2
    int k2 = 2;
    vector<int> prices2 = {3, 2, 6, 5, 0, 3};
    cout << "测试用例 2: k=2, prices=[3,2,6,5,0,3]" << endl;
    cout << "最大利润: " << solution.maxProfit(k2, prices2) << endl;
    cout << "期望: 7" << endl << endl;

    // 测试用例 3
    int k3 = 2;
    vector<int> prices3 = {1, 2, 3, 4, 5};
    cout << "测试用例 3: k=2, prices=[1,2,3,4,5]" << endl;
    cout << "最大利润: " << solution.maxProfit(k3, prices3) << endl;
    cout << "期望: 4" << endl << endl;

    // 测试用例 4：k 很大的情况
    int k4 = 100;
    vector<int> prices4 = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    cout << "测试用例 4: k=100, prices=[1,2,4,2,5,7,2,4,9,0]" << endl;
    cout << "最大利润: " << solution.maxProfit(k4, prices4) << endl;
    cout << "期望: 15" << endl << endl;

    return 0;
}
