/*
LeetCode 56. 合并区间 (Merge Intervals)

题目概述 (Problem Summary)
-------------------------
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi]。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

关键约束 (Key Constraints)
-------------------------
- 1 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= starti <= endi <= 10^4

示例 (Example)
-------------
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠，将它们合并为 [1,6]

输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 区间合并问题：将所有重叠的区间合并成一个区间
- 核心是判断两个区间是否重叠，以及如何合并

关键观察：
1. 无序的区间很难判断重叠关系
2. 如果按起点排序，相邻的区间更容易判断是否重叠
3. 排序后，只需要和当前合并的最后一个区间比较

什么是区间重叠？
- 区间 A = [a1, a2]，区间 B = [b1, b2]
- 如果 a1 <= b1 <= a2，则 A 和 B 重叠
- 排序后，只需判断：当前区间的起点 <= 上一个区间的终点

如何合并区间？
- 如果重叠：合并后的终点 = max(区间A的终点, 区间B的终点)
- 如果不重叠：直接将当前区间加入结果

为什么要排序？
- 排序后，只需要和结果中的最后一个区间比较
- 不排序的话，需要两两比较所有区间，复杂度 O(n²)

区间合并的变化过程示例（intervals = [[1,3],[2,6],[8,10],[15,18]]）：
排序后：[[1,3],[2,6],[8,10],[15,18]]

初始：result = []
处理 [1,3]：result = [[1,3]]
处理 [2,6]：2 <= 3（重叠），合并为 [1,6]，result = [[1,6]]
处理 [8,10]：8 > 6（不重叠），直接加入，result = [[1,6],[8,10]]
处理 [15,18]：15 > 10（不重叠），直接加入，result = [[1,6],[8,10],[15,18]]

区间问题的通用模板
-----------------
1. 排序：按起点或终点排序
2. 遍历：逐个处理区间
3. 判断：当前区间与结果中最后一个区间的关系
4. 合并或添加：根据判断结果进行操作
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：排序 + 一次遍历 (Approach 1: Sort + One Pass) - 最优解法

核心思想
--------
先按区间起点排序，然后遍历所有区间，判断当前区间是否与结果中的最后一个区间重叠。
如果重叠则合并，否则直接加入结果。

算法流程：
1. 按区间起点对所有区间排序
2. 将第一个区间加入结果
3. 遍历剩余区间：
   a. 如果当前区间的起点 <= 结果中最后一个区间的终点（重叠）
      - 更新最后一个区间的终点为 max(当前终点, 最后区间终点)
   b. 否则（不重叠）
      - 将当前区间直接加入结果
4. 返回结果

为什么这样做是对的？
- 排序后，如果区间 i 和区间 j 重叠（i < j），那么区间 i 一定和区间 i+1 到 j 之间的所有区间重叠
- 所以只需要维护当前合并的区间，不断更新其终点即可

复杂度分析
---------
时间复杂度：O(n log n)
- 排序：O(n log n)
- 遍历：O(n)
- 总时间：O(n log n)

空间复杂度：O(log n)
- 排序的递归栈空间：O(log n)
- 结果数组不计入空间复杂度

其中：
n = intervals.length
*/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 边界情况：空数组或只有一个区间
        if (intervals.empty()) {
            return {};
        }

        // 按区间起点排序
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        vector<vector<int>> result;
        // 将第一个区间加入结果
        result.push_back(intervals[0]);

        // 遍历剩余区间
        for (int i = 1; i < intervals.size(); i++) {
            // 获取结果中最后一个区间的引用（方便修改）
            vector<int>& last = result.back();

            // 判断当前区间是否与最后一个区间重叠
            if (intervals[i][0] <= last[1]) {
                // 重叠：更新最后一个区间的终点
                // 注意：需要取 max，因为当前区间可能完全包含在最后一个区间中
                last[1] = max(last[1], intervals[i][1]);
            } else {
                // 不重叠：直接加入当前区间
                result.push_back(intervals[i]);
            }
        }

        return result;
    }
};

