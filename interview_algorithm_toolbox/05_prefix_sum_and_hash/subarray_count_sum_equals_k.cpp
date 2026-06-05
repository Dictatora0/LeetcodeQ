/*
题目 / 示例名称：和为 k 的子数组个数
核心知识点：前缀和、哈希表、出现次数统计
适用场景：题目要求统计“有多少个连续子数组的和等于 k”
关键思路：
1. 设 `prefix[i]` 表示前 i 个数的和。
2. 如果区间 `(j, i]` 的和为 k，那么：
   prefix[i] - prefix[j] = k
   也就是
   prefix[j] = prefix[i] - k
3. 所以当我们扫描到当前位置 i 时，只要之前出现过前缀和 `prefix[i] - k`，
   那么这些前缀都能和当前位置组成合法区间。
4. 因此哈希表要存“某个前缀和出现过多少次”。
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 把这题和“最长长度”混淆，错误地只记录第一次出现位置。
2. 忘记初始化前缀和 0 的出现次数为 1。
3. 先更新当前前缀和次数，再统计答案，导致把空区间也算进去。
4. 前缀和范围大，仍然使用 int，可能溢出。
示例输入：
5 3
1 -1 5 -2 3
示例输出：
3
手动推演：
和为 3 的子数组有：
[1, -1, 5, -2]
[5, -2]
[3]
一共 3 个。
对比说明：
- 统计“个数”：哈希表存出现次数。
- 求“最长长度”：哈希表存第一次出现位置，见 `longest_subarray_sum_equals_k.cpp`。
*/

#include <iostream>
#include <unordered_map>
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

    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    unordered_map<long long, long long> count;
    // 前缀和 0 先出现一次，表示“空前缀”。
    count[0] = 1;

    long long prefix_sum = 0;
    long long answer = 0;

    for (int i = 1; i <= n; ++i) {
        prefix_sum += a[i];

        long long needed = prefix_sum - k;
        if (count.count(needed)) {
            // 每个之前出现过的 needed，都能和当前位置组成一个合法子数组。
            answer += count[needed];
        }

        // 先统计答案，再登记当前前缀和，避免把空区间错误算进去。
        ++count[prefix_sum];
    }

    cout << answer << '\n';
    return 0;
}
