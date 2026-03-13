/*
LeetCode 41. 缺失的第一个正数 (First Missing Positive)

题目概述 (Problem Summary)
-------------------------
给定一个未排序的整数数组 nums，找出其中缺失的最小正整数。
要求时间复杂度 O(n)，空间复杂度 O(1)。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 5 * 10^5
- -2^31 <= nums[i] <= 2^31 - 1
- 需要 O(n) 时间 + O(1) 额外空间

示例 (Example)
-------------
输入：nums = [3,4,-1,1]
输出：2
解释：最小缺失正整数为 2

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在数组中找最小的缺失正整数，范围应在 [1, n+1]

关键观察：
1. 若数组长度为 n，答案只可能在 [1, n+1]
2. 可以将值为 x 的元素放到索引 x-1 的位置
3. 排完后，第一处 nums[i] != i+1 即为答案

根据这些观察，可以得到两种典型解法：
1. 原地置换（循环排序）
2. 哈希集合（对比方法）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
原地将每个正整数 x 放到索引 x-1 位置。
最终扫描数组，找到第一个 nums[i] != i+1 的位置。

算法流程：
1. 遍历数组，如果 nums[i] 在 [1,n] 且不在正确位置，则交换到正确位置
2. 避免重复交换，使用 while
3. 完成后扫描，返回第一个不匹配的位置 + 1
4. 若都匹配，返回 n+1

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        for (int i = 0; i < n; ++i) {
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) return i + 1;
        }

        return n + 1;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Hash Set)

优化思路
--------
用哈希集合存储所有正整数，依次检查从 1 开始的最小缺失值。

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution_Optimized {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> s;
        for (int x : nums) {
            if (x > 0) s.insert(x);
        }
        int cur = 1;
        while (s.count(cur)) cur++;
        return cur;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [3,4,-1,1]

原地交换：
交换 3 -> 放到索引 2
交换 4 -> 放到索引 3
数组变为 [1,-1,3,4]
扫描：nums[0]=1 ok，nums[1]!=2 -> 答案 2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：原地置换
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：满足题目要求
- 缺点：实现细节较多

方法二：哈希集合
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：实现简单
- 缺点：不满足 O(1) 空间要求
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全部为负数或 0：答案为 1
2. 包含 1..n：答案为 n+1
3. 有重复元素：仍可正确处理
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {3, 4, -1, 1};
    cout << "测试用例 1 - 输出: " << solution.firstMissingPositive(nums1)
         << " (期望: 2)" << endl;

    // 测试用例 2
    vector<int> nums2 = {1, 2, 0};
    cout << "测试用例 2 - 输出: " << solution.firstMissingPositive(nums2)
         << " (期望: 3)" << endl;

    return 0;
}
