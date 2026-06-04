/*
题目 / 示例名称：二进制后缀连续 1 求和（暴力版）
核心知识点：二进制、连续后缀 1、暴力验证规律
适用场景：先验证 `f(x)` 的定义和小数据规律，再过渡到优化版
关键思路：
1. `f(x)` 表示 x 的二进制里，从最低位开始连续 1 的那一段对应的十进制值。
2. 如果最低位连续有 k 个 1，那么这段二进制就是 `111...111`（共 k 个），对应十进制 `2^k - 1`。
3. 暴力版直接枚举 `1..n`，逐个计算 `f(i)` 再累加。
时间复杂度：O(n log n)
空间复杂度：O(1)
常见错误：
1. 只算连续 1 的个数，却忘记题目要的是这段 1 对应的十进制值。
2. 以为末尾有 3 个 1 时贡献是 3，实际上是 `111(2) = 7`。
3. 用暴力版直接打 `n = 1e9`，必然超时。
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
`f(1)=1`
`f(2)=0`，因为二进制 10 末尾不是 1
`f(3)=3`，因为二进制 11 末尾连续两个 1，对应 `2^2-1=3`
所以前 3 项和是 `1+0+3=4`
对比说明：
- 暴力版适合验证规律。
- 真正的大数据需要看优化版。
*/

#include <iostream>

using namespace std;

long long suffixOnesValue(long long x) {
    int count = 0;

    while ((x & 1LL) == 1LL) {
        ++count;
        x >>= 1;
    }

    if (count == 0) {
        return 0;
    }

    // k 个连续的 1 对应的二进制数是 111...111，共 k 位。
    // 它的十进制值正好是 2^k - 1。
    return (1LL << count) - 1;
}

long long solveBruteforce(long long n) {
    long long answer = 0;

    for (long long i = 1; i <= n; ++i) {
        answer += suffixOnesValue(i);
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
        cout << solveBruteforce(n) << '\n';
    }

    return 0;
}
