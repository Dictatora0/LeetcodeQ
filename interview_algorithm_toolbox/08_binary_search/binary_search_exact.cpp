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

    // 闭区间写法：当前仍需搜索的答案范围是 [left, right]。
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        // 用这种写法求 mid，可以避免 left + right 直接相加溢出。
        int mid = left + (right - left) / 2;
        if (a[mid] == target) {
            // 找到目标就可以直接返回，因为本题只要求任意一个精确位置。
            cout << mid << '\n';
            return 0;
        }
        if (a[mid] < target) {
            // 中点值太小，目标只能在右边。
            left = mid + 1;
        } else {
            // 中点值太大，目标只能在左边。
            right = mid - 1;
        }
    }

    // 如果循环结束仍然没提前返回，说明数组里不存在 target。
    cout << -1 << '\n';
    return 0;
}
