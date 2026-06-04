/*
题目 / 示例名称：统计数组中的奇数个数
核心知识点：遍历、计数、奇偶判断
适用场景：题目要求统计满足某个简单条件的元素个数
关键思路：逐个读入元素，满足奇数条件就把计数器加一
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 把 `x % 2 == 1` 当成通用奇数判断，遇到负数时会有歧义。
2. 忘记初始化计数器。
3. 把 `x & 1` 和 `x % 2` 的含义混在一起，写成难读代码。
示例输入：
6
1 2 3 4 5 6
示例输出：
3
手动推演：
奇数是 1、3、5，所以答案是 3。
对比说明：
- `x % 2 != 0`：可读性强，基础题优先用这个。
- `x & 1`：位运算题常用，但如果题面只是模拟统计，优先可读性。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    int odd_count = 0;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;

        if (x % 2 != 0) {
            ++odd_count;
        }
    }

    cout << odd_count << '\n';
    return 0;
}
