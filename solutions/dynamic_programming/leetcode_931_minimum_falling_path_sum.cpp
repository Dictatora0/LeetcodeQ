/*
LeetCode 931. 下降路径最小和 (Minimum Falling Path Sum)

题目概述 (Problem Summary)
-------------------------
给定一个 n x n 的整数矩阵，下降路径从第一行任意元素开始，
每次可以向下移动到下一行的同列或相邻列。
求所有下降路径中的最小路径和。

关键约束 (Key Constraints)
-------------------------
- 1 <= n <= 100
- -100 <= matrix[i][j] <= 100

示例 (Example)
-------------
输入：matrix = [[2,1,3],[6,5,4],[7,8,9]]
输出：13
解释：下降路径 1 -> 5 -> 7 的和最小，为 13

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在每一行选择一个元素，使得从上到下相邻列移动的和最小

关键观察：
1. dp[i][j] 表示到达 (i,j) 的最小路径和
2. 当前位置可来自上一行的 (i-1,j-1), (i-1,j), (i-1,j+1)
3. 可用滚动数组节省空间

根据这些观察，可以得到两种典型解法：
1. 二维 DP
2. 一维滚动数组优化
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用二维 dp 表记录到达每个位置的最小路径和。
转移来自上一行同列或相邻列。

算法流程：
1. dp[0][j] = matrix[0][j]
2. 对每个 i>0，计算 dp[i][j] = matrix[i][j] + min(上方可达的 dp 值)
3. 答案为 dp 最后一行的最小值

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n^2)
*/
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = static_cast<int>(matrix.size());
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int j = 0; j < n; ++j) dp[0][j] = matrix[0][j];

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int best = dp[i - 1][j];
                if (j > 0) best = min(best, dp[i - 1][j - 1]);
                if (j + 1 < n) best = min(best, dp[i - 1][j + 1]);
                dp[i][j] = matrix[i][j] + best;
            }
        }

        int ans = dp[n - 1][0];
        for (int j = 1; j < n; ++j) ans = min(ans, dp[n - 1][j]);
        return ans;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Rolling Array)

优化思路
--------
只保留上一行 dp，逐行滚动更新当前行。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = static_cast<int>(matrix.size());
        vector<int> dp = matrix[0];

        for (int i = 1; i < n; ++i) {
            vector<int> next(n, 0);
            for (int j = 0; j < n; ++j) {
                int best = dp[j];
                if (j > 0) best = min(best, dp[j - 1]);
                if (j + 1 < n) best = min(best, dp[j + 1]);
                next[j] = matrix[i][j] + best;
            }
            dp.swap(next);
        }

        return *min_element(dp.begin(), dp.end());
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
matrix =
2 1 3
6 5 4
7 8 9

dp 第 0 行：2 1 3
dp 第 1 行：7 6 5
dp 第 2 行：13 13 14
最小值为 13
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维 DP
- 时间复杂度：O(n^2)
- 空间复杂度：O(n^2)
- 优点：直观
- 缺点：空间较大

方法二：滚动数组
- 时间复杂度：O(n^2)
- 空间复杂度：O(n)
- 优点：节省空间
- 缺点：需要额外数组保存当前行
*/

/*
特殊情况 (Edge Cases)
--------------------
1. n = 1：直接返回 matrix[0][0]
2. 含负数：仍适用
3. 大矩阵：推荐滚动数组
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<vector<int>> matrix1 = {{2,1,3},{6,5,4},{7,8,9}};
    cout << "测试用例 1 - 输出: " << solution.minFallingPathSum(matrix1)
         << " (期望: 13)" << endl;

    // 测试用例 2
    vector<vector<int>> matrix2 = {{-19,57},{-40,-5}};
    cout << "测试用例 2 - 输出: " << solution.minFallingPathSum(matrix2)
         << " (期望: -59)" << endl;

    return 0;
}
