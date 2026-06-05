/*
题目 / 示例名称：和为 k 的最长连续子数组
核心知识点：前缀和、哈希表、第一次出现位置、最长区间
适用场景：题目要求“和为 k 的最长子数组长度”，或者“某种区间和条件下的最长长度”
关键思路：
1. 设 `prefix[i]` 表示前 i 个数的和。
2. 如果区间 `(j, i]` 的和为 k，那么：
   prefix[i] - prefix[j] = k
   也就是
   prefix[j] = prefix[i] - k
3. 所以当我们扫描到当前位置 i 时，只要之前出现过前缀和 `prefix[i] - k`，
   就能得到一个和为 k 的区间。
4. 为了让区间尽可能长，哈希表要记录某个前缀和第一次出现的位置。
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 哈希表记录最后一次出现位置，导致最长区间被缩短。
2. 忘记初始化前缀和 0 在位置 0 出现，漏掉从开头开始的合法区间。
3. 题目求“最长长度”，却误写成统计“个数”。
4. 前缀和可能很大，仍然用 int 存储。
示例输入：
5 3
1 -1 5 -2 3
示例输出：
4
手动推演：
前 4 个数 `1 + (-1) + 5 + (-2) = 3`，
所以区间 `[1, 4]` 的和为 3，长度为 4。
对比说明：
- 统计“有多少个和为 k 的子数组”：哈希表通常存出现次数。
- 求“和为 k 的最长子数组长度”：哈希表通常存第一次出现位置。
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

    unordered_map<long long, int> first_position;
    // 前缀和 0 在位置 0 先出现一次，方便统计从开头开始的合法区间。
    first_position[0] = 0;

    // prefix_sum 是扫描到当前位置时的总和。
    long long prefix_sum = 0;
    int best_length = 0;

    for (int i = 1; i <= n; ++i) {
        // 一边扫描，一边维护前 i 个数的和。
        prefix_sum += a[i];

        long long needed = prefix_sum - k;
        if (first_position.count(needed)) {
            // 如果之前出现过 prefix_sum - k，
            // 那么两次前缀和之间的区间和恰好是 k。
            int current_length = i - first_position[needed];
            if (current_length > best_length) {
                best_length = current_length;
            }
        }

        // 求最长长度时，只保留第一次出现位置，区间才可能更长。
        if (!first_position.count(prefix_sum)) {
            first_position[prefix_sum] = i;
        }
    }

    // 所有位置都扫描完后，best_length 就是最长合法长度。
    cout << best_length << '\n';
    return 0;
}
