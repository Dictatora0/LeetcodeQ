/*
题目 / 示例名称：ACM 单组数据输入输出模板
核心知识点：ACM 输入输出、一次扫描、min/max/sum 统计
适用场景：题目只有一组数据，需要读入数组并做线性统计
关键思路：读入 n 和数组后，用一次循环同时维护总和、最小值、最大值
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 忘记开 fast io，导致大输入下超时。
2. 用 int 存总和，遇到大数据可能溢出。
3. 没处理 n = 1 时的最小值和最大值初始化。
示例输入：
5
3 1 4 1 5
示例输出：
14 1 5
手动推演：
依次读入 3,1,4,1,5，sum 变成 14，min 是 1，max 是 5。
对比说明：
- 先读完整个数组再扫一遍：也可以，但这里演示“一边读一边统计”。
- `long long` 比 `int` 更稳，尤其是总和可能超过 2^31 - 1。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<long long> a(n);
    long long sum = 0;
    long long mn = 0;
    long long mx = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];

        // 第一个元素负责初始化最小值和最大值，后续元素再比较更新。
        if (i == 0) {
            mn = a[i];
            mx = a[i];
        } else {
            if (a[i] < mn) {
                mn = a[i];
            }
            if (a[i] > mx) {
                mx = a[i];
            }
        }

        sum += a[i];
    }

    cout << sum << ' ' << mn << ' ' << mx << '\n';
    return 0;
}
