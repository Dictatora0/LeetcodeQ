/*
LeetCode 63. 不同路径 II (Unique Paths II)

题目概述 (Problem Summary)
-------------------------
在一个 m x n 的网格中，机器人从左上角出发，只能向下或向右移动。
网格中有障碍物（1 表示障碍），机器人不能经过障碍。
问到达右下角的不同路径数量。

关键约束 (Key Constraints)
-------------------------
- 1 <= m, n <= 100
- obstacleGrid[i][j] 为 0 或 1
- 结果在 32 位整数范围内

示例 (Example)
-------------
输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
输出：2
解释：有 2 条不同路径避开障碍

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在带障碍的网格中计数路径数

关键观察：
1. 与 LeetCode 62 类似，但遇到障碍时路径数为 0
2. dp[i][j] 表示到达 (i,j) 的路径数
3. 若当前格子是障碍，dp[i][j]=0

根据这些观察，可以得到两种典型解法：
1. 二维动态规划
2. 一维滚动数组优化空间
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用二维 DP，遇到障碍直接置 0。
非障碍格子的路径数 = 上方 + 左方。

算法流程：
1. 初始化 dp[0][0]，若起点是障碍则返回 0
2. 填充第一行与第一列，遇到障碍后全为 0
3. 逐行逐列更新 dp
4. 返回 dp[m-1][n-1]

复杂度分析
---------
时间复杂度：O(mn)
空间复杂度：O(mn)
*/
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = static_cast<int>(obstacleGrid.size());
        int n = static_cast<int>(obstacleGrid[0].size());
        vector<vector<int>> dp(m, vector<int>(n, 0));

        if (obstacleGrid[0][0] == 1) return 0;
        dp[0][0] = 1;

        for (int i = 1; i < m; ++i) {
            dp[i][0] = (obstacleGrid[i][0] == 0) ? dp[i - 1][0] : 0;
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = (obstacleGrid[0][j] == 0) ? dp[0][j - 1] : 0;
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Rolling Array)

优化思路
--------
用一维数组 dp[j] 表示当前行的路径数，
逐行滚动更新，节省空间。

复杂度分析
---------
时间复杂度：O(mn)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = static_cast<int>(obstacleGrid.size());
        int n = static_cast<int>(obstacleGrid[0].size());
        vector<int> dp(n, 0);

        dp[0] = (obstacleGrid[0][0] == 0) ? 1 : 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                } else if (j > 0) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[n - 1];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
obstacleGrid =
0 0 0
0 1 0
0 0 0

dp 逐行变化：
第一行：1 1 1
第二行：1 0 1
第三行：1 1 2
结果为 2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维 DP
- 时间复杂度：O(mn)
- 空间复杂度：O(mn)
- 优点：直观清晰
- 缺点：空间较大

方法二：一维滚动数组
- 时间复杂度：O(mn)
- 空间复杂度：O(n)
- 优点：节省空间
- 缺点：理解稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 起点或终点是障碍：返回 0
2. 只有一行或一列：需要考虑障碍阻断
3. 全部无障碍：退化为 LeetCode 62
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<vector<int>> grid1 = {{0,0,0},{0,1,0},{0,0,0}};
    cout << "测试用例 1 - 输出: " << solution.uniquePathsWithObstacles(grid1)
         << " (期望: 2)" << endl;

    // 测试用例 2
    vector<vector<int>> grid2 = {{0,1},{0,0}};
    cout << "测试用例 2 - 输出: " << solution.uniquePathsWithObstacles(grid2)
         << " (期望: 1)" << endl;

    return 0;
}
