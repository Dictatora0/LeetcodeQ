/*
 * ============================================================================
 * 动态规划算法 - 面试必备完整模板
 * Dynamic Programming - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 动态规划通过将复杂问题分解为子问题，并存储子问题的解来避免重复计算。
 *
 * 【通俗解释】
 * 想象你爬楼梯：
 * - 到第 n 阶的方法数 = 到第 n-1 阶的方法数 + 到第 n-2 阶的方法数
 * - 记录每一阶的结果，避免重复计算
 * - 从小问题逐步推导到大问题
 *
 * 【DP 五部曲】
 * 1. 确定 dp 数组含义
 * 2. 确定递推公式
 * 3. 初始化 dp 数组
 * 4. 确定遍历顺序
 * 5. 举例推导 dp 数组
 *
 * 【与其他算法对比】
 * - vs 递归：DP 避免重复计算
 * - vs 贪心：DP 考虑所有情况，贪心只看当前最优
 * - vs 回溯：DP 记忆化，回溯暴力搜索
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别 DP 题目】
 *
 * ✅ 关键词识别：
 * 1. "最优解" - 最大/最小/最长/最短
 * 2. "有多少种方法" - 计数问题
 * 3. "能否..." - 可行性问题
 * 4. "子序列/子数组" - 序列 DP
 * 5. "背包" - 背包 DP
 *
 * ✅ 题目特征：
 * - 求最值
 * - 求方案数
 * - 有重叠子问题
 * - 有最优子结构
 *
 * ❌ 不适合 DP：
 * - 需要所有解（用回溯）
 * - 贪心能解决
 * - 没有重叠子问题
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：一维 DP（爬楼梯类型）
// 时间复杂度：O(n)
// 空间复杂度：O(n) 可优化到 O(1)
// ============================================================================

class OneDimensionalDP {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;

        // 1. dp[i] 表示到第 i 阶的方法数
        vector<int> dp(n + 1);

        // 2. 初始化
        dp[1] = 1;
        dp[2] = 2;

        // 3. 递推
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }

        return dp[n];
    }

    // 空间优化版本
    int climbStairsOptimized(int n) {
        if (n <= 2) return n;

        int prev2 = 1, prev1 = 2;

        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

// ============================================================================
// 模板 2：二维 DP（背包/路径类型）
// 时间复杂度：O(m * n)
// 空间复杂度：O(m * n) 可优化到 O(n)
// ============================================================================

class TwoDimensionalDP {
public:
    // 不同路径
    int uniquePaths(int m, int n) {
        // 1. dp[i][j] 表示到 (i,j) 的路径数
        vector<vector<int>> dp(m, vector<int>(n, 1));

        // 2. 递推
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[m-1][n-1];
    }

    // 空间优化版本
    int uniquePathsOptimized(int m, int n) {
        vector<int> dp(n, 1);

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j-1];
            }
        }

        return dp[n-1];
    }
};

// ============================================================================
// 模板 3：01 背包
// 时间复杂度：O(n * capacity)
// 空间复杂度：O(capacity)
// ============================================================================

class Knapsack01 {
public:
    int knapsack(vector<int>& weights, vector<int>& values, int capacity) {
        int n = weights.size();
        // dp[j] 表示容量为 j 时的最大价值
        vector<int> dp(capacity + 1, 0);

        // 遍历物品
        for (int i = 0; i < n; i++) {
            // 倒序遍历容量（避免重复使用）
            for (int j = capacity; j >= weights[i]; j--) {
                dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
            }
        }

        return dp[capacity];
    }
};

// ============================================================================
// 模板 4：完全背包
// 时间复杂度：O(n * capacity)
// 空间复杂度：O(capacity)
// ============================================================================

class KnapsackComplete {
public:
    int knapsack(vector<int>& weights, vector<int>& values, int capacity) {
        vector<int> dp(capacity + 1, 0);

        // 遍历物品
        for (int i = 0; i < weights.size(); i++) {
            // 正序遍历容量（可以重复使用）
            for (int j = weights[i]; j <= capacity; j++) {
                dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
            }
        }

        return dp[capacity];
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：打家劫舍
// LeetCode 198: House Robber
// ============================================================================

class Solution_Rob {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        // dp[i] 表示前 i 个房子能偷的最大金额
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            // 偷第 i 个 vs 不偷第 i 个
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }

        return dp[n-1];
    }
};

// ============================================================================
// 变体 2：最长递增子序列
// LeetCode 300: Longest Increasing Subsequence
// ============================================================================

class Solution_LengthOfLIS {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        // dp[i] 表示以 nums[i] 结尾的最长递增子序列长度
        vector<int> dp(n, 1);
        int maxLen = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        return maxLen;
    }
};

// ============================================================================
// 变体 3：零钱兑换
// LeetCode 322: Coin Change
// ============================================================================

class Solution_CoinChange {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] 表示凑成金额 i 所需的最少硬币数
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i >= coin && dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

// ============================================================================
// 变体 4：最长公共子序列
// LeetCode 1143: Longest Common Subsequence
// ============================================================================

class Solution_LongestCommonSubsequence {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();

        // dp[i][j] 表示 text1[0..i-1] 和 text2[0..j-1] 的 LCS 长度
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[m][n];
    }
};

// ============================================================================
// 变体 5：编辑距离
// LeetCode 72: Edit Distance
// ============================================================================

class Solution_MinDistance {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();

        // dp[i][j] 表示 word1[0..i-1] 转换为 word2[0..j-1] 的最少操作数
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        // 初始化
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min({
                        dp[i-1][j] + 1,    // 删除
                        dp[i][j-1] + 1,    // 插入
                        dp[i-1][j-1] + 1   // 替换
                    });
                }
            }
        }

        return dp[m][n];
    }
};

// ============================================================================
// 变体 6：分割等和子集（01 背包变形）
// LeetCode 416: Partition Equal Subset Sum
// ============================================================================

class Solution_CanPartition {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) sum += num;

        if (sum % 2 != 0) return false;

        int target = sum / 2;
        // dp[j] 表示是否能凑成和为 j
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
 * ============================================================================
 * 第五至十部分：面试技巧、易错点、复杂度、真题、示例、速查表
 * ============================================================================
 */

