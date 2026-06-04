/*
题目 / 示例名称：十进制整数转二进制字符串
核心知识点：二进制表示、除 2 取余、位权
适用场景：需要手动输出一个数的二进制形式，或解释每一位是如何得到的
关键思路：不断对 2 取余，拿到的是从低位到高位的二进制位，最后再反转
时间复杂度：O(log x)
空间复杂度：O(log x)
常见错误：
1. 忘记 `x = 0` 的特判。
2. 取余顺序没反转，导致输出倒着的二进制串。
3. 只会用 `bitset`，不会手推二进制来源。
示例输入：
19
示例输出：
10011
手动推演：
19 % 2 = 1
9 % 2 = 1
4 % 2 = 0
2 % 2 = 0
1 % 2 = 1
从下往上读，得到 10011。
对比说明：
- 手动构造字符串，适合理解二进制来源。
- `bitset` 更适合固定宽度调试。
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    if (!(cin >> x)) {
        return 0;
    }

    if (x == 0) {
        cout << "0\n";
        return 0;
    }

    string reversed_bits;
    while (x > 0) {
        reversed_bits.push_back(static_cast<char>('0' + (x % 2)));
        x /= 2;
    }

    for (int i = static_cast<int>(reversed_bits.size()) - 1; i >= 0; --i) {
        cout << reversed_bits[i];
    }
    cout << '\n';

    return 0;
}
