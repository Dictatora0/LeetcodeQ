/*
题目 / 示例名称：完全背包基础版 - 最大价值
核心知识点：完全背包、一维 DP、容量正序枚举
适用场景：每种物品可以使用无限次，要求不超过容量时的最大总价值
关键思路：
1. `dp[j]` 表示容量恰好或不超过 j 时能得到的最大价值。
2. 每种物品可以重复使用，所以枚举当前物品时，容量必须从小到大枚举。
3. 状态转移：
   dp[j] = max(dp[j], dp[j - weight[i]] + value[i])
4. 为什么容量要正序？
   因为当前物品允许在同一轮里被重复使用。
   当 j 增大时，`dp[j - weight[i]]` 可能已经包含了当前物品的贡献。
时间复杂度：O(n * capacity)
空间复杂度：O(capacity)
常见错误：
1. 把完全背包写成容量倒序，结果变成 0/1 背包。
2. 不理解“为什么正序就允许重复选同一物品”。
3. 状态定义不清，分不清是“恰好装满”还是“不超过容量”。
示例输入：
3 5
1 2
2 4
3 4
示例输出：
10
手动推演：
容量为 5 时，选 5 个重量为 1、价值为 2 的物品，总价值是 10。
因为物品 1 可以无限使用，所以这是合法的。
对比说明：
- 0/1 背包：容量倒序，防止同一物品重复使用。
- 完全背包：容量正序，允许同一物品在同一轮重复使用。
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

    // dp[j] 表示容量不超过 j 时的最大价值。
    vector<long long> dp(capacity + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = weight[i]; j <= capacity; ++j) {
            // 完全背包容量正序枚举，表示当前物品可以在这一轮被重复使用。
            // 因此 dp[j - weight[i]] 里可能已经包含了当前物品的贡献。
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    // 容量上限为 capacity 时的最优值。
    cout << dp[capacity] << '\n';
    return 0;
}
