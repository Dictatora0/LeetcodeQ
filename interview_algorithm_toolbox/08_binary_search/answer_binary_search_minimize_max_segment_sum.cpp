/*
题目 / 示例名称：答案二分 + 贪心 check - 最小化分段后的最大段和
核心知识点：答案二分、贪心 check、单调性、数组分段
适用场景：题目要求“把数组分成不超过 m 段，使最大的那一段尽量小”
关键思路：
1. 假设答案是 `limit`，问题变成：
   能否把数组分成不超过 m 段，并且每一段的和都不超过 `limit`。
2. 如果 `limit` 越大，约束越宽松，就越容易做到。
   这说明“是否可行”关于 `limit` 具有单调性，所以可以二分答案。
3. check 怎么做？
   用贪心从左到右尽量往当前段里塞元素。
   一旦再加入下一个元素会超过 `limit`，就必须新开一段。
4. 为什么这个 check 是贪心？
   因为在给定 `limit` 的前提下，当前段能塞就塞，才能让段数尽可能少。
   如果你提前切断，只会让段数更多，不会更优。
时间复杂度：O(n log S)，S 是答案范围
空间复杂度：O(1)
常见错误：
1. 没先证明“答案越大越容易满足”，就直接二分。
2. check 时不是“尽量塞满当前段”，导致段数计算偏大。
3. 左边界取得过小，没有从数组最大值开始。
4. 把“最多 m 段”误写成“恰好 m 段”。
示例输入：
5 2
7 2 5 10 8
示例输出：
18
手动推演：
如果最大允许段和是 18：
第一段可以取 [7,2,5]，和为 14
第二段取 [10,8]，和为 18
一共 2 段，可行

如果最大允许段和是 17：
[7,2,5] 和为 14
下一段若放 10 就得到 24，只能新开段
10 之后再放 8 又会超过 17，还得再开一段
这样需要 3 段，不可行
所以答案是 18。
对比说明：
- `answer_binary_search_minimum_capacity.cpp` 是“容量类”答案二分。
- 本文件是“最大段和最小化”答案二分。
- 两者共同点都是：
  1. 先二分答案
  2. 再用线性贪心 check 某个答案是否可行
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool canSplitWithinMParts(const vector<long long>& a, int m, long long limit) {
    int used_parts = 1;
    long long current_sum = 0;

    for (long long x : a) {
        if (current_sum + x <= limit) {
            // 当前元素还能放进这一段，就尽量继续塞。
            current_sum += x;
        } else {
            // 一旦超 limit，只能另开一段。
            ++used_parts;
            current_sum = x;
        }
    }

    return used_parts <= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<long long> a(n);
    long long left = 0;
    long long right = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        // 答案下界至少是数组最大值。
        left = max(left, a[i]);
        // 答案上界可以取整个数组总和。
        right += a[i];
    }

    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (canSplitWithinMParts(a, m, mid)) {
            // mid 可行，尝试继续压小最大段和。
            right = mid;
        } else {
            // mid 不可行，说明限制太紧。
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
