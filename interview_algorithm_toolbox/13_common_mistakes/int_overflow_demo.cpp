/*
题目 / 示例名称：整数溢出风险示例
核心知识点：`int` 上界、`long long`、乘法溢出判断
适用场景：总和、乘积、前缀和、交叉相乘比较
关键思路：先用 `long long` 计算，再判断结果是否超出 `int` 范围
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. 直接用 int 做乘法，结果已经错了才想起改类型。
2. 只给变量改 `long long`，却忘记常量和中间表达式也要提升。
3. 认为“样例过了就没溢出”。
示例输入：
50000 50000
示例输出：
product 2500000000
int_overflow YES
手动推演：
50000 * 50000 = 25 亿，已经超过 32 位 int 上界 2147483647。
对比说明：
- `1LL * a * b` 是常见提类型写法。
- 交叉相乘、前缀和、区间和都要警惕溢出。
*/

#include <iostream>
#include <limits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    if (!(cin >> a >> b)) {
        return 0;
    }

    long long product = a * b;
    bool overflow_int = (product > numeric_limits<int>::max() ||
                         product < numeric_limits<int>::min());

    cout << "product " << product << '\n';
    cout << "int_overflow " << (overflow_int ? "YES" : "NO") << '\n';
    return 0;
}
