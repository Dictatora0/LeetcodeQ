/*
LeetCode 152. 乘积最大子数组 (Maximum Product Subarray)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 nums，找出数组中乘积最大的非空连续子数组（至少包含一个数字），返回该子数组的乘积。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 2 * 10^4
- -10 <= nums[i] <= 10
- 乘积结果保证在 32 位整数范围内

示例 (Example)
-------------
输入：nums = [2,3,-2,4]
输出：6
解释：子数组 [2,3] 有最大乘积 6

输入：nums = [-2,0,-1]
输出：0
解释：结果不能为 2，因为 [-2,-1] 不是连续子数组

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 在所有连续子数组中找到乘积最大值

关键观察：
1. 负数乘以负数会变成正数，所以需要同时维护最大值和最小值
2. 当前位置的最大乘积可能来自：
   - 当前元素本身（重新开始）
   - 前面的最大乘积 × 当前元素
   - 前面的最小乘积 × 当前元素（如果当前元素是负数）
3. 0 会重置乘积，需要特殊处理

根据这些观察，可以得到典型解法：
1. 动态规划（同时维护最大值和最小值）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：动态规划 (Approach 1: Dynamic Programming)

核心思想
--------
同时维护以当前位置结尾的最大乘积和最小乘积。

状态定义：
maxF = 以当前位置结尾的子数组的最大乘积
minF = 以当前位置结尾的子数组的最小乘积

状态转移方程：
maxF = max(nums[i], max(maxF * nums[i], minF * nums[i]))
minF = min(nums[i], min(maxF * nums[i], minF * nums[i]))

为什么需要维护最小值？
- 当遇到负数时，最小值（负数）乘以负数会变成最大值
- 例如：[-2, 3, -4]，在 -4 时，前面的最小值 -6 乘以 -4 得到 24

初始状态：
maxF = nums[0]
minF = nums[0]
ans = nums[0]

算法流程：
1. 初始化 maxF, minF, ans 为 nums[0]
2. 从 i=1 开始遍历
3. 保存当前的 maxF 和 minF（因为计算时会相互依赖）
4. 更新 maxF 和 minF
5. 更新全局最大值 ans

复杂度分析
---------
时间复杂度：O(n) - 单次遍历
空间复杂度：O(1) - 只用常量空间
*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int ans = nums[0];
        int maxF = nums[0];
        int minF = nums[0];

        for (int i = 1; i < n; i++) {
            int mx = maxF;
            int mn = minF;

            maxF = max(nums[i], max(mx * nums[i], mn * nums[i]));
            minF = min(nums[i], min(mx * nums[i], mn * nums[i]));

            ans = max(maxF, ans);
        }

        return ans;
    }
};

/*
方法二：动态规划数组版本 (Approach 2: DP with Arrays)

优化思路
--------
使用两个 dp 数组分别记录最大值和最小值，更直观地展示状态转移。

状态定义：
dpMax[i] = 以 nums[i] 结尾的子数组的最大乘积
dpMin[i] = 以 nums[i] 结尾的子数组的最小乘积

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n) - 两个 dp 数组
*/
class Solution_Array {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> dpMax(n);
        vector<int> dpMin(n);

        dpMax[0] = nums[0];
        dpMin[0] = nums[0];
        int ans = nums[0];

        for (int i = 1; i < n; i++) {
            dpMax[i] = max({nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            dpMin[i] = min({nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            ans = max(ans, dpMax[i]);
        }

        return ans;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [2,3,-2,4]

初始状态：
maxF = 2, minF = 2, ans = 2

i=1, nums[1]=3:
  mx = 2, mn = 2
  maxF = max(3, max(2*3, 2*3)) = max(3, 6) = 6
  minF = min(3, min(2*3, 2*3)) = min(3, 6) = 3
  ans = max(6, 2) = 6

i=2, nums[2]=-2:
  mx = 6, mn = 3
  maxF = max(-2, max(6*(-2), 3*(-2))) = max(-2, max(-12, -6)) = max(-2, -6) = -2
  minF = min(-2, min(6*(-2), 3*(-2))) = min(-2, min(-12, -6)) = min(-2, -12) = -12
  ans = max(-2, 6) = 6

i=3, nums[3]=4:
  mx = -2, mn = -12
  maxF = max(4, max(-2*4, -12*4)) = max(4, max(-8, -48)) = max(4, -8) = 4
  minF = min(4, min(-2*4, -12*4)) = min(4, min(-8, -48)) = min(4, -48) = -48
  ans = max(4, 6) = 6

最终答案：6

另一个例子：nums = [-2,3,-4]

初始状态：
maxF = -2, minF = -2, ans = -2

i=1, nums[1]=3:
  mx = -2, mn = -2
  maxF = max(3, max(-2*3, -2*3)) = max(3, -6) = 3
  minF = min(3, min(-2*3, -2*3)) = min(3, -6) = -6
  ans = max(3, -2) = 3

i=2, nums[2]=-4:
  mx = 3, mn = -6
  maxF = max(-4, max(3*(-4), -6*(-4))) = max(-4, max(-12, 24)) = 24
  minF = min(-4, min(3*(-4), -6*(-4))) = min(-4, min(-12, 24)) = -12
  ans = max(24, 3) = 24

最终答案：24（子数组 [3,-4] 或完整数组 [-2,3,-4]）
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：空间优化的动态规划
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：不容易回溯路径

方法二：数组版动态规划
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：状态转移更清晰
- 缺点：需要额外空间
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 只有一个元素：返回该元素
2. 包含 0：0 会重置乘积，需要重新开始
3. 全为负数：偶数个负数乘积为正，奇数个为负
4. 包含 1 和 -1：不影响乘积的绝对值
*/

int main() {
    Solution solution;
    Solution_Array solution_array;

    // 测试用例 1
    vector<int> nums1 = {2, 3, -2, 4};
    cout << "测试用例 1 - 方法一输出: " << solution.maxProduct(nums1)
         << " (期望: 6)" << endl;
    cout << "测试用例 1 - 方法二输出: " << solution_array.maxProduct(nums1)
         << " (期望: 6)" << endl;

    // 测试用例 2
    vector<int> nums2 = {-2, 0, -1};
    cout << "测试用例 2 - 方法一输出: " << solution.maxProduct(nums2)
         << " (期望: 0)" << endl;
    cout << "测试用例 2 - 方法二输出: " << solution_array.maxProduct(nums2)
         << " (期望: 0)" << endl;

    // 测试用例 3
    vector<int> nums3 = {-2, 3, -4};
    cout << "测试用例 3 - 方法一输出: " << solution.maxProduct(nums3)
         << " (期望: 24)" << endl;
    cout << "测试用例 3 - 方法二输出: " << solution_array.maxProduct(nums3)
         << " (期望: 24)" << endl;

    // 测试用例 4
    vector<int> nums4 = {-4, -3, -2};
    cout << "测试用例 4 - 方法一输出: " << solution.maxProduct(nums4)
         << " (期望: 12)" << endl;
    cout << "测试用例 4 - 方法二输出: " << solution_array.maxProduct(nums4)
         << " (期望: 12)" << endl;

    return 0;
}
