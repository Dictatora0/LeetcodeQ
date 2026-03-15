/*
LeetCode 252. 会议室 (Meeting Rooms)

题目概述 (Problem Summary)
-------------------------
给定一个会议时间安排的数组 intervals，每个会议时间都会包括开始和结束的时间 intervals[i] = [starti, endi]。
请你判断一个人是否能够参加这里面的全部会议。

关键约束 (Key Constraints)
-------------------------
- 0 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= starti < endi <= 10^6

示例 (Example)
-------------
输入：intervals = [[0,30],[5,10],[15,20]]
输出：false
解释：会议 [0,30] 与 [5,10] 和 [15,20] 都有重叠

输入：intervals = [[7,10],[2,4]]
输出：true
解释：两个会议没有重叠

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 判断是否存在区间重叠
- 如果任意两个会议时间重叠，就无法参加所有会议

关键观察：
1. 一个人同一时间只能参加一个会议
2. 只要有任意两个会议时间重叠，就返回 false
3. 所有会议都不重叠，才返回 true

什么是会议时间重叠？
- 会议 A = [a1, a2]，会议 B = [b1, b2]
- 如果 max(a1, b1) < min(a2, b2)，则重叠
- 排序后更简单：如果 b1 < a2，则重叠（假设 a1 <= b1）

为什么要排序？
- 排序后，只需要检查相邻的会议是否重叠
- 如果相邻的会议都不重叠，那么所有会议都不重叠
- 不排序的话，需要两两比较，复杂度 O(n²)

排序后的判断逻辑：
- 按起始时间排序
- 检查每个会议的起始时间是否 < 前一个会议的结束时间
- 如果是，说明重叠，返回 false

示例推演（intervals = [[0,30],[5,10],[15,20]]）：
排序后：[[0,30],[5,10],[15,20]]

检查 [5,10] 和 [0,30]：
- 5 < 30（重叠）
- 返回 false

示例推演（intervals = [[7,10],[2,4]]）：
排序后：[[2,4],[7,10]]

检查 [7,10] 和 [2,4]：
- 7 >= 4（不重叠）
- 继续检查，没有更多会议
- 返回 true
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：排序 + 检查重叠 (Approach 1: Sort + Check Overlap) - 最优解法

核心思想
--------
先按会议开始时间排序，然后检查相邻的会议是否重叠。
如果任意相邻会议重叠，返回 false；否则返回 true。

算法流程：
1. 按会议开始时间对所有会议排序
2. 遍历排序后的会议：
   - 检查当前会议的开始时间是否 < 前一个会议的结束时间
   - 如果是，说明重叠，返回 false
3. 如果遍历完都没有重叠，返回 true

为什么只需要检查相邻会议？
- 排序后，如果会议 i 和会议 j 重叠（i < j），那么会议 i 一定和会议 i+1 到 j 之间的某个会议重叠
- 所以只需要检查相邻会议即可

复杂度分析
---------
时间复杂度：O(n log n)
- 排序：O(n log n)
- 遍历：O(n)
- 总时间：O(n log n)

空间复杂度：O(log n)
- 排序的递归栈空间

其中：
n = intervals.length
*/
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        // 边界情况：没有会议或只有一个会议
        if (intervals.size() <= 1) {
            return true;
        }

        // 按会议开始时间排序
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        // 检查相邻会议是否重叠
        for (int i = 1; i < intervals.size(); i++) {
            // 如果当前会议的开始时间 < 前一个会议的结束时间，说明重叠
            if (intervals[i][0] < intervals[i-1][1]) {
                return false;
            }
        }

        // 所有会议都不重叠
        return true;
    }
};

