/*
题目 / 示例名称：和不超过 k 的最长连续子数组
核心知识点：滑动窗口、连续子数组、窗口收缩
适用场景：数组元素非负，需要维护一个满足条件的最长区间
关键思路：右端点扩张窗口，若总和超过 k，就不断移动左端点缩小窗口
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 数组有负数时仍直接套这个模板。
2. 窗口超限后只缩一次，不持续缩到合法。
3. 忘记在每次扩张后更新答案。
示例输入：
7 8
1 2 1 1 1 3 2
示例输出：
5
手动推演：
最长合法窗口可以是 [1,2,1,1,1]，长度为 5，总和刚好 6。
对比说明：
- 元素非负时，窗口和随右端点右移单调不减，滑窗成立。
- 如果有负数，窗口和不再单调，通常要换思路。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    if (!(cin >> n >> k)) {
        return 0;
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int left = 0;
    long long window_sum = 0;
    int best_length = 0;

    for (int right = 0; right < n; ++right) {
        // 右端点加入窗口。
        window_sum += a[right];

        while (left <= right && window_sum > k) {
            // 只要窗口和超限，就不断缩小左端点直到重新合法。
            window_sum -= a[left];
            ++left;
        }

        // 这里窗口 [left, right] 一定满足 sum <= k，可以尝试更新答案。
        int current_length = right - left + 1;
        if (current_length > best_length) {
            best_length = current_length;
        }
    }

    cout << best_length << '\n';
    return 0;
}
