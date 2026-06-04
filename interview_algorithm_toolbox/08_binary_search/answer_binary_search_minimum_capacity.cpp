/*
题目 / 示例名称：答案二分 - 最小运输容量
核心知识点：答案二分、单调性、可行性检查
适用场景：题目问“最小的 x，使得某条件成立”
关键思路：
1. 如果容量越大，越容易在规定天数内运完，那么“是否可行”关于容量具有单调性。
2. 有了单调性，就能二分答案。
3. 每次检查某个容量 cap 是否能在 days 天内完成运输。
时间复杂度：O(n log S)，S 是答案范围
空间复杂度：O(1)
常见错误：
1. 没先证明单调性就盲目二分。
2. 左边界取得太小，导致 check 无意义。
3. `mid` 可行时还往右走，结果求成了最大可行值。
示例输入：
5 3
1 2 3 4 5
示例输出：
6
手动推演：
容量 5 时：
第 1 天运 1+2=3，再加 3 会超，停。
第 2 天运 3
第 3 天运 4
第 4 天运 5
需要 4 天，不行。
容量 6 时：
第 1 天运 1+2+3=6
第 2 天运 4
第 3 天运 5
刚好 3 天，可行，所以答案是 6。
对比说明：
- 精确二分是“在有序数组里找值”。
- 答案二分是“在答案空间里找最小可行值”。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool canFinish(const vector<int>& weights, int days, long long capacity) {
    int used_days = 1;
    long long current_load = 0;

    for (int weight : weights) {
        if (current_load + weight <= capacity) {
            current_load += weight;
        } else {
            ++used_days;
            current_load = weight;
        }
    }

    return used_days <= days;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, days;
    if (!(cin >> n >> days)) {
        return 0;
    }

    vector<int> weights(n);
    long long left = 0;
    long long right = 0;

    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
        left = max(left, static_cast<long long>(weights[i]));
        right += weights[i];
    }

    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (canFinish(weights, days, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
