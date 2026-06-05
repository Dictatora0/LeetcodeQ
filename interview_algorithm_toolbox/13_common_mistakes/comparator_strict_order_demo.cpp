/*
题目 / 示例名称：比较器必须满足严格顺序
核心知识点：严格弱序、比较器设计
适用场景：排序规则稍复杂，容易下意识写出 `<=` 或 `>=`
关键思路：只在“明确应该排在前面”时返回 true；相等时必须返回 false
时间复杂度：O(n log n)
空间复杂度：O(log n)
常见错误：
1. 写成 `return a >= b;`，这是错误的。
2. 相等时仍返回 true，会破坏排序契约。
3. 比较器逻辑不自洽，自己都不能解释“谁应该在前”。
示例输入：
6
21 14 32 45 11 20
示例输出：
20 21 11 32 14 45
手动推演：
按个位数字升序排，个位相同再按整体数值升序。
对比说明：
- 正确比较器必须回答“a 是否应排在 b 前面”。
- 绝不能把“a 是否不大于 b”直接当成比较器。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool compareByLastDigit(const int& a, const int& b) {
    int da = a % 10;
    int db = b % 10;
    if (da != db) {
        // 个位数小的排前面。
        return da < db;
    }
    // 个位数相同时，再按整体数值升序排，保持规则完整。
    return a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), compareByLastDigit);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
