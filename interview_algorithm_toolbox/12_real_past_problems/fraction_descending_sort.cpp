/*
题目 / 示例名称：分数降序排序
核心知识点：结构体、普通比较函数、交叉相乘、严格比较器
适用场景：题目要比较比值大小，但又不能安全使用整数除法或浮点数
关键思路：
1. 不能用整数除法，因为 `1 / 2` 会直接变成 0。
2. 不建议直接转成 double，因为浮点数会有精度误差。
3. 分母都为正数时，`a / b > c / d` 等价于 `a * d > c * b`。
4. 比较器 `compareFraction(x, y)` 返回 true，表示 x 应排在 y 前面。
5. 降序时要在“x 更大”时返回 true，不能写成 `>=`。
时间复杂度：O(n log n)
空间复杂度：O(log n)
常见错误：
1. 使用整数除法比较，结果大量分数都被截断成 0。
2. 直接转 double 比较，近似值非常接近时可能出错。
3. 比较器写成 `>=`，破坏严格弱序。
4. 忽略交叉相乘也可能溢出，所以比较时要警惕范围。
示例输入：
5
1 2
3 4
-1 3
0 5
2 3
示例输出：
3/4
2/3
1/2
0/5
-1/3
手动推演：
`3/4 = 0.75`，`2/3 ≈ 0.666...`，`1/2 = 0.5`，`0/5 = 0`，`-1/3 < 0`。
对比说明：
- 整数除法比较：错，因为 1/2 和 2/3 都会被截成 0。
- 浮点比较：很多时候能过，但不是最稳的竞赛写法。
- 交叉相乘：前提是分母同号；本题分母都为正，刚好满足。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Fraction {
    long long numerator;
    long long denominator;
};

bool compareFraction(const Fraction& x, const Fraction& y) {
    // compareFraction(x, y) 返回 true，表示 x 应排在 y 前面。
    // 本题要求分数值严格降序，因此当 x 对应分数更大时返回 true。
    //
    // 不能写成 x.numerator / x.denominator > y.numerator / y.denominator：
    // 因为整数除法会截断小数部分。
    //
    // 也不建议直接转 double：
    // 因为极其接近的分数可能受浮点误差影响。
    //
    // 分母都为正数时，可以安全比较：
    // x.numerator / x.denominator > y.numerator / y.denominator
    // 等价于
    // x.numerator * y.denominator > y.numerator * x.denominator
    //
    // 这里用 __int128 做中间乘法，避免 long long 交叉相乘时溢出。
    __int128 left = static_cast<__int128>(x.numerator) * y.denominator;
    __int128 right = static_cast<__int128>(y.numerator) * x.denominator;

    if (left != right) {
        return left > right;
    }

    // 题面说分数互不相同，通常这里不会走到。
    // 但为了保持比较器是“严格”的，这里补一个稳定的 tie-break。
    if (x.numerator != y.numerator) {
        return x.numerator < y.numerator;
    }
    return x.denominator < y.denominator;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<Fraction> fractions(n);
    for (int i = 0; i < n; ++i) {
        cin >> fractions[i].numerator >> fractions[i].denominator;
    }

    sort(fractions.begin(), fractions.end(), compareFraction);

    for (const Fraction& fraction : fractions) {
        cout << fraction.numerator << '/' << fraction.denominator << '\n';
    }

    return 0;
}
