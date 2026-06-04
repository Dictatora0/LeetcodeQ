/*
题目 / 示例名称：二进制后缀连续 1 求和（优化版）
核心知识点：位权、周期、贡献法、O(log n) 求和
适用场景：测试组数较多，n 可达 1e9，无法枚举 1..n
关键思路：
1. 如果一个数的二进制末尾至少有 k 个连续 1，那么它的 `f(x)` 一定会额外贡献 `2^(k-1)`。
2. 为什么是 `2^(k-1)`？
   因为 `f(x)` 的末尾连续 1 段如果长度至少为 k，那么这段值里一定包含第 k 位的那一项：
   `1 + 2 + 4 + ... + 2^(k-1)`。
3. 末尾至少有 k 个连续 1 的数，恰好形如：
   `2^k - 1, 2 * 2^k - 1, 3 * 2^k - 1, ...`
   也就是每隔 `2^k` 出现一次。
4. 因此它们在区间 `[1, n]` 中的个数是 `floor((n + 1) / 2^k)`。
5. 累加所有 k 的贡献即可，复杂度降为 O(log n)。
时间复杂度：O(log n)
空间复杂度：O(1)
常见错误：
1. 还是试图枚举到 n。
2. 只知道“有规律”，但不会把规律写成计数公式。
3. 忘记 `1LL << k` 表示 `2^k`。
4. 中间乘法和答案不用 `long long`。
示例输入：
5
1
2
3
7
8
示例输出：
1
1
4
12
12
手动推演：
以 n = 7 为例：
k = 1：末尾至少 1 个 1 的数有 1,3,5,7，共 4 个，每个额外贡献 1，总贡献 4
k = 2：末尾至少 2 个 1 的数有 3,7，共 2 个，每个额外贡献 2，总贡献 4
k = 3：末尾至少 3 个 1 的数有 7，共 1 个，每个额外贡献 4，总贡献 4
答案 = 4 + 4 + 4 = 12
对比说明：
- 暴力版是“逐个算 f(i)”。
- 优化版是“按每一位的贡献反过来数有多少个 i 能提供这份贡献”。
*/

#include <iostream>

using namespace std;

long long solveOptimized(long long n) {
    long long answer = 0;

    // k 表示“至少有 k 个连续后缀 1”。
    // 例如 k = 3 时，我们在统计所有二进制末尾至少是 ...111 的数。
    for (int k = 1; k < 62 && (1LL << k) <= n + 1; ++k) {
        long long period = 1LL << k;          // 每隔 2^k 个数出现一次
        long long count = (n + 1) / period;   // [1, n] 中这类数的个数
        long long contribution = 1LL << (k - 1);

        // 末尾至少包含 k 个连续 1 的数共有 count 个。
        // 每个这样的数都会在 f(x) 中包含第 k 个 1 的权值 2^(k-1)。
        // 因此，本轮总贡献是 count * contribution。
        answer += count * contribution;
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        long long n;
        cin >> n;
        cout << solveOptimized(n) << '\n';
    }

    return 0;
}
