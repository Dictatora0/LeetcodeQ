/*
LeetCode 322. 零钱兑换 (Coin Change)

题目概述 (Problem Summary)
-------------------------
给定不同面额的硬币 coins 和一个总金额 amount。
计算凑成总金额所需的最少硬币个数。
如果无法凑成，返回 -1。

关键约束 (Key Constraints)
-------------------------
- 1 <= coins.length <= 12
- 1 <= coins[i] <= 2^31 - 1
- 0 <= amount <= 10^4
- 每种硬币可以无限使用

示例 (Example)
-------------
输入：coins = [1,2,5], amount = 11
输出：3
解释：11 = 5 + 5 + 1

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 完全背包问题：每个硬币可以无限次使用，求最少数量

关键观察：
1. dp[i] 表示凑成金额 i 所需的最少硬币数
2. 状态转移：dp[i] = min(dp[i], dp[i - coin] + 1)
3. 初始化：dp[0] = 0，其他为无穷大
4. 遍历顺序：外层金额，内层硬币

根据这些观察，可以得到两种典型解法：
1. 一维 DP（完全背包）
2. 二维 DP（更直观但空间更大）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - 1D DP)

核心思想
--------
使用一维 DP 数组，对于每个金额，尝试所有硬币，
选择使用硬币数最少的方案。

状态定义：
dp[i] = 凑成金额 i 所需的最少硬币数

状态转移方程：
dp[i] = min(dp[i], dp[i - coins[j]] + 1)
其中 i >= coins[j] 且 dp[i - coins[j]] 可达

算法流程：
1. 初始化 dp 数组为无穷大，dp[0] = 0
2. 遍历每个金额 i (1 到 amount)
3. 对每个金额，尝试所有硬币
4. 如果 i >= coin 且 dp[i - coin] 可达，更新 dp[i]

复杂度分析
---------
时间复杂度：O(amount * n)，n 为硬币种类数
空间复杂度：O(amount)
*/
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, 1e9);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                // 注意：不要把"某个硬币是否合法"写到循环条件里，否则会提前结束循环
                if (i - coins[j] >= 0 && dp[i - coins[j]] != 1e9) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }

        // 判断能不能凑出来，要看 dp[amount]，不是看中间有没有成功过
        return dp[amount] == 1e9 ? -1 : dp[amount];
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Cleaner Code)

优化思路
--------
代码结构更清晰，使用 INT_MAX 表示不可达状态。

复杂度分析
---------
时间复杂度：O(amount * n)
空间复杂度：O(amount)
*/
class Solution_Optimized {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i >= coin && dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
coins = [1,2,5], amount = 11

初始：dp = [0, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞]

i=1: 用硬币1 -> dp[1]=1
i=2: 用硬币1 -> dp[2]=2, 用硬币2 -> dp[2]=1
i=3: 用硬币1 -> dp[3]=2, 用硬币2 -> dp[3]=2
i=4: 用硬币2 -> dp[4]=2
i=5: 用硬币5 -> dp[5]=1
i=6: 用硬币1+5 -> dp[6]=2
i=7: 用硬币2+5 -> dp[7]=2
i=8: 用硬币1+2+5 -> dp[8]=3
i=9: 用硬币2+2+5 -> dp[9]=3
i=10: 用硬币5+5 -> dp[10]=2
i=11: 用硬币1+5+5 -> dp[11]=3

结果：3
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：1D DP（原始版本）
- 时间复杂度：O(amount * n)
- 空间复杂度：O(amount)
- 优点：逻辑清晰，注释详细
- 缺点：代码稍冗长

方法二：1D DP（优化版本）
- 时间复杂度：O(amount * n)
- 空间复杂度：O(amount)
- 优点：代码简洁
- 缺点：需要理解完全背包模型
*/

/*
特殊情况 (Edge Cases)
--------------------
1. amount = 0：返回 0
2. 无法凑成：返回 -1
3. 只有一种硬币：amount % coin == 0 ? amount/coin : -1
4. 硬币面额大于 amount：无法使用该硬币
*/

/*
易错点 (Common Mistakes)
-----------------------
1. 初始化错误：dp[0] 必须为 0，其他为无穷大
2. 判断条件：要检查 dp[i - coin] 是否可达
3. 循环顺序：外层金额，内层硬币（完全背包）
4. 返回值：要判断 dp[amount] 是否为无穷大
*/

int main() {
    Solution solution;

    // 测试用例 1：基本情况
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    cout << "测试用例 1 - 输出: " << solution.coinChange(coins1, amount1)
         << " (期望: 3)" << endl;

    // 测试用例 2：无法凑成
    vector<int> coins2 = {2};
    int amount2 = 3;
    cout << "测试用例 2 - 输出: " << solution.coinChange(coins2, amount2)
         << " (期望: -1)" << endl;

    // 测试用例 3：金额为 0
    vector<int> coins3 = {1};
    int amount3 = 0;
    cout << "测试用例 3 - 输出: " << solution.coinChange(coins3, amount3)
         << " (期望: 0)" << endl;

    // 测试用例 4：只需一个硬币
    vector<int> coins4 = {1, 2, 5};
    int amount4 = 5;
    cout << "测试用例 4 - 输出: " << solution.coinChange(coins4, amount4)
         << " (期望: 1)" << endl;

    return 0;
}
