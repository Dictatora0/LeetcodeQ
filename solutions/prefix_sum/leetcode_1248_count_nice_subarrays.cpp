/*
 * LeetCode 1248: 统计优美子数组 (Count Number of Nice Subarrays)
 * 难度：Medium
 *
 * ============================================================================
 * 题目概述
 * ============================================================================
 * 给你一个整数数组 nums 和一个整数 k。如果某个连续子数组中恰好有 k 个奇数数字，
 * 我们就认为这个子数组是「优美子数组」。
 *
 * 请返回这个数组中「优美子数组」的数目。
 *
 * 关键约束：
 * - 1 <= nums.length <= 50000
 * - 1 <= nums[i] <= 10^5
 * - 1 <= k <= nums.length
 *
 * ============================================================================
 * 示例
 * ============================================================================
 * 示例 1:
 * 输入：nums = [1,1,2,1,1], k = 3
 * 输出：2
 * 解释：包含 3 个奇数的子数组是 [1,1,2,1] 和 [1,2,1,1]
 *
 * 示例 2:
 * 输入：nums = [2,4,6], k = 1
 * 输出：0
 * 解释：数组中没有奇数，所以不存在优美子数组
 *
 * 示例 3:
 * 输入：nums = [2,2,2,1,2,2,1,2,2,2], k = 2
 * 输出：16
 *
 * ============================================================================
 * 核心思想：问题转换 + 前缀和 + 哈希表
 * ============================================================================
 *
 * 1. 问题转换：
 *    将奇数转换为 1，偶数转换为 0
 *    问题变为：找和为 k 的子数组个数
 *    这就是 LeetCode 560 的变形！
 *
 * 2. 转换示例：
 *    原数组：[1, 1, 2, 1, 1]  k = 3
 *    转换后：[1, 1, 0, 1, 1]  k = 3
 *    问题：找和为 3 的子数组个数
 *
 * 3. 前缀和定义：
 *    prefixSum[i] = 前 i 个数中奇数的个数
 *
 * 4. 算法流程：
 *    - 遍历数组，将奇数计为 1，偶数计为 0
 *    - 计算前缀和（奇数个数）
 *    - 使用哈希表记录每个前缀和出现的次数
 *    - 查找 (prefixSum - k) 在哈希表中的次数
 *
 * ============================================================================
 * 问题转换详解
 * ============================================================================
 *
 * 为什么可以转换：
 * - 奇数的个数 = 1 的个数
 * - 子数组中奇数的个数 = 子数组中 1 的个数 = 子数组的和
 *
 * 转换的好处：
 * - 将"计数"问题转换为"求和"问题
 * - 可以使用前缀和技巧
 * - 降低问题复杂度
 *
 * ============================================================================
 * 前缀和原理图解
 * ============================================================================
 *
 * 原数组：   [1,  1,  2,  1,  1]    k = 3
 * 转换后：   [1,  1,  0,  1,  1]
 * 索引：      0   1   2   3   4
 *
 * 前缀和（奇数个数）：
 * prefixSum[0] = 0  (初始)
 * prefixSum[1] = 1  (1个奇数)
 * prefixSum[2] = 2  (2个奇数)
 * prefixSum[3] = 2  (2个奇数)
 * prefixSum[4] = 3  (3个奇数)
 * prefixSum[5] = 4  (4个奇数)
 *
 * 查找过程：
 * i=0: prefixSum=1, 查找 1-3=-2 (不存在), count=0
 * i=1: prefixSum=2, 查找 2-3=-1 (不存在), count=0
 * i=2: prefixSum=2, 查找 2-3=-1 (不存在), count=0
 * i=3: prefixSum=3, 查找 3-3=0 (存在1次), count=1  -> 子数组[0,3]
 * i=4: prefixSum=4, 查找 4-3=1 (存在1次), count=2  -> 子数组[1,4]
 *
 * 结果：2 个优美子数组
 *
 * ============================================================================
 * 复杂度分析
 * ============================================================================
 *
 * 方法1：前缀和 + 哈希表（最优）
 * 时间复杂度：O(n) - 遍历一次数组
 * 空间复杂度：O(n) - 哈希表最多存储 n 个前缀和
 *
 * 方法2：滑动窗口
 * 时间复杂度：O(n) - 需要仔细处理边界
 * 空间复杂度：O(1)
 *
 * 方法3：暴力枚举
 * 时间复杂度：O(n²) - 双重循环
 * 空间复杂度：O(1)
 *
 * ============================================================================
 * 特殊情况处理
 * ============================================================================
 *
 * 1. 全是偶数：没有奇数，返回 0
 * 2. 全是奇数：每个长度为 k 的子数组都是优美子数组
 * 3. k = 1：每个包含一个奇数的子数组都是优美子数组
 * 4. k > 奇数总数：返回 0
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
    // 1. 将奇数转换为 1，偶数转换为 0
    // 2. 问题变为：找和为 k 的子数组个数（LeetCode 560）
    // 3. 使用前缀和 + 哈希表解决
    // ========================================================================
    int numberOfSubarrays(vector<int>& nums, int k) {
        // 哈希表：key = 前缀和（奇数个数），value = 该前缀和出现的次数
        unordered_map<int, int> prefixSumCount;

        // 初始化：前缀和为 0 出现 1 次（表示空数组）
        prefixSumCount[0] = 1;

        int prefixSum = 0;  // 当前前缀和（奇数个数）
        int count = 0;      // 优美子数组个数

        // 遍历数组
        for (int i = 0; i < nums.size(); i++) {
            // 更新前缀和：奇数计为 1，偶数计为 0
            if (nums[i] % 2 == 1) {
                prefixSum++;
            }

            // 查找是否存在前缀和为 (prefixSum - k)
            // 如果存在，说明从那个位置到当前位置有 k 个奇数
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
    // 方法2：滑动窗口（另一种思路）
    // ========================================================================
    // 核心思想：
    // 1. 找到恰好包含 k 个奇数的窗口
    // 2. 计算左右两侧可以扩展的偶数个数
    // 3. 组合数 = (左侧偶数+1) * (右侧偶数+1)
    // ========================================================================
    int numberOfSubarraysSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;
        int oddCount = 0;  // 当前窗口中奇数的个数
        int left = 0;

        // 记录每个奇数的位置
        vector<int> oddPositions;
        oddPositions.push_back(-1);  // 哨兵

        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 1) {
                oddPositions.push_back(i);
            }
        }
        oddPositions.push_back(n);  // 哨兵

        // 如果奇数个数小于 k，返回 0
        if (oddPositions.size() - 2 < k) {
            return 0;
        }

        // 枚举每个包含 k 个奇数的窗口
        for (int i = 1; i + k < oddPositions.size(); i++) {
            // 第 i 个奇数到第 i+k-1 个奇数
            int leftCount = oddPositions[i] - oddPositions[i - 1];
            int rightCount = oddPositions[i + k] - oddPositions[i + k - 1];
            count += leftCount * rightCount;
        }

        return count;
    }

    // ========================================================================
    // 方法3：暴力枚举（用于对比）
    // ========================================================================
    // 枚举所有子数组，统计奇数个数
    // ========================================================================
    int numberOfSubarraysBruteForce(vector<int>& nums, int k) {
        int count = 0;
        int n = nums.size();

        // 枚举起点 i
        for (int i = 0; i < n; i++) {
            int oddCount = 0;
            // 枚举终点 j
            for (int j = i; j < n; j++) {
                if (nums[j] % 2 == 1) {
                    oddCount++;
                }
                if (oddCount == k) {
                    count++;
                }
                if (oddCount > k) {
                    break;  // 剪枝
                }
            }
        }

        return count;
    }
};

// ============================================================================
// 示例推演：展示问题转换和前缀和的变化过程
// ============================================================================
void demonstrateAlgorithm() {
    cout << "============================================" << endl;
    cout << "示例推演：nums = [1, 1, 2, 1, 1], k = 3" << endl;
    cout << "============================================" << endl;

    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;

    cout << "步骤 1: 问题转换" << endl;
    cout << "  原数组: [";
    for (int i = 0; i < nums.size(); i++) {
        if (i > 0) cout << ", ";
        cout << nums[i];
    }
    cout << "]" << endl;

    cout << "  转换后: [";
    for (int i = 0; i < nums.size(); i++) {
        if (i > 0) cout << ", ";
        cout << (nums[i] % 2);
    }
    cout << "] (奇数->1, 偶数->0)" << endl;
    cout << "  问题变为：找和为 " << k << " 的子数组个数" << endl << endl;

    cout << "步骤 2: 前缀和 + 哈希表" << endl;

    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;

    int prefixSum = 0;
    int count = 0;

    cout << "初始状态：" << endl;
    cout << "  哈希表: {0: 1}" << endl;
    cout << "  count = 0" << endl << endl;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] % 2 == 1) {
            prefixSum++;
        }

        int target = prefixSum - k;

        cout << "步骤 " << (i + 1) << ": 处理 nums[" << i << "] = " << nums[i]
             << " (" << (nums[i] % 2 == 1 ? "奇数" : "偶数") << ")" << endl;
        cout << "  当前前缀和（奇数个数）: " << prefixSum << endl;
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

    cout << "最终结果：" << count << " 个优美子数组" << endl;
    cout << "============================================" << endl << endl;
}

// ============================================================================
// 问题转换演示
// ============================================================================
void demonstrateTransformation() {
    cout << "============================================" << endl;
    cout << "问题转换演示" << endl;
    cout << "============================================" << endl;

    cout << "原问题：找恰好有 k 个奇数的子数组" << endl;
    cout << "转换后：找和为 k 的子数组（奇数=1, 偶数=0）" << endl << endl;

    cout << "为什么可以转换：" << endl;
    cout << "  - 奇数的个数 = 1 的个数" << endl;
    cout << "  - 子数组中奇数的个数 = 子数组中 1 的个数 = 子数组的和" << endl << endl;

    cout << "转换的好处：" << endl;
    cout << "  - 将\"计数\"问题转换为\"求和\"问题" << endl;
    cout << "  - 可以使用前缀和技巧" << endl;
    cout << "  - 降低问题复杂度" << endl << endl;

    cout << "示例：" << endl;
    cout << "  原数组: [1, 1, 2, 1, 1], k = 3" << endl;
    cout << "  转换后: [1, 1, 0, 1, 1], k = 3" << endl;
    cout << "  问题: 找和为 3 的子数组个数" << endl;
    cout << "  这就是 LeetCode 560 的问题！" << endl << endl;

    cout << "============================================" << endl << endl;
}

// ============================================================================
// 测试用例
// ============================================================================
int main() {
    Solution solution;

    // 演示问题转换
    demonstrateTransformation();

    // 演示算法过程
    demonstrateAlgorithm();

    // 测试用例 1：基本情况
    vector<int> nums1 = {1, 1, 2, 1, 1};
    int k1 = 3;
    cout << "测试 1: nums = [1,1,2,1,1], k = 3" << endl;
    cout << "前缀和: " << solution.numberOfSubarrays(nums1, k1) << " (期望: 2)" << endl;
    cout << "滑窗: " << solution.numberOfSubarraysSlidingWindow(nums1, k1) << endl;
    cout << "暴力: " << solution.numberOfSubarraysBruteForce(nums1, k1) << endl << endl;

    // 测试用例 2：全是偶数
    vector<int> nums2 = {2, 4, 6};
    int k2 = 1;
    cout << "测试 2: nums = [2,4,6], k = 1" << endl;
    cout << "前缀和: " << solution.numberOfSubarrays(nums2, k2) << " (期望: 0)" << endl;
    cout << "滑窗: " << solution.numberOfSubarraysSlidingWindow(nums2, k2) << endl;
    cout << "暴力: " << solution.numberOfSubarraysBruteForce(nums2, k2) << endl << endl;

    // 测试用例 3：复杂情况
    vector<int> nums3 = {2, 2, 2, 1, 2, 2, 1, 2, 2, 2};
    int k3 = 2;
    cout << "测试 3: nums = [2,2,2,1,2,2,1,2,2,2], k = 2" << endl;
    cout << "前缀和: " << solution.numberOfSubarrays(nums3, k3) << " (期望: 16)" << endl;
    cout << "滑窗: " << solution.numberOfSubarraysSlidingWindow(nums3, k3) << endl;
    cout << "暴力: " << solution.numberOfSubarraysBruteForce(nums3, k3) << endl << endl;

    // 测试用例 4：全是奇数
    vector<int> nums4 = {1, 3, 5, 7, 9};
    int k4 = 3;
    cout << "测试 4: nums = [1,3,5,7,9], k = 3" << endl;
    cout << "前缀和: " << solution.numberOfSubarrays(nums4, k4) << " (期望: 3)" << endl;
    cout << "滑窗: " << solution.numberOfSubarraysSlidingWindow(nums4, k4) << endl;
    cout << "暴力: " << solution.numberOfSubarraysBruteForce(nums4, k4) << endl << endl;

    // 测试用例 5：k = 1
    vector<int> nums5 = {1, 2, 3, 4, 5};
    int k5 = 1;
    cout << "测试 5: nums = [1,2,3,4,5], k = 1" << endl;
    cout << "前缀和: " << solution.numberOfSubarrays(nums5, k5) << " (期望: 9)" << endl;
    cout << "滑窗: " << solution.numberOfSubarraysSlidingWindow(nums5, k5) << endl;
    cout << "暴力: " << solution.numberOfSubarraysBruteForce(nums5, k5) << endl << endl;

    // 测试用例 6：单个元素
    vector<int> nums6 = {1};
    int k6 = 1;
    cout << "测试 6: nums = [1], k = 1" << endl;
    cout << "前缀和: " << solution.numberOfSubarrays(nums6, k6) << " (期望: 1)" << endl;
    cout << "滑窗: " << solution.numberOfSubarraysSlidingWindow(nums6, k6) << endl;
    cout << "暴力: " << solution.numberOfSubarraysBruteForce(nums6, k6) << endl << endl;

    return 0;
}

/*
 * ============================================================================
 * 关键要点总结
 * ============================================================================
 *
 * 1. 问题转换的重要性：
 *    - 将"计数"问题转换为"求和"问题
 *    - 奇数转换为 1，偶数转换为 0
 *    - 问题变为 LeetCode 560 的变形
 *
 * 2. 前缀和的应用：
 *    - prefixSum[i] = 前 i 个数中奇数的个数
 *    - 子数组 [i, j] 中奇数个数 = prefixSum[j+1] - prefixSum[i]
 *
 * 3. 哈希表的作用：
 *    - 记录每个前缀和（奇数个数）出现的次数
 *    - 快速查找 (prefixSum - k) 的次数
 *
 * 4. 与 LeetCode 560 的关系：
 *    - 本质上是同一个问题
 *    - 只是将奇数转换为 1，偶数转换为 0
 *
 * 5. 滑动窗口的思路：
 *    - 找到恰好包含 k 个奇数的窗口
 *    - 计算左右两侧可以扩展的偶数个数
 *    - 组合数 = (左侧偶数+1) * (右侧偶数+1)
 *
 * 6. 时间复杂度优化：
 *    - 从 O(n²) 优化到 O(n)
 *    - 问题转换 + 前缀和 + 哈希表
 *
 * ============================================================================
 * 相关题目
 * ============================================================================
 *
 * - LeetCode 560: 和为 K 的子数组（本题的原型）
 * - LeetCode 930: 和相同的二元子数组
 * - LeetCode 1371: 每个元音包含偶数次的最长子字符串
 * - LeetCode 525: 连续数组
 *
 */
