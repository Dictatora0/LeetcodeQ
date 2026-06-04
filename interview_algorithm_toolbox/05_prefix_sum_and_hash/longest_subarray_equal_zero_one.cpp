/*
题目 / 示例名称：0 和 1 数量相等的最长连续子数组
核心知识点：前缀和、哈希表、首次出现位置、最长区间
适用场景：题目要求找“满足某个前缀状态相同”的最长连续区间
关键思路：
1. 把数组里的 0 看成 -1，把 1 看成 +1。
2. 这样一来，某个区间里 0 和 1 数量相等，就等价于这个区间的和为 0。
3. 如果 prefix[i] == prefix[j]，那么区间 (i, j] 的和为 0。
4. 想让区间尽可能长，就要记录每个前缀和第一次出现的位置。
5. 当同一个前缀和再次出现时，用“当前位置 - 第一次出现位置”更新答案。
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 只想到统计个数，却没想到把 0 转成 -1。
2. 哈希表里存最后一次出现位置，导致最长区间被缩短。
3. 忘记初始化前缀和 0 在位置 0 出现过，漏掉从开头开始的合法区间。
示例输入：
8
0 1 0 0 1 1 0 1
示例输出：
8
手动推演：
把 0/1 转成 -1/+1 后，整段数组总和就是 0，所以整段长度 8 都是合法答案。
对比说明：
- 统计“有多少个合法区间”：常见做法是哈希计数。
- 统计“最长合法区间”：常见做法是哈希记录第一次出现位置。
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    unordered_map<int, int> first_position;
    first_position[0] = 0;

    int prefix_sum = 0;
    int best_length = 0;

    for (int i = 1; i <= n; ++i) {
        if (a[i] == 0) {
            prefix_sum -= 1;
        } else {
            prefix_sum += 1;
        }

        if (first_position.count(prefix_sum)) {
            int current_length = i - first_position[prefix_sum];
            if (current_length > best_length) {
                best_length = current_length;
            }
        } else {
            // 只记录第一次出现的位置，才能保证后面得到尽可能长的区间。
            first_position[prefix_sum] = i;
        }
    }

    cout << best_length << '\n';
    return 0;
}
