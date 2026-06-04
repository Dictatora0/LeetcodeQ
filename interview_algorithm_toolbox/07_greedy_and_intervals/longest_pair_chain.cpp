/*
题目 / 示例名称：最长数对链
核心知识点：贪心、区间思想、排序
适用场景：每个数对 `(a, b)` 只能接在满足 `prev.second < next.first` 的后面
关键思路：本质上和区间调度非常像，仍然优先选结束更早的 pair
时间复杂度：O(n log n)
空间复杂度：O(1) 额外空间
常见错误：
1. 没认出这是区间调度的变形。
2. 连接条件是严格小于，却写成小于等于。
3. 误以为必须用 DP，其实基础版本贪心即可。
示例输入：
4
1 2
2 3
3 4
5 6
示例输出：
3
手动推演：
[1,2] -> [3,4] -> [5,6] 可以形成长度为 3 的链。
对比说明：
- 如果题目只是求最长数量，贪心很适合。
- 如果题目还要求统计方案数，往往就要换 DP 思路。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct PairNode {
    int first_value;
    int second_value;
};

bool compareBySecond(const PairNode& a, const PairNode& b) {
    if (a.second_value != b.second_value) {
        return a.second_value < b.second_value;
    }
    return a.first_value < b.first_value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<PairNode> pairs(n);
    for (int i = 0; i < n; ++i) {
        cin >> pairs[i].first_value >> pairs[i].second_value;
    }

    sort(pairs.begin(), pairs.end(), compareBySecond);

    int answer = 0;
    int last_second = -2000000000;

    for (const PairNode& pair_node : pairs) {
        if (last_second < pair_node.first_value) {
            ++answer;
            last_second = pair_node.second_value;
        }
    }

    cout << answer << '\n';
    return 0;
}
