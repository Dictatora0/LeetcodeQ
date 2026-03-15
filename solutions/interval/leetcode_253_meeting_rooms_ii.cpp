/*
LeetCode 253. 会议室 II (Meeting Rooms II)

题目概述 (Problem Summary)
-------------------------
给你一个会议时间安排的数组 intervals，每个会议时间都会包括开始和结束的时间 intervals[i] = [starti, endi]。
请你计算至少需要多少间会议室，才能满足这些会议安排。

关键约束 (Key Constraints)
-------------------------
- 1 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= starti < endi <= 10^6

示例 (Example)
-------------
输入：intervals = [[0,30],[5,10],[15,20]]
输出：2
解释：
- 时间 0-5：需要 1 间会议室（会议 [0,30]）
- 时间 5-10：需要 2 间会议室（会议 [0,30] 和 [5,10]）
- 时间 10-15：需要 1 间会议室（会议 [0,30]）
- 时间 15-20：需要 2 间会议室（会议 [0,30] 和 [15,20]）
- 时间 20-30：需要 1 间会议室（会议 [0,30]）
- 最多同时需要 2 间会议室

输入：intervals = [[7,10],[2,4]]
输出：1
解释：两个会议不重叠，只需要 1 间会议室

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 求同时进行的会议的最大数量
- 这个最大数量就是需要的会议室数量

关键观察：
1. 当一个会议开始时，需要分配一个会议室
2. 当一个会议结束时，释放一个会议室
3. 在任意时刻，同时进行的会议数量 = 需要的会议室数量
4. 答案 = 同时进行的会议数量的最大值

三种经典解法：
1. 最小堆（优先队列）：维护当前进行的会议的结束时间
2. 扫描线算法：处理所有开始和结束事件
3. 差分数组：统计每个时间点的会议数量变化

为什么最小堆有效？
- 堆中存储当前进行的会议的结束时间
- 堆的大小 = 当前需要的会议室数量
- 当新会议开始时，检查最早结束的会议是否已结束
- 如果已结束，可以复用该会议室；否则需要新会议室

扫描线算法的思想：
- 将每个会议的开始和结束看作事件
- 开始事件：会议室需求 +1
- 结束事件：会议室需求 -1
- 按时间顺序处理所有事件，记录最大需求

示例推演（intervals = [[0,30],[5,10],[15,20]]）：
按开始时间排序：[[0,30],[5,10],[15,20]]

使用最小堆：
- 时间 0：会议 [0,30] 开始，堆 = [30]，会议室数 = 1
- 时间 5：会议 [5,10] 开始，30 > 5（未结束），堆 = [10,30]，会议室数 = 2
- 时间 15：会议 [15,20] 开始，10 < 15（已结束），复用会议室，堆 = [20,30]，会议室数 = 2
- 最大会议室数 = 2
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

/*
方法一：最小堆（优先队列）(Approach 1: Min Heap) - 最优解法

核心思想
--------
使用最小堆维护当前进行的所有会议的结束时间。
堆的大小就是当前需要的会议室数量，记录过程中的最大值即为答案。

算法流程：
1. 按会议开始时间排序
2. 创建最小堆，存储会议的结束时间
3. 遍历每个会议：
   a. 如果堆不为空且堆顶（最早结束的会议）<= 当前会议开始时间
      - 说明有会议室空出来了，弹出堆顶
   b. 将当前会议的结束时间加入堆
   c. 更新最大会议室数量
4. 返回最大会议室数量

为什么这样做是对的？
- 堆中存储的是当前正在进行的会议的结束时间
- 堆的大小 = 当前需要的会议室数量
- 每次检查最早结束的会议，如果已结束就可以复用该会议室
- 最大堆大小 = 需要的最少会议室数量

复杂度分析
---------
时间复杂度：O(n log n)
- 排序：O(n log n)
- 遍历 n 个会议，每次堆操作 O(log n)
- 总时间：O(n log n)

空间复杂度：O(n)
- 最坏情况下，所有会议都重叠，堆的大小为 n

其中：
n = intervals.length
*/
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        // 按会议开始时间排序
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        // 最小堆，存储当前进行的会议的结束时间
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // 第一个会议需要一个会议室
        minHeap.push(intervals[0][1]);
        int maxRooms = 1;

        // 遍历剩余会议
        for (int i = 1; i < intervals.size(); i++) {
            // 如果最早结束的会议已经结束，释放该会议室
            if (!minHeap.empty() && minHeap.top() <= intervals[i][0]) {
                minHeap.pop();
            }

            // 当前会议占用一个会议室
            minHeap.push(intervals[i][1]);

            // 更新最大会议室数量
            maxRooms = max(maxRooms, (int)minHeap.size());
        }

        return maxRooms;
    }
};

