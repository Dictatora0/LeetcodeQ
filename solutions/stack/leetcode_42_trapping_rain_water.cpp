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
2. 单调栈可以找到”凹槽”的边界并计算面积
3. 双指针可以用左右最大值动态决定当前可接水量

为什么用单调栈？
1. 单调栈可以按层计算雨水（横向计算）
2. 维护一个递减栈，当遇到更高的柱子时，形成凹槽
3. 凹槽的左边界是栈中的前一个元素，右边界是当前元素

单调栈的定义：
- 单调递减栈：从栈底到栈顶元素递减（本题使用）

栈中存什么？
- 存储索引（需要计算宽度和高度）

什么时候入栈？
- 当前高度 <= 栈顶高度时，入栈

什么时候出栈？
- 当前高度 > 栈顶高度时，形成凹槽，出栈并计算雨水量

单调栈原理图解 (Monotonic Stack Visualization)
--------------------------------------------
height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
索引:    [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11]

关键：单调栈按层计算雨水（横向计算）

示例：索引 1(高度1) 和 索引 3(高度2) 之间的凹槽
- 底部：索引 2(高度0)
- 左边界：索引 1(高度1)
- 右边界：索引 3(高度2)
- 水的高度：min(1, 2) - 0 = 1
- 宽度：3 - 1 - 1 = 1
- 雨水量：1 × 1 = 1

单调栈模板代码 (Monotonic Stack Template)
---------------------------------------
// 单调递减栈模板（按层计算雨水）
int trap(vector<int>& height) {
    stack<int> st;  // 单调递减栈，存储索引
    int water = 0;

    for (int i = 0; i < height.size(); i++) {
        // 当前高度大于栈顶，形成凹槽
        while (!st.empty() && height[i] > height[st.top()]) {
            int bottom = st.top();  // 凹槽底部
            st.pop();
            if (st.empty()) break;  // 没有左边界

            int left = st.top();  // 左边界
            int width = i - left - 1;  // 宽度
            int h = min(height[left], height[i]) - height[bottom];  // 水的高度
            water += width * h;
        }
        st.push(i);
    }

    return water;
}

时间复杂度分析：
- 每个元素最多入栈、出栈各一次
- 时间复杂度 O(n)

根据这些观察，可以得到三种典型解法：
1. 单调栈（按层计算，横向）
2. 双指针（空间 O(1)）
3. 动态规划（预处理左右最大值）
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/*
方法一：单调栈（按层计算）(Approach 1: Monotonic Stack - Layer by Layer)

核心思想
--------
使用单调递减栈存储柱子索引，按层计算雨水（横向计算）。
当遇到更高的柱子时，形成一个凹槽，可计算凹槽接水量。

关键点：
- 单调栈维护递减序列
- 当前柱子高于栈顶时，栈顶作为凹槽底部
- 左边界是新栈顶，右边界是当前柱子
- 按层计算：每次只计算一层的雨水

算法流程：
1. 遍历每个柱子 i
2. 若当前柱高大于栈顶，说明形成凹槽
3. 弹出栈顶作为凹槽底部
4. 如果栈空，说明没有左边界，跳过
5. 计算宽度 = i - 新栈顶 - 1
6. 计算高度 = min(左边界高度, 右边界高度) - 底部高度
7. 累加雨水量 = 宽度 × 高度
8. 当前索引入栈

复杂度分析
---------
时间复杂度：O(n) - 每个元素最多入栈、出栈各一次
空间复杂度：O(n) - 栈的空间
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
方法二：双指针 (Approach 2: Two Pointers)

核心思想
--------
用左右指针与左右最大值进行单次扫描。
若左侧最大值小于右侧最大值，左侧水量可确定；反之确定右侧。

关键点：
- 不需要知道确切的左右最大值，只需要知道哪边更小
- 水的高度由较小的一边决定
- 双指针从两端向中间移动

算法流程：
1. 初始化左右指针和左右最大值
2. 当左指针 <= 右指针时循环
3. 如果左边高度 <= 右边高度，处理左边
   - 如果当前高度 >= 左最大值，更新左最大值
   - 否则，累加雨水量 = 左最大值 - 当前高度
   - 左指针右移
4. 否则，处理右边（类似）

为什么更快：
- 空间 O(1)，实现简洁
- 只需要一次遍历

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution_TwoPointers {
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
方法三：动态规划 (Approach 3: Dynamic Programming)

核心思想
--------
预处理每个位置的左侧最大值和右侧最大值。
对每个位置，水的高度 = min(左最大值, 右最大值) - 当前高度。

算法流程：
1. 预处理 leftMax[i]：位置 i 左侧（包括 i）的最大高度
2. 预处理 rightMax[i]：位置 i 右侧（包括 i）的最大高度
3. 对每个位置 i，计算雨水量 = min(leftMax[i], rightMax[i]) - height[i]

复杂度分析
---------
时间复杂度：O(n) - 三次遍历
空间复杂度：O(n) - 需要两个数组存储左右最大值
*/
class Solution_DP {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;

