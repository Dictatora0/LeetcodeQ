/*
题目 / 示例名称：计数型一维 DP - 凑出目标和的方案数
核心知识点：计数型 DP、完全背包、组合数统计
适用场景：每种数值可无限次使用，问“有多少种方法凑出 target”
关键思路：
1. `dp[s]` 表示凑出和为 s 的方案数。
2. 初始条件 `dp[0] = 1`，表示“什么都不选”是一种合法起点。
3. 每种硬币可以无限次使用，因此容量仍然正序枚举。
4. 如果题目要统计“组合数”而不是“排列数”，就要把“物品”放在外层循环。
时间复杂度：O(n * target)
空间复杂度：O(target)
常见错误：
1. 忘记 `dp[0] = 1`，整张表都会是 0。
2. 把循环顺序写反，结果从“组合数”变成“排列数”。
3. 以为计数型 DP 和求最大值的 DP 完全一样，实际上加法和 max 的语义不同。
示例输入：
3 5
1 2 5
示例输出：
4
手动推演：
凑出 5 的组合有：
1+1+1+1+1
1+1+1+2
1+2+2
5
所以答案是 4。
对比说明：
- 求最大值：转移通常是 `max(...)`。
- 计数型：转移通常是“把可行方案数加起来”。
- 组合数：物品外层、容量内层。
- 排列数：如果顺序也算不同，循环顺序通常会改变。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    if (!(cin >> n >> target)) {
        return 0;
    }

    vector<int> coin(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> coin[i];
    }

    // dp[sum] 表示凑出总和为 sum 的方案数。
    vector<long long> dp(target + 1, 0);
    // 凑出和为 0 的方案数是 1：什么都不选。
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int sum = coin[i]; sum <= target; ++sum) {
            // 如果最后一次使用的是 coin[i]，那么前一状态就是 sum - coin[i]。
            // 因为 coin[i] 可以无限使用，所以这里仍然是正序枚举。
            // 又因为“物品在外层”，所以统计的是组合数而不是排列数。
            dp[sum] += dp[sum - coin[i]];
        }
    }

    // target 这一格就是最终方案数。
    cout << dp[target] << '\n';
    return 0;
}
