/*
题目 / 示例名称：比较器常见错误示例
核心知识点：严格弱序、绝对值排序、比较器设计
适用场景：题目需要自定义“谁应该排前面”的规则
关键思路：按绝对值升序；若绝对值相同，再按实际数值升序
时间复杂度：O(n log n)
空间复杂度：O(log n)
常见错误：
1. 写成 `return abs(a) <= abs(b);`，这是错误写法。
2. 绝对值相等时不补 tie-break，结果容易不稳定。
3. 比较器里做副作用操作，例如修改全局变量。
示例输入：
7
3 -1 -4 2 -2 1 0
示例输出：
0 -1 1 -2 2 3 -4
手动推演：
先看绝对值：0,1,1,2,2,3,4；绝对值相同的 -1 在 1 前，-2 在 2 前。
对比说明：
- 错误：`<=` 或 `>=` 不满足严格顺序。
- 正确：先比较主规则，不同直接返回；相同再比较次规则。
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

bool compareByAbsoluteValue(const int& a, const int& b) {
    int abs_a = abs(a);
    int abs_b = abs(b);

    if (abs_a != abs_b) {
        return abs_a < abs_b;
    }
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

    sort(a.begin(), a.end(), compareByAbsoluteValue);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
