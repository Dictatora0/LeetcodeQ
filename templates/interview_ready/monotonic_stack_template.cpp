/*
 * ============================================================================
 * 单调栈算法 - 面试必备完整模板
 * Monotonic Stack - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 单调栈是一种特殊的栈，栈内元素保持单调递增或递减。
 * 用于高效解决"下一个更大/更小元素"类问题。
 *
 * 【通俗解释】
 * 想象你站在一排人中：
 * - 单调递减栈：栈顶到栈底，身高递减
 * - 当来一个更高的人，矮的人都要出栈
 * - 出栈的人找到了"右边第一个比自己高的人"
 *
 * 【为什么有效】
 * 1. O(n) 时间：每个元素最多入栈出栈一次
 * 2. 自动维护：栈自动保持单调性
 * 3. 快速查找：栈顶就是答案
 *
 * 【与其他算法对比】
 * - vs 暴力：O(n) vs O(n²)
 * - vs 优先队列：单调栈更简单
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别单调栈题目】
 *
 * ✅ 关键词识别：
 * 1. "下一个更大/更小元素" - 90% 是单调栈
 * 2. "左边/右边第一个..." - 单调栈
 * 3. "柱状图" - 单调栈
 * 4. "温度" - 单调栈
 * 5. "接雨水" - 单调栈
 *
 * ✅ 题目特征：
 * - 需要找相邻关系
 * - 需要维护最大/最小值
 * - 一维数组问题
 *
 * ❌ 不适合单调栈：
 * - 需要排序
 * - 二维问题
 * - 需要全局最值
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：单调递减栈（找下一个更大元素）
// 时间复杂度：O(n)
// 空间复杂度：O(n)
// ============================================================================

class MonotonicDecreasingStack {
public:
    vector<int> nextGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> st;  // 存储下标

        for (int i = 0; i < n; i++) {
            // 当前元素大于栈顶，栈顶找到了答案
            while (!st.empty() && nums[i] > nums[st.top()]) {
                int idx = st.top();
                st.pop();
                result[idx] = nums[i];
            }

            st.push(i);
        }

        return result;
    }
};

// ============================================================================
// 模板 2：单调递增栈（找下一个更小元素）
// 时间复杂度：O(n)
// 空间复杂度：O(n)
// ============================================================================

class MonotonicIncreasingStack {
public:
    vector<int> nextSmallerElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            // 当前元素小于栈顶，栈顶找到了答案
            while (!st.empty() && nums[i] < nums[st.top()]) {
                int idx = st.top();
                st.pop();
                result[idx] = nums[i];
            }

            st.push(i);
        }

        return result;
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：每日温度
// LeetCode 739: Daily Temperatures
// ============================================================================

class Solution_DailyTemperatures {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        stack<int> st;  // 单调递减栈

        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int idx = st.top();
                st.pop();
                result[idx] = i - idx;  // 天数差
            }

            st.push(i);
        }

        return result;
    }
};

// ============================================================================
// 变体 2：柱状图中最大的矩形
// LeetCode 84: Largest Rectangle in Histogram
// ============================================================================

class Solution_LargestRectangle {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        heights.push_back(0);  // 哨兵
        int maxArea = 0;

        for (int i = 0; i < heights.size(); i++) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();

                int w = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, h * w);
            }

            st.push(i);
        }

        return maxArea;
    }
};

// ============================================================================
// 变体 3：接雨水
// LeetCode 42: Trapping Rain Water
// ============================================================================

class Solution_Trap {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int water = 0;

        for (int i = 0; i < height.size(); i++) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int bottom = st.top();
                st.pop();

                if (st.empty()) break;

                int left = st.top();
                int h = min(height[left], height[i]) - height[bottom];
                int w = i - left - 1;
                water += h * w;
            }

            st.push(i);
        }

        return water;
    }
};

// ============================================================================
// 变体 4：下一个更大元素 I
// LeetCode 496: Next Greater Element I
// ============================================================================

class Solution_NextGreaterElement {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        stack<int> st;

        // 先处理 nums2
        for (int num : nums2) {
            while (!st.empty() && num > st.top()) {
                nextGreater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }

        // 查询 nums1
        vector<int> result;
        for (int num : nums1) {
            result.push_back(nextGreater.count(num) ? nextGreater[num] : -1);
        }

        return result;
    }
};

/*
 * ============================================================================
 * 第五至十部分：面试技巧、易错点、复杂度、真题、示例、速查表
 * ============================================================================
 */

/*
 * 【面试技巧】
 * 1. 说明单调性：递增还是递减
 * 2. 解释入栈出栈时机
 * 3. 强调 O(n) 时间复杂度
 *
 * 【易错点】
 * ❌ 栈存值还是下标（通常存下标）
 * ❌ 单调性搞反
 * ❌ 忘记处理栈中剩余元素
 *
 * 【复杂度】
 * 时间：O(n)
 * 空间：O(n)
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 739, LC 84, LC 42
 * ⭐⭐⭐⭐ LC 496, LC 503, LC 901
 *
 * 【速查表】
 * // 单调递减栈（找下一个更大）
 * stack<int> st;
 * for (int i = 0; i < n; i++) {
 *     while (!st.empty() && nums[i] > nums[st.top()]) {
 *         int idx = st.top(); st.pop();
 *         result[idx] = nums[i];
 *     }
 *     st.push(i);
 * }
 *
 * // 单调递增栈（找下一个更小）
 * stack<int> st;
 * for (int i = 0; i < n; i++) {
 *     while (!st.empty() && nums[i] < nums[st.top()]) {
 *         int idx = st.top(); st.pop();
 *         result[idx] = nums[i];
 *     }
 *     st.push(i);
 * }
 */

int main() {
    Solution_DailyTemperatures sol;
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    auto result = sol.dailyTemperatures(temps);

    cout << "每日温度结果: ";
    for (int days : result) cout << days << " ";
    cout << endl;

    cout << "单调栈算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o monotonic_stack monotonic_stack_template.cpp && ./monotonic_stack
 */