        vector<int> leftMax(n), rightMax(n);

        // 预处理左侧最大值
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        // 预处理右侧最大值
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        // 计算雨水量
        int water = 0;
        for (int i = 0; i < n; i++) {
            water += min(leftMax[i], rightMax[i]) - height[i];
        }

        return water;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
height = [0,1,0,2,1,0,1,3,2,1,2,1]

方法一：单调栈（按层计算）

详细步骤：
i=0, h=0: 栈空，入栈 -> 栈: [0]
i=1, h=1: 1>0，索引0出栈，栈空，无左边界 -> 栈: [1]
i=2, h=0: 0<1，入栈 -> 栈: [1,2]
i=3, h=2: 2>0，索引2出栈（底部）
          左边界=索引1(h=1)，右边界=索引3(h=2)
          宽度=3-1-1=1，高度=min(1,2)-0=1，雨水=1×1=1
          2>1，索引1出栈，栈空，无左边界
          入栈 -> 栈: [3]
i=4, h=1: 1<2，入栈 -> 栈: [3,4]
i=5, h=0: 0<1，入栈 -> 栈: [3,4,5]
i=6, h=1: 1>0，索引5出栈（底部）
          左边界=索引4(h=1)，右边界=索引6(h=1)
          宽度=6-4-1=1，高度=min(1,1)-0=1，雨水=1×1=1
          1=1，不出栈，入栈 -> 栈: [3,4,6]
i=7, h=3: 3>1，索引6出栈（底部）
          左边界=索引4(h=1)，右边界=索引7(h=3)
          宽度=7-4-1=2，高度=min(1,3)-1=0，雨水=0
          3>1，索引4出栈（底部）
          左边界=索引3(h=2)，右边界=索引7(h=3)
          宽度=7-3-1=3，高度=min(2,3)-1=1，雨水=3×1=3
          3>2，索引3出栈（底部），栈空，无左边界
          入栈 -> 栈: [7]
...继续类似过程

总雨水量：6

以 2 和 3 形成的凹槽为例：
索引 3 高度 2，索引 7 高度 3
中间最低 0 -> 可接雨水
累计总和为 6
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：单调栈（按层计算）
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：单调栈经典应用，按层计算思路清晰
- 缺点：需要维护栈，理解难度较高

方法二：双指针
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优，代码简洁
- 缺点：需要理解左右最大值的关系

方法三：动态规划
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：思路最直观，易于理解
- 缺点：需要额外空间存储左右最大值
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全部递增或递减：结果为 0
2. 全部为 0：结果为 0
3. 只有 1-2 根柱子：结果为 0
*/

int main() {
    Solution solution;

    // 测试用例 1：标准示例
    vector<int> h1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "测试用例 1 - 输出: " << solution.trap(h1)
         << " (期望: 6)" << endl;

    // 测试用例 2：标准示例
    vector<int> h2 = {4,2,0,3,2,5};
    cout << "测试用例 2 - 输出: " << solution.trap(h2)
         << " (期望: 9)" << endl;

    // 测试用例 3：单调递增
    vector<int> h3 = {1, 2, 3, 4, 5};
    cout << "测试用例 3 - 输出: " << solution.trap(h3)
         << " (期望: 0)" << endl;

    // 测试用例 4：单调递减
    vector<int> h4 = {5, 4, 3, 2, 1};
    cout << "测试用例 4 - 输出: " << solution.trap(h4)
         << " (期望: 0)" << endl;

    return 0;
}
