/*
题目 / 示例名称：0/1 背包基础版 - 最大价值
核心知识点：0/1 背包、一维 DP、容量倒序枚举
适用场景：每种物品最多只能选一次，要求不超过容量时的最大总价值
关键思路：
1. `dp[j]` 表示容量不超过 j 时的最大价值。
2. 每种物品只能使用一次，所以枚举当前物品时，容量必须从大到小枚举。
3. 状态转移：
   dp[j] = max(dp[j], dp[j - weight[i]] + value[i])
4. 为什么容量要倒序？
   因为如果正序枚举，当前物品在同一轮里可能被重复使用，就会错误地变成完全背包。
时间复杂度：O(n * capacity)
空间复杂度：O(capacity)
常见错误：
1. 把 0/1 背包写成正序，结果同一物品被重复选。
2. 没搞清楚“每种物品一次”和“每种物品无限次”的本质区别。
3. 状态定义和初始化不一致，导致推导混乱。
示例输入：
3 5
1 2
2 4
3 4
示例输出：
8
手动推演：
容量 5 时，最优选法是选重量 2、价值 4 和重量 3、价值 4，共价值 8。
不能选 5 次重量 1 的物品，因为每种物品最多只能选一次。
对比说明：
- 0/1 背包：容量倒序，防止同一轮重复使用当前物品。
- 完全背包：容量正序，允许同一轮重复使用当前物品。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;
    if (!(cin >> n >> capacity)) {
        return 0;
    }

    vector<int> weight(n + 1);
    vector<int> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i] >> value[i];
    }

    // dp[j] 表示“容量不超过 j 时”的最大价值。
    vector<long long> dp(capacity + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = capacity; j >= weight[i]; --j) {
            // 0/1 背包容量倒序枚举，防止当前物品在同一轮被重复选中。
            // 不选第 i 件：保持 dp[j]
            // 选第 i 件：尝试 dp[j - weight[i]] + value[i]
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    // dp[capacity] 就是容量限制下的最大总价值。
    cout << dp[capacity] << '\n';
    return 0;
}
