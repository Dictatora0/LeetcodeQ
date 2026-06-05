/*
题目 / 示例名称：第一个大于等于 target 的位置
核心知识点：左闭右开区间、lower_bound 思想
适用场景：找最左满足条件的位置
关键思路：维护 `[left, right)`，当 `a[mid] >= target` 时把答案压到左半边
时间复杂度：O(log n)
空间复杂度：O(1)
常见错误：
1. 在 `a[mid] >= target` 时写成 `left = mid + 1`，方向反了。
2. 忘记这是左闭右开区间，所以 `right = n`。
3. 找不到时没处理返回 `n`。
示例输入：
6 5
1 3 5 5 8 10
示例输出：
2
手动推演：
第一个 >=5 的位置就是第一个 5，下标 2。
对比说明：
- 这是手写版 `lower_bound`。
- “第一个满足条件的位置”是很典型的答案二分原型。
*/

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

    // 当前搜索区间是左闭右开 [left, right)。
    // 也就是说，所有可能成为答案的位置，都落在这个区间里。
    int left = 0;
    int right = n;

    while (left < right) {
        // mid 是当前候选位置，用安全写法避免 left + right 直接相加溢出。
        int mid = left + (right - left) / 2;
        if (a[mid] >= target) {
            // mid 已经满足条件，但还要继续向左找更早的位置。
            right = mid;
        } else {
            // mid 不满足条件，答案只能在右边。
            left = mid + 1;
        }
    }

    // 循环结束时 left == right，并且它们都停在第一个 >= target 的位置。
    // 如果数组里所有数都 < target，那么这里会返回 n。
    cout << left << '\n';
    return 0;
}
