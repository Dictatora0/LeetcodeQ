/*
LeetCode 221. 最大正方形 (Maximal Square)

题目概述 (Problem Summary)
-------------------------
在一个由 '0' 和 '1' 组成的二维矩阵中，找到只包含 '1' 的最大正方形，
返回其面积。

关键约束 (Key Constraints)
-------------------------
- 1 <= matrix.length, matrix[0].length <= 300
- matrix[i][j] 是 '0' 或 '1'

示例 (Example)
-------------
输入：matrix = [
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
输出：4
解释：最大正方形边长为 2，面积为 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 找到以每个位置为右下角的最大正方形边长

关键观察：
1. 若 matrix[i][j] 为 '1'，最大边长取决于上、左、左上三个位置
2. dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
3. 最大边长的平方即为面积

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
dp[i][j] 表示以 (i,j) 为右下角的最大正方形边长。
若当前为 '1'，取上、左、左上最小值 + 1。

算法流程：
1. 初始化 dp，首行首列按 matrix 直接赋值
2. 遍历其余位置，应用转移方程
3. 记录最大边长

复杂度分析
---------
时间复杂度：O(mn)
空间复杂度：O(mn)
*/
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix[0].size());
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxSide = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    }
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }

        return maxSide * maxSide;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Rolling Array)

优化思路
--------
使用一维数组 dp[j] 表示当前行的 dp 值，
用 prev 保存左上角 dp[i-1][j-1]。

复杂度分析
---------
时间复杂度：O(mn)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix[0].size());
        vector<int> dp(n, 0);
        int maxSide = 0;
        int prev = 0;

        for (int i = 0; i < m; ++i) {
            prev = 0;
            for (int j = 0; j < n; ++j) {
                int temp = dp[j]; // 保存 dp[i-1][j]
                if (matrix[i][j] == '1') {
                    if (j == 0) {
                        dp[j] = 1;
                    } else {
                        dp[j] = min({dp[j], dp[j - 1], prev}) + 1;
                    }
                    maxSide = max(maxSide, dp[j]);
                } else {
                    dp[j] = 0;
                }
                prev = temp;
            }
        }

        return maxSide * maxSide;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
matrix =
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

dp 结果（边长）：
1 0 1 0 0
1 0 1 1 1
1 1 1 2 2
1 0 0 1 0
最大边长 = 2，面积 = 4
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：二维 DP
- 时间复杂度：O(mn)
- 空间复杂度：O(mn)
- 优点：直观清晰
- 缺点：空间占用较大

方法二：滚动数组
- 时间复杂度：O(mn)
- 空间复杂度：O(n)
- 优点：节省空间
- 缺点：实现稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全为 '0'：结果为 0
2. 只有一行或一列：最大面积为 1 或 0
3. 空矩阵：题目保证非空
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<vector<char>> matrix1 = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << "测试用例 1 - 输出: " << solution.maximalSquare(matrix1)
         << " (期望: 4)" << endl;

    // 测试用例 2
    vector<vector<char>> matrix2 = {{'0','1'},{'1','0'}};
    cout << "测试用例 2 - 输出: " << solution.maximalSquare(matrix2)
         << " (期望: 1)" << endl;

    return 0;
}