/*
方法二：扫描线算法 (Approach 2: Sweep Line)

核心思想
--------
将每个会议的开始和结束时间看作事件，按时间顺序处理所有事件。
如果在任意时刻有超过 1 个会议在进行，返回 false。

算法流程：
1. 将所有会议的开始和结束时间提取出来，标记为开始事件和结束事件
2. 按时间排序所有事件（开始事件在前，结束事件在后）
3. 遍历所有事件：
   - 遇到开始事件，当前会议数 +1
   - 遇到结束事件，当前会议数 -1
   - 如果当前会议数 > 1，说明有重叠，返回 false
4. 如果遍历完都没有超过 1 个会议，返回 true

为什么结束事件要在开始事件之后？
- 如果一个会议在时间 t 结束，另一个会议在时间 t 开始，这不算重叠
- 所以相同时间的结束事件要在开始事件之前处理

复杂度分析
---------
时间复杂度：O(n log n)
- 创建事件：O(n)
- 排序事件：O(n log n)
- 遍历事件：O(n)
- 总时间：O(n log n)

空间复杂度：O(n)
- 存储事件：O(n)

对比方法一：
- 方法一更简洁，代码更短
- 方法二更通用，可以扩展到会议室 II（需要多少个会议室）
*/
class Solution_SweepLine {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1) {
            return true;
        }

        // 创建事件列表：{时间, 类型}，类型 1 表示开始，-1 表示结束
        vector<pair<int, int>> events;
        for (const auto& interval : intervals) {
            events.push_back({interval[0], 1});   // 开始事件
            events.push_back({interval[1], -1});  // 结束事件
        }

        // 排序事件：先按时间，时间相同时结束事件在前
        sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) {
                return a.second < b.second;  // 结束事件（-1）在开始事件（1）之前
            }
            return a.first < b.first;
        });

        // 遍历事件，统计当前进行的会议数
        int ongoingMeetings = 0;
        for (const auto& event : events) {
            ongoingMeetings += event.second;
            // 如果当前有超过 1 个会议在进行，说明有重叠
            if (ongoingMeetings > 1) {
                return false;
            }
        }

        return true;
    }
};

/*
两种方法对比 (Comparison)
------------------------
方法一：排序 + 检查重叠
- 时间复杂度：O(n log n)
- 空间复杂度：O(log n)
- 优点：代码简洁，易于理解
- 缺点：只能判断是否有重叠，不能扩展到其他问题

方法二：扫描线算法
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：思路通用，可以扩展到会议室 II
- 缺点：代码稍复杂，空间复杂度稍高

推荐方案：
- 面试中：方法一（更简洁）
- 需要扩展：方法二（更通用）

区间重叠判断总结
--------------
对于两个区间 A = [a1, a2] 和 B = [b1, b2]：

1. 通用判断（不需要排序）：
   - 重叠：max(a1, b1) < min(a2, b2)
   - 不重叠：max(a1, b1) >= min(a2, b2)

2. 排序后判断（假设 a1 <= b1）：
   - 重叠：b1 < a2
   - 不重叠：b1 >= a2

3. 边界情况：
   - [1,5] 和 [5,10]：5 >= 5，不重叠（题目说明 starti < endi）
   - [1,5] 和 [4,10]：4 < 5，重叠
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：intervals = [[0,30],[5,10],[15,20]]

方法一：排序 + 检查重叠
---------------------
步骤 1：排序
intervals = [[0,30],[5,10],[15,20]]（已经有序）

步骤 2：检查相邻会议
i = 1, 当前会议 [5,10]，前一个会议 [0,30]：
- 5 < 30（重叠）
- 返回 false

输出：false

方法二：扫描线算法
----------------
步骤 1：创建事件
events = [
    {0, 1},   // [0,30] 开始
    {30, -1}, // [0,30] 结束
    {5, 1},   // [5,10] 开始
    {10, -1}, // [5,10] 结束
    {15, 1},  // [15,20] 开始
    {20, -1}  // [15,20] 结束
]

步骤 2：排序事件
events = [
    {0, 1},   // 时间 0，开始
    {5, 1},   // 时间 5，开始
    {10, -1}, // 时间 10，结束
    {15, 1},  // 时间 15，开始
    {20, -1}, // 时间 20，结束
    {30, -1}  // 时间 30，结束
]

步骤 3：遍历事件
时间 0：ongoingMeetings = 0 + 1 = 1
时间 5：ongoingMeetings = 1 + 1 = 2（超过 1，返回 false）

输出：false

示例 2：intervals = [[7,10],[2,4]]
---------------------------------
方法一：排序 + 检查重叠

排序后：[[2,4],[7,10]]

检查 [7,10] 和 [2,4]：
- 7 >= 4（不重叠）
- 返回 true

输出：true
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 没有会议：
   - 输入：[]
   - 输出：true

2. 只有一个会议：
   - 输入：[[1,5]]
   - 输出：true

3. 两个会议边界相接：
   - 输入：[[1,5],[5,10]]
   - 输出：true
   - 注意：5 >= 5，不算重叠

4. 两个会议完全重叠：
   - 输入：[[1,10],[2,8]]
   - 输出：false

5. 多个会议连续不重叠：
   - 输入：[[1,2],[2,3],[3,4]]
   - 输出：true

6. 一个会议包含另一个：
   - 输入：[[1,10],[3,5]]
   - 输出：false

7. 会议时间相同：
   - 输入：[[1,5],[1,5]]
   - 输出：false
*/

