/*
LeetCode 128. 最长连续序列 (Longest Consecutive Sequence)

题目概述 (Problem Summary)
-------------------------
给定一个未排序的整数数组 nums，找出最长连续序列的长度。
要求算法复杂度为 O(n)。

关键约束 (Key Constraints)
-------------------------
- 0 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9
- 需要 O(n) 级别复杂度

示例 (Example)
-------------
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长连续序列为 [1,2,3,4]，长度为 4

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在无序数组中找最长连续整数序列的长度

关键观察：
1. 若某个数 x 的前驱 x-1 不存在，说明 x 是连续序列的起点
2. 只从起点向右扩展，才能避免重复遍历
3. 哈希集合可 O(1) 判断元素是否存在

根据这些观察，可以得到两种典型解法：
1. 哈希集合 + 起点扩展（最优 O(n)）
2. 排序后扫描（O(n log n)）
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用哈希集合存储所有数字。
对于每个数字 x，只有当 x-1 不存在时，才从 x 开始向右扩展计数。

算法流程：
1. 将所有数字放入 unordered_set
2. 遍历每个数字 x
3. 若 x-1 不存在，开始从 x 向右扩展，统计长度
4. 更新最大长度

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int best = 0;

        for (int x : s) {
            if (s.find(x - 1) == s.end()) { // 只从起点开始
                int cur = x;
                int len = 1;
                while (s.find(cur + 1) != s.end()) {
                    cur++;
                    len++;
                }
                if (len > best) best = len;
            }
        }

        return best;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Sort Scan)

优化思路
--------
将数组排序后线性扫描，统计连续序列长度。
虽然不是 O(n)，但实现简单。

复杂度分析
---------
时间复杂度：O(n log n)
空间复杂度：O(1)（忽略排序额外空间）
*/
class Solution_Optimized {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        sort(nums.begin(), nums.end());

        int best = 1;
        int curLen = 1;
        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            if (nums[i] == nums[i - 1]) {
                continue; // 去重
            } else if (nums[i] == nums[i - 1] + 1) {
                curLen++;
            } else {
                best = max(best, curLen);
                curLen = 1;
            }
        }
        best = max(best, curLen);
        return best;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [100,4,200,1,3,2]

哈希集合：{100,4,200,1,3,2}
起点：
1 (0 不存在) -> 1,2,3,4 长度 4
3 (2 存在) 跳过
4 (3 存在) 跳过
100 (99 不存在) 长度 1
200 (199 不存在) 长度 1
最大长度 = 4
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：哈希集合 + 起点扩展
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：符合题目 O(n) 要求
- 缺点：需要额外哈希空间

方法二：排序后扫描
- 时间复杂度：O(n log n)
- 空间复杂度：O(1)
- 优点：实现简单
- 缺点：不满足严格 O(n) 要求
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 空数组：返回 0
2. 全是重复数：返回 1
3. 全部不连续：返回 1
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    cout << "测试用例 1 - 输出: " << solution.longestConsecutive(nums1)
         << " (期望: 4)" << endl;

    // 测试用例 2
    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << "测试用例 2 - 输出: " << solution.longestConsecutive(nums2)
         << " (期望: 9)" << endl;

    return 0;
}
