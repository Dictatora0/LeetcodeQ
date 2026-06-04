/*
题目 / 示例名称：判断是否为 2 的幂
核心知识点：`x > 0 && (x & (x - 1)) == 0`
适用场景：判断二进制里是否只有一个 1
关键思路：2 的幂的二进制只有一位是 1，例如 1、10、100、1000
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. 忘记排除 `x <= 0`。
2. 记住了公式，却没理解为什么成立。
3. 把 0 当成 2 的幂。
示例输入：
16
示例输出：
YES
手动推演：
16 的二进制是 10000，只有一个 1，所以是 2 的幂。
对比说明：
- 如果一个数只有一个 1，那么执行 `x & (x - 1)` 后会直接变成 0。
- 例如 10000 & 01111 = 00000。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    if (!(cin >> x)) {
        return 0;
    }

    bool is_power_of_two = (x > 0) && ((x & (x - 1)) == 0);
    cout << (is_power_of_two ? "YES" : "NO") << '\n';
    return 0;
}
