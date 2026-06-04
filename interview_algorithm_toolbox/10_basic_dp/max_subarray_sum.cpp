/*
题目 / 示例名称：最大子数组和
核心知识点：Kadane、DP、连续子数组
适用场景：题目要求连续子数组最大和
关键思路：`dp[i]` 表示以 i 结尾的最大子数组和，要么接在前面，要么从自己重新开始
时间复杂度：O(n)
空间复杂度：O(1) 额外空间
常见错误：
1. 把“子数组”误写成“子序列”。
2. 全负数时错误地输出 0。
3. 没搞清楚状态是“以 i 结尾”还是“前 i 个里的最大值”。
示例输入：
9
-2 1 -3 4 -1 2 1 -5 4
示例输出：
6
手动推演：
最大连续子数组是 [4, -1, 2, 1]，和为 6。
对比说明：
- 这是 DP，但写到熟练以后会像贪心一样简洁。
- 关键不是公式本身，而是“必须连续”这个限制。
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

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    long long best = a[0];
    long long current = a[0];

    for (int i = 1; i < n; ++i) {
        current = max(a[i], current + a[i]);
        best = max(best, current);
    }

    cout << best << '\n';
    return 0;
}
