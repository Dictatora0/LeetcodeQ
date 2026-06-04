/*
题目 / 示例名称：模拟题 Problem C - 0/1 背包最大价值
核心知识点：0/1 背包、一维 DP、容量倒序
适用场景：每种物品最多一次、容量受限、求最大价值
关键思路：
1. `dp[j]` 表示容量不超过 j 时能得到的最大总价值。
2. 枚举每件物品时，容量必须从大到小枚举。
3. 转移：
   dp[j] = max(dp[j], dp[j - weight[i]] + value[i])
4. 为什么倒序？
   因为当前物品只能用一次。
   如果正序，`dp[j - weight[i]]` 可能已经在这一轮使用过当前物品，等于重复选。
时间复杂度：O(n * m)
空间复杂度：O(m)
常见错误：
1. 容量正序，误写成完全背包。
2. 用 int 存大价值总和，可能溢出。
3. 没先确认题目是“最多一次”还是“无限次”。
示例输入：
4 7
1 2
3 4
4 5
5 7
示例输出：
9
手动推演：
选重量 3、价值 4 和重量 4、价值 5，总重量 7，总价值 9。
如果选重量 5、价值 7，再加任意别的都超或不优。
对比说明：
- 0/1 背包：倒序。
- 完全背包：正序。
- 如果题目问方案数而不是最大值，就要换成计数型 DP。
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

    vector<long long> dp(capacity + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = capacity; j >= weight[i]; --j) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    cout << dp[capacity] << '\n';
    return 0;
}
