/*
题目 / 示例名称：分发饼干的简单贪心
核心知识点：排序、双指针、局部最优
适用场景：有两组对象，想让尽可能多的小需求被满足
关键思路：把最小的饼干尽量留给当前最小胃口的小朋友，避免浪费大饼干
时间复杂度：O(n log n + m log m)
空间复杂度：O(1) 额外空间
常见错误：
1. 先拿最大饼干喂最小胃口，浪费资源。
2. 排序后双指针移动方向写错。
3. 不理解“先满足最容易满足的人”为何是合理局部最优。
示例输入：
3 4
1 2 3
1 1 2 3
示例输出：
3
手动推演：
胃口 1 用饼干 1，胃口 2 用饼干 2，胃口 3 用饼干 3，共满足 3 人。
对比说明：
- 这是“排序后从小到大匹配”的典型贪心。
- 如果题目要求最少代价或有回退操作，未必还能直接贪心。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<int> appetite(n);
    vector<int> cookie(m);

    for (int i = 0; i < n; ++i) {
        cin >> appetite[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> cookie[i];
    }

    sort(appetite.begin(), appetite.end());
    sort(cookie.begin(), cookie.end());

    int i = 0;
    int j = 0;
    int satisfied = 0;

    while (i < n && j < m) {
        if (cookie[j] >= appetite[i]) {
            // 当前最小可用饼干已经能满足当前最小胃口，立刻匹配最省资源。
            ++satisfied;
            ++i;
            ++j;
        } else {
            // 当前饼干太小，连最小胃口都满足不了，只能尝试更大的饼干。
            ++j;
        }
    }

    cout << satisfied << '\n';
    return 0;
}
