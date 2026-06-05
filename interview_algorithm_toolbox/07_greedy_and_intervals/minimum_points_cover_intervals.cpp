/*
题目 / 示例名称：最少用多少个点覆盖所有区间
核心知识点：贪心、区间覆盖、按右端点排序
适用场景：题目要求用尽量少的点、箭、设备去覆盖所有区间
关键思路：
1. 先按右端点升序。
2. 每次在当前最早结束的未覆盖区间右端点放一个点。
3. 这个点会尽可能覆盖后续更多区间，因此是局部最优。
时间复杂度：O(n log n)
空间复杂度：O(1) 额外空间
常见错误：
1. 放点放在左端点，覆盖能力通常更差。
2. 排序按左端点做贪心，证明更困难且容易错。
3. 没分清“相交”与“包含边界也算覆盖”。
示例输入：
5
1 3
2 5
3 6
7 8
8 10
示例输出：
2
手动推演：
先在 3 放点，可以覆盖 `[1,3]`、`[2,5]`、`[3,6]`。
再在 8 放点，可以覆盖 `[7,8]`、`[8,10]`。
所以只需 2 个点。
对比说明：
- 这是“最少覆盖资源”类区间贪心。
- `interval_scheduling.cpp` 是“最多选多少个不冲突区间”，两者排序都常看右端点，但目标不同。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Segment {
    int left;
    int right;
};

bool compareByRightEnd(const Segment& a, const Segment& b) {
    if (a.right != b.right) {
        // 右端点更早结束的区间先处理，便于尽早确定必须放点的位置。
        return a.right < b.right;
    }
    // 右端点相同时按左端点升序排，作为补充规则。
    return a.left < b.left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<Segment> segments(n);
    for (int i = 0; i < n; ++i) {
        cin >> segments[i].left >> segments[i].right;
    }

    // 先按右端点排序，后面才能稳定地把点放在“当前最早结束区间”的右端。
    sort(segments.begin(), segments.end(), compareByRightEnd);

    // answer 统计目前一共放了多少个点。
    int answer = 0;
    // last_point 记录上一次放置的点的位置。
    // 初始设成很小，表示还没有任何点。
    int last_point = -2000000000;

    for (const Segment& segment : segments) {
        // 如果上一次选的点不在当前区间内，就必须新放一个点。
        if (last_point < segment.left || last_point > segment.right) {
            ++answer;
            // 把点放在当前区间最右端，能尽量兼顾后面更多区间。
            last_point = segment.right;
        } else {
            // 如果 last_point 已经落在当前区间内，说明当前区间已经被覆盖，不需要新增点。
        }
    }

    cout << answer << '\n';
    return 0;
}
