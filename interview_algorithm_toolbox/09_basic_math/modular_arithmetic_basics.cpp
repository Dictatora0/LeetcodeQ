/*
题目 / 示例名称：取模运算基础
核心知识点：模加、模减、模乘
适用场景：答案很大，需要对某个 mod 取模
关键思路：
1. `(a + b) % mod`
2. `(a - b) % mod` 可能为负，需要修正
3. `(a % mod) * (b % mod) % mod`
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. 直接输出 `(a - b) % mod`，结果可能是负数。
2. 乘法取模前不先转 `long long`。
3. 不明白为什么要在每一步都取模。
示例输入：
10 17 7
示例输出：
add 6
sub 0
mul 2
手动推演：
(10 + 17) % 7 = 27 % 7 = 6
(10 - 17) % 7 = -7 % 7 = 0，修正后仍为 0
10 * 17 % 7 = 170 % 7 = 2
对比说明：
- 模减法常写成 `((a - b) % mod + mod) % mod`。
- 如果 `mod` 很大且乘法有溢出风险，还要更进一步处理，这里只讲基础版。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, mod;
    if (!(cin >> a >> b >> mod)) {
        return 0;
    }

    cout << "add " << ((a % mod + b % mod) % mod) << '\n';
    cout << "sub " << (((a - b) % mod + mod) % mod) << '\n';
    cout << "mul " << ((a % mod) * (b % mod) % mod) << '\n';
    return 0;
}
