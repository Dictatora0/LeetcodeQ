/*
题目 / 示例名称：不选相邻元素的最大和（打家劫舍线性版）
核心知识点：一维 DP、相邻限制、选或不选
适用场景：数组中不能同时选择相邻元素，要求最大总收益
关键思路：
1. 设 `dp[i]` 表示考虑前 i 个元素时，能取得的最大总和。
2. 第 i 个元素有两种处理方式：
   - 不选第 i 个：答案就是 `dp[i - 1]`
   - 选第 i 个：那第 i-1 个就不能选，答案是 `dp[i - 2] + a[i]`
3. 因此状态转移为：
   `dp[i] = max(dp[i - 1], dp[i - 2] + a[i])`
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 把“不能相邻”误看成“只能选一个”。
2. 状态转移里写成 `dp[i - 1] + a[i]`，这会把相邻元素一起选上。
3. 基础状态 `dp[0]`、`dp[1]` 没处理清楚。
示例输入：
5
2 7 9 3 1
示例输出：
12
手动推演：
最优选法是选 2、9、1，总和 12。
不能选 7 和 9 一起，因为它们相邻。
对比说明：
- 这题和 `climbing_stairs.cpp` 一样都是一维 DP。
- 差别在于：
  爬楼梯是“把前面的方案数加起来”，
  本题是“当前元素选或不选取更优”。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    if (n == 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<long long> dp(n + 1, 0);
    // 前 0 个元素的最优值是 0。
    dp[0] = 0;
    // 只看第 1 个元素时，最优值就是选它本身。
    dp[1] = a[1];

    for (int i = 2; i <= n; ++i) {
        // 不选第 i 个元素：保留前 i-1 个的最优解。
        long long skip_current = dp[i - 1];
        // 选第 i 个元素：那第 i-1 个必须不选，只能接到 dp[i-2] 后面。
        long long take_current = dp[i - 2] + a[i];
        // 两种方案取更优。
        dp[i] = max(skip_current, take_current);
    }

    cout << dp[n] << '\n';
    return 0;
}