/*
方法二：扫描线算法 (Approach 2: Sweep Line)

核心思想
--------
将每个会议的开始和结束看作事件，按时间顺序处理所有事件。
统计任意时刻同时进行的会议数量，取最大值。

算法流程：
1. 创建事件列表：
   - 开始事件：{时间, +1}
   - 结束事件：{时间, -1}
2. 按时间排序事件（结束事件在开始事件之前）
3. 遍历所有事件：
   - 累加事件值（+1 或 -1）
   - 记录最大值
4. 返回最大值

为什么结束事件要在开始事件之前？
- 如果一个会议在时间 t 结束，另一个会议在时间 t 开始
- 这两个会议不重叠，可以使用同一个会议室
- 所以先处理结束事件（释放会议室），再处理开始事件（占用会议室）

复杂度分析
---------
时间复杂度：O(n log n)
- 创建事件：O(n)
- 排序事件：O(n log n)
- 遍历事件：O(n)

空间复杂度：O(n)
- 存储事件：O(n)

优点：
- 思路清晰，易于理解
- 可以扩展到其他区间问题
*/
class Solution_SweepLine {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
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
        int currentRooms = 0;
        int maxRooms = 0;
        for (const auto& event : events) {
            currentRooms += event.second;
            maxRooms = max(maxRooms, currentRooms);
        }

        return maxRooms;
    }
};

/*
方法三：差分数组 (Approach 3: Difference Array)

核心思想
--------
使用差分数组记录每个时间点的会议数量变化。
然后遍历差分数组，累加得到每个时间点的会议数量，取最大值。

算法流程：
1. 使用 map 记录每个时间点的会议数量变化
   - 开始时间：+1
   - 结束时间：-1
2. 按时间顺序遍历 map：
   - 累加会议数量变化
   - 记录最大值
3. 返回最大值

复杂度分析
---------
时间复杂度：O(n log n)
- 插入 map：O(n log n)
- 遍历 map：O(n)

空间复杂度：O(n)
- map 的大小：O(n)

优点：
- 代码简洁
- 适合时间范围较小的情况

缺点：
- 使用 map，常数较大
*/
class Solution_DifferenceArray {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        // 差分数组：记录每个时间点的会议数量变化
        map<int, int> diff;
        for (const auto& interval : intervals) {
            diff[interval[0]]++;  // 开始时间 +1
            diff[interval[1]]--;  // 结束时间 -1
        }

        // 遍历差分数组，累加得到每个时间点的会议数量
        int currentRooms = 0;
        int maxRooms = 0;
        for (const auto& [time, change] : diff) {
            currentRooms += change;
            maxRooms = max(maxRooms, currentRooms);
        }

        return maxRooms;
    }
};

/*
三种方法对比 (Comparison)
------------------------
方法一：最小堆
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：直观，易于理解，效率高
- 缺点：需要理解堆的使用

方法二：扫描线算法
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：思路清晰，通用性强
- 缺点：需要创建事件列表

方法三：差分数组
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：代码简洁
- 缺点：使用 map，常数较大

推荐方案：
- 面试中：方法一（最小堆）或方法二（扫描线）
- 代码简洁：方法三（差分数组）

扫描线算法的应用场景
------------------
1. 区间重叠问题：
   - 会议室问题
   - 天际线问题
   - 区间覆盖问题

2. 核心思想：
   - 将区间的开始和结束看作事件
   - 按时间顺序处理事件
   - 维护当前状态

3. 关键技巧：
   - 事件排序：先按时间，时间相同时按类型
   - 结束事件通常在开始事件之前
   - 累加事件值，记录最大值
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：intervals = [[0,30],[5,10],[15,20]]

方法一：最小堆
------------
步骤 1：排序
intervals = [[0,30],[5,10],[15,20]]（已经有序）

步骤 2：处理会议
初始：minHeap = [], maxRooms = 0

i = 0, 会议 [0,30]：
- 堆为空，直接加入
- minHeap = [30]
- maxRooms = 1

i = 1, 会议 [5,10]：
- 堆顶 30 > 5（未结束），不能复用
- 加入 10
- minHeap = [10,30]
- maxRooms = 2

i = 2, 会议 [15,20]：
- 堆顶 10 <= 15（已结束），可以复用
- 弹出 10，加入 20
- minHeap = [20,30]
- maxRooms = 2

输出：2

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
时间 0：currentRooms = 0 + 1 = 1，maxRooms = 1
时间 5：currentRooms = 1 + 1 = 2，maxRooms = 2
时间 10：currentRooms = 2 - 1 = 1，maxRooms = 2
时间 15：currentRooms = 1 + 1 = 2，maxRooms = 2
时间 20：currentRooms = 2 - 1 = 1，maxRooms = 2
时间 30：currentRooms = 1 - 1 = 0，maxRooms = 2

输出：2

方法三：差分数组
--------------
步骤 1：构建差分数组
diff = {
    0: 1,   // [0,30] 开始
    30: -1, // [0,30] 结束
    5: 1,   // [5,10] 开始
    10: -1, // [5,10] 结束
    15: 1,  // [15,20] 开始
    20: -1  // [15,20] 结束
}

步骤 2：遍历差分数组（map 自动按 key 排序）
时间 0：currentRooms = 0 + 1 = 1，maxRooms = 1
时间 5：currentRooms = 1 + 1 = 2，maxRooms = 2
时间 10：currentRooms = 2 - 1 = 1，maxRooms = 2
时间 15：currentRooms = 1 + 1 = 2，maxRooms = 2
时间 20：currentRooms = 2 - 1 = 1，maxRooms = 2
时间 30：currentRooms = 1 - 1 = 0，maxRooms = 2

输出：2
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个会议：
   - 输入：[[1,5]]
   - 输出：1

2. 所有会议都不重叠：
   - 输入：[[1,2],[3,4],[5,6]]
   - 输出：1

3. 所有会议都重叠：
   - 输入：[[1,10],[2,10],[3,10]]
   - 输出：3

4. 会议边界相接：
   - 输入：[[1,5],[5,10]]
   - 输出：1
   - 注意：5 时刻，一个会议结束，另一个开始，可以复用会议室

5. 一个长会议包含多个短会议：
   - 输入：[[0,30],[5,10],[15,20]]
   - 输出：2

6. 多个会议同时开始：
   - 输入：[[1,5],[1,6],[1,7]]
   - 输出：3

7. 多个会议同时结束：
   - 输入：[[1,5],[2,5],[3,5]]
   - 输出：3
*/

