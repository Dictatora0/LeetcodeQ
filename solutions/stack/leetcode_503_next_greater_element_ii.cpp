/*
LeetCode 503. 下一个更大元素 II (Next Greater Element II)

题目概述 (Problem Summary)
-------------------------
给定一个循环数组 nums（最后一个元素的下一个元素是数组的第一个元素），
返回 nums 中每个元素的下一个更大元素。

数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，
这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^4
- -10^9 <= nums[i] <= 10^9

示例 (Example)
-------------
输入：nums = [1,2,1]
输出：[2,-1,2]
解释：
- 第一个 1 的下一个更大的数是 2
- 数字 2 找不到下一个更大的数
- 第二个 1 需要循环搜索，找到第一个元素 2

输入：nums = [1,2,3,4,3]
输出：[2,3,4,-1,4]
解释：
- 1 的下一个更大元素是 2
- 2 的下一个更大元素是 3
- 3 的下一个更大元素是 4
- 4 没有更大元素，返回 -1
- 最后的 3 循环到开头，找到 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在循环数组中，找到每个元素右侧第一个更大的元素

为什么用单调栈？
1. 普通数组找下一个更大元素：单调栈 O(n)
2. 循环数组：需要考虑从头开始的元素
3. 技巧：遍历两次数组（或使用取模运算），第二次遍历时可以找到循环部分的答案

单调栈的定义：
- 单调递减栈：从栈底到栈顶元素递减（本题使用）

栈中存什么？
- 存储索引（需要计算位置，且可能有重复元素）

循环数组的处理技巧：
1. 方法一：遍历 2n 次，使用 i % n 获取实际索引
2. 方法二：将数组拼接成 [nums, nums]，遍历 2n 个元素

什么时候入栈？
- 当前元素 <= 栈顶元素时，入栈

什么时候出栈？
- 当前元素 > 栈顶元素时，栈顶找到答案，出栈并记录

单调栈原理图解 (Monotonic Stack Visualization)
--------------------------------------------
nums = [1, 2, 1]
索引:  [ 0, 1, 2]

遍历 2n = 6 次，使用 i % n 获取实际索引：

i=0, idx=0, num=1: 栈空，入栈 -> 栈: [0]
i=1, idx=1, num=2: 2>1，索引0出栈，answer[0]=2 -> 栈: [1]
i=2, idx=2, num=1: 1<2，入栈 -> 栈: [1,2]
i=3, idx=0, num=1: 1<1，不入栈（已处理过索引0）
i=4, idx=1, num=2: 2>1，索引2出栈，answer[2]=2
                   栈顶是1，不出栈（已处理过索引1）
i=5, idx=2, num=1: 不入栈（已处理过索引2）

最终栈中剩余索引 1，answer[1]=-1

结果：[2, -1, 2]

关键点：
- 遍历 2n 次，但只在第一次遇到索引时入栈
- 第二轮遍历时，可以为第一轮未找到答案的元素找到循环部分的答案

单调栈模板代码 (Monotonic Stack Template)
---------------------------------------
// 循环数组的单调栈模板（找下一个更大元素）
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // 单调递减栈，存储索引

    // 遍历 2n 次，模拟循环数组
    for (int i = 0; i < 2 * n; i++) {
        int idx = i % n;  // 实际索引

        // 当前元素大于栈顶元素，栈顶找到答案
        while (!st.empty() && nums[idx] > nums[st.top()]) {
            result[st.top()] = nums[idx];
            st.pop();
        }

        // 只在第一轮遍历时入栈
        if (i < n) {
            st.push(idx);
        }
    }

    return result;
}

时间复杂度分析：
- 遍历 2n 次，每个元素最多入栈、出栈各一次
- 时间复杂度 O(n)
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
方法一：单调栈 + 循环数组技巧 (Approach 1: Monotonic Stack + Circular Array)

核心思想
--------
使用单调递减栈，遍历 2n 次数组（使用 % 运算模拟循环）。
第一轮遍历时元素入栈，第二轮遍历时为第一轮未找到答案的元素找到循环部分的答案。

算法流程：
1. 遍历 2n 次，i 从 0 到 2n-1
2. 实际索引 idx = i % n
3. 当前元素大于栈顶元素时，栈顶找到答案，出栈并记录
4. 只在第一轮（i < n）时入栈
5. 栈中剩余元素没有更大元素，保持 -1

复杂度分析
---------
时间复杂度：O(n) - 每个元素最多入栈、出栈各一次
空间复杂度：O(n) - 栈的空间
*/
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);  // 初始化为 -1
        stack<int> st;  // 单调递减栈，存储索引

        // 遍历 2n 次，模拟循环数组
        for (int i = 0; i < 2 * n; i++) {
            int idx = i % n;  // 实际索引

            // 当前元素大于栈顶元素，栈顶找到答案
            while (!st.empty() && nums[idx] > nums[st.top()]) {
                result[st.top()] = nums[idx];
                st.pop();
            }

            // 只在第一轮遍历时入栈
            if (i < n) {
                st.push(idx);
            }
        }

        // 栈中剩余元素没有更大元素，result 保持为 -1
        return result;
    }
};

