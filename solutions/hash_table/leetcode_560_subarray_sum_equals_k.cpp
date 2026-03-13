/*
LeetCode 560. 和为 K 的子数组 (Subarray Sum Equals K)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 nums 和一个整数 k，返回数组中和为 k 的连续子数组的个数。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 2 * 10^4
- -1000 <= nums[i] <= 1000
- -10^7 <= k <= 10^7
- 元素可能为负数（重要）

示例 (Example)
-------------
输入：nums = [1,1,1], k = 2
输出：2
解释：子数组 [1,1] 出现 2 次

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 统计所有连续子数组中，和等于 k 的数量

关键观察：
1. 设前缀和 prefix[i] 表示 nums[0..i] 的和
2. 若 prefix[i] - prefix[j] = k，则 (j+1..i) 的和为 k
3. 对每个 prefix[i]，只需统计之前出现过多少个 prefix[i] - k

根据这些观察，可以得到两种典型解法：
1. 前缀和 + 哈希表（O(n)）
2. 枚举子数组（O(n^2)）
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用前缀和 + 哈希表统计前缀和出现次数。
遍历数组时，累加当前前缀和 sum，查找 sum - k 出现次数并累加到答案。

算法流程：
1. map 记录前缀和出现次数，初始化 map[0] = 1
2. 遍历 nums，累加 sum
3. 若 map 中存在 sum - k，则增加对应次数
4. 更新 map[sum] 计数

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        count[0] = 1;
        int sum = 0;
        int ans = 0;

        for (int x : nums) {
            sum += x;
            if (count.find(sum - k) != count.end()) {
                ans += count[sum - k];
            }
            count[sum]++;
        }

        return ans;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Brute Force)

优化思路
--------
枚举所有子数组并计算和，判断是否等于 k。
该方法用于对比学习，复杂度较高。

复杂度分析
---------
时间复杂度：O(n^2)
空间复杂度：O(1)
*/
class Solution_Optimized {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int j = i; j < n; ++j) {
                sum += nums[j];
                if (sum == k) ans++;
            }
        }
        return ans;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [1,1,1], k = 2

前缀和：
index 0: sum=1
index 1: sum=2 -> sum-k=0 出现 1 次 -> ans=1
index 2: sum=3 -> sum-k=1 出现 1 次 -> ans=2
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：前缀和 + 哈希表
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：线性时间，最优
- 缺点：需要哈希表

方法二：枚举子数组
- 时间复杂度：O(n^2)
- 空间复杂度：O(1)
- 优点：思路简单
- 缺点：效率低
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 包含负数：滑动窗口不可用，前缀和仍适用
2. k 为 0：允许子数组和为 0
3. 全部为 0：结果为 n*(n+1)/2
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    cout << "测试用例 1 - 输出: " << solution.subarraySum(nums1, k1)
         << " (期望: 2)" << endl;

    // 测试用例 2
    vector<int> nums2 = {1, 2, 3};
    int k2 = 3;
    cout << "测试用例 2 - 输出: " << solution.subarraySum(nums2, k2)
         << " (期望: 2)" << endl;

    return 0;
}
