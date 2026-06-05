/*
题目 / 示例名称：答案二分 + DP check - 网格最小初始生命值
核心知识点：答案二分、DP check、单调性、网格动态规划
适用场景：题目要求“最小初始值”，并且可行性判断需要综合多条路径状态，不能用简单贪心
关键思路：
1. 给定一个初始生命值 H，判断能否从左上走到右下。
2. 走到某个格子时，当前生命值 = 进入前的生命值 + 该格子数值。
   全程生命值必须始终 >= 1。
3. 如果初始生命值 H 可行，那么更大的 H 也一定可行。
   这说明“是否可行”关于 H 具有单调性，可以二分答案。
4. check(H) 怎么做？
   用 DP 记录“到达每个格子时，最多还能剩多少生命值”。
   如果某个格子不可达，就记为无效状态。
5. 这类 check 不是贪心，也不是纯数学计数，而是 DP。
时间复杂度：O(n * m * log answer)
空间复杂度：O(n * m)
常见错误：
1. 试图用局部最优路径贪心，忽略后续路径可能更优。
2. 没证明单调性就二分。
3. DP 里只记“是否可达”，却不记剩余生命值大小，导致后续比较失真。
4. 初始生命值进入起点后也必须 >= 1，这个边界容易漏。
示例输入：
3 3
-2 -3 3
-5 -10 1
10 30 -5
示例输出：
7
手动推演：
如果初始生命值是 7：
起点后生命值变成 5
存在一条可行路径一直保持生命值 >= 1，最终到达终点

如果初始生命值是 6：
进入起点后剩 4，再往后无论怎么走都会在某一步掉到 0 或以下
所以答案是 7。
对比说明：
- `answer_binary_search_minimize_max_segment_sum.cpp`：贪心 check
- `answer_binary_search_minimum_production_time.cpp`：数学 check
- 本文件：DP check
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool canSurvive(const vector<vector<long long>>& grid, long long initial_health) {
    int n = static_cast<int>(grid.size()) - 1;
    int m = static_cast<int>(grid[0].size()) - 1;
    const long long NEG_INF = -(1LL << 60);

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, NEG_INF));

    // 连起点都无法存活，当前初始生命值就直接不合法。
    long long start_health = initial_health + grid[1][1];
    if (start_health < 1) {
        return false;
    }
    dp[1][1] = start_health;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }

            long long best_previous = NEG_INF;
            if (i > 1) {
                // 可以从上方转移过来。
                best_previous = max(best_previous, dp[i - 1][j]);
            }
            if (j > 1) {
                // 也可以从左方转移过来。
                best_previous = max(best_previous, dp[i][j - 1]);
            }

            if (best_previous == NEG_INF) {
                // 上方和左方都不可达，则当前格子也不可达。
                continue;
            }

            // 进入当前格子后的生命值 = 进入前最好状态 + 当前格子的增减值。
            long long current_health = best_previous + grid[i][j];
            if (current_health >= 1) {
                // 生命值始终要至少为 1，合法状态才保留下来。
                dp[i][j] = max(dp[i][j], current_health);
            }
        }
    }

    return dp[n][m] >= 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<vector<long long>> grid(n + 1, vector<long long>(m + 1, 0));
    long long total_negative_loss = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] < 0) {
                // 用所有负值损失之和构造一个保守但一定够大的右边界。
                total_negative_loss += -grid[i][j];
            }
        }
    }

    long long left = 1;
    long long right = total_negative_loss + 1;

    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (canSurvive(grid, mid)) {
            // mid 已经可行，继续尝试更小初始生命值。
            right = mid;
        } else {
            // mid 不够，说明初始生命值还要更大。
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
