/*
题目 / 示例名称：手写精确二分查找
核心知识点：有序数组、闭区间二分、mid 防溢出
适用场景：在有序数组中查找某个目标值是否存在
关键思路：维护闭区间 `[left, right]`，每轮用中点把搜索区间砍掉一半
时间复杂度：O(log n)
空间复杂度：O(1)
常见错误：
1. `mid` 写成 `(left + right) / 2`，大范围时可能溢出。
2. `left <= right` 写成 `left < right`，导致漏查最后一个位置。
3. 区间更新方向写反。
示例输入：
6 9
-1 0 3 5 9 12
示例输出：
4
手动推演：
mid 先落在 3，然后再落到 9，对应下标 4。
对比说明：
- 精确查找和边界查找的循环条件不同，别混用。
- 本文件用 0-based 下标输出。
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

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == target) {
            cout << mid << '\n';
            return 0;
        }
        if (a[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << -1 << '\n';
    return 0;
}
