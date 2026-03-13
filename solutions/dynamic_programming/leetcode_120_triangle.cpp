/*
LeetCode 120. 三角形最小路径和 (Triangle)

题目概述 (Problem Summary)
-------------------------
给定一个三角形数组，从顶部到底部，每次只能移动到下一行的相邻位置，
求路径上的最小和。

关键约束 (Key Constraints)
-------------------------
- 1 <= triangle.length <= 200
- triangle[i].length = i + 1
- -10^4 <= triangle[i][j] <= 10^4

示例 (Example)
-------------
输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
输出：11
解释：路径 2 -> 3 -> 5 -> 1 的和最小

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在三角形结构中选择一条从顶到底的最小代价路径

关键观察：
1. 位置 (i,j) 只能来自上一行的 (i-1,j-1) 或 (i-1,j)
2. dp[i][j] 表示到达 (i,j) 的最小路径和
3. 可用一维数组从底向上滚动更新

根据这些观察，可以得到两种典型解法：
1. 自顶向下 DP
2. 自底向上 DP（空间优化）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
自顶向下动态规划，dp[i][j] 表示到达 (i,j) 的最小路径和。

算法流程：
1. dp[0][0] = triangle[0][0]
2. 每行边界只能从上一行单一位置转移
3. 内部位置取 min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j]
4. 答案为最后一行 dp 的最小值

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n^2)
*/
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = static_cast<int>(triangle.size());
        vector<vector<int>> dp(n);
        for (int i = 0; i < n; ++i) {
            dp[i].resize(i + 1, 0);
        }

        dp[0][0] = triangle[0][0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = dp[i - 1][0] + triangle[i][0];
            dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
            for (int j = 1; j < i; ++j) {
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
        }

        int ans = dp[n - 1][0];
        for (int j = 1; j < n; ++j) {
            ans = min(ans, dp[n - 1][j]);
        }
        return ans;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Bottom Up)

优化思路
--------
从底向上合并，dp[j] 表示从当前位置到底部的最小路径和。
直接在 dp 中更新，节省空间。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = static_cast<int>(triangle.size());
        vector<int> dp = triangle[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }

        return dp[0];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
triangle =
  2
 3 4
6 5 7
4 1 8 3

自底向上：
dp = [4,1,8,3]
i=2 -> dp = [7,6,10]
i=1 -> dp = [9,10]
i=0 -> dp = [11]
结果 11
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：自顶向下二维 DP
- 时间复杂度：O(n^2)
- 空间复杂度：O(n^2)
- 优点：过程直观
- 缺点：空间较大

方法二：自底向上一维 DP
- 时间复杂度：O(n^2)
- 空间复杂度：O(n)
- 优点：空间最优
- 缺点：理解需要反向思考
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一行：直接返回顶点值
2. 含负数：仍可正确求最小和
3. 大规模三角形：推荐使用空间优化
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<vector<int>> tri1 = {{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << "测试用例 1 - 输出: " << solution.minimumTotal(tri1)
         << " (期望: 11)" << endl;

    // 测试用例 2
    vector<vector<int>> tri2 = {{-10}};
    cout << "测试用例 2 - 输出: " << solution.minimumTotal(tri2)
         << " (期望: -10)" << endl;

    return 0;
}
