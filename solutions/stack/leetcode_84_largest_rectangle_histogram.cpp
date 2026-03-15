/*
LeetCode 84. 柱状图中最大的矩形 (Largest Rectangle in Histogram)

题目概述 (Problem Summary)
-------------------------
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

关键约束 (Key Constraints)
-------------------------
- 1 <= heights.length <= 10^5
- 0 <= heights[i] <= 10^4

示例 (Example)
-------------
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10

输入：heights = [2,4]
输出：4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对每个柱子 i，找到以它为高度的最大矩形面积
- 矩形的宽度 = 右边界 - 左边界 + 1
- 右边界：右侧第一个小于 heights[i] 的位置
- 左边界：左侧第一个小于 heights[i] 的位置

为什么用单调栈？
1. 暴力解法：对每个柱子，向左右扩展找边界，时间复杂度 O(n²)
2. 单调栈：维护一个递增栈，当遇到更小的柱子时，栈中所有大于它的柱子都找到了右边界
3. 每个柱子最多入栈一次、出栈一次，时间复杂度 O(n)

单调栈的定义：
- 单调递增栈：从栈底到栈顶元素递增（本题使用）
- 注意：这里是递增栈，与前面的递减栈不同

栈中存什么？
- 存储索引（需要计算宽度）

什么时候入栈？
- 当前高度 >= 栈顶高度时，入栈

什么时候出栈？
- 当前高度 < 栈顶高度时，栈顶找到了右边界，出栈并计算面积

如何计算面积？
- 高度：heights[栈顶索引]
- 右边界：当前索引 i（第一个小于栈顶的位置）
- 左边界：新栈顶索引 + 1（栈顶出栈后，新栈顶是左侧第一个小于它的位置）
- 宽度：i - 新栈顶索引 - 1
- 面积：高度 × 宽度

单调栈原理图解 (Monotonic Stack Visualization)
--------------------------------------------
heights = [2, 1, 5, 6, 2, 3]
索引:     [ 0, 1, 2, 3, 4, 5]

遍历过程：
i=0, h=2: 栈空，入栈 -> 栈: [0]
i=1, h=1: 1<2，索引0出栈，计算面积
          高度=2，左边界=-1，右边界=1，宽度=1-(-1)-1=1，面积=2×1=2
          入栈 -> 栈: [1]
i=2, h=5: 5>1，入栈 -> 栈: [1,2]
i=3, h=6: 6>5，入栈 -> 栈: [1,2,3]
i=4, h=2: 2<6，索引3出栈，计算面积
          高度=6，左边界=2，右边界=4，宽度=4-2-1=1，面积=6×1=6
          2<5，索引2出栈，计算面积
          高度=5，左边界=1，右边界=4，宽度=4-1-1=2，面积=5×2=10
          2>1，入栈 -> 栈: [1,4]
i=5, h=3: 3>2，入栈 -> 栈: [1,4,5]

遍历结束，栈中剩余 [1,4,5]，依次出栈计算：
- 索引5：高度=3，左边界=4，右边界=6，宽度=6-4-1=1，面积=3×1=3
- 索引4：高度=2，左边界=1，右边界=6，宽度=6-1-1=4，面积=2×4=8
- 索引1：高度=1，左边界=-1，右边界=6，宽度=6-(-1)-1=6，面积=1×6=6

最大面积：10

关键技巧：
- 在数组末尾添加一个高度为 0 的哨兵，确保所有柱子都能出栈
- 在栈底添加一个索引 -1 的哨兵，简化左边界的计算

单调栈模板代码 (Monotonic Stack Template)
---------------------------------------
// 单调递增栈模板（找左右边界）
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    st.push(-1);  // 哨兵，简化左边界计算
    int maxArea = 0;

    for (int i = 0; i < heights.size(); i++) {
        // 当前高度小于栈顶，栈顶找到右边界
        while (st.top() != -1 && heights[i] < heights[st.top()]) {
            int h = heights[st.top()];
            st.pop();
            int width = i - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }

    // 处理栈中剩余元素
    while (st.top() != -1) {
        int h = heights[st.top()];
        st.pop();
        int width = heights.size() - st.top() - 1;
        maxArea = max(maxArea, h * width);
    }

    return maxArea;
}

时间复杂度分析：
- 每个元素最多入栈、出栈各一次
- 时间复杂度 O(n)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/*
方法一：单调栈（递增栈）(Approach 1: Monotonic Increasing Stack)

核心思想
--------
维护一个单调递增栈，栈中存储柱子的索引。
当遇到更矮的柱子时，栈中所有比它高的柱子都找到了右边界，可以计算面积。

算法流程：
1. 在栈底压入 -1 作为哨兵
2. 遍历每个柱子 i
3. 若当前高度小于栈顶高度，栈顶找到右边界，出栈并计算面积
4. 重复步骤 3 直到栈顶高度不大于当前高度
5. 当前索引入栈
6. 遍历结束后，处理栈中剩余元素

复杂度分析
---------
时间复杂度：O(n) - 每个元素最多入栈、出栈各一次
空间复杂度：O(n) - 栈的空间
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        st.push(-1);  // 哨兵，简化左边界计算
        int maxArea = 0;
        int n = heights.size();

        for (int i = 0; i < n; i++) {
            // 当前高度小于栈顶高度，栈顶找到右边界
            while (st.top() != -1 && heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();
                int width = i - st.top() - 1;  // 宽度 = 右边界 - 左边界 - 1
                maxArea = max(maxArea, h * width);
            }
            st.push(i);
        }

        // 处理栈中剩余元素（右边界为 n）
        while (st.top() != -1) {
            int h = heights[st.top()];
            st.pop();
            int width = n - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }

        return maxArea;
    }
};

/*
方法二：单调栈优化版（添加哨兵）(Approach 2: Monotonic Stack with Sentinel)

核心思想
--------
在数组末尾添加一个高度为 0 的哨兵，确保所有柱子都能出栈。
这样可以统一处理，不需要单独处理栈中剩余元素。

算法流程：
1. 在 heights 末尾添加 0
2. 在栈底压入 -1
3. 遍历每个柱子（包括哨兵）
4. 当前高度小于栈顶高度时，出栈并计算面积
5. 当前索引入栈

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);  // 添加哨兵
        stack<int> st;
        st.push(-1);  // 栈底哨兵
        int maxArea = 0;

        for (int i = 0; i < heights.size(); i++) {
            while (st.top() != -1 && heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();
                int width = i - st.top() - 1;
                maxArea = max(maxArea, h * width);
            }
            st.push(i);
        }

        return maxArea;
    }
};

/*
方法三：暴力枚举 (Approach 3: Brute Force)

核心思想
--------
对每个柱子，向左右扩展找到边界，计算以它为高度的最大矩形面积。

算法流程：
1. 对每个柱子 i
2. 向左找到第一个小于 heights[i] 的位置 left
3. 向右找到第一个小于 heights[i] 的位置 right
4. 计算面积 = heights[i] × (right - left - 1)
5. 更新最大面积

复杂度分析
---------
时间复杂度：O(n²) - 对每个柱子向左右扩展
空间复杂度：O(1)
*/
class Solution_BruteForce {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxArea = 0;

