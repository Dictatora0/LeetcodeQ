/*
题目 / 示例名称：有序数组中找和为 target 的一对数
核心知识点：双指针、有序数组、左右夹逼
适用场景：数组已经有序，需要找两个数满足和、差、区间之类的条件
关键思路：左指针从最小值出发，右指针从最大值出发，根据当前和与 target 的大小关系移动
时间复杂度：O(n)
空间复杂度：O(1)
常见错误：
1. 数组没排序却套双指针。
2. 和太大时移动左指针，方向写反。
3. 输出位置时搞错 0-based 与 1-based。
示例输入：
5 9
1 2 4 7 11
示例输出：
2 4
手动推演：
2 + 7 = 9，所以答案是位置 2 和 4。
对比说明：
- 有序数组：双指针优先。
- 无序数组：哈希表优先，见 `05_prefix_sum_and_hash/two_sum_hash.cpp`。
*/

#include <iostream>
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
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int left = 1;
    int right = n;

    while (left < right) {
        // 数组有序时，当前和太小就只能增大左边，太大就只能减小右边。
        long long current_sum = a[left] + a[right];
        if (current_sum == target) {
            cout << left << ' ' << right << '\n';
            return 0;
        }
        if (current_sum < target) {
            // 和太小，需要更大的数。
            ++left;
        } else {
            // 和太大，需要更小的数。
            --right;
        }
    }

    cout << "-1 -1\n";
    return 0;
}
