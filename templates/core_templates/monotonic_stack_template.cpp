
/*
算法名称：单调栈 Monotonic Stack

算法核心思想
-----------
使用栈维护单调递增或递减的序列，
在 O(n) 时间内解决“下一个更大/更小元素”、区间边界问题。

思路要点
-------
- 栈一般存索引，便于计算距离或区间宽度
- 递减栈常用于“下一个更大元素”
- 递增栈常用于“下一个更小元素”
- 处理循环数组时可遍历 2n

什么时候使用
-----------
适用场景：
- 下一个更大/更小元素
- 柱状图最大矩形
- 需要寻找左右最近更大/更小的位置

常见算法变体
-----------
1) 单调递减栈：找下一个更大元素
2) 单调递增栈：找下一个更小元素
3) 双向边界：求每个位置左右最近更小/更大
4) 循环数组下一个更大元素

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)

ASCII 示例
---------
nums: [2,1,2,4,3]
下一个更大元素: [4,2,4,-1,-1]

典型题目扩展
-----------
- 496 Next Greater Element I
- 739 Daily Temperatures
- 84 Largest Rectangle in Histogram
- 42 Trapping Rain Water
- 907 Sum of Subarray Minimums

可直接使用的代码模板
------------------
见下方 MonotonicStack_Template

常见错误
--------
- 栈存值还是存索引混淆
- 忘记处理栈空的情况
- 边界计算 off-by-one
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class MonotonicStack_Template {
public:
    // 下一个更大元素（右侧）
    vector<int> nextGreaterRight(const vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> ans(n, -1);
        stack<int> st; // 存索引，保持递减

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[i] > nums[st.top()]) {
                ans[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }

    // 下一个更小元素（右侧）
    vector<int> nextSmallerRight(const vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> ans(n, -1);
        stack<int> st; // 存索引，保持递增

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[i] < nums[st.top()]) {
                ans[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }

    // 每个位置左侧最近更小元素的索引
    vector<int> prevSmallerIndex(const vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> ans(n, -1);
        stack<int> st; // 递增栈
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] >= nums[i]) st.pop();
            ans[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        return ans;
    }

    // 循环数组下一个更大元素
    vector<int> nextGreaterCircular(const vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> ans(n, -1);
        stack<int> st;
        for (int i = 0; i < 2 * n; ++i) {
            int idx = i % n;
            while (!st.empty() && nums[idx] > nums[st.top()]) {
                ans[st.top()] = nums[idx];
                st.pop();
            }
            if (i < n) st.push(idx);
        }
        return ans;
    }

    // 柱状图最大矩形
    int largestRectangleArea(const vector<int>& heights) {
        vector<int> h(heights);
        h.push_back(0); // 哨兵
        stack<int> st; // 单调递增栈
        int best = 0;
        for (int i = 0; i < (int)h.size(); ++i) {
            while (!st.empty() && h[i] < h[st.top()]) {
                int height = h[st.top()];
                st.pop();
                int left = st.empty() ? -1 : st.top();
                int width = i - left - 1;
                best = max(best, height * width);
            }
            st.push(i);
        }
        return best;
    }
};

int main() {
    MonotonicStack_Template solver;
    vector<int> nums = {2,1,2,4,3};
    auto res = solver.nextGreaterRight(nums);
    cout << "Next Greater Right: ";
    for (int x : res) cout << x << " ";
    cout << endl;

    vector<int> heights = {2,1,5,6,2,3};
    cout << "Largest Rectangle: " << solver.largestRectangleArea(heights) << endl;
    return 0;
}
