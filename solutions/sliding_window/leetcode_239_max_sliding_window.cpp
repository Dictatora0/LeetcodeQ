/*
LeetCode 239. 滑动窗口最大值 (Sliding Window Maximum)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 nums 和一个整数 k，窗口大小为 k，
从左到右移动窗口，输出每个窗口中的最大值。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- 1 <= k <= nums.length

示例 (Example)
-------------
输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
窗口分别为：
[1,3,-1] -> 3
[3,-1,-3] -> 3
[-1,-3,5] -> 5
[-3,5,3] -> 5
[5,3,6] -> 6
[3,6,7] -> 7

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在滑动窗口内快速维护最大值

关键观察：
1. 朴素做法每个窗口扫描一次，复杂度 O(nk)
2. 单调队列可以维护一个递减序列，队首即最大值
3. 当窗口右移时，需要移除过期元素

根据这些观察，可以得到两种典型解法：
1. 单调队列（最优，O(n)）
2. 优先队列（堆，O(n log n)）
*/

#include <iostream>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用单调队列（递减），队首始终是当前窗口最大值。

算法流程：
1. 右指针移动，维护队列递减性（移除队尾较小元素）
2. 队首元素若已滑出窗口，弹出
3. 当形成完整窗口时，记录队首为当前最大值

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(k)
*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;        // 存索引，保证对应值递减
        vector<int> result;

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            // 移除窗口外的索引
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // 维护递减队列
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);

            // 形成窗口后记录最大值
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Max Heap)

优化思路
--------
使用最大堆存储 (value, index)，堆顶为当前最大值。
当堆顶元素过期时，弹出直到合法。

为什么可行：
- 堆顶始终是最大值
- 通过索引判断是否在窗口内

复杂度分析
---------
时间复杂度：O(n log n)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> pq; // (value, index)
        vector<int> result;

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            pq.push({nums[i], i});

            // 窗口形成后开始输出
            if (i >= k - 1) {
                while (!pq.empty() && pq.top().second <= i - k) {
                    pq.pop();
                }
                result.push_back(pq.top().first);
            }
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [1,3,-1,-3,5,3,6,7], k = 3

单调队列状态（存索引）：
窗口 [1,3,-1] -> 队列索引 [1,2] -> 最大值 nums[1]=3
窗口 [3,-1,-3] -> 队列索引 [1,2,3] -> 最大值 3
窗口 [-1,-3,5] -> 队列索引 [4] -> 最大值 5
...
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：单调队列
- 时间复杂度：O(n)
- 空间复杂度：O(k)
- 优点：最优解法
- 缺点：实现细节需要仔细处理

方法二：最大堆
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：思路直观
- 缺点：性能略差
*/

/*
特殊情况 (Edge Cases)
--------------------
1. k = 1：结果为原数组
2. k = nums.length：结果为单个最大值
3. 数组含负数：仍适用
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    vector<int> result1 = solution.maxSlidingWindow(nums1, k1);
    cout << "测试用例 1 - 输出: ";
    printVector(result1);
    cout << " (期望: [3, 3, 5, 5, 6, 7])" << endl;

    // 测试用例 2
    vector<int> nums2 = {1};
    int k2 = 1;
    vector<int> result2 = solution.maxSlidingWindow(nums2, k2);
    cout << "测试用例 2 - 输出: ";
    printVector(result2);
    cout << " (期望: [1])" << endl;

    return 0;
}
