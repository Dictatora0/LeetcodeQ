/*
题目 / 示例名称：lowbit 与删除最低位 1
核心知识点：`x & (-x)`、`x & (x - 1)`
适用场景：树状数组、位运算规律题、快速定位最低位 1
关键思路：
1. `x & (-x)` 只保留最低位的一个 1。
2. `x & (x - 1)` 删除最低位的一个 1。
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. 只背结论，不会举具体二进制例子。
2. 把两个公式的效果记反。
3. 在不清楚补码概念时强记 `-x`，结果理解不牢。
示例输入：
12
示例输出：
lowbit 4
remove_lowest_one 8
手动推演：
12 的二进制是 1100。
`x & (-x)` 得到 0100，也就是 4。
`x & (x - 1)` 得到 1000，也就是 8。
对比说明：
- `lowbit` 是“只留下最低位 1”。
- `x & (x - 1)` 是“删掉最低位 1”。
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

    cout << "lowbit " << (x & (-x)) << '\n';
    cout << "remove_lowest_one " << (x & (x - 1)) << '\n';
    return 0;
}
