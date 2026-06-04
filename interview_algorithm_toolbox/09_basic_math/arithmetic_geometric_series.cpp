/*
题目 / 示例名称：等差数列与等比数列基础公式
核心知识点：等差数列、等比数列、通项、前 n 项和
适用场景：题目给出首项、公差或公比，要求快速求某一项或前缀和
关键思路：
1. 等差数列：
   第 n 项 = a1 + (n - 1) * d
   前 n 项和 = n * (a1 + an) / 2
2. 等比数列：
   第 n 项 = b1 * r^(n - 1)
   若 r != 1，前 n 项和 = b1 * (r^n - 1) / (r - 1)
时间复杂度：O(log n)，这里用快速幂求等比数列项
空间复杂度：O(1)
常见错误：
1. 把等差和等比公式混淆。
2. `r = 1` 时仍套一般等比求和公式，导致除以 0。
3. 中间乘法不用 `long long`，很容易溢出。
示例输入：
2 3 5
3 2 4
示例输出：
arithmetic_nth 14
arithmetic_sum 40
geometric_nth 24
geometric_sum 45
手动推演：
等差数列是 2,5,8,11,14，前 5 项和为 40。
等比数列是 3,6,12,24，前 4 项和为 45。
对比说明：
- 增量固定：等差。
- 倍率固定：等比。
*/

#include <iostream>

using namespace std;

long long fastPower(long long base, long long exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1LL) {
            result *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a1, d, n;
    long long b1, r, m;
    if (!(cin >> a1 >> d >> n)) {
        return 0;
    }
    cin >> b1 >> r >> m;

    long long arithmetic_nth = a1 + (n - 1) * d;
    long long arithmetic_sum = n * (a1 + arithmetic_nth) / 2;

    long long geometric_nth = b1 * fastPower(r, m - 1);
    long long geometric_sum = 0;
    if (r == 1) {
        geometric_sum = b1 * m;
    } else {
        geometric_sum = b1 * (fastPower(r, m) - 1) / (r - 1);
    }

    cout << "arithmetic_nth " << arithmetic_nth << '\n';
    cout << "arithmetic_sum " << arithmetic_sum << '\n';
    cout << "geometric_nth " << geometric_nth << '\n';
    cout << "geometric_sum " << geometric_sum << '\n';
    return 0;
}
