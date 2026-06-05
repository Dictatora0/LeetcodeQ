/*
题目 / 示例名称：模拟题 Problem B - 最长平衡 0/1 区间
核心知识点：前缀和、哈希表、第一次出现位置、最长区间
适用场景：最长连续子数组、平衡数量、前缀状态相同则区间满足条件
关键思路：
1. 把 0 转成 -1，把 1 转成 +1。
2. 这样 0 和 1 数量相等，等价于区间和为 0。
3. 如果两个位置的前缀和相同，那么它们之间的区间和为 0。
4. 为了求最长区间，哈希表只记录某个前缀和第一次出现的位置。
时间复杂度：O(n)
空间复杂度：O(n)
常见错误：
1. 哈希表记录成最后一次出现位置。
2. 忘记初始化前缀和 0 在位置 0 出现。
3. 想成双指针，但这题窗口条件不具单调性。
示例输入：
8
0 1 0 0 1 1 0 1
示例输出：
8
手动推演：
把数组转成：
-1 +1 -1 -1 +1 +1 -1 +1
整段和正好为 0，所以整段长度 8 就是合法答案。
对比说明：
- 统计个数时，哈希表常存“出现次数”。
- 求最长时，哈希表常存“第一次出现位置”。
*/

/*
5 分钟应急写法：
1. 一看到“0 和 1 数量相等的最长连续子数组”，先把 0 当成 -1，1 当成 +1。
2. 立刻写：
   - `unordered_map<int, int> first_position;`
   - `first_position[0] = 0;`
3. 扫一遍数组，维护 `prefix_sum`。
4. 如果当前前缀和以前出现过，就用当前位置减去第一次出现位置更新答案。
5. 如果当前前缀和第一次出现，才把位置记进哈希表。
6. 最后 10 秒只检查：
   - 是否忘了 `first_position[0] = 0`
   - 是否把“第一次出现位置”误写成了“最后一次出现位置”
   - 是否真的把 0 转成了 -1
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
            int length = i - first_position[prefix_sum];
            if (length > best_length) {
                best_length = length;
            }
        } else {
            first_position[prefix_sum] = i;
        }
    }

    cout << best_length << '\n';
    return 0;
}
