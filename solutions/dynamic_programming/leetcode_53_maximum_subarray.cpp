/*
LeetCode 53. 最大子数组和 (Maximum Subarray)

题目概述 (Problem Summary)
-------------------------
给定一个整数数组 nums，找出具有最大和的连续子数组（至少包含一个元素），返回其最大和。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4

示例 (Example)
-------------
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：最大子数组为 [4,-1,2,1]，和为 6

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 需要在所有连续子数组中找到最大和

关键观察：
1. 如果当前子数组和为负数，继续扩展只会拖累结果
2. 动态规划可以记录“以当前位置结尾的最大和”
3. 全局最大值在遍历过程中更新

根据这些观察，可以得到两种典型解法：
1. 动态规划（Kadane 算法）
2. 分治法（对比思路）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
用 dp 表示以当前位置结尾的最大子数组和：
dp[i] = max(nums[i], dp[i-1] + nums[i])
遍历过程中维护全局最大值。

算法流程：
1. 初始化 current = nums[0], best = nums[0]
2. 从 i=1 开始遍历
3. current = max(nums[i], current + nums[i])
4. best = max(best, current)

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int current = nums[0];
        int best = nums[0];

        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            current = max(nums[i], current + nums[i]);
            best = max(best, current);
        }

        return best;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Divide and Conquer)

优化思路
--------
分治将数组分为左右两部分，最大子数组可能在：
1. 左区间
2. 右区间
3. 跨越中点

合并时只需计算跨越中点的最大和。

复杂度分析
---------
时间复杂度：O(n log n)
空间复杂度：O(log n)
*/
class Solution_Optimized {
public:
    int maxSubArray(vector<int>& nums) {
        return divide(nums, 0, static_cast<int>(nums.size()) - 1);
    }

private:
    int divide(vector<int>& nums, int left, int right) {
        if (left == right) return nums[left];
        int mid = left + (right - left) / 2;

        int leftMax = divide(nums, left, mid);
        int rightMax = divide(nums, mid + 1, right);

        int sum = 0;
        int leftSum = nums[mid];
        for (int i = mid; i >= left; --i) {
            sum += nums[i];
            leftSum = max(leftSum, sum);
        }

        sum = 0;
        int rightSum = nums[mid + 1];
        for (int i = mid + 1; i <= right; ++i) {
            sum += nums[i];
            rightSum = max(rightSum, sum);
        }

        return max({leftMax, rightMax, leftSum + rightSum});
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [-2,1,-3,4,-1,2,1,-5,4]

扫描过程：
current = -2, best = -2
current = max(1, -2+1)=1, best=1
current = max(-3, 1-3)=-2, best=1
current = max(4, -2+4)=4, best=4
current = max(-1, 4-1)=3, best=4
current = max(2, 3+2)=5, best=5
current = max(1, 5+1)=6, best=6
current = max(-5, 6-5)=1, best=6
current = max(4, 1+4)=5, best=6
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：Kadane 动态规划
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：线性最优
- 缺点：只给最大和，不给区间

方法二：分治
- 时间复杂度：O(n log n)
- 空间复杂度：O(log n)
- 优点：思路清晰，可拓展统计
- 缺点：复杂度更高
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全为负数：返回最大（最不负）值
2. 只有一个元素：直接返回该元素
3. 含 0：正常处理
*/

int main() {
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "测试用例 1 - 输出: " << solution.maxSubArray(nums1)
         << " (期望: 6)" << endl;

    // 测试用例 2
    vector<int> nums2 = {1};
    cout << "测试用例 2 - 输出: " << solution.maxSubArray(nums2)
         << " (期望: 1)" << endl;

    return 0;
}
