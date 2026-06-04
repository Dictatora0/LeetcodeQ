/*
题目 / 示例名称：bitset 固定宽度演示
核心知识点：`bitset`、固定宽度二进制显示、调试
适用场景：想快速观察一个整数在固定若干位下的二进制样子
关键思路：`bitset<N>(x)` 会把 x 按 N 位二进制显示出来，不足部分补 0
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. 误以为 `bitset<8>(300)` 只会显示有效位，不会；它会按低 8 位截断。
2. 用 `bitset` 输出后，不理解每一位对应的权值。
3. 把 `bitset` 当成变长二进制字符串来理解。
示例输入：
13 2
示例输出：
bitset16 0000000000001101
kth_bit 1
手动推演：
13 的二进制是 1101，在 16 位显示里就是前面补 12 个 0。
第 2 位从 0 开始编号，对应值是 1。
对比说明：
- `bitset` 适合调试。
- 真正做题时，取某一位仍然常用 `(x >> k) & 1`。
*/

#include <bitset>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long x;
    int k;
    if (!(cin >> x >> k)) {
        return 0;
    }

    cout << "bitset16 " << bitset<16>(x) << '\n';
    cout << "kth_bit " << ((x >> k) & 1ULL) << '\n';

    return 0;
}