/*
 * 【面试技巧】
 * 1. 说明 DP 五部曲
 * 2. 画表格推导 dp 数组
 * 3. 说明空间优化方法
 *
 * 【易错点】
 * ❌ dp 数组含义不清
 * ❌ 初始化错误
 * ❌ 遍历顺序错误（01背包倒序，完全背包正序）
 * ❌ 边界条件处理不当
 *
 * 【复杂度】
 * 一维 DP：O(n)
 * 二维 DP：O(m*n)
 * 背包：O(n*capacity)
 *
 * 【高频题目】
 * ⭐⭐⭐⭐⭐ LC 198, LC 300, LC 322, LC 1143, LC 72
 * ⭐⭐⭐⭐ LC 416, LC 518, LC 139, LC 221
 *
 * 【速查表】
 * // 一维 DP
 * vector<int> dp(n+1);
 * dp[0] = 初始值;
 * for (int i = 1; i <= n; i++) {
 *     dp[i] = 根据 dp[i-1], dp[i-2]... 推导;
 * }
 *
 * // 二维 DP
 * vector<vector<int>> dp(m+1, vector<int>(n+1));
 * for (int i = 1; i <= m; i++) {
 *     for (int j = 1; j <= n; j++) {
 *         dp[i][j] = 根据 dp[i-1][j], dp[i][j-1]... 推导;
 *     }
 * }
 *
 * // 01 背包
 * for (int i = 0; i < n; i++) {
 *     for (int j = capacity; j >= weight[i]; j--) {  // 倒序
 *         dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
 *     }
 * }
 *
 * // 完全背包
 * for (int i = 0; i < n; i++) {
 *     for (int j = weight[i]; j <= capacity; j++) {  // 正序
 *         dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
 *     }
 * }
 */

int main() {
    Solution_Rob sol;
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << "打家劫舍最大金额: " << sol.rob(nums) << endl;
    cout << "动态规划算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o dp dp_template.cpp && ./dp
 */
