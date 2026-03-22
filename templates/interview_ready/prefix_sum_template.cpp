/*
 * ============================================================================
 * 前缀和算法 - 面试必备完整模板
 * Prefix Sum - Complete Interview Template
 * ============================================================================
 *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
 * ============================================================================
 * 第一部分：算法概述
 * ============================================================================
 */

/*
 * 【核心思想】
 * 前缀和是预处理数组，使得查询区间和的时间复杂度从 O(n) 降到 O(1)。
 *
 * 【通俗解释】
 * 想象你要计算第 3 到第 7 天的销售额：
 * - 暴力：把第 3、4、5、6、7 天的销售额加起来
 * - 前缀和：前 7 天总和 - 前 2 天总和
 *
 * 【核心公式】
 * prefix[i] = nums[0] + nums[1] + ... + nums[i-1]
 * sum(i, j) = prefix[j+1] - prefix[i]
 *
 * 【与其他算法对比】
 * - vs 暴力：O(1) vs O(n) 查询
 * - vs 线段树：前缀和更简单，但不支持修改
 */

/*
 * ============================================================================
 * 第二部分：识别题型
 * ============================================================================
 */

/*
 * 【如何快速识别前缀和题目】
 *
 * ✅ 关键词识别：
 * 1. "区间和" - 90% 是前缀和
 * 2. "子数组和" - 前缀和 + 哈希表
 * 3. "连续子数组" - 前缀和
 * 4. "和为 K" - 前缀和 + 哈希表
 * 5. "多次查询" - 前缀和
 *
 * ✅ 题目特征：
 * - 频繁查询区间和
 * - 数组不变或很少变
 * - 需要优化查询时间
 *
 * ❌ 不适合前缀和：
 * - 频繁修改数组（用线段树）
 * - 不是求和问题
 * - 需要最值而非和
 */

/*
 * ============================================================================
 * 第三部分：核心模板
 * ============================================================================
 */

// ============================================================================
// 模板 1：一维前缀和
// 预处理：O(n)
// 查询：O(1)
// 空间：O(n)
// ============================================================================

class PrefixSum1D {
private:
    vector<int> prefix;

public:
    PrefixSum1D(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);

        // 构建前缀和数组
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    // 查询区间 [left, right] 的和
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

// ============================================================================
// 模板 2：二维前缀和
// 预处理：O(m * n)
// 查询：O(1)
// 空间：O(m * n)
// ============================================================================

class PrefixSum2D {
private:
    vector<vector<int>> prefix;

public:
    PrefixSum2D(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;

        int m = matrix.size(), n = matrix[0].size();
        prefix.resize(m + 1, vector<int>(n + 1, 0));

        // 构建二维前缀和
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1]
                             + prefix[i-1][j]
                             + prefix[i][j-1]
                             - prefix[i-1][j-1];
            }
        }
    }

    // 查询子矩阵 (row1, col1) 到 (row2, col2) 的和
    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefix[row2+1][col2+1]
             - prefix[row1][col2+1]
             - prefix[row2+1][col1]
             + prefix[row1][col1];
    }
};

// ============================================================================
// 模板 3：前缀和 + 哈希表（求和为 K 的子数组）
// 时间复杂度：O(n)
// 空间复杂度：O(n)
// ============================================================================

class PrefixSumWithHash {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixCount;  // 前缀和 -> 出现次数
        prefixCount[0] = 1;  // 重要：前缀和为 0 出现 1 次

        int prefixSum = 0, count = 0;

        for (int num : nums) {
            prefixSum += num;

            // 查找 prefixSum - k 是否存在
            if (prefixCount.count(prefixSum - k)) {
                count += prefixCount[prefixSum - k];
            }

            prefixCount[prefixSum]++;
        }

        return count;
    }
};

/*
 * ============================================================================
 * 第四部分：常见变体
 * ============================================================================
 */

// ============================================================================
// 变体 1：区域和检索 - 数组不可变
// LeetCode 303: Range Sum Query - Immutable
// ============================================================================

class NumArray {
private:
    vector<int> prefix;

public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

// ============================================================================
// 变体 2：二维区域和检索 - 矩阵不可变
// LeetCode 304: Range Sum Query 2D - Immutable
// ============================================================================

class NumMatrix {
private:
    vector<vector<int>> prefix;

public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;

        int m = matrix.size(), n = matrix[0].size();
        prefix.resize(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1]
                             + prefix[i-1][j]
                             + prefix[i][j-1]
                             - prefix[i-1][j-1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefix[row2+1][col2+1]
             - prefix[row1][col2+1]
             - prefix[row2+1][col1]
             + prefix[row1][col1];
    }
};

// ============================================================================
// 变体 3：和为 K 的子数组
// LeetCode 560: Subarray Sum Equals K
// ============================================================================

class Solution_SubarraySum {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixCount;
        prefixCount[0] = 1;

        int prefixSum = 0, count = 0;

        for (int num : nums) {
            prefixSum += num;

            if (prefixCount.count(prefixSum - k)) {
                count += prefixCount[prefixSum - k];
            }

            prefixCount[prefixSum]++;
        }

        return count;
    }
};

// ============================================================================
// 变体 4：连续的子数组和
// LeetCode 523: Continuous Subarray Sum
// ============================================================================