/*
方法二：排序 + 栈 (Approach 2: Sort + Stack)

核心思想
--------
使用栈来维护当前合并的区间，栈顶始终是当前正在合并的区间。

算法流程：
1. 按区间起点排序
2. 将第一个区间入栈
3. 遍历剩余区间：
   a. 如果当前区间与栈顶区间重叠，弹出栈顶，合并后重新入栈
   b. 否则，直接将当前区间入栈
4. 栈中的所有区间就是结果

复杂度分析
---------
时间复杂度：O(n log n)
- 排序：O(n log n)
- 遍历：O(n)

空间复杂度：O(n)
- 栈的空间：O(n)

对比方法一：
- 方法一更简洁，直接用数组维护结果
- 方法二用栈，概念上更清晰，但空间复杂度稍高
*/
class Solution_Stack {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        // 按区间起点排序
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        // 使用 vector 模拟栈
        vector<vector<int>> stack;
        stack.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            vector<int> top = stack.back();

            if (intervals[i][0] <= top[1]) {
                // 重叠：弹出栈顶，合并后重新入栈
                stack.pop_back();
                top[1] = max(top[1], intervals[i][1]);
                stack.push_back(top);
            } else {
                // 不重叠：直接入栈
                stack.push_back(intervals[i]);
            }
        }

        return stack;
    }
};

/*
两种方法对比 (Comparison)
------------------------
方法一：排序 + 一次遍历
- 时间复杂度：O(n log n)
- 空间复杂度：O(log n)
- 优点：代码简洁，空间效率高
- 缺点：无

方法二：排序 + 栈
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：概念清晰，易于理解
- 缺点：空间复杂度稍高

推荐方案：
- 面试中：方法一（更优）
- 学习理解：方法二（更直观）

区间重叠的判断条件总结
--------------------
对于排序后的区间 A = [a1, a2] 和 B = [b1, b2]（a1 <= b1）：
- 重叠：b1 <= a2
- 不重叠：b1 > a2

注意边界情况：
- [1,4] 和 [4,5]：4 <= 4，算重叠
- [1,3] 和 [4,5]：4 > 3，不重叠
*/

/*
示例推演 (Example Walkthrough)
-----------------------------
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]

方法一：排序 + 一次遍历
---------------------
步骤 1：排序
intervals = [[1,3],[2,6],[8,10],[15,18]]（已经有序）

步骤 2：初始化
result = [[1,3]]

步骤 3：遍历处理
i = 1, 当前区间 [2,6]：
- last = [1,3]
- 2 <= 3（重叠）
- 更新 last[1] = max(3, 6) = 6
- result = [[1,6]]

i = 2, 当前区间 [8,10]：
- last = [1,6]
- 8 > 6（不重叠）
- 加入 [8,10]
- result = [[1,6],[8,10]]

i = 3, 当前区间 [15,18]：
- last = [8,10]
- 15 > 10（不重叠）
- 加入 [15,18]
- result = [[1,6],[8,10],[15,18]]

输出：[[1,6],[8,10],[15,18]]

复杂示例：intervals = [[1,4],[2,3]]
----------------------------------
排序后：[[1,4],[2,3]]

初始：result = [[1,4]]
处理 [2,3]：
- 2 <= 4（重叠）
- 更新 last[1] = max(4, 3) = 4
- result = [[1,4]]

注意：[2,3] 完全包含在 [1,4] 中，所以合并后还是 [1,4]
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个区间：
   - 输入：[[1,3]]
   - 输出：[[1,3]]

2. 所有区间都重叠：
   - 输入：[[1,4],[2,5],[3,6]]
   - 输出：[[1,6]]

3. 所有区间都不重叠：
   - 输入：[[1,2],[3,4],[5,6]]
   - 输出：[[1,2],[3,4],[5,6]]

4. 区间完全包含：
   - 输入：[[1,5],[2,3]]
   - 输出：[[1,5]]

5. 区间边界相接：
   - 输入：[[1,4],[4,5]]
   - 输出：[[1,5]]
   - 注意：题目说明 [1,4] 和 [4,5] 算重叠

6. 区间无序：
   - 输入：[[2,6],[1,3],[8,10]]
   - 排序后：[[1,3],[2,6],[8,10]]
   - 输出：[[1,6],[8,10]]

7. 起点相同：
   - 输入：[[1,4],[1,5]]
   - 输出：[[1,5]]
*/

