/*
题目 / 示例名称：区间排序基础
核心知识点：区间排序、结构体、多关键字比较器
适用场景：合并区间、区间扫描、会议安排等题的第一步预处理
关键思路：通常先按左端点升序；若左端点相同，再按右端点升序
时间复杂度：O(n log n)
空间复杂度：O(log n)
常见错误：
1. 左端点相同却不补第二关键字，结果后续扫描更难写。
2. 比较器方向写反。
3. 题目真正需要按右端点排序，却机械套左端点排序模板。
示例输入：
5
3 5
1 4
1 2
2 6
3 4
示例输出：
1 2
1 4
2 6
3 4
3 5
手动推演：
先看左端点，1 最小，所以 `(1,2)` 和 `(1,4)` 在最前。
左端点都为 1 时，再按右端点升序，所以 `(1,2)` 在 `(1,4)` 前。
对比说明：
- 合并区间题常按左端点排序。
- 区间调度题常按右端点排序，见 `07_greedy_and_intervals/interval_scheduling.cpp`。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int left;
    int right;
};

bool compareInterval(const Interval& a, const Interval& b) {
    if (a.left != b.left) {
        return a.left < b.left;
    }
    return a.right < b.right;
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

    sort(intervals.begin(), intervals.end(), compareInterval);

    for (const Interval& interval : intervals) {
        cout << interval.left << ' ' << interval.right << '\n';
    }

    return 0;
}
