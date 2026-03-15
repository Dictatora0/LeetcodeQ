/*
LeetCode 123. 买卖股票的最佳时机 III (Best Time to Buy and Sell Stock III)

题目概述 (Problem Summary)
-------------------------
给定一个数组 prices，其中 prices[i] 表示某支股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成两笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

关键约束 (Key Constraints)
-------------------------
- 1 <= prices.length <= 10^5
- 0 <= prices[i] <= 10^5
- 最多完成两笔交易

示例 (Example)
-------------
输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，利润 = 3-0 = 3。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天（股票价格 = 4）的时候卖出，利润 = 4-1 = 3。
     总利润 = 3 + 3 = 6。

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 5）的时候卖出，利润 = 5-1 = 4。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下，没有交易完成，所以最大利润为 0。

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 最多完成两笔交易，求最大利润

关键观察：
1. 相比 122 题，这里限制了交易次数为 2
2. 需要追踪当前是第几次交易
3. 可以用状态机模型清晰地表示

状态机模型：
```
        买入1         卖出1         买入2         卖出2
未持有 ────> 持有1 ────> 未持有 ────> 持有2 ────> 未持有
(初始)                  (完成1次)              (完成2次)
```

DP 状态定义（方法一）：
定义 4 个状态变量：
- buy1：第一次买入后的最大利润（负数）
- sell1：第一次卖出后的最大利润
- buy2：第二次买入后的最大利润
- sell2：第二次卖出后的最大利润

状态转移方程：
- buy1 = max(buy1, -prices[i])           // 第一次买入
- sell1 = max(sell1, buy1 + prices[i])   // 第一次卖出
- buy2 = max(buy2, sell1 - prices[i])    // 第二次买入
- sell2 = max(sell2, buy2 + prices[i])   // 第二次卖出

初始状态：
- buy1 = -prices[0]
- sell1 = 0
- buy2 = -prices[0]
- sell2 = 0

DP 状态定义（方法二）：
- dp[i][k][0]：第 i 天，完成了 k 次交易，当前不持有股票的最大利润
- dp[i][k][1]：第 i 天，完成了 k 次交易，当前持有股票的最大利润

根据这些观察，可以得到几种典型解法：
1. DP（4 个状态变量）- 时间 O(n)，空间 O(1) ⭐ 推荐
2. DP（3 维数组）- 时间 O(n)，空间 O(n)
3. DP（前后两次遍历）- 时间 O(n)，空间 O(n)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
方法一：DP（4 个状态变量）(Approach 1: DP with 4 State Variables)

核心思想
--------
使用 4 个变量分别表示：
- buy1：第一次买入后的最大利润
- sell1：第一次卖出后的最大利润
- buy2：第二次买入后的最大利润
- sell2：第二次卖出后的最大利润

状态转移：
每天更新这 4 个状态，最终 sell2 就是答案。

这是最优解法！

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组

空间复杂度：O(1)
- 只使用 4 个变量
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // 初始化 4 个状态
        int buy1 = -prices[0];   // 第一次买入
        int sell1 = 0;           // 第一次卖出
        int buy2 = -prices[0];   // 第二次买入
        int sell2 = 0;           // 第二次卖出

        for (int i = 1; i < n; i++) {
            // 状态转移（注意顺序：从后往前更新）
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, buy1 + prices[i]);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, buy2 + prices[i]);
        }

        // 最多完成两笔交易的最大利润
        return sell2;
    }
};

/*
方法二：DP（3 维数组）(Approach 2: DP with 3D Array)

核心思想
--------
使用三维数组 dp[i][k][s]：
- i：第 i 天
- k：已完成的交易次数（0, 1, 2）
- s：是否持有股票（0 不持有，1 持有）

状态定义：
dp[i][k][0]：第 i 天，已完成 k 次交易，不持有股票的最大利润
dp[i][k][1]：第 i 天，已完成 k 次交易，持有股票的最大利润

状态转移：
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

注意：一次完整的交易是"买入 + 卖出"，这里我们在卖出时增加交易次数。

复杂度分析
---------
时间复杂度：O(n)
- 遍历一次数组，每次更新常数个状态

空间复杂度：O(n)
- dp 数组，可优化到 O(1)
*/
class Solution_3D {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // dp[i][k][0/1]：第 i 天，完成 k 次交易，不持有/持有股票的最大利润
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(3, vector<int>(2, 0)));

        // 初始状态
        dp[0][0][0] = 0;
        dp[0][0][1] = -prices[0];
        dp[0][1][0] = 0;
        dp[0][1][1] = INT_MIN / 2;  // 不可能的状态
        dp[0][2][0] = 0;
        dp[0][2][1] = INT_MIN / 2;  // 不可能的状态

        for (int i = 1; i < n; i++) {
            for (int k = 0; k <= 2; k++) {
                // 不持有：保持不持有 或 今天卖出
                dp[i][k][0] = dp[i-1][k][0];
                if (k > 0) {
                    dp[i][k][0] = max(dp[i][k][0], dp[i-1][k-1][1] + prices[i]);
                }

                // 持有：保持持有 或 今天买入
                dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k][0] - prices[i]);
            }
        }

        // 返回最多完成 2 次交易，不持有股票的最大利润
        return max({dp[n-1][0][0], dp[n-1][1][0], dp[n-1][2][0]});
    }
};

