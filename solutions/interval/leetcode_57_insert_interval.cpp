/*
LeetCode 57. 插入区间 (Insert Interval)

题目概述 (Problem Summary)
-------------------------
给你一个无重叠的、按照区间起始端点排序的区间列表 intervals，在列表中插入一个新的区间 newInterval。
插入之后，intervals 仍然有序且无重叠（如果有必要的话，可以合并区间）。

关键约束 (Key Constraints)
-------------------------
- 0 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= starti <= endi <= 10^5
- intervals 根据 starti 按升序排列
- newInterval.length == 2
- 0 <= start <= end <= 10^5

示例 (Example)
-------------
输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]

输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：新区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在已排序的区间列表中插入新区间并合并
- 关键是利用已排序的性质，不需要重新排序

关键观察：
1. intervals 已经按起点排序，这是重要条件
2. 新区间可能与多个已有区间重叠
3. 可以将所有区间分为三部分：
   - 左边：完全在 newInterval 左边的区间（不重叠）
   - 中间：与 newInterval 重叠的区间（需要合并）
   - 右边：完全在 newInterval 右边的区间（不重叠）

如何判断区间位置关系？
设当前区间为 [a, b]，新区间为 [start, end]：
- 在左边（不重叠）：b < start
- 在右边（不重叠）：a > end
- 重叠：!(b < start) && !(a > end)，即 b >= start && a <= end

三段处理的思路：
1. 左段：将所有终点 < newInterval.start 的区间直接加入结果
2. 中段：将所有与 newInterval 重叠的区间合并成一个大区间
3. 右段：将所有起点 > newInterval.end 的区间直接加入结果

为什么不需要排序？
- intervals 已经有序
- 只需要一次遍历，按顺序处理三段即可
- 时间复杂度 O(n)，比先插入再排序的 O(n log n) 更优

处理过程示例（intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]）：
左段：[1,2]（2 < 4，不重叠）
中段：[3,5],[6,7],[8,10]（都与 [4,8] 重叠）
  - 合并起点：min(3, 4) = 3
  - 合并终点：max(10, 8) = 10
  - 合并结果：[3,10]
右段：[12,16]（12 > 8，不重叠）
最终结果：[[1,2],[3,10],[12,16]]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：三段处理 (Approach 1: Three-Part Processing) - 最优解法

核心思想
--------
将所有区间分为三部分处理：左边不重叠、中间重叠需合并、右边不重叠。
利用已排序的性质，一次遍历完成。

算法流程：
1. 第一段：遍历所有终点 < newInterval.start 的区间，直接加入结果
2. 第二段：遍历所有与 newInterval 重叠的区间
   - 更新合并区间的起点：min(newInterval.start, 当前区间起点)
   - 更新合并区间的终点：max(newInterval.end, 当前区间终点)
3. 将合并后的区间加入结果
4. 第三段：将剩余区间（起点 > newInterval.end）直接加入结果

为什么这样做是对的？
- intervals 已排序，所以三段是连续的
- 第一段的区间一定不会与 newInterval 重叠
- 第二段的区间一定会与 newInterval 重叠
- 第三段的区间一定不会与 newInterval 重叠

复杂度分析
---------
时间复杂度：O(n)
- 只需要一次遍历所有区间
- 每个区间只处理一次

空间复杂度：O(1)
- 只使用常数额外空间（结果数组不计入）

其中：
n = intervals.length

优势：
- 利用已排序的性质，不需要重新排序
- 一次遍历，效率最高
*/
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        int n = intervals.size();

        // 第一段：添加所有在 newInterval 左边的区间
        // 条件：当前区间的终点 < newInterval 的起点
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            i++;
        }

        // 第二段：合并所有与 newInterval 重叠的区间
        // 条件：当前区间的起点 <= newInterval 的终点
        while (i < n && intervals[i][0] <= newInterval[1]) {
            // 更新合并区间的起点和终点
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        // 将合并后的区间加入结果
        result.push_back(newInterval);

        // 第三段：添加所有在 newInterval 右边的区间
        // 剩余的区间都在右边，直接加入
        while (i < n) {
            result.push_back(intervals[i]);
            i++;
        }

        return result;
    }
};

