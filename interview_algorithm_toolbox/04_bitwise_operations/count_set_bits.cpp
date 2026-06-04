/*
题目 / 示例名称：统计二进制中 1 的个数
核心知识点：位运算、`x & (x - 1)`、Brian Kernighan 算法
适用场景：题目要求统计 popcount，或需要反复删除最低位 1
关键思路：每次执行 `x = x & (x - 1)`，都会删掉最低位的一个 1
时间复杂度：O(1 的个数)
空间复杂度：O(1)
常见错误：
1. 不理解为什么 `x - 1` 会把最低位 1 变成 0，并把后面的 0 变成 1。
2. 直接循环 64 次也能做，但没掌握更高效的方法。
3. 对负数做位运算统计时没考虑表示方式，本示例只讨论非负数。
示例输入：
13
示例输出：
loop 3
kernighan 3
手动推演：
13 = 1101
第一次删最低位 1：1101 -> 1100
第二次：1100 -> 1000
第三次：1000 -> 0000
所以一共删了 3 次。
对比说明：
- 普通循环：逐位检查，容易理解。
- `x & (x - 1)`：更经典，更适合竞赛与笔试。
*/

#include <iostream>

using namespace std;

int countByLoop(long long x) {
    int count = 0;
    while (x > 0) {
        count += static_cast<int>(x & 1LL);
        x >>= 1;
    }
    return count;
}

int countByKernighan(long long x) {
    int count = 0;
    while (x > 0) {
        x = x & (x - 1);
        ++count;
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    if (!(cin >> x)) {
        return 0;
    }

    cout << "loop " << countByLoop(x) << '\n';
    cout << "kernighan " << countByKernighan(x) << '\n';
    return 0;
}
