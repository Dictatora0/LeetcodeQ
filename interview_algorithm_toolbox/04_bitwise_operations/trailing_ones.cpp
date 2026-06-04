/*
题目 / 示例名称：统计二进制末尾连续 1
核心知识点：末尾连续 1、位移、`(1LL << k) - 1`
适用场景：规律题、位运算题、与后缀连续 1 有关的计数问题
关键思路：
1. 只要最低位还是 1，就不断右移并计数。
2. 如果末尾连续有 k 个 1，那么这段对应的十进制值就是 `2^k - 1`。
时间复杂度：O(末尾连续 1 的个数)
空间复杂度：O(1)
常见错误：
1. 把“连续 1 的个数”与“这段 1 对应的十进制值”混在一起。
2. 忘记 `1LL << k` 表示 `2^k`。
3. 没注意 `k = 0` 时对应值应该是 0。
示例输入：
23
示例输出：
count 3
value 7
手动推演：
23 的二进制是 10111，末尾连续 3 个 1。
`111(2)` 对应十进制 7，也就是 `(1 << 3) - 1`。
对比说明：
- 这个文件统计的是单个数。
- `12_real_past_problems/` 里的二进制真题统计的是从 1 到 n 的总和。
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

    int count = 0;
    while ((x & 1LL) == 1LL) {
        ++count;
        x >>= 1;
    }

    long long value = 0;
    if (count > 0) {
        value = (1LL << count) - 1;
    }

    cout << "count " << count << '\n';
    cout << "value " << value << '\n';
    return 0;
}
