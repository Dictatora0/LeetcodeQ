/*
LeetCode 42. 接雨水 (Trapping Rain Water)

题目概述 (Problem Summary)
-------------------------
给定 n 个非负整数表示柱子的高度图，计算下雨后能够接多少雨水。

关键约束 (Key Constraints)
-------------------------
- 1 <= height.length <= 2 * 10^4
- 0 <= height[i] <= 10^5

示例 (Example)
-------------
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：图中能接到的雨水总量为 6

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对每个位置 i，水的高度取决于左边最高与右边最高的较小值

关键观察：
1. 柱子之间形成凹槽，雨水高度由两侧较低的边界决定
2. 单调栈可以找到“凹槽”的边界并计算面积
3. 双指针可以用左右最大值动态决定当前可接水量

根据这些观察，可以得到两种典型解法：
1. 单调栈（栈类典型解法）
2. 双指针（空间 O(1)）
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用单调递减栈存储柱子索引。
当遇到更高的柱子时，形成一个凹槽，可计算凹槽接水量。

算法流程：
1. 遍历每个柱子 i
2. 若当前柱高大于栈顶，说明形成凹槽
3. 弹出栈顶作为凹槽底部，计算左右边界和高度差
4. 累加雨水量

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int n = static_cast<int>(height.size());
        stack<int> st;
        int water = 0;

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int bottom = st.top();
                st.pop();
                if (st.empty()) break;

                int left = st.top();
                int width = i - left - 1;
                int boundedHeight = min(height[left], height[i]) - height[bottom];
                if (boundedHeight > 0) {
                    water += width * boundedHeight;
                }
            }
            st.push(i);
        }

        return water;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Two Pointers)

优化思路
--------
用左右指针与左右最大值进行单次扫描。
若左侧最大值小于右侧最大值，左侧水量可确定；反之确定右侧。

为什么更快：
- 空间 O(1)，实现简洁

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int trap(vector<int>& height) {
        int n = static_cast<int>(height.size());
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;

        while (left <= right) {
            if (height[left] <= height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    water += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    water += rightMax - height[right];
                }
                right--;
            }
        }

        return water;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
height = [0,1,0,2,1,0,1,3,2,1,2,1]

以 2 和 3 形成的凹槽为例：
索引 3 高度 2，索引 7 高度 3
中间最低 0 -> 可接雨水
累计总和为 6
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：单调栈
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：适合学习“栈 + 凹槽”思路
- 缺点：需要维护栈

方法二：双指针
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：理解需要左右最大值思路
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全部递增或递减：结果为 0
2. 全部为 0：结果为 0
3. 只有 1-2 根柱子：结果为 0
*/

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<int> h1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "测试用例 1 - 输出: " << solution.trap(h1)
         << " (期望: 6)" << endl;

    // 测试用例 2
    vector<int> h2 = {4,2,0,3,2,5};
    cout << "测试用例 2 - 输出: " << solution.trap(h2)
         << " (期望: 9)" << endl;

    return 0;
}
