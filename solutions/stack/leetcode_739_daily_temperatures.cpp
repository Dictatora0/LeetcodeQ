/*
LeetCode 739. 每日温度 (Daily Temperatures)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 temperatures，表示每天的温度，返回一个数组 answer，
其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。
如果气温在这之后都不会升高，请在该位置用 0 来代替。

关键约束 (Key Constraints)
-------------------------
- 1 <= temperatures.length <= 10^5
- 30 <= temperatures[i] <= 100

示例 (Example)
-------------
输入：temperatures = [73,74,75,71,69,72,76,73]
输出：[1,1,4,2,1,1,0,0]
解释：
- 第 0 天：73°C，第 1 天 74°C 更高，等待 1 天
- 第 1 天：74°C，第 2 天 75°C 更高，等待 1 天
- 第 2 天：75°C，第 6 天 76°C 更高，等待 4 天
- 第 3 天：71°C，第 5 天 72°C 更高，等待 2 天

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对每个位置 i，找到右侧第一个比它大的元素的位置

为什么用单调栈？
1. 暴力解法：对每个元素向右遍历，时间复杂度 O(n²)
2. 单调栈：维护一个递减栈，当遇到更大元素时，栈中所有小于它的元素都找到了答案
3. 每个元素最多入栈一次、出栈一次，时间复杂度 O(n)

单调栈的定义：
- 单调递减栈：从栈底到栈顶元素递减（本题使用）
- 单调递增栈：从栈底到栈顶元素递增

栈中存什么？
- 存储索引（而不是温度值），因为需要计算天数差

什么时候入栈？
- 当前温度 <= 栈顶温度时，入栈

什么时候出栈？
- 当前温度 > 栈顶温度时，栈顶找到了答案，出栈并记录

单调栈原理图解 (Monotonic Stack Visualization)
--------------------------------------------
temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
索引:          [ 0,  1,  2,  3,  4,  5,  6,  7]

遍历过程：
i=0, temp=73: 栈空，入栈 -> 栈: [0]
i=1, temp=74: 74>73，索引0出栈，answer[0]=1-0=1 -> 栈: [1]
i=2, temp=75: 75>74，索引1出栈，answer[1]=2-1=1 -> 栈: [2]
i=3, temp=71: 71<75，入栈 -> 栈: [2,3]
i=4, temp=69: 69<71，入栈 -> 栈: [2,3,4]
i=5, temp=72: 72>69，索引4出栈，answer[4]=5-4=1
              72>71，索引3出栈，answer[3]=5-3=2
              72<75，入栈 -> 栈: [2,5]
i=6, temp=76: 76>72，索引5出栈，answer[5]=6-5=1
              76>75，索引2出栈，answer[2]=6-2=4
              栈空，入栈 -> 栈: [6]
i=7, temp=73: 73<76，入栈 -> 栈: [6,7]

最终栈中剩余的索引 [6,7] 都没有找到更高温度，answer[6]=0, answer[7]=0

单调栈模板代码 (Monotonic Stack Template)
---------------------------------------
// 单调递减栈模板（找右侧第一个更大元素）
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 0);  // 初始化结果数组
    stack<int> st;             // 单调栈，存储索引

    for (int i = 0; i < n; i++) {
        // 当前元素大于栈顶元素时，栈顶找到了答案
        while (!st.empty() && nums[i] > nums[st.top()]) {
            int idx = st.top();
            st.pop();
            result[idx] = i - idx;  // 计算距离
        }
        st.push(i);  // 当前索引入栈
    }

    // 栈中剩余元素没有找到答案，保持默认值 0
    return result;
}

时间复杂度分析：
- 每个元素最多入栈一次、出栈一次
- 总操作次数 = 2n
- 时间复杂度 O(n)
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
方法一：单调栈（递减栈）(Approach 1: Monotonic Decreasing Stack)

核心思想
--------
维护一个单调递减栈，栈中存储温度的索引。
当遇到更高的温度时，栈中所有比它低的温度都找到了答案。

算法流程：
1. 遍历每个温度 i
2. 若当前温度大于栈顶温度，栈顶找到答案，出栈并记录天数差
3. 重复步骤 2 直到栈空或当前温度不大于栈顶
4. 当前索引入栈

复杂度分析
---------
时间复杂度：O(n) - 每个元素最多入栈、出栈各一次
空间复杂度：O(n) - 栈的空间
*/
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);  // 初始化为 0
        stack<int> st;  // 单调递减栈，存储索引

        for (int i = 0; i < n; i++) {
            // 当前温度大于栈顶温度，栈顶找到了答案
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevIndex = st.top();
                st.pop();
                answer[prevIndex] = i - prevIndex;  // 计算天数差
            }
            st.push(i);  // 当前索引入栈
        }

        // 栈中剩余的索引都没有找到更高温度，answer 保持为 0
        return answer;
    }
};

