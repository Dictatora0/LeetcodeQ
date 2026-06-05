/*
题目 / 示例名称：双串 DP 入门 - 编辑距离
核心知识点：双串 DP、状态定义、插入删除替换
适用场景：题目要求把一个字符串变成另一个字符串，并且每次操作代价相同
关键思路：
1. 设 `dp[i][j]` 表示把 `s` 的前 i 个字符变成 `t` 的前 j 个字符的最少操作次数。
2. 如果 `s[i - 1] == t[j - 1]`，最后一个字符已经匹配，不需要额外操作：
   `dp[i][j] = dp[i - 1][j - 1]`
3. 如果最后一个字符不同，就有三种选择：
   - 删除 `s[i - 1]`：`dp[i - 1][j] + 1`
   - 插入 `t[j - 1]`：`dp[i][j - 1] + 1`
   - 把 `s[i - 1]` 替换成 `t[j - 1]`：`dp[i - 1][j - 1] + 1`
4. 取三者最小值即可。
时间复杂度：O(n * m)
空间复杂度：O(n * m)
常见错误：
1. `dp[i][j]` 的含义没想清楚，导致插入、删除、替换的方向写乱。
2. 忘记初始化 `dp[i][0]` 和 `dp[0][j]`。
3. 看到双串问题就直接想 LCS，其实编辑距离和最长公共子序列不是一回事。
示例输入：
horse
ros
示例输出：
3
手动推演：
一种最优变换方式是：
horse -> rorse   （把 h 替换成 r）
rorse -> rose    （删除一个 r）
rose  -> ros     （删除 e）
一共 3 次操作。
对比说明：
- LCS 常问“最多能保留多少共同字符”。
- 编辑距离常问“最少修改几次才能变成目标串”。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    if (!(cin >> s >> t)) {
        return 0;
    }

    int n = static_cast<int>(s.size());
    int m = static_cast<int>(t.size());

    // dp[i][j] 表示：s 的前 i 个字符 -> t 的前 j 个字符 的最少操作次数。
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // 把前 i 个字符变成空串，只能连续删除 i 次。
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = i;
    }
    // 把空串变成前 j 个字符，只能连续插入 j 次。
    for (int j = 0; j <= m; ++j) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == t[j - 1]) {
                // 当前两个字符已经相同，直接继承左上角状态。
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // 删除 s 的最后一个字符。
                int delete_cost = dp[i - 1][j] + 1;
                // 在 s 末尾插入一个字符，使其去匹配 t[j - 1]。
                int insert_cost = dp[i][j - 1] + 1;
                // 把 s[i - 1] 直接替换成 t[j - 1]。
                int replace_cost = dp[i - 1][j - 1] + 1;

                // 三种编辑操作里，取代价最小的那一种。
                dp[i][j] = min({delete_cost, insert_cost, replace_cost});
            }
        }
    }

    // 右下角状态就是把整个 s 变成整个 t 的最少编辑次数。
    cout << dp[n][m] << '\n';
    return 0;
}
