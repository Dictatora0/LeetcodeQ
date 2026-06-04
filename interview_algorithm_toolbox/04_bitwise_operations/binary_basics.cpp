/*
题目 / 示例名称：二进制基础表示
核心知识点：二进制、位权、`bitset`
适用场景：需要把十进制数转成二进制，或解释每一位代表什么
关键思路：二进制的第 k 位权值是 `2^k`，可以用 `bitset` 或手动取余得到表示
时间复杂度：O(log x)
空间复杂度：O(log x)
常见错误：
1. 把最低位和最高位搞反。
2. 忘了第 0 位的权值是 1。
3. 输出二进制时没处理 `x = 0`。
示例输入：
13
示例输出：
binary 1101
lowest_bit 1
手动推演：
13 = 8 + 4 + 1，所以二进制是 1101。
对比说明：
- `bitset` 适合调试和固定长度展示。
- 手动构造二进制字符串更适合讲位权来源。
*/

#include <bitset>
#include <iostream>
#include <string>

using namespace std;

string toBinaryString(long long x) {
    if (x == 0) {
        return "0";
    }

    string reversed_bits;
    while (x > 0) {
        reversed_bits.push_back(static_cast<char>('0' + (x % 2)));
        x /= 2;
    }

    return string(reversed_bits.rbegin(), reversed_bits.rend());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    if (!(cin >> x)) {
        return 0;
    }

    cout << "binary " << toBinaryString(x) << '\n';
    cout << "lowest_bit " << (x & 1LL) << '\n';

    // 固定宽度展示更适合调试，这里额外输出 8 位示意。
    cout << "bitset8 " << bitset<8>(x) << '\n';
    return 0;
}