/*
方法二：先插入再合并 (Approach 2: Insert Then Merge)

核心思想
--------
先将 newInterval 插入到正确的位置，然后使用合并区间的算法合并所有重叠的区间。

算法流程：
1. 找到 newInterval 应该插入的位置（保持有序）
2. 将 newInterval 插入到该位置
3. 使用合并区间的算法（LeetCode 56）合并所有重叠的区间

复杂度分析
---------
时间复杂度：O(n)
- 找到插入位置：O(n)（最坏情况）
- 插入：O(n)（需要移动元素）
- 合并：O(n)
- 总时间：O(n)

空间复杂度：O(1)
- 不计结果数组

对比方法一：
- 方法一更简洁，直接三段处理
- 方法二思路更直观，但代码稍复杂
*/
class Solution_InsertThenMerge {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // 找到插入位置并插入
        auto it = intervals.begin();
        while (it != intervals.end() && (*it)[0] < newInterval[0]) {
            it++;
        }
        intervals.insert(it, newInterval);

        // 合并重叠区间（与 LeetCode 56 相同）
        vector<vector<int>> result;
        result.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            vector<int>& last = result.back();
            if (intervals[i][0] <= last[1]) {
                last[1] = max(last[1], intervals[i][1]);
            } else {
                result.push_back(intervals[i]);
            }
        }

        return result;
    }
};

/*
两种方法对比 (Comparison)
------------------------
方法一：三段处理
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：一次遍历，效率最高，代码简洁
- 缺点：需要理解三段处理的思路

方法二：先插入再合并
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：思路直观，复用合并区间的代码
- 缺点：需要修改原数组，代码稍复杂

推荐方案：
- 面试中：方法一（更优雅）
- 学习理解：方法二（更直观）

关键技巧
--------
1. 利用已排序的性质：
   - 不需要重新排序
   - 可以一次遍历完成

2. 三段处理的判断条件：
   - 左段：intervals[i][1] < newInterval[0]
   - 中段：intervals[i][0] <= newInterval[1]
   - 右段：剩余的所有区间

3. 合并时的更新：
   - 起点：min(newInterval[0], intervals[i][0])
   - 终点：max(newInterval[1], intervals[i][1])
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]

方法一：三段处理
--------------
初始：result = [], i = 0, newInterval = [4,8]

第一段：添加左边不重叠的区间
i = 0, [1,2]：2 < 4，加入结果
- result = [[1,2]], i = 1

i = 1, [3,5]：5 >= 4，不满足条件，退出第一段

第二段：合并重叠的区间
i = 1, [3,5]：3 <= 8，重叠
- newInterval[0] = min(4, 3) = 3
- newInterval[1] = max(8, 5) = 8
- newInterval = [3,8], i = 2

i = 2, [6,7]：6 <= 8，重叠
- newInterval[0] = min(3, 6) = 3
- newInterval[1] = max(8, 7) = 8
- newInterval = [3,8], i = 3

i = 3, [8,10]：8 <= 8，重叠
- newInterval[0] = min(3, 8) = 3
- newInterval[1] = max(8, 10) = 10
- newInterval = [3,10], i = 4

i = 4, [12,16]：12 > 10，不满足条件，退出第二段
加入合并后的区间：result = [[1,2],[3,10]]

第三段：添加右边不重叠的区间
i = 4, [12,16]：直接加入
- result = [[1,2],[3,10],[12,16]], i = 5

输出：[[1,2],[3,10],[12,16]]

边界情况示例：newInterval 完全在左边
------------------------------------
输入：intervals = [[3,5],[6,9]], newInterval = [1,2]

第一段：无区间满足条件（3 > 2）
第二段：无区间满足条件（3 > 2）
- 直接加入 newInterval = [1,2]
第三段：[3,5],[6,9] 都加入

输出：[[1,2],[3,5],[6,9]]

边界情况示例：newInterval 完全在右边
------------------------------------
输入：intervals = [[1,2],[3,5]], newInterval = [6,8]

第一段：[1,2],[3,5] 都满足条件（2 < 6, 5 < 6）
- result = [[1,2],[3,5]]
第二段：无区间满足条件
- 加入 newInterval = [6,8]
第三段：无剩余区间

输出：[[1,2],[3,5],[6,8]]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. intervals 为空：
   - 输入：intervals = [], newInterval = [5,7]
   - 输出：[[5,7]]

2. newInterval 在最左边：
   - 输入：intervals = [[3,5],[6,9]], newInterval = [1,2]
   - 输出：[[1,2],[3,5],[6,9]]

3. newInterval 在最右边：
   - 输入：intervals = [[1,2],[3,5]], newInterval = [6,8]
   - 输出：[[1,2],[3,5],[6,8]]

4. newInterval 与所有区间重叠：
   - 输入：intervals = [[1,2],[3,5],[6,7]], newInterval = [0,8]
   - 输出：[[0,8]]

5. newInterval 完全包含在某个区间中：
   - 输入：intervals = [[1,5]], newInterval = [2,3]
   - 输出：[[1,5]]

6. newInterval 完全包含某些区间：
   - 输入：intervals = [[2,3],[4,5],[6,7]], newInterval = [1,8]
   - 输出：[[1,8]]

7. newInterval 与一个区间边界相接：
   - 输入：intervals = [[1,3],[6,9]], newInterval = [3,5]
   - 输出：[[1,5],[6,9]]

8. 只有一个区间且重叠：
   - 输入：intervals = [[1,5]], newInterval = [2,7]
   - 输出：[[1,7]]
*/