/*
方法二：暴力枚举 (Approach 2: Brute Force)

核心思想
--------
对每个位置，向右遍历找到第一个更高的温度。

算法流程：
1. 对每个位置 i
2. 从 i+1 开始向右遍历
3. 找到第一个大于 temperatures[i] 的位置 j
4. 记录 answer[i] = j - i

复杂度分析
---------
时间复杂度：O(n²) - 双重循环
空间复杂度：O(1) - 不计结果数组
*/
class Solution_BruteForce {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    answer[i] = j - i;
                    break;
                }
            }
        }

        return answer;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
temperatures = [73, 74, 75, 71, 69, 72, 76, 73]

详细步骤：
i=0, temp=73:
  栈空，入栈
  栈: [0]

i=1, temp=74:
  74 > 73 (栈顶)，索引 0 出栈，answer[0] = 1 - 0 = 1
  入栈索引 1
  栈: [1]

i=2, temp=75:
  75 > 74 (栈顶)，索引 1 出栈，answer[1] = 2 - 1 = 1
  入栈索引 2
  栈: [2]

i=3, temp=71:
  71 < 75 (栈顶)，入栈
  栈: [2, 3]

i=4, temp=69:
  69 < 71 (栈顶)，入栈
  栈: [2, 3, 4]

i=5, temp=72:
  72 > 69 (栈顶)，索引 4 出栈，answer[4] = 5 - 4 = 1
  72 > 71 (栈顶)，索引 3 出栈，answer[3] = 5 - 3 = 2
  72 < 75 (栈顶)，入栈
  栈: [2, 5]

i=6, temp=76:
  76 > 72 (栈顶)，索引 5 出栈，answer[5] = 6 - 5 = 1
  76 > 75 (栈顶)，索引 2 出栈，answer[2] = 6 - 2 = 4
  栈空，入栈
  栈: [6]

i=7, temp=73:
  73 < 76 (栈顶)，入栈
  栈: [6, 7]

遍历结束，栈中剩余 [6, 7]，它们没有更高温度，answer[6]=0, answer[7]=0

最终结果：[1, 1, 4, 2, 1, 1, 0, 0]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：单调栈
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：时间最优，单调栈入门题
- 缺点：需要理解单调栈原理

方法二：暴力枚举
- 时间复杂度：O(n²)
- 空间复杂度：O(1)
- 优点：思路简单直观
- 缺点：数据量大时超时
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单调递减序列：[100, 90, 80, 70] -> [0, 0, 0, 0]
2. 单调递增序列：[30, 40, 50, 60] -> [1, 1, 1, 0]
3. 全部相同：[50, 50, 50] -> [0, 0, 0]
4. 只有一个元素：[73] -> [0]
5. 最大值在中间：[30, 100, 40] -> [1, 0, 0]
*/

int main() {
    Solution solution;

    // 测试用例 1：标准示例
    vector<int> t1 = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> r1 = solution.dailyTemperatures(t1);
    cout << "测试用例 1 - 输出: [";
    for (int i = 0; i < r1.size(); i++) {
        cout << r1[i];
        if (i < r1.size() - 1) cout << ", ";
    }
    cout << "] (期望: [1, 1, 4, 2, 1, 1, 0, 0])" << endl;

    // 测试用例 2：单调递减
    vector<int> t2 = {100, 90, 80, 70};
    vector<int> r2 = solution.dailyTemperatures(t2);
    cout << "测试用例 2 - 输出: [";
    for (int i = 0; i < r2.size(); i++) {
        cout << r2[i];
        if (i < r2.size() - 1) cout << ", ";
    }
    cout << "] (期望: [0, 0, 0, 0])" << endl;

    // 测试用例 3：单调递增
    vector<int> t3 = {30, 40, 50, 60};
    vector<int> r3 = solution.dailyTemperatures(t3);
    cout << "测试用例 3 - 输出: [";
    for (int i = 0; i < r3.size(); i++) {
        cout << r3[i];
        if (i < r3.size() - 1) cout << ", ";
    }
    cout << "] (期望: [1, 1, 1, 0])" << endl;

    return 0;
}
