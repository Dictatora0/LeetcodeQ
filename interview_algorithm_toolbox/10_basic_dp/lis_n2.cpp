/*
题目 / 示例名称：最长递增子序列基础版 O(n^2)
核心知识点：一维 DP、LIS、状态转移
适用场景：数据范围不大，先掌握最稳的 LIS 基础写法
关键思路：`dp[i]` 表示以 `a[i]` 结尾的最长递增子序列长度，枚举前面的 j 来转移
时间复杂度：O(n^2)
空间复杂度：O(n)
常见错误：
1. 把“递增子序列”误写成“连续子数组”。
2. `a[j] < a[i]` 写成 `<=`，导致变成非严格递增。
3. 以为 LIS 一定要用 O(n log n) 写法，结果基础版反而写不稳。
示例输入：
8
10 9 2 5 3 7 101 18
示例输出：
4
手动推演：
一种最长递增子序列是 2,3,7,101，长度为 4。
对比说明：
- O(n^2) 版本最适合教学和第一遍复习。
- O(n log n) 更快，但更容易在细节上混淆。
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

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> dp(n, 1);
    // 每个元素单独都能构成长度为 1 的递增子序列。
    int answer = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i]) {
                // 如果 a[j] 能接到 a[i] 前面，
                // 那么“以 i 结尾”的 LIS 就可以从 j 转移过来。
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        // 扫完所有前驱后，更新全局最长长度。
        answer = max(answer, dp[i]);
    }

    // answer 表示所有“以 i 结尾”的 LIS 里的最大值。
    cout << answer << '\n';
    return 0;
}
