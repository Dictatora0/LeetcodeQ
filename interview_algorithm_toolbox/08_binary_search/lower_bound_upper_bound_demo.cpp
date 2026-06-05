/*
题目 / 示例名称：lower_bound 与 upper_bound 演示
核心知识点：STL 二分接口、边界查找
适用场景：快速得到第一个 `>= target` 和第一个 `> target` 的位置
关键思路：标准库已经帮你实现了稳定的边界二分，直接调用即可
时间复杂度：O(log n)
空间复杂度：O(1)
常见错误：
1. 不理解返回的是“位置”而不是“值”。
2. 找不到时没意识到返回值可能是 `n`。
3. 把 `lower_bound` 和 `upper_bound` 含义记反。
示例输入：
7 4
1 2 4 4 4 6 9
示例输出：
lower_bound 2
upper_bound 5
手动推演：
第一个 >=4 的位置是 2；第一个 >4 的位置是 5。
对比说明：
- `lower_bound` 适合找左边界。
- `upper_bound` 常和 `-1` 搭配得到右边界。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    if (!(cin >> n >> target)) {
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 前提是数组已经有序。
    // lower_bound / upper_bound 都是在有序区间上做二分。
    // lower_bound 会返回一个迭代器，指向第一个 >= target 的元素。
    // 减去 a.begin() 后，才能把它转换成 0-based 下标。
    int lower = static_cast<int>(lower_bound(a.begin(), a.end(), target) - a.begin());
    // upper_bound 同理，返回的是第一个 > target 的位置。
    int upper = static_cast<int>(upper_bound(a.begin(), a.end(), target) - a.begin());

    // 这里输出的是“位置”，不是具体元素值。
    // 如果目标不存在且比所有元素都大，这两个位置都可能等于 n。
    cout << "lower_bound " << lower << '\n';
    cout << "upper_bound " << upper << '\n';
    return 0;
}