/*
方法二：单调栈 + 拼接数组 (Approach 2: Monotonic Stack + Concatenated Array)

核心思想
--------
将数组拼接成 [nums, nums]，然后使用单调栈遍历。
只记录前 n 个元素的结果。

算法流程：
1. 创建拼接数组 doubled = nums + nums
2. 使用单调栈遍历 doubled
3. 只记录前 n 个元素的结果

复杂度分析
---------
时间复杂度：O(n) - 遍历 2n 个元素
空间复杂度：O(n) - 拼接数组和栈的空间
*/
class Solution_Concatenate {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);

        // 拼接数组
        vector<int> doubled = nums;
        doubled.insert(doubled.end(), nums.begin(), nums.end());

        stack<int> st;  // 单调递减栈，存储索引

        for (int i = 0; i < doubled.size(); i++) {
            while (!st.empty() && doubled[i] > doubled[st.top()]) {
                int idx = st.top();
                st.pop();
                // 只记录前 n 个元素的结果
                if (idx < n) {
                    result[idx] = doubled[i];
                }
            }
            st.push(i);
        }

        return result;
    }
};

/*
方法三：暴力枚举 (Approach 3: Brute Force)

核心思想
--------
对每个位置，向右循环遍历找第一个更大的元素。

算法流程：
1. 对每个位置 i
2. 从 i+1 开始循环遍历（使用 % 运算）
3. 找到第一个大于 nums[i] 的元素
4. 如果遍历一圈都没找到，返回 -1

复杂度分析
---------
时间复杂度：O(n²) - 双重循环
空间复杂度：O(1) - 不计结果数组
*/
class Solution_BruteForce {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);

        for (int i = 0; i < n; i++) {
            // 循环遍历，最多遍历 n 个元素
            for (int j = 1; j < n; j++) {
                int idx = (i + j) % n;
                if (nums[idx] > nums[i]) {
                    result[i] = nums[idx];
                    break;
                }
            }
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [1, 2, 1]

详细步骤（方法一）：

i=0, idx=0, num=1:
  栈空，入栈
  栈: [0]

i=1, idx=1, num=2:
  2 > 1 (栈顶索引0)，索引 0 出栈，result[0] = 2
  入栈索引 1
  栈: [1]

i=2, idx=2, num=1:
  1 < 2 (栈顶索引1)，入栈
  栈: [1, 2]

--- 第二轮遍历开始 ---

i=3, idx=0, num=1:
  1 < 1 (栈顶索引2)，不入栈（i >= n）
  栈: [1, 2]

i=4, idx=1, num=2:
  2 > 1 (栈顶索引2)，索引 2 出栈，result[2] = 2
  2 = 2 (栈顶索引1)，不出栈
  不入栈（i >= n）
  栈: [1]

i=5, idx=2, num=1:
  1 < 2 (栈顶索引1)，不入栈（i >= n）
  栈: [1]

遍历结束，栈中剩余索引 1，result[1] 保持为 -1

最终结果：[2, -1, 2]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：单调栈 + 循环数组技巧
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：时间最优，空间效率高（不需要拼接数组）
- 缺点：需要理解循环数组的处理技巧

方法二：单调栈 + 拼接数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：思路直观，容易理解
- 缺点：需要额外空间存储拼接数组

方法三：暴力枚举
- 时间复杂度：O(n²)
- 空间复杂度：O(1)
- 优点：思路简单
- 缺点：时间复杂度高，数据量大时超时
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 单调递减：[5, 4, 3, 2, 1] -> [-1, -1, -1, -1, -1]
2. 单调递增：[1, 2, 3, 4, 5] -> [2, 3, 4, 5, -1]
3. 全部相同：[3, 3, 3] -> [-1, -1, -1]
4. 只有一个元素：[1] -> [-1]
5. 最大值在开头：[5, 1, 2, 3] -> [-1, 2, 3, 5]
6. 最大值在中间：[1, 5, 2, 3] -> [5, -1, 3, 5]
*/

int main() {
    Solution solution;

    // 测试用例 1：标准示例
    vector<int> n1 = {1, 2, 1};
    vector<int> r1 = solution.nextGreaterElements(n1);
    cout << "测试用例 1 - 输出: [";
    for (int i = 0; i < r1.size(); i++) {
        cout << r1[i];
        if (i < r1.size() - 1) cout << ", ";
    }
    cout << "] (期望: [2, -1, 2])" << endl;

    // 测试用例 2：标准示例
    vector<int> n2 = {1, 2, 3, 4, 3};
    vector<int> r2 = solution.nextGreaterElements(n2);
    cout << "测试用例 2 - 输出: [";
    for (int i = 0; i < r2.size(); i++) {
        cout << r2[i];
        if (i < r2.size() - 1) cout << ", ";
    }
    cout << "] (期望: [2, 3, 4, -1, 4])" << endl;

    // 测试用例 3：单调递减
    vector<int> n3 = {5, 4, 3, 2, 1};
    vector<int> r3 = solution.nextGreaterElements(n3);
    cout << "测试用例 3 - 输出: [";
    for (int i = 0; i < r3.size(); i++) {
        cout << r3[i];
        if (i < r3.size() - 1) cout << ", ";
    }
    cout << "] (期望: [-1, -1, -1, -1, -1])" << endl;

    // 测试用例 4：最大值在开头
    vector<int> n4 = {5, 1, 2, 3};
    vector<int> r4 = solution.nextGreaterElements(n4);
    cout << "测试用例 4 - 输出: [";
    for (int i = 0; i < r4.size(); i++) {
        cout << r4[i];
        if (i < r4.size() - 1) cout << ", ";
    }
    cout << "] (期望: [-1, 2, 3, 5])" << endl;

    return 0;
}
