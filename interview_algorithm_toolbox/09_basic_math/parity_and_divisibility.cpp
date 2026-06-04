/*
题目 / 示例名称：奇偶与整除基础判断
核心知识点：奇偶性、整除、取模
适用场景：题目要求判断奇偶、能否整除、余数是什么
关键思路：`x % 2` 判断奇偶，`x % d == 0` 判断是否能被 d 整除
时间复杂度：O(1)
空间复杂度：O(1)
常见错误：
1. 忘记 `d` 不能为 0。
2. 只会背公式，不会根据题意解释“整除”的含义。
3. 在复杂题里忽略奇偶性这个最简单但最有力的剪枝条件。
示例输入：
15 5
示例输出：
odd
divisible
remainder 0
手动推演：
15 是奇数，且 15 能被 5 整除，余数为 0。
对比说明：
- 奇偶性是很多题的第一层观察。
- “能否整除”本质就是余数是否等于 0。
*/

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x, d;
    if (!(cin >> x >> d)) {
        return 0;
    }

    cout << (x % 2 == 0 ? "even" : "odd") << '\n';
    cout << (x % d == 0 ? "divisible" : "not_divisible") << '\n';
    cout << "remainder " << (x % d) << '\n';
    return 0;
}