/*
方法三：DP（前后两次遍历）(Approach 3: DP with Two Passes)

核心思想
--------
将问题分解为两个子问题：
1. 第一次遍历：计算 [0, i] 区间内一次交易的最大利润
2. 第二次遍历：计算 [i, n-1] 区间内一次交易的最大利润
3. 枚举分割点，找到最大值

算法流程：
1. left[i]：表示 [0, i] 区间内一次交易的最大利润
2. right[i]：表示 [i, n-1] 区间内一次交易的最大利润
3. 答案：max(left[i] + right[i])

复杂度分析
---------
时间复杂度：O(n)
- 三次遍历

空间复杂度：O(n)
- left 和 right 数组
*/
class Solution_TwoPass {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // left[i]：[0, i] 区间内一次交易的最大利润
        vector<int> left(n, 0);
        int minPrice = prices[0];
        for (int i = 1; i < n; i++) {
            left[i] = max(left[i-1], prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }

        // right[i]：[i, n-1] 区间内一次交易的最大利润
        vector<int> right(n, 0);
        int maxPrice = prices[n-1];
        for (int i = n-2; i >= 0; i--) {
            right[i] = max(right[i+1], maxPrice - prices[i]);
            maxPrice = max(maxPrice, prices[i]);
        }

        // 枚举分割点，找到最大利润
        int maxProfit = 0;
        for (int i = 0; i < n; i++) {
            maxProfit = max(maxProfit, left[i] + right[i]);
        }

        return maxProfit;
    }
};

/*
状态机图解 (State Machine Diagram)
---------------------------------
```
初始状态：未持有，利润 = 0

第一次交易：
  未持有 ──买入──> 持有1 ──卖出──> 未持有
  (0)      (-p)    (buy1)  (+p)    (sell1)

第二次交易：
  未持有 ──买入──> 持有2 ──卖出──> 未持有
 (sell1)   (-p)    (buy2)  (+p)    (sell2)

最终答案：sell2
```

状态转移：
buy1  = max(buy1, -prices[i])
sell1 = max(sell1, buy1 + prices[i])
buy2  = max(buy2, sell1 - prices[i])
sell2 = max(sell2, buy2 + prices[i])
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：prices = [3,3,5,0,0,3,1,4]

方法一（4 个状态变量）：
初始：buy1=-3, sell1=0, buy2=-3, sell2=0

i=1, price=3:
  buy1 = max(-3, -3) = -3
  sell1 = max(0, -3+3) = 0
  buy2 = max(-3, 0-3) = -3
  sell2 = max(0, -3+3) = 0

i=2, price=5:
  buy1 = max(-3, -5) = -3
  sell1 = max(0, -3+5) = 2
  buy2 = max(-3, 2-5) = -3
  sell2 = max(0, -3+5) = 2

i=3, price=0:
  buy1 = max(-3, 0) = 0
  sell1 = max(2, 0+0) = 2
  buy2 = max(-3, 2-0) = 2
  sell2 = max(2, 2+0) = 2

i=4, price=0:
  buy1 = max(0, 0) = 0
  sell1 = max(2, 0+0) = 2
  buy2 = max(2, 2-0) = 2
  sell2 = max(2, 2+0) = 2

i=5, price=3:
  buy1 = max(0, -3) = 0
  sell1 = max(2, 0+3) = 3
  buy2 = max(2, 3-3) = 2
  sell2 = max(2, 2+3) = 5

i=6, price=1:
  buy1 = max(0, -1) = 0
  sell1 = max(3, 0+1) = 3
  buy2 = max(2, 3-1) = 2
  sell2 = max(5, 2+1) = 5

i=7, price=4:
  buy1 = max(0, -4) = 0
  sell1 = max(3, 0+4) = 4
  buy2 = max(2, 4-4) = 2
  sell2 = max(5, 2+4) = 6

返回 sell2 = 6

状态变化表：
天数  价格  buy1  sell1  buy2  sell2
 0     3    -3     0     -3     0
 1     3    -3     0     -3     0
 2     5    -3     2     -3     2
 3     0     0     2      2     2
 4     0     0     2      2     2
 5     3     0     3      2     5
 6     1     0     3      2     5
 7     4     0     4      2     6
*/

/*
方法对比 (Approach Comparison)
----------------------------
方法一：4 个状态变量 ⭐ 推荐
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：代码简洁，空间最优
- 缺点：需要理解状态含义

方法二：3 维数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：状态转移清晰，通用性强
- 缺点：空间未优化

方法三：前后两次遍历
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：思路直观，易于理解
- 缺点：需要额外数组

推荐使用方法一，代码简洁且效率最高。
*/

/*
关键要点 (Key Points)
-------------------
1. 状态机模型：4 个状态表示两次交易的过程
2. 状态转移：从前往后依次更新
3. 初始化：buy1 和 buy2 都初始化为 -prices[0]
4. 最终答案：sell2（完成两次交易后的最大利润）
5. 可以只完成一次交易：sell1 会自动传递到 sell2
*/

/*
常见错误 (Common Mistakes)
------------------------
1. 状态更新顺序错误：应该从 buy1 到 sell2 依次更新
2. 初始化错误：buy2 应该初始化为 -prices[0]，而不是 0
3. 误以为必须完成两次交易：实际上可以只完成一次
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> prices1 = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "测试用例 1: [3,3,5,0,0,3,1,4]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices1) << endl;
    cout << "期望: 6" << endl << endl;

    // 测试用例 2
    vector<int> prices2 = {1, 2, 3, 4, 5};
    cout << "测试用例 2: [1,2,3,4,5]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices2) << endl;
    cout << "期望: 4" << endl << endl;

    // 测试用例 3
    vector<int> prices3 = {7, 6, 4, 3, 1};
    cout << "测试用例 3: [7,6,4,3,1]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices3) << endl;
    cout << "期望: 0" << endl << endl;

    // 测试用例 4
    vector<int> prices4 = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    cout << "测试用例 4: [1,2,4,2,5,7,2,4,9,0]" << endl;
    cout << "最大利润: " << solution.maxProfit(prices4) << endl;
    cout << "期望: 13" << endl << endl;

    return 0;
}
