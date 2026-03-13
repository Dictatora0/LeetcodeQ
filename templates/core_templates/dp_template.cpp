
/*
算法名称：动态规划 DP

算法核心思想
-----------
把问题拆成子问题，记录子问题最优解，避免重复计算。
通常需要明确：状态定义、状态转移、初始化、答案位置。

思路要点
-------
- 先确定状态 dp[i]/dp[i][j] 表示什么
- 写出转移方程，再确定初始化
- 若状态多维，考虑滚动数组降空间
- 注意答案是 dp 的哪个位置

什么时候使用
-----------
适用场景：
- 最优解/计数问题
- 子问题重叠且最优子结构
- 需要从前一步推导当前状态

常见算法变体
-----------
1) 一维 DP（线性）
2) 二维 DP（网格/区间）
3) 记忆化搜索（自顶向下）
4) 状态压缩 DP（位掩码）
5) 背包 DP（0/1、完全）

复杂度分析
---------
时间复杂度：O(状态数 * 转移代价)
空间复杂度：O(状态数)

ASCII 示例
---------
爬楼梯：dp[i] = dp[i-1] + dp[i-2]

典型题目扩展
-----------
- 70 Climbing Stairs
- 198 House Robber
- 64 Minimum Path Sum
- 1143 Longest Common Subsequence
- 322 Coin Change

可直接使用的代码模板
------------------
见下方 DP_Template

常见错误
--------
- 状态定义含糊导致转移不清晰
- 初始化遗漏导致结果错误
- 忘记取最优/取模
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DP_Template {
public:
    // 示例：爬楼梯（1D DP）
    int climbStairs(int n) {
        if (n <= 2) return n;
        int prev2 = 1, prev1 = 2;
        for (int i = 3; i <= n; ++i) {
            int cur = prev1 + prev2;
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }

    // 示例：网格最小路径和（2D DP）
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) dp[i][0] = dp[i-1][0] + grid[i][0];
        for (int j = 1; j < n; ++j) dp[0][j] = dp[0][j-1] + grid[0][j];
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }

    // 0/1 背包（容量 W）
    int knap01(const vector<int>& w, const vector<int>& v, int W) {
        vector<int> dp(W + 1, 0);
        for (int i = 0; i < (int)w.size(); ++i) {
            for (int cap = W; cap >= w[i]; --cap) {
                dp[cap] = max(dp[cap], dp[cap - w[i]] + v[i]);
            }
        }
        return dp[W];
    }
};

int main() {
    DP_Template solver;
    cout << "climbStairs(5) = " << solver.climbStairs(5) << endl;
    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    cout << "minPathSum = " << solver.minPathSum(grid) << endl;
    vector<int> w = {2, 3, 4};
    vector<int> v = {4, 5, 6};
    cout << "knap01 = " << solver.knap01(w, v, 5) << endl;
    return 0;
}
