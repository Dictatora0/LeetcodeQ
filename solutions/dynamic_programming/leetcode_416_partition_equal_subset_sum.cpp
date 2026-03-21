/*
LeetCode 416. 分割等和子集 (Partition Equal Subset Sum)

题目概述 (Problem Summary)
-------------------------
给定一个只包含正整数的非空数组 nums。
判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 200
- 1 <= nums[i] <= 100

示例 (Example)
-------------
输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11]

输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个和相等的子集

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 0-1 背包问题：判断是否能从数组中选出若干数，使其和为 sum/2

关键观察：
1. 如果数组总和为奇数，直接返回 false
2. 问题转化为：能否选出若干数，使其和为 target = sum/2
3. dp[j] 表示是否能凑出和为 j
4. 状态转移：dp[j] = dp[j] || dp[j - num]
5. 必须倒序遍历，避免重复使用同一个数

根据这些观察，可以得到两种典型解法：
1. 一维 DP（空间优化的 0-1 背包）
2. 二维 DP（更直观）
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution - 1D DP)

核心思想
--------
使用一维 DP 数组，判断是否能凑出和为 target 的子集。

状态定义：
dp[j] = 是否能从数组中选出若干数，使其和为 j

状态转移方程：
dp[j] = dp[j] || dp[j - num]

算法流程：
1. 计算数组总和 sum，如果为奇数返回 false
2. 目标值 target = sum / 2
3. 初始化 dp[0] = true，其他为 false
4. 遍历每个数 num
5. 倒序遍历 j (从 target 到 num)
6. 更新 dp[j] = dp[j] || dp[j - num]
7. 返回 dp[target]

为什么要倒序遍历？
- 0-1 背包问题，每个数只能使用一次
- 倒序遍历保证 dp[j - num] 是上一轮的值
- 正序遍历会导致同一个数被使用多次

复杂度分析
---------
时间复杂度：O(n * sum)
空间复杂度：O(sum)
*/
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) sum += num;

        if (sum % 2 == 1) return false;

        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }
};

/*
方法二：二维 DP 解法 (Approach 2: 2D DP Solution)

核心思想
--------
使用二维 DP 数组，更直观地表示状态转移。

状态定义：
dp[i][j] = 使用前 i 个数，是否能凑出和为 j

状态转移方程：
dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]]

复杂度分析
---------
时间复杂度：O(n * sum)
空间复杂度：O(n * sum)
*/
class Solution_2D {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1) return false;

        int n = nums.size();
        int target = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        // 初始化：不选任何数，和为 0
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                // 不选第 i 个数
                dp[i][j] = dp[i - 1][j];
                // 选第 i 个数
                if (j >= nums[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }

        return dp[n][target];
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [1,5,11,5], sum = 22, target = 11

一维 DP：
初始：dp = [T, F, F, F, F, F, F, F, F, F, F, F]

处理 1：
dp[11] = dp[11] || dp[10] = F
...
dp[1] = dp[1] || dp[0] = T
结果：dp = [T, T, F, F, F, F, F, F, F, F, F, F]

处理 5：
dp[11] = dp[11] || dp[6] = F
dp[6] = dp[6] || dp[1] = T
dp[5] = dp[5] || dp[0] = T
结果：dp = [T, T, F, F, F, T, T, F, F, F, F, F]

处理 11：
dp[11] = dp[11] || dp[0] = T
结果：dp = [T, T, F, F, F, T, T, F, F, F, F, T]

处理 5：
dp[11] = dp[11] || dp[6] = T
结果：dp[11] = true
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：一维 DP
- 时间复杂度：O(n * sum)
- 空间复杂度：O(sum)
- 优点：空间优化
- 缺点：需要理解倒序遍历的原因

方法二：二维 DP
- 时间复杂度：O(n * sum)
- 空间复杂度：O(n * sum)
- 优点：状态转移更直观
- 缺点：空间占用大
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 数组长度为 1：返回 false
2. 数组总和为奇数：返回 false
3. 所有数相等且为偶数个：返回 true
4. 存在一个数等于 sum/2：返回 true
*/

/*
易错点 (Common Mistakes)
-----------------------
1. 忘记判断总和是否为奇数
2. 一维 DP 忘记倒序遍历
3. 二维 DP 索引错误（nums[i-1]）
4. 初始化错误（dp[0] = true）
*/

int main() {
    Solution solution;

    // 测试用例 1：可以分割
    vector<int> nums1 = {1, 5, 11, 5};
    cout << "测试用例 1 - 输出: " << (solution.canPartition(nums1) ? "true" : "false")
         << " (期望: true)" << endl;

    // 测试用例 2：不能分割
    vector<int> nums2 = {1, 2, 3, 5};
    cout << "测试用例 2 - 输出: " << (solution.canPartition(nums2) ? "true" : "false")
         << " (期望: false)" << endl;

    // 测试用例 3：总和为奇数
    vector<int> nums3 = {1, 2, 5};
    cout << "测试用例 3 - 输出: " << (solution.canPartition(nums3) ? "true" : "false")
         << " (期望: false)" << endl;

    // 测试用例 4：简单情况
    vector<int> nums4 = {2, 2};
    cout << "测试用例 4 - 输出: " << (solution.canPartition(nums4) ? "true" : "false")
         << " (期望: true)" << endl;

    return 0;
}
