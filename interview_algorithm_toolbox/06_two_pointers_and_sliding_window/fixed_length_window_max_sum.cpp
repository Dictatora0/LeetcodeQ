/*
题目 / 示例名称：固定长度窗口最大和
核心知识点：固定窗口、滑动窗口、减左加右
适用场景：连续长度恰好为 k 的子数组最值问题
关键思路：
1. 先计算前 k 个元素的和，作为第一个窗口。
2. 每向右滑动一次，就减掉离开窗口的元素，加上新进入窗口的元素。
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 每个窗口都重新求和，退化成 O(nk)。
2. 忘记先特判 `k > n`。
3. 移动窗口时减错元素或加错元素。
示例输入：
7 3
2 1 5 1 3 2 4
示例输出：
9
手动推演：
长度为 3 的窗口依次是：
[2,1,5] 和为 8
[1,5,1] 和为 7
[5,1,3] 和为 9
[1,3,2] 和为 6
[3,2,4] 和为 9
最大和为 9。
对比说明：
- 固定长度窗口：窗口大小不变，模板最简单。
- 可变长度窗口：需要根据条件扩张和收缩，见 `longest_subarray_basic_window.cpp`。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) {
        return 0;
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (k > n || k <= 0) {
        cout << -1 << '\n';
        return 0;
    }

    // window_sum 始终表示“当前这个长度为 k 的窗口”的元素和。
    long long window_sum = 0;
    for (int i = 0; i < k; ++i) {
        // 先求出第一个长度为 k 的窗口和。
        window_sum += a[i];
    }

    // best 保存遍历到目前为止看到的最大窗口和。
    long long best = window_sum;

    for (int right = k; right < n; ++right) {
        // 窗口向右滑一步：加上新进来的元素，减去离开的元素。
        window_sum += a[right];
        window_sum -= a[right - k];

        // 每次滑动完成后，window_sum 对应的新窗口是 [right - k + 1, right]。
        if (window_sum > best) {
            best = window_sum;
        }
    }

    cout << best << '\n';
    return 0;
}
