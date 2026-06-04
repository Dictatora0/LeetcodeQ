/*
题目 / 示例名称：gcd 与 lcm 基础
核心知识点：最大公约数、最小公倍数、`std::gcd`
适用场景：周期、整除、最简分数、步长同步类题目
关键思路：
1. `gcd(a, b)` 表示最大公约数。
2. `lcm(a, b) = a / gcd(a, b) * b`，先除后乘更安全。
时间复杂度：O(log(min(a, b)))
空间复杂度：O(1)
常见错误：
1. 直接写 `a * b / gcd`，乘法可能先溢出。
2. 不理解 gcd/lcm 和整除关系，只会套公式。
3. 忘记 `std::gcd` 需要 `<numeric>`。
示例输入：
12 18
示例输出：
gcd 6
lcm 36
手动推演：
12 和 18 的最大公约数是 6，最小公倍数是 12 / 6 * 18 = 36。
对比说明：
- 先除再乘比先乘再除更安全。
- `gcd` 是很多规律题的共同底层工具。
*/

#include <iostream>
#include <numeric>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    if (!(cin >> a >> b)) {
        return 0;
    }

    long long g = gcd(a, b);
    long long l = a / g * b;

    cout << "gcd " << g << '\n';
    cout << "lcm " << l << '\n';
    return 0;
}
