/*
LeetCode 64. 最小路径和 (Minimum Path Sum)

题目概述 (Problem Summary)
-------------------------
给定一个 m x n 的网格 grid，每个格子包含一个非负整数。
从左上角出发，只能向右或向下移动，求到达右下角的最小路径和。

关键约束 (Key Constraints)
-------------------------
- 1 <= m, n <= 200
- 0 <= grid[i][j] <= 100

示例 (Example)
-------------
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：路径 1→3→1→1→1 的和最小，结果为 7

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在网格中找一条从左上到右下的最小代价路径

关键观察：
1. 到达 (i,j) 的最小代价只可能来自上方或左方
2. dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
3. 可以使用滚动数组节省空间

根据这些观察，可以得到两种典型解法：
1. 二维 DP
2. 一维滚动数组
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用二维 dp 表记录到达每个格子的最小路径和。

算法流程：
1. dp[0][0] = grid[0][0]
2. 初始化第一行与第一列
3. 逐行更新 dp[i][j]
4. 返回 dp[m-1][n-1]

复杂度分析
---------
时间复杂度：O(mn)
空间复杂度：O(mn)
*/
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        return dp[m - 1][n - 1];
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Rolling Array)

优化思路
--------
用一维数组 dp[j] 表示当前行的最小路径和。
逐行更新时，dp[j] 表示来自上方，dp[j-1] 表示来自左方。

复杂度分析
---------
时间复杂度：O(mn)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        vector<int> dp(n, 0);

        dp[0] = grid[0][0];
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        for (int i = 1; i < m; ++i) {
            dp[0] += grid[i][0];
            for (int j = 1; j < n; ++j) {
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }

        return dp[n - 1];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
grid =
1 3 1
1 5 1
4 2 1

dp 表：
1 4 5
2 7 6
6 8 7
最小路径和为 7
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维 DP
- 时间复杂度：O(mn)
- 空间复杂度：O(mn)
- 优点：直观易懂
- 缺点：占用空间较大

方法二：滚动数组
- 时间复杂度：O(mn)
- 空间复杂度：O(n)
- 优点：节省空间
- 缺点：需要注意覆盖顺序
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一行或一列：直接累加
2. 全为 0：结果为 0
3. 大网格：使用滚动数组更节省空间
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<vector<int>> grid1 = {{1,3,1},{1,5,1},{4,2,1}};
    cout << "测试用例 1 - 输出: " << solution.minPathSum(grid1)
         << " (期望: 7)" << endl;

    // 测试用例 2
    vector<vector<int>> grid2 = {{1,2,3},{4,5,6}};
    cout << "测试用例 2 - 输出: " << solution.minPathSum(grid2)
         << " (期望: 12)" << endl;

    return 0;
}