/*
会议室问题系列总结
----------------
LeetCode 252：会议室
- 问题：判断一个人是否能参加所有会议
- 方法：排序 + 检查相邻会议是否重叠
- 复杂度：O(n log n)

LeetCode 253：会议室 II
- 问题：计算需要的最少会议室数量
- 方法：扫描线算法 / 最小堆
- 复杂度：O(n log n)

LeetCode 56：合并区间
- 问题：合并所有重叠的区间
- 方法：排序 + 合并
- 复杂度：O(n log n)

LeetCode 57：插入区间
- 问题：在已排序的区间列表中插入新区间
- 方法：三段处理
- 复杂度：O(n)

LeetCode 435：无重叠区间
- 问题：移除最少的区间，使剩余区间不重叠
- 方法：贪心（按结束时间排序）
- 复杂度：O(n log n)

关键技巧：
1. 排序：按起点或终点排序
2. 扫描线：处理开始和结束事件
3. 贪心：选择结束时间最早的区间
4. 堆：维护当前进行的会议
*/

int main() {
    Solution solution;
    Solution_SweepLine solutionSweep;

    // 测试用例 1：有重叠
    vector<vector<int>> intervals1 = {{0,30},{5,10},{15,20}};
    cout << "测试用例 1 - 输入: [[0,30],[5,10],[15,20]]" << endl;
    cout << "方法一（排序+检查）: " << (solution.canAttendMeetings(intervals1) ? "true" : "false")
         << " (期望: false)" << endl;
    cout << "方法二（扫描线）: " << (solutionSweep.canAttendMeetings(intervals1) ? "true" : "false")
         << " (期望: false)" << endl << endl;

    // 测试用例 2：无重叠
    vector<vector<int>> intervals2 = {{7,10},{2,4}};
    cout << "测试用例 2 - 输入: [[7,10],[2,4]]" << endl;
    cout << "方法一（排序+检查）: " << (solution.canAttendMeetings(intervals2) ? "true" : "false")
         << " (期望: true)" << endl << endl;

    // 测试用例 3：边界相接
    vector<vector<int>> intervals3 = {{1,5},{5,10}};
    cout << "测试用例 3 - 输入: [[1,5],[5,10]]" << endl;
    cout << "方法一（排序+检查）: " << (solution.canAttendMeetings(intervals3) ? "true" : "false")
         << " (期望: true)" << endl << endl;

    // 测试用例 4：完全包含
    vector<vector<int>> intervals4 = {{1,10},{3,5}};
    cout << "测试用例 4 - 输入: [[1,10],[3,5]]" << endl;
    cout << "方法一（排序+检查）: " << (solution.canAttendMeetings(intervals4) ? "true" : "false")
         << " (期望: false)" << endl << endl;

    // 测试用例 5：空数组
    vector<vector<int>> intervals5 = {};
    cout << "测试用例 5 - 输入: []" << endl;
    cout << "方法一（排序+检查）: " << (solution.canAttendMeetings(intervals5) ? "true" : "false")
         << " (期望: true)" << endl << endl;

    // 测试用例 6：只有一个会议
    vector<vector<int>> intervals6 = {{1,5}};
    cout << "测试用例 6 - 输入: [[1,5]]" << endl;
    cout << "方法一（排序+检查）: " << (solution.canAttendMeetings(intervals6) ? "true" : "false")
         << " (期望: true)" << endl << endl;

    // 测试用例 7：多个会议连续不重叠
    vector<vector<int>> intervals7 = {{1,2},{2,3},{3,4}};
    cout << "测试用例 7 - 输入: [[1,2],[2,3],[3,4]]" << endl;
    cout << "方法二（扫描线）: " << (solutionSweep.canAttendMeetings(intervals7) ? "true" : "false")
         << " (期望: true)" << endl;

    return 0;
}