/*
会议室问题的变体
--------------
1. 会议室 I（LeetCode 252）：
   - 问题：判断一个人是否能参加所有会议
   - 方法：排序 + 检查相邻会议是否重叠
   - 本质：判断是否存在区间重叠

2. 会议室 II（LeetCode 253）：
   - 问题：计算需要的最少会议室数量
   - 方法：最小堆 / 扫描线 / 差分数组
   - 本质：求同时进行的会议的最大数量

3. 会议室 III（LeetCode 2402）：
   - 问题：分配会议室，求使用次数最多的会议室
   - 方法：模拟 + 优先队列
   - 本质：区间调度问题

关键区别：
- I：判断是否有重叠（二值问题）
- II：求最大重叠数量（计数问题）
- III：模拟分配过程（模拟问题）
*/

int main() {
    Solution solution;
    Solution_SweepLine solutionSweep;
    Solution_DifferenceArray solutionDiff;

    // 测试用例 1：标准情况
    vector<vector<int>> intervals1 = {{0,30},{5,10},{15,20}};
    cout << "测试用例 1 - 输入: [[0,30],[5,10],[15,20]]" << endl;
    cout << "方法一（最小堆）: " << solution.minMeetingRooms(intervals1) << " (期望: 2)" << endl;
    cout << "方法二（扫描线）: " << solutionSweep.minMeetingRooms(intervals1) << " (期望: 2)" << endl;
    cout << "方法三（差分数组）: " << solutionDiff.minMeetingRooms(intervals1) << " (期望: 2)" << endl << endl;

    // 测试用例 2：无重叠
    vector<vector<int>> intervals2 = {{7,10},{2,4}};
    cout << "测试用例 2 - 输入: [[7,10],[2,4]]" << endl;
    cout << "方法一（最小堆）: " << solution.minMeetingRooms(intervals2) << " (期望: 1)" << endl << endl;

    // 测试用例 3：边界相接
    vector<vector<int>> intervals3 = {{1,5},{5,10}};
    cout << "测试用例 3 - 输入: [[1,5],[5,10]]" << endl;
    cout << "方法一（最小堆）: " << solution.minMeetingRooms(intervals3) << " (期望: 1)" << endl << endl;

    // 测试用例 4：所有会议都重叠
    vector<vector<int>> intervals4 = {{1,10},{2,10},{3,10}};
    cout << "测试用例 4 - 输入: [[1,10],[2,10],[3,10]]" << endl;
    cout << "方法一（最小堆）: " << solution.minMeetingRooms(intervals4) << " (期望: 3)" << endl << endl;

    // 测试用例 5：只有一个会议
    vector<vector<int>> intervals5 = {{1,5}};
    cout << "测试用例 5 - 输入: [[1,5]]" << endl;
    cout << "方法一（最小堆）: " << solution.minMeetingRooms(intervals5) << " (期望: 1)" << endl << endl;

    // 测试用例 6：多个会议同时开始
    vector<vector<int>> intervals6 = {{1,5},{1,6},{1,7}};
    cout << "测试用例 6 - 输入: [[1,5],[1,6],[1,7]]" << endl;
    cout << "方法二（扫描线）: " << solutionSweep.minMeetingRooms(intervals6) << " (期望: 3)" << endl << endl;

    // 测试用例 7：复杂情况
    vector<vector<int>> intervals7 = {{1,3},{2,6},{8,10},{9,11},{10,12}};
    cout << "测试用例 7 - 输入: [[1,3],[2,6],[8,10],[9,11],[10,12]]" << endl;
    cout << "方法三（差分数组）: " << solutionDiff.minMeetingRooms(intervals7) << " (期望: 2)" << endl;

    return 0;
}
