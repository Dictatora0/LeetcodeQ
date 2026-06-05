/*
题目 / 示例名称：无序数组中的两数之和
核心知识点：哈希表、补数、一次遍历
适用场景：数组无序，要求找出和为 target 的一对下标
关键思路：遍历到 `a[i]` 时，检查 `target - a[i]` 是否已经出现
时间复杂度：均摊 O(n)
空间复杂度：O(n)
常见错误：
1. 先把当前元素插入哈希表，再查补数，导致同一个元素被重复使用。
2. 输出的是值而不是下标，和题意不一致。
3. 明明数组无序，却先排序，最后丢失原下标。
示例输入：
5 9
2 7 11 15 1
示例输出：
1 2
手动推演：
看到 7 时，补数 2 已经出现，所以答案是位置 1 和 2。
对比说明：
- 无序数组：哈希表最方便。
- 已排序数组：更适合双指针，见 `06_two_pointers_and_sliding_window/`。
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    if (!(cin >> n >> target)) {
        return 0;
    }

    vector<long long> a(n + 1, 0);
    unordered_map<long long, int> first_position;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        long long need = target - a[i];
        // 如果补数之前已经出现过，就找到了一组合法答案。
        if (first_position.count(need)) {
            cout << first_position[need] << ' ' << i << '\n';
            return 0;
        }
        // 只记录第一次出现位置，让下标更稳定，也避免覆盖更早位置。
        if (!first_position.count(a[i])) {
            first_position[a[i]] = i;
        }
    }

    cout << "-1 -1\n";
    return 0;
}
