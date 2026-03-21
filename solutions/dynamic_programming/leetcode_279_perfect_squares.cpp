/*
LeetCode 279. 完全平方数 (Perfect Squares)

题目概述 (Problem Summary)
-------------------------
给定正整数 n，找到若干个完全平方数（如 1, 4, 9, 16, ...）
使得它们的和等于 n。返回和为 n 的完全平方数的最少数量。

关键约束 (Key Constraints)
-------------------------
- 1 <= n <= 10^4

示例 (Example)
-------------
输入：n = 12
输出：3
解释：12 = 4 + 4 + 4

输入：n = 13
输出：2
解释：13 = 4 + 9

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 完全背包问题：每个完全平方数可以无限次使用，求最少数量

关键观察：
1. dp[i] 表示和为 i 的完全平方数的最少数量
2. 完全平方数有：1, 4, 9, 16, 25, ...
3. 状态转移：dp[i] = min(dp[i], dp[i - j*j] + 1)
4. 初始化：dp[0] = 0，其他为无穷大

根据这些观察，可以得到两种典型解法：
1. 动态规划（完全背包）
2. BFS（层序遍历）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - DP)

核心思想
--------
使用动态规划，对于每个数 i，尝试所有可能的完全平方数，
选择使用数量最少的方案。

状态定义：
dp[i] = 和为 i 的完全平方数的最少数量

状态转移方程：
dp[i] = min(dp[i], dp[i - j*j] + 1)
其中 j*j <= i

算法流程：
1. 初始化 dp 数组为无穷大，dp[0] = 0
2. 遍历每个数 i (1 到 n)
3. 对每个数，尝试所有完全平方数 j*j <= i
4. 更新 dp[i] 为最小值

复杂度分析
---------
时间复杂度：O(n * √n)
空间复杂度：O(n)
*/
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, 1e9);
        dp[0] = 0;

        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }

        return dp[n];
    }
};

/*
方法二：BFS 解法 (Approach 2: BFS Solution)

核心思想
--------
将问题看作图的最短路径问题：
- 从 0 开始，每次可以加上一个完全平方数
- 第一次到达 n 时的层数就是答案

算法流程：
1. 使用队列进行 BFS
2. 从 0 开始，每次尝试加上所有可能的完全平方数
3. 使用 visited 数组避免重复访问
4. 第一次到达 n 时返回步数

复杂度分析
---------
时间复杂度：O(n * √n)
空间复杂度：O(n)
*/
class Solution_BFS {
public:
    int numSquares(int n) {
        if (n == 0) return 0;

        queue<int> q;
        vector<bool> visited(n + 1, false);
        q.push(0);
        visited[0] = true;

        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            level++;

            for (int i = 0; i < size; i++) {
                int cur = q.front();
                q.pop();

                for (int j = 1; j * j <= n; j++) {
                    int next = cur + j * j;
                    if (next == n) return level;
                    if (next < n && !visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
        }

        return level;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
n = 12

DP 方法：
dp[0] = 0
dp[1] = dp[0] + 1 = 1  (1)
dp[2] = dp[1] + 1 = 2  (1+1)
dp[3] = dp[2] + 1 = 3  (1+1+1)
dp[4] = dp[0] + 1 = 1  (4)
dp[5] = dp[4] + 1 = 2  (4+1)
dp[6] = dp[5] + 1 = 3  (4+1+1)
dp[7] = dp[6] + 1 = 4  (4+1+1+1)
dp[8] = dp[4] + 1 = 2  (4+4)
dp[9] = dp[0] + 1 = 1  (9)
dp[10] = dp[9] + 1 = 2  (9+1)
dp[11] = dp[10] + 1 = 3  (9+1+1)
dp[12] = dp[8] + 1 = 3  (4+4+4)

结果：3
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：动态规划
- 时间复杂度：O(n * √n)
- 空间复杂度：O(n)
- 优点：代码简洁，易于理解
- 缺点：需要计算所有状态

方法二：BFS
- 时间复杂度：O(n * √n)
- 空间复杂度：O(n)
- 优点：可以提前终止
- 缺点：代码稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. n = 1：返回 1
2. n 是完全平方数：返回 1
3. n = 2：返回 2 (1+1)
*/

/*
数学定理 (Mathematical Theorem)
------------------------------
四平方和定理（Lagrange's Four-Square Theorem）：
任何正整数都可以表示为至多 4 个完全平方数的和。

进一步优化：
- 如果 n 是完全平方数，返回 1
- 如果 n = 4^k * (8m + 7)，返回 4
- 否则尝试是否可以用 2 个完全平方数表示
- 剩余情况返回 3
*/

int main() {
    Solution solution;

    // 测试用例 1
    int n1 = 12;
    cout << "测试用例 1 - 输出: " << solution.numSquares(n1)
         << " (期望: 3)" << endl;

    // 测试用例 2
    int n2 = 13;
    cout << "测试用例 2 - 输出: " << solution.numSquares(n2)
         << " (期望: 2)" << endl;

    // 测试用例 3：完全平方数
    int n3 = 16;
    cout << "测试用例 3 - 输出: " << solution.numSquares(n3)
         << " (期望: 1)" << endl;

    // 测试用例 4
    int n4 = 1;
    cout << "测试用例 4 - 输出: " << solution.numSquares(n4)
         << " (期望: 1)" << endl;

    return 0;
}
