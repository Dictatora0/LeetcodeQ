/*
题目 / 示例名称：一次扫描求最小值、最大值与总和
核心知识点：遍历、同时维护多个答案、`long long`
适用场景：题目要求对数组做基础聚合统计
关键思路：每读入一个数，就立刻更新 sum、min、max，不额外开多次循环
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. `sum` 用 int，数组元素较大时溢出。
2. `min` 和 `max` 初始化成 0，导致全负数时出错。
3. 多组测试时忘记把答案变量重置。
示例输入：
4
1000000000 2 3 4
示例输出：
1000000009 2 1000000000
手动推演：
总和已经超过 32 位 int 的安全线，所以必须用 `long long`。
对比说明：
- “先存数组再求值” 与 “边读边求值” 都能做。
- 如果后续还要复用数组，就存；如果只是统计，边读边算更省空间。
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

    long long sum = 0;
    long long mn = 0;
    long long mx = 0;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;

        if (i == 0) {
            mn = x;
            mx = x;
        } else {
            if (x < mn) {
                mn = x;
            }
            if (x > mx) {
                mx = x;
            }
        }

        sum += x;
    }

    cout << sum << ' ' << mn << ' ' << mx << '\n';
    return 0;
}
