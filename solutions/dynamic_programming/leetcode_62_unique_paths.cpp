/*
LeetCode 62. 不同路径 (Unique Paths)

题目概述 (Problem Summary)
-------------------------
一个机器人在 m x n 的网格中，从左上角出发，只能向下或向右移动，
问到达右下角共有多少条不同路径。

关键约束 (Key Constraints)
-------------------------
- 1 <= m, n <= 100
- 结果在 32 位整数范围内

示例 (Example)
-------------
输入：m = 3, n = 7
输出：28
解释：共有 28 条不同路径

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 计算从 (0,0) 到 (m-1,n-1) 的路径数量

关键观察：
1. 只能向右或向下移动
2. 到达某个格子的路径数 = 来自上方 + 来自左方
3. 动态规划可逐格累计

根据这些观察，可以得到两种典型解法：
1. 动态规划 O(mn)
2. 组合数学 C(m+n-2, m-1)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用二维 DP 表：
dp[i][j] 表示到达 (i,j) 的路径数量。

算法流程：
1. 第一行和第一列都只有 1 条路径
2. dp[i][j] = dp[i-1][j] + dp[i][j-1]
3. 返回 dp[m-1][n-1]

复杂度分析
---------
时间复杂度：O(mn)
空间复杂度：O(mn)
*/
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Combinatorics)

优化思路
--------
从 (0,0) 到 (m-1,n-1) 总共需要走：
向下 m-1 次，向右 n-1 次，总步数为 m+n-2。
路径数量等于在这些步中选择 m-1 次向下（或 n-1 次向右）的组合数。

复杂度分析
---------
时间复杂度：O(min(m,n))
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int uniquePaths(int m, int n) {
        int a = m + n - 2;
        int b = min(m - 1, n - 1);
        long long result = 1;

        // 计算 C(a, b)
        for (int i = 1; i <= b; ++i) {
            result = result * (a - b + i) / i;
        }

        return static_cast<int>(result);
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
m = 3, n = 7

DP 表：
1 1 1 1 1 1 1
1 2 3 4 5 6 7
1 3 6 10 15 21 28
结果：28
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维 DP
- 时间复杂度：O(mn)
- 空间复杂度：O(mn)
- 优点：直观易理解
- 缺点：空间较大

方法二：组合数学
- 时间复杂度：O(min(m,n))
- 空间复杂度：O(1)
- 优点：更高效
- 缺点：需要小心溢出
*/

/*
特殊情况 (Edge Cases)
--------------------
1. m=1 或 n=1：只有 1 条路径
2. m,n 较大：需注意组合数计算精度
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    int m1 = 3, n1 = 7;
    cout << "测试用例 1 - 输出: " << solution.uniquePaths(m1, n1)
         << " (期望: 28)" << endl;

    // 测试用例 2
    int m2 = 3, n2 = 2;
    cout << "测试用例 2 - 输出: " << solution.uniquePaths(m2, n2)
         << " (期望: 3)" << endl;

    return 0;
}
