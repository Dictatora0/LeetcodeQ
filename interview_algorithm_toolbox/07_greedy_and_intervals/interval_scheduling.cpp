/*
题目 / 示例名称：区间调度，最多选多少个互不重叠区间
核心知识点：贪心、按右端点排序、区间
适用场景：题目要求选最多个互不冲突任务、会议、活动
关键思路：每次优先选结束最早的区间，给后面的区间留出最大空间
时间复杂度：O(n log n)
空间复杂度：O(1) 额外空间（不计存输入）
常见错误：
1. 按左端点排序后贪心，通常不对。
2. 把“互不重叠”边界条件写错，例如 `l > last_end` 和 `l >= last_end` 混淆。
3. 没先证明局部最优选择的合理性就硬写。
示例输入：
4
1 3
2 4
3 5
0 7
示例输出：
2
手动推演：
按结束时间排序后，可选 [1,3] 和 [3,5]，共 2 个。
对比说明：
- 这类题的核心不是遍历本身，而是“排序规则为什么这样选”。
- 边界是否允许相接，要根据题意决定，本示例允许 `l >= last_end`。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int left;
    int right;
};

bool compareByRight(const Interval& a, const Interval& b) {
    if (a.right != b.right) {
        return a.right < b.right;
    }
    return a.left < b.left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<Interval> intervals(n);
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].left >> intervals[i].right;
    }

    sort(intervals.begin(), intervals.end(), compareByRight);

    int answer = 0;
    int last_right = -2000000000;

    for (const Interval& interval : intervals) {
        // 当前区间如果和上一个已选区间不冲突，就把它选进答案。
        if (interval.left >= last_right) {
            ++answer;
            // 记录最新已选区间的右端点，供后面继续判冲突。
            last_right = interval.right;
        }
    }

    cout << answer << '\n';
    return 0;
}