        for (int i = 0; i < n; i++) {
            int h = heights[i];

            // 向左找边界
            int left = i;
            while (left > 0 && heights[left - 1] >= h) {
                left--;
            }

            // 向右找边界
            int right = i;
            while (right < n - 1 && heights[right + 1] >= h) {
                right++;
            }

            int width = right - left + 1;
            maxArea = max(maxArea, h * width);
        }

        return maxArea;
    }
};

/*
方法四：分治法 (Approach 4: Divide and Conquer)

核心思想
--------
找到最小高度的柱子，最大矩形要么在左侧，要么在右侧，要么跨越最小柱子。

算法流程：
1. 找到最小高度的柱子 minIndex
2. 递归计算左侧的最大矩形
3. 递归计算右侧的最大矩形
4. 计算跨越 minIndex 的矩形：minHeight × 区间长度
5. 返回三者的最大值

复杂度分析
---------
时间复杂度：平均 O(n log n)，最坏 O(n²)（数组单调时）
空间复杂度：O(n) - 递归栈空间
*/
class Solution_DivideConquer {
public:
    int largestRectangleArea(vector<int>& heights) {
        return calculateArea(heights, 0, heights.size() - 1);
    }

private:
    int calculateArea(vector<int>& heights, int left, int right) {
        if (left > right) return 0;

        // 找到最小高度的索引
        int minIndex = left;
        for (int i = left; i <= right; i++) {
            if (heights[i] < heights[minIndex]) {
                minIndex = i;
            }
        }

        // 跨越 minIndex 的矩形面积
        int area = heights[minIndex] * (right - left + 1);

        // 递归计算左右两侧
        int leftArea = calculateArea(heights, left, minIndex - 1);
        int rightArea = calculateArea(heights, minIndex + 1, right);

        return max({area, leftArea, rightArea});
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
heights = [2, 1, 5, 6, 2, 3]

详细步骤（方法一）：

初始：栈: [-1]

i=0, h=2:
  栈顶=-1，2 不小于任何元素，入栈
  栈: [-1, 0]

i=1, h=1:
  1 < 2 (索引0)，索引0出栈
  高度=2，左边界=-1，右边界=1，宽度=1-(-1)-1=1，面积=2×1=2
  入栈索引1
  栈: [-1, 1]

i=2, h=5:
  5 > 1，入栈
  栈: [-1, 1, 2]

i=3, h=6:
  6 > 5，入栈
  栈: [-1, 1, 2, 3]

i=4, h=2:
  2 < 6 (索引3)，索引3出栈
  高度=6，左边界=2，右边界=4，宽度=4-2-1=1，面积=6×1=6
  2 < 5 (索引2)，索引2出栈
  高度=5，左边界=1，右边界=4，宽度=4-1-1=2，面积=5×2=10 ✓ 最大
  2 > 1，入栈
  栈: [-1, 1, 4]

i=5, h=3:
  3 > 2，入栈
  栈: [-1, 1, 4, 5]

遍历结束，处理栈中剩余元素：
- 索引5：高度=3，左边界=4，右边界=6，宽度=6-4-1=1，面积=3×1=3
- 索引4：高度=2，左边界=1，右边界=6，宽度=6-1-1=4，面积=2×4=8
- 索引1：高度=1，左边界=-1，右边界=6，宽度=6-(-1)-1=6，面积=1×6=6

最大面积：10
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：单调栈
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：时间最优，单调栈经典难题
- 缺点：理解难度较高

方法二：单调栈优化版
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：代码更简洁，统一处理
- 缺点：需要修改原数组（可以恢复）

方法三：暴力枚举
- 时间复杂度：O(n²)
- 空间复杂度：O(1)
- 优点：思路简单直观
- 缺点：时间复杂度高，数据量大时超时

方法四：分治法
- 时间复杂度：平均 O(n log n)，最坏 O(n²)
- 空间复杂度：O(n)
- 优点：思路清晰，易于理解
- 缺点：最坏情况下性能较差
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单调递增：[1, 2, 3, 4, 5] -> 最大面积 = 3×3 = 9
2. 单调递减：[5, 4, 3, 2, 1] -> 最大面积 = 5×1 = 5
3. 全部相同：[3, 3, 3, 3] -> 最大面积 = 3×4 = 12
4. 只有一个柱子：[5] -> 最大面积 = 5
5. 包含 0：[2, 0, 2] -> 最大面积 = 2
6. 最小值在中间：[5, 1, 5] -> 最大面积 = 5
*/

int main() {
    Solution solution;

    // 测试用例 1：标准示例
    vector<int> h1 = {2, 1, 5, 6, 2, 3};
    cout << "测试用例 1 - 输出: " << solution.largestRectangleArea(h1)
         << " (期望: 10)" << endl;

    // 测试用例 2：标准示例
    vector<int> h2 = {2, 4};
    cout << "测试用例 2 - 输出: " << solution.largestRectangleArea(h2)
         << " (期望: 4)" << endl;

    // 测试用例 3：单调递增
    vector<int> h3 = {1, 2, 3, 4, 5};
    cout << "测试用例 3 - 输出: " << solution.largestRectangleArea(h3)
         << " (期望: 9)" << endl;

    // 测试用例 4：全部相同
    vector<int> h4 = {3, 3, 3, 3};
    cout << "测试用例 4 - 输出: " << solution.largestRectangleArea(h4)
         << " (期望: 12)" << endl;

    // 测试用例 5：包含 0
    vector<int> h5 = {2, 0, 2};
    cout << "测试用例 5 - 输出: " << solution.largestRectangleArea(h5)
         << " (期望: 2)" << endl;

    return 0;
}
