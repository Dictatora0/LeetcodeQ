/*
LeetCode 121. 买卖股票的最佳时机 (Best Time to Buy and Sell Stock)

题目概述 (Problem Summary)
-------------------------
给定一个数组 prices，其中 prices[i] 表示某支股票第 i 天的价格。

你只能选择某一天买入这只股票，并选择在未来的某一个不同的日子卖出该股票。
设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0。

关键约束 (Key Constraints)
-------------------------
- 1 <= prices.length <= 10^5
- 0 <= prices[i] <= 10^4
- 只能买卖一次（先买后卖）

示例 (Example)
-------------
输入：prices = [7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5。
     注意利润不能是 7-1 = 6，因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下，没有交易完成，所以最大利润为 0。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在数组中找到两个数，使得后面的数减去前面的数最大

关键观察：
1. 这是股票买卖问题的入门题，只能交易一次
2. 必须先买入后卖出，不能反向操作
3. 可以用多种方法解决：一次遍历、DP、贪心

状态机模型：
```
    买入
  ┌─────┐
  │     │
  ▼     │
未持有 ──┘
  │
  │ 卖出
  ▼
结束
```

DP 状态定义：
- dp[i][0]：第 i 天不持有股票的最大利润
- dp[i][1]：第 i 天持有股票的最大利润（负数，表示成本）

状态转移方程：
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  // 保持不持有 或 今天卖出
- dp[i][1] = max(dp[i-1][1], -prices[i])              // 保持持有 或 今天买入

初始状态：
- dp[0][0] = 0           // 第 0 天不持有，利润为 0
- dp[0][1] = -prices[0]  // 第 0 天持有，花费 prices[0]

根据这些观察，可以得到几种典型解法：
1. 一次遍历（维护最低价格）- 时间 O(n)，空间 O(1) ⭐ 最优
2. DP（状态机）- 时间 O(n)，空间 O(n)，可优化到 O(1)
3. 贪心 - 时间 O(n)，空间 O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
方法一：一次遍历（维护最低价格）(Approach 1: One Pass with Min Price)

核心思想
--------
遍历数组，维护到目前为止的最低价格，计算当前价格与最低价格的差值，更新最大利润。

算法流程：
1. 初始化 minPrice = INT_MAX, maxProfit = 0
2. 遍历每一天的价格：
   - 如果当前价格 < minPrice，更新 minPrice
   - 否则，计算利润 = 当前价格 - minPrice，更新 maxProfit
3. 返回 maxProfit

这是最直观、最优的解法！

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(1)
- 只使用常数个变量
*/
class Solution_OnePass {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;  // 记录到目前为止的最低价格
        int maxProfit = 0;       // 记录最大利润

        for (int price : prices) {
            if (price < minPrice) {
                // 更新最低价格
                minPrice = price;
            } else {
                // 计算当前卖出的利润，更新最大利润
                maxProfit = max(maxProfit, price - minPrice);
            }
        }

        return maxProfit;
    }
};

/*
方法二：DP（状态机）(Approach 2: Dynamic Programming with State Machine)

核心思想
--------
使用动态规划，定义两个状态：持有股票和不持有股票。

状态定义：
- dp[i][0]：第 i 天不持有股票的最大利润
- dp[i][1]：第 i 天持有股票的最大利润（负数）

状态转移：
- dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
  - dp[i-1][0]：昨天就不持有，今天继续不持有
  - dp[i-1][1] + prices[i]：昨天持有，今天卖出

- dp[i][1] = max(dp[i-1][1], -prices[i])
  - dp[i-1][1]：昨天就持有，今天继续持有
  - -prices[i]：今天买入（因为只能交易一次，所以成本就是 -prices[i]）

初始状态：
- dp[0][0] = 0
- dp[0][1] = -prices[0]

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(n)
- dp 数组，可优化到 O(1)
*/
class Solution_DP {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // dp[i][0]：第 i 天不持有股票的最大利润
        // dp[i][1]：第 i 天持有股票的最大利润
        vector<vector<int>> dp(n, vector<int>(2));

        // 初始状态
        dp[0][0] = 0;           // 第 0 天不持有，利润为 0
        dp[0][1] = -prices[0];  // 第 0 天持有，花费 prices[0]

