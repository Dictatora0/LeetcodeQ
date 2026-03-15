/*
 * LeetCode 560: 和为 K 的子数组 (Subarray Sum Equals K)
 * 难度：Medium
 *
 * ============================================================================
 * 题目概述
 * ============================================================================
 * 给你一个整数数组 nums 和一个整数 k，请你统计并返回该数组中和为 k 的连续子数组的个数。
 *
 * 关键约束：
 * - 1 <= nums.length <= 2 * 10^4
 * - -1000 <= nums[i] <= 1000
 * - -10^7 <= k <= 10^7
 * - 数组中可能包含负数和零
 *
 * ============================================================================
 * 示例
 * ============================================================================
 * 示例 1:
 * 输入：nums = [1,1,1], k = 2
 * 输出：2
 * 解释：子数组 [1,1] 和 [1,1] 的和都为 2
 *
 * 示例 2:
 * 输入：nums = [1,2,3], k = 3
 * 输出：2
 * 解释：子数组 [1,2] 和 [3] 的和都为 3
 *
 * 示例 3:
 * 输入：nums = [1,-1,0], k = 0
 * 输出：3
 * 解释：子数组 [1,-1], [-1,1], [0] 的和都为 0
 *
 * ============================================================================
 * 核心思想：前缀和 + 哈希表
 * ============================================================================
 *
 * 1. 前缀和定义：
 *    prefixSum[i] = nums[0] + nums[1] + ... + nums[i-1]
 *    prefixSum[0] = 0（表示空数组的和）
 *
 * 2. 区间和公式：
 *    sum(i, j) = nums[i] + nums[i+1] + ... + nums[j]
 *              = prefixSum[j+1] - prefixSum[i]
 *
 * 3. 问题转换：
 *    要找和为 k 的子数组 [i, j]，即：
 *    prefixSum[j+1] - prefixSum[i] = k
 *    => prefixSum[i] = prefixSum[j+1] - k
 *
 * 4. 算法流程：
 *    - 遍历数组，计算当前前缀和 prefixSum
 *    - 查找哈希表中是否存在 (prefixSum - k)
 *    - 如果存在，说明找到了若干个和为 k 的子数组
 *    - 将当前 prefixSum 加入哈希表
 *
 * ============================================================================
 * 前缀和原理图解
 * ============================================================================
 *
 * 数组：     [1,  2,  3,  -2,  1]    k = 3
 * 索引：      0   1   2   3    4
 *
 * 前缀和：
 * prefixSum[0] = 0
 * prefixSum[1] = 0 + 1 = 1
 * prefixSum[2] = 1 + 2 = 3
 * prefixSum[3] = 3 + 3 = 6
 * prefixSum[4] = 6 + (-2) = 4
 * prefixSum[5] = 4 + 1 = 5
 *
 * 查找过程：
 * i=0: prefixSum=1, 查找 1-3=-2 (不存在), count=0
 * i=1: prefixSum=3, 查找 3-3=0 (存在1次), count=1  -> 子数组[0,1]
 * i=2: prefixSum=6, 查找 6-3=3 (存在1次), count=2  -> 子数组[2,2]
 * i=3: prefixSum=4, 查找 4-3=1 (存在1次), count=3  -> 子数组[1,3]
 * i=4: prefixSum=5, 查找 5-3=2 (不存在), count=3
 *
 * 结果：3 个子数组 [1,2], [3], [2,3,-2,1]
 *
 * ============================================================================
 * 复杂度分析
 * ============================================================================
 *
 * 方法1：前缀和 + 哈希表（最优）
 * 时间复杂度：O(n) - 遍历一次数组，哈希表操作 O(1)
 * 空间复杂度：O(n) - 哈希表最多存储 n 个前缀和
 *
 * 方法2：暴力枚举
 * 时间复杂度：O(n²) - 双重循环枚举所有子数组
 * 空间复杂度：O(1) - 只需常数空间
 *
 * ============================================================================
 * 特殊情况处理
 * ============================================================================
 *
 * 1. 负数：前缀和可能减小，不影响算法正确性
 * 2. 零：前缀和可能不变，哈希表计数会增加
 * 3. 初始化：哈希表需要初始化 {0: 1}，表示空数组的前缀和为 0
 * 4. 重复前缀和：使用哈希表记录每个前缀和出现的次数
 *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // ========================================================================
    // 方法1：前缀和 + 哈希表（最优解法）
    // ========================================================================
    // 核心思想：
    // 1. 使用哈希表记录每个前缀和出现的次数
    // 2. 对于当前前缀和 prefixSum，查找 (prefixSum - k) 在哈希表中的次数
    // 3. 这个次数就是以当前位置结尾、和为 k 的子数组个数
    // ========================================================================
    int subarraySum(vector<int>& nums, int k) {
        // 哈希表：key = 前缀和，value = 该前缀和出现的次数
        unordered_map<int, int> prefixSumCount;

        // 初始化：前缀和为 0 出现 1 次（表示空数组）
        // 这是为了处理从索引 0 开始的子数组
        prefixSumCount[0] = 1;

        int prefixSum = 0;  // 当前前缀和
        int count = 0;      // 和为 k 的子数组个数

        // 遍历数组，计算前缀和
        for (int i = 0; i < nums.size(); i++) {
            // 更新前缀和
            prefixSum += nums[i];

            // 查找是否存在前缀和为 (prefixSum - k)
            // 如果存在，说明从那个位置到当前位置的子数组和为 k
            int target = prefixSum - k;
            if (prefixSumCount.find(target) != prefixSumCount.end()) {
                count += prefixSumCount[target];
            }

            // 将当前前缀和加入哈希表（或更新计数）
            prefixSumCount[prefixSum]++;
        }

        return count;
    }

    // ========================================================================
    // 方法2：暴力枚举（用于对比）
    // ========================================================================
    // 枚举所有可能的子数组 [i, j]，计算和是否等于 k
    // ========================================================================
    int subarraySumBruteForce(vector<int>& nums, int k) {
        int count = 0;
        int n = nums.size();

        // 枚举起点 i
        for (int i = 0; i < n; i++) {
            int sum = 0;
            // 枚举终点 j
            for (int j = i; j < n; j++) {
                sum += nums[j];
                if (sum == k) {
                    count++;
                }
            }
        }

        return count;
    }
};

// ============================================================================
// 示例推演：展示前缀和和哈希表的变化过程
// ============================================================================
void demonstrateAlgorithm() {
    cout << "============================================" << endl;
    cout << "示例推演：nums = [1, 2, 3, -2, 1], k = 3" << endl;
    cout << "============================================" << endl;

    vector<int> nums = {1, 2, 3, -2, 1};
    int k = 3;

    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;

    int prefixSum = 0;
    int count = 0;

    cout << "初始状态：" << endl;
    cout << "  哈希表: {0: 1}" << endl;
    cout << "  count = 0" << endl << endl;

    for (int i = 0; i < nums.size(); i++) {
        prefixSum += nums[i];
        int target = prefixSum - k;

        cout << "步骤 " << (i + 1) << ": 处理 nums[" << i << "] = " << nums[i] << endl;
        cout << "  当前前缀和: " << prefixSum << endl;
        cout << "  查找目标: " << target << " (prefixSum - k)" << endl;

        if (prefixSumCount.find(target) != prefixSumCount.end()) {
            cout << "  找到 " << prefixSumCount[target] << " 个匹配" << endl;
            count += prefixSumCount[target];
        } else {
            cout << "  未找到匹配" << endl;
        }

        prefixSumCount[prefixSum]++;

        cout << "  更新后 count = " << count << endl;
        cout << "  更新后哈希表: {";
        bool first = true;
        for (auto& p : prefixSumCount) {
            if (!first) cout << ", ";
            cout << p.first << ": " << p.second;
            first = false;
        }
        cout << "}" << endl << endl;
    }

    cout << "最终结果：" << count << " 个和为 " << k << " 的子数组" << endl;
    cout << "============================================" << endl << endl;
}

// ============================================================================
// 测试用例
// ============================================================================
int main() {
    Solution solution;

    // 演示算法过程
    demonstrateAlgorithm();

    // 测试用例 1：基本情况
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    cout << "测试 1: nums = [1,1,1], k = 2" << endl;
    cout << "结果: " << solution.subarraySum(nums1, k1) << " (期望: 2)" << endl;
    cout << "暴力: " << solution.subarraySumBruteForce(nums1, k1) << endl << endl;

    // 测试用例 2：包含负数
    vector<int> nums2 = {1, -1, 0};
    int k2 = 0;
    cout << "测试 2: nums = [1,-1,0], k = 0" << endl;
    cout << "结果: " << solution.subarraySum(nums2, k2) << " (期望: 3)" << endl;
    cout << "暴力: " << solution.subarraySumBruteForce(nums2, k2) << endl << endl;

    // 测试用例 3：单个元素
    vector<int> nums3 = {3};
    int k3 = 3;
    cout << "测试 3: nums = [3], k = 3" << endl;
    cout << "结果: " << solution.subarraySum(nums3, k3) << " (期望: 1)" << endl;
    cout << "暴力: " << solution.subarraySumBruteForce(nums3, k3) << endl << endl;

    // 测试用例 4：无解
    vector<int> nums4 = {1, 2, 3};
    int k4 = 7;
    cout << "测试 4: nums = [1,2,3], k = 7" << endl;
    cout << "结果: " << solution.subarraySum(nums4, k4) << " (期望: 0)" << endl;
    cout << "暴力: " << solution.subarraySumBruteForce(nums4, k4) << endl << endl;

    // 测试用例 5：多个重复前缀和
    vector<int> nums5 = {1, 2, 1, 2, 1};
    int k5 = 3;
    cout << "测试 5: nums = [1,2,1,2,1], k = 3" << endl;
    cout << "结果: " << solution.subarraySum(nums5, k5) << " (期望: 4)" << endl;
    cout << "暴力: " << solution.subarraySumBruteForce(nums5, k5) << endl << endl;

    // 测试用例 6：全是负数
    vector<int> nums6 = {-1, -1, -1};
    int k6 = -2;
    cout << "测试 6: nums = [-1,-1,-1], k = -2" << endl;
    cout << "结果: " << solution.subarraySum(nums6, k6) << " (期望: 2)" << endl;
    cout << "暴力: " << solution.subarraySumBruteForce(nums6, k6) << endl << endl;

    return 0;
}

/*
 * ============================================================================
 * 关键要点总结
 * ============================================================================
 *
 * 1. 前缀和的本质：
 *    - 将"子数组和"问题转换为"两个前缀和的差"问题
 *    - prefixSum[j] - prefixSum[i] = sum(i, j-1)
 *
 * 2. 哈希表的作用：
 *    - 快速查找是否存在某个前缀和
 *    - 记录每个前缀和出现的次数（处理重复）
 *
 * 3. 初始化的重要性：
 *    - prefixSumCount[0] = 1 是关键
 *    - 处理从索引 0 开始的子数组
 *
 * 4. 为什么不能用双指针/滑动窗口：
 *    - 数组中有负数，和不具有单调性
 *    - 无法通过移动指针来调整和的大小
 *
 * 5. 时间复杂度优化：
 *    - 从 O(n²) 优化到 O(n)
 *    - 空间换时间的经典案例
 *
 * ============================================================================
 * 相关题目
 * ============================================================================
 *
 * - LeetCode 974: 和可被 K 整除的子数组
 * - LeetCode 523: 连续的子数组和
 * - LeetCode 1248: 统计优美子数组
 * - LeetCode 525: 连续数组
 * - LeetCode 930: 和相同的二元子数组
 *
 */