/*
区间插入问题的关键点
------------------
1. 利用已排序的性质：
   - 不需要重新排序
   - 可以线性时间完成

2. 三段处理的本质：
   - 左段：不受影响的区间
   - 中段：需要合并的区间
   - 右段：不受影响的区间

3. 重叠判断：
   - 不重叠（左边）：intervals[i][1] < newInterval[0]
   - 不重叠（右边）：intervals[i][0] > newInterval[1]
   - 重叠：其他情况

4. 合并技巧：
   - 不断更新 newInterval 的边界
   - 最后一次性加入结果

5. 与 LeetCode 56 的区别：
   - 56 需要排序，时间 O(n log n)
   - 57 已排序，时间 O(n)
   - 57 是 56 的优化版本
*/

int main() {
    Solution solution;
    Solution_InsertThenMerge solutionInsert;

    // 测试用例 1：标准情况
    vector<vector<int>> intervals1 = {{1,3},{6,9}};
    vector<int> newInterval1 = {2,5};
    cout << "测试用例 1 - 输入: [[1,3],[6,9]], newInterval = [2,5]" << endl;
    auto result1 = solution.insert(intervals1, newInterval1);
    cout << "方法一（三段处理）: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,5],[6,9]])" << endl << endl;

    // 测试用例 2：与多个区间重叠
    vector<vector<int>> intervals2 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    vector<int> newInterval2 = {4,8};
    cout << "测试用例 2 - 输入: [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]" << endl;
    auto result2 = solution.insert(intervals2, newInterval2);
    cout << "方法一（三段处理）: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << "[" << result2[i][0] << "," << result2[i][1] << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,2],[3,10],[12,16]])" << endl << endl;

    // 测试用例 3：newInterval 在最左边
    vector<vector<int>> intervals3 = {{3,5},{6,9}};
    vector<int> newInterval3 = {1,2};
    cout << "测试用例 3 - 输入: [[3,5],[6,9]], newInterval = [1,2]" << endl;
    auto result3 = solution.insert(intervals3, newInterval3);
    cout << "方法一（三段处理）: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << "[" << result3[i][0] << "," << result3[i][1] << "]";
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,2],[3,5],[6,9]])" << endl << endl;

    // 测试用例 4：newInterval 在最右边
    vector<vector<int>> intervals4 = {{1,2},{3,5}};
    vector<int> newInterval4 = {6,8};
    cout << "测试用例 4 - 输入: [[1,2],[3,5]], newInterval = [6,8]" << endl;
    auto result4 = solution.insert(intervals4, newInterval4);
    cout << "方法一（三段处理）: [";
    for (int i = 0; i < result4.size(); i++) {
        cout << "[" << result4[i][0] << "," << result4[i][1] << "]";
        if (i < result4.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,2],[3,5],[6,8]])" << endl << endl;

    // 测试用例 5：intervals 为空
    vector<vector<int>> intervals5 = {};
    vector<int> newInterval5 = {5,7};
    cout << "测试用例 5 - 输入: [], newInterval = [5,7]" << endl;
    auto result5 = solution.insert(intervals5, newInterval5);
    cout << "方法一（三段处理）: [";
    for (int i = 0; i < result5.size(); i++) {
        cout << "[" << result5[i][0] << "," << result5[i][1] << "]";
        if (i < result5.size() - 1) cout << ",";
    }
    cout << "] (期望: [[5,7]])" << endl << endl;

    // 测试用例 6：newInterval 完全包含某些区间
    vector<vector<int>> intervals6 = {{2,3},{4,5},{6,7}};
    vector<int> newInterval6 = {1,8};
    cout << "测试用例 6 - 输入: [[2,3],[4,5],[6,7]], newInterval = [1,8]" << endl;
    auto result6 = solutionInsert.insert(intervals6, newInterval6);
    cout << "方法二（插入后合并）: [";
    for (int i = 0; i < result6.size(); i++) {
        cout << "[" << result6[i][0] << "," << result6[i][1] << "]";
        if (i < result6.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,8]])" << endl;

    return 0;
}