        // 状态转移
        for (int i = 1; i < n; i++) {
            // 不持有：保持不持有 或 今天卖出
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);

            // 持有：保持持有 或 今天买入
            dp[i][1] = max(dp[i-1][1], -prices[i]);
        }

        // 最后一天不持有股票的利润最大
        return dp[n-1][0];
    }
};

/*
方法三：DP（空间优化）(Approach 3: DP with Space Optimization)

核心思想
--------
观察到 dp[i] 只依赖于 dp[i-1]，可以用两个变量代替数组。

这是 DP 的最优实现！

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(1)
- 只使用两个变量
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // 状态变量
        int hold = -prices[0];  // 持有股票的最大利润
        int notHold = 0;        // 不持有股票的最大利润

        for (int i = 1; i < n; i++) {
            // 更新状态（注意顺序）
            int newNotHold = max(notHold, hold + prices[i]);
            int newHold = max(hold, -prices[i]);

            notHold = newNotHold;
            hold = newHold;
        }

        return notHold;
    }
};

/*
股票问题通用模板 (General Stock Trading Template)
----------------------------------------------
股票买卖问题的通用 DP 框架：

状态定义：
dp[i][k][0]：第 i 天，最多进行 k 次交易，当前不持有股票的最大利润
dp[i][k][1]：第 i 天，最多进行 k 次交易，当前持有股票的最大利润

状态转移：
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

对于本题（k = 1）：
dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i])
            = max(dp[i-1][1][1], -prices[i])  // 因为 dp[i-1][0][0] = 0

简化为：
dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][1] = max(dp[i-1][1], -prices[i])
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：prices = [7,1,5,3,6,4]

方法一（一次遍历）：
i=0: price=7, minPrice=7, maxProfit=0
i=1: price=1, minPrice=1, maxProfit=0
i=2: price=5, minPrice=1, maxProfit=4 (5-1)
i=3: price=3, minPrice=1, maxProfit=4
i=4: price=6, minPrice=1, maxProfit=5 (6-1)
i=5: price=4, minPrice=1, maxProfit=5
返回 5

方法二（DP）：
i=0: dp[0][0]=0, dp[0][1]=-7
i=1: dp[1][0]=0, dp[1][1]=-1
i=2: dp[2][0]=4, dp[2][1]=-1
i=3: dp[3][0]=4, dp[3][1]=-1
i=4: dp[4][0]=5, dp[4][1]=-1
i=5: dp[5][0]=5, dp[5][1]=-1
返回 5

DP 数组变化：
天数  价格  不持有  持有
 0     7      0     -7
 1     1      0     -1
 2     5      4     -1
 3     3      4     -1
 4     6      5     -1
 5     4      5     -1
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：一次遍历 ⭐ 推荐
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：代码简洁，直观易懂
- 缺点：无

方法二：DP（数组）
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：状态转移清晰，易于扩展
- 缺点：空间未优化

方法三：DP（空间优化）
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优，适合理解 DP
- 缺点：相比方法一稍复杂

推荐使用方法一，但理解方法二和方法三对学习股票问题的 DP 框架很重要。
*/

/*
关键要点 (Key Points)
-------------------
1. 状态定义：持有 vs 不持有
2. 只能交易一次：买入时成本就是 -prices[i]
3. 必须先买后卖：不能在第 0 天卖出
4. 空间优化：滚动变量代替数组
5. 贪心思想：在最低点买入，在最高点卖出
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "测试用例 1: [7,1,5,3,6,4]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices1) << endl;
    cout << "期望: 5" << endl << endl;

    // 测试用例 2
    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << "测试用例 2: [7,6,4,3,1]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices2) << endl;
    cout << "期望: 0" << endl << endl;

    // 测试用例 3
    vector<int> prices3 = {1, 2, 3, 4, 5};
    cout << "测试用例 3: [1,2,3,4,5]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices3) << endl;
    cout << "期望: 4" << endl << endl;

    // 测试用例 4
    vector<int> prices4 = {2, 4, 1};
    cout << "测试用例 4: [2,4,1]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices4) << endl;
    cout << "期望: 2" << endl << endl;

    return 0;
}
