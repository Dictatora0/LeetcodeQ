/*
题目 / 示例名称：二维网格 DP 入门 - 最小路径和
核心知识点：二维 DP、网格转移、从上方和左方转移
适用场景：从左上走到右下，每次只能向右或向下，要求路径代价最小
关键思路：
1. 设 `dp[i][j]` 表示走到格子 `(i, j)` 时的最小路径和。
2. 因为每次只能从上方或左方走到当前格子，所以：
   `dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]`
3. 边界上：
   - 起点 `dp[1][1] = grid[1][1]`
   - 第一行只能从左边过来
   - 第一列只能从上边过来
时间复杂度：O(n * m)
空间复杂度：O(n * m)
常见错误：
1. 忘记处理第一行和第一列的边界。
2. 把“最小路径和”误写成 BFS，其实这里不是无权最短路。
3. 状态定义不清，把 `dp[i][j]` 写成“从 i,j 出发”而不是“走到 i,j 为止”。
示例输入：
3 3
1 3 1
1 5 1
4 2 1
示例输出：
7
手动推演：
一条最优路径是：
1 -> 3 -> 1 -> 1 -> 1
总和为 7。
对比说明：
- 网格最短步数：常用 BFS
- 网格最小代价和：常用 DP
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<vector<long long>> grid(n + 1, vector<long long>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
        }
    }

    const long long INF = (1LL << 60);
    // 先把所有状态设成一个很大的数，表示“当前还没被合法更新过”。
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));

    // 起点的最小路径和就是它自己本身的代价。
    dp[1][1] = grid[1][1];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }

            // 如果从上方走得到的代价更小，就优先继承上方状态。
            if (i > 1) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j]);
            }
            // 如果从左方走得到的代价更小，就优先继承左方状态。
            if (j > 1) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j]);
            }
        }
    }

    // 终点格子的 dp 值就是从左上走到右下的最小路径和。
    cout << dp[n][m] << '\n';
    return 0;
}