/*
区间问题的关键技巧
----------------
1. 排序策略：
   - 按起点排序：适合合并区间、插入区间
   - 按终点排序：适合无重叠区间（贪心）
   - 按长度排序：适合特殊问题

2. 重叠判断：
   - 排序后：当前起点 <= 上一个终点
   - 未排序：max(a1, b1) <= min(a2, b2)

3. 合并技巧：
   - 更新终点：max(当前终点, 上一个终点)
   - 不要忘记处理完全包含的情况

4. 边界处理：
   - 空数组
   - 单个区间
   - 边界相接算不算重叠（看题目要求）
*/

int main() {
    Solution solution;
    Solution_Stack solutionStack;

    // 测试用例 1：标准情况
    vector<vector<int>> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    cout << "测试用例 1 - 输入: [[1,3],[2,6],[8,10],[15,18]]" << endl;
    auto result1 = solution.merge(intervals1);
    cout << "方法一（排序+遍历）: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,6],[8,10],[15,18]])" << endl << endl;

    // 测试用例 2：边界相接
    vector<vector<int>> intervals2 = {{1,4},{4,5}};
    cout << "测试用例 2 - 输入: [[1,4],[4,5]]" << endl;
    auto result2 = solution.merge(intervals2);
    cout << "方法一（排序+遍历）: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << "[" << result2[i][0] << "," << result2[i][1] << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,5]])" << endl << endl;

    // 测试用例 3：完全包含
    vector<vector<int>> intervals3 = {{1,5},{2,3}};
    cout << "测试用例 3 - 输入: [[1,5],[2,3]]" << endl;
    auto result3 = solution.merge(intervals3);
    cout << "方法一（排序+遍历）: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << "[" << result3[i][0] << "," << result3[i][1] << "]";
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,5]])" << endl << endl;

    // 测试用例 4：所有区间都不重叠
    vector<vector<int>> intervals4 = {{1,2},{3,4},{5,6}};
    cout << "测试用例 4 - 输入: [[1,2],[3,4],[5,6]]" << endl;
    auto result4 = solution.merge(intervals4);
    cout << "方法一（排序+遍历）: [";
    for (int i = 0; i < result4.size(); i++) {
        cout << "[" << result4[i][0] << "," << result4[i][1] << "]";
        if (i < result4.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,2],[3,4],[5,6]])" << endl << endl;

    // 测试用例 5：所有区间都重叠
    vector<vector<int>> intervals5 = {{1,4},{2,5},{3,6}};
    cout << "测试用例 5 - 输入: [[1,4],[2,5],[3,6]]" << endl;
    auto result5 = solution.merge(intervals5);
    cout << "方法一（排序+遍历）: [";
    for (int i = 0; i < result5.size(); i++) {
        cout << "[" << result5[i][0] << "," << result5[i][1] << "]";
        if (i < result5.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,6]])" << endl << endl;

    // 测试用例 6：无序区间
    vector<vector<int>> intervals6 = {{2,6},{1,3},{8,10}};
    cout << "测试用例 6 - 输入: [[2,6],[1,3],[8,10]]" << endl;
    auto result6 = solutionStack.merge(intervals6);
    cout << "方法二（排序+栈）: [";
    for (int i = 0; i < result6.size(); i++) {
        cout << "[" << result6[i][0] << "," << result6[i][1] << "]";
        if (i < result6.size() - 1) cout << ",";
    }
    cout << "] (期望: [[1,6],[8,10]])" << endl;

    return 0;
}