class Solution_CheckSubarraySum {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> remainderIndex;  // 余数 -> 第一次出现的位置
        remainderIndex[0] = -1;

        int prefixSum = 0;

        for (int i = 0; i < nums.size(); i++) {
            prefixSum += nums[i];
            int remainder = prefixSum % k;

            if (remainderIndex.count(remainder)) {
                if (i - remainderIndex[remainder] >= 2) {
                    return true;
                }
            } else {
                remainderIndex[remainder] = i;
            }
        }

        return false;
    }
};

// ============================================================================
// 变体 5：和可被 K 整除的子数组
// LeetCode 974: Subarray Sums Divisible by K
// ============================================================================

class Solution_SubarraysDivByK {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int> remainderCount;
        remainderCount[0] = 1;

        int prefixSum = 0, count = 0;

        for (int num : nums) {
            prefixSum += num;
            int remainder = ((prefixSum % k) + k) % k;  // 处理负数

            count += remainderCount[remainder];
            remainderCount[remainder]++;
        }

        return count;
    }
};

/*
 * ============================================================================
 * 第五部分：面试技巧
 * ============================================================================
 */

/*
 * 【30 秒讲清前缀和】
 * 1. 先说痛点：
 *    "如果每次都遍历区间求和，单次 O(n)，多次查询会超时。"
 * 2. 再说优化：
 *    "我先做 O(n) 预处理，后续区间和都用两次前缀和相减 O(1) 得到。"
 * 3. 最后扩展：
 *    "若题目是统计子数组个数，可配合哈希表记录前缀和频次。"
 *
 * 【面试官高频追问】
 * Q1: 为什么 prefix 长度是 n+1？
 * A1: 让区间公式统一为 prefix[r+1]-prefix[l]，避免 left=0 特判。
 *
 * Q2: 为什么哈希初始化 prefixCount[0]=1？
 * A2: 表示空前缀，支持从下标 0 开始的合法子数组。
 */

/*
 * ============================================================================
 * 第六部分：易错点
 * ============================================================================
 */

/*
 * 【常见错误 1：区间公式 off-by-one】
 * ❌ prefix[right] - prefix[left]
 * ✅ prefix[right + 1] - prefix[left]
 *
 * 【常见错误 2：漏初始化空前缀】
 * ❌ unordered_map<int, int> cnt;
 * ✅ cnt[0] = 1;
 *
 * 【常见错误 3：取模余数为负】
 * ❌ int r = sum % k;
 * ✅ int r = ((sum % k) + k) % k;
 *
 * 【常见错误 4：二维容斥写反】
 * ✅ prefix[i][j] = a + up + left - overlap
 */

/*
 * ============================================================================
 * 第七部分：复杂度分析
 * ============================================================================
 */

/*
 * 【一维前缀和】
 * 预处理：O(n)
 * 单次查询：O(1)
 * 空间：O(n)
 *
 * 【二维前缀和】
 * 预处理：O(m * n)
 * 单次查询：O(1)
 * 空间：O(m * n)
 *
 * 【前缀和 + 哈希表计数】
 * 时间：O(n)
 * 空间：O(n)
 */

/*
 * ============================================================================
 * 第八部分：真题实战
 * ============================================================================
 */

/*
 * ⭐ 简单
 * 1. LC 303: 区域和检索 - 数组不可变
 * 2. LC 724: 寻找数组的中心下标
 *
 * ⭐⭐ 中等（高频）
 * 3. LC 560: 和为 K 的子数组 ⭐⭐⭐⭐⭐
 * 4. LC 304: 二维区域和检索 ⭐⭐⭐⭐
 * 5. LC 523: 连续的子数组和 ⭐⭐⭐⭐
 * 6. LC 974: 和可被 K 整除的子数组 ⭐⭐⭐⭐
 *
 * ⭐⭐⭐ 困难
 * 7. LC 1074: 元素和为目标值的子矩阵数量
 */

/*
 * ============================================================================
 * 第九部分：完整示例
 * ============================================================================
 */

void testSubarraySum() {
    vector<int> nums = {1, 1, 1};
    int k = 2;
    PrefixSumWithHash solver;
    cout << "和为 " << k << " 的子数组个数: " << solver.subarraySum(nums, k) << endl;
}

/*
 * ============================================================================
 * 第十部分：速查表
 * ============================================================================
 */

/*
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │                    Prefix Sum 算法速查表                                │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 * 【一维前缀和】
 * vector<int> prefix(n + 1, 0);
 * for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + nums[i];
 * sum(l, r) = prefix[r + 1] - prefix[l];
 *
 * 【二维前缀和】
 * ps[i][j] = a[i-1][j-1] + ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1];
 * sum(r1,c1,r2,c2) = ps[r2+1][c2+1] - ps[r1][c2+1] - ps[r2+1][c1] + ps[r1][c1];
 *
 * 【前缀和 + 哈希】
 * cnt[0] = 1;
 * sum += nums[i];
 * ans += cnt[sum - k];
 * cnt[sum]++;
 */

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    PrefixSum1D ps(nums);
    cout << "区间 [1, 3] 的和: " << ps.sumRange(1, 3) << endl;

    testSubarraySum();
    cout << "前缀和算法模板测试完成" << endl;
    return 0;
}

/*
 * 编译运行：
 * g++ -std=c++11 -o prefix_sum prefix_sum_template.cpp && ./prefix_sum
 */
