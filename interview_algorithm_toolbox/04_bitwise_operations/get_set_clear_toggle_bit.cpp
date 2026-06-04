/*
题目 / 示例名称：取位、设位、清位、翻转位
核心知识点：`(x >> k) & 1`、`x | (1LL << k)`、`x & ~(1LL << k)`、`x ^ (1LL << k)`
适用场景：题目要求操作二进制某一位
关键思路：先构造第 k 位掩码 `1LL << k`，再和原数做按位与、或、异或
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. 写成 `1 << k`，当 k 较大时可能溢出 int。
2. 清位时忘记先取反掩码。
3. 不清楚 k 是从第 0 位开始数。
示例输入：
10 1
示例输出：
get 1
set 10
clear 8
toggle 8
手动推演：
10 的二进制是 1010，第 1 位本来就是 1，所以 set 后不变；clear 后变成 1000。
对比说明：
- 第 k 位通常从右往左、从 0 开始编号。
- 所有掩码最好写成 `1LL << k`，避免类型问题。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    int k;
    if (!(cin >> x >> k)) {
        return 0;
    }

    long long mask = 1LL << k;

    cout << "get " << ((x >> k) & 1LL) << '\n';
    cout << "set " << (x | mask) << '\n';
    cout << "clear " << (x & ~mask) << '\n';
    cout << "toggle " << (x ^ mask) << '\n';
    return 0;
}
