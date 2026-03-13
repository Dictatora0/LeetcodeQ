/*
LeetCode 238. 除自身以外数组的乘积 (Product of Array Except Self)

题目概述 (Problem Summary)
-------------------------
给定一个长度为 n 的整数数组 nums，返回一个数组 answer，
其中 answer[i] 等于 nums 中除 nums[i] 之外所有元素的乘积。
要求：不使用除法，且时间复杂度 O(n)。

关键约束 (Key Constraints)
-------------------------
- 2 <= nums.length <= 10^5
- -30 <= nums[i] <= 30
- 所有元素的前缀或后缀乘积都在 32 位整数范围内
- 不允许使用除法

示例 (Example)
-------------
输入：nums = [1,2,3,4]
输出：[24,12,8,6]
解释：
answer[0] = 2*3*4 = 24
answer[1] = 1*3*4 = 12
answer[2] = 1*2*4 = 8
answer[3] = 1*2*3 = 6

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 对每个位置 i，需要“左侧所有元素乘积”与“右侧所有元素乘积”

关键观察：
1. 若预先计算每个位置的左乘积与右乘积，可 O(1) 得到结果
2. 左乘积数组 prefix[i] = nums[0..i-1] 的乘积
3. 右乘积数组 suffix[i] = nums[i+1..n-1] 的乘积

根据这些观察，可以得到两种典型解法：
1. 前缀乘积 + 后缀乘积数组
2. 原地使用输出数组 + 右侧累计乘积（空间优化）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
分别构建 prefix 与 suffix 数组，
答案为 prefix[i] * suffix[i]。

算法流程：
1. prefix[i] = nums[0..i-1] 的乘积
2. suffix[i] = nums[i+1..n-1] 的乘积
3. answer[i] = prefix[i] * suffix[i]

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> prefix(n, 1), suffix(n, 1), result(n, 1);

        for (int i = 1; i < n; ++i) {
            prefix[i] = prefix[i - 1] * nums[i - 1];
        }
        for (int i = n - 2; i >= 0; --i) {
            suffix[i] = suffix[i + 1] * nums[i + 1];
        }
        for (int i = 0; i < n; ++i) {
            result[i] = prefix[i] * suffix[i];
        }

        return result;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - O(1) Extra Space)

优化思路
--------
直接在结果数组中存储前缀乘积，
再从右往左维护一个 right 乘积，动态乘上去。

为什么更快：
- 减少额外数组使用
- 仍然线性时间

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(1)（不计输出数组）
*/
class Solution_Optimized {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> result(n, 1);

        // result[i] 先存左侧乘积
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] * nums[i - 1];
        }

        // right 维护右侧乘积
        int right = 1;
        for (int i = n - 1; i >= 0; --i) {
            result[i] = result[i] * right;
            right *= nums[i];
        }

        return result;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [1,2,3,4]

前缀乘积：
result = [1,1,2,6]

从右向左维护 right：
right=1 -> result[3]=6*1=6, right=4
right=4 -> result[2]=2*4=8, right=12
right=12 -> result[1]=1*12=12, right=24
right=24 -> result[0]=1*24=24
最终 [24,12,8,6]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：前缀 + 后缀数组
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：思路直观
- 缺点：额外空间

方法二：输出数组复用
- 时间复杂度：O(n)
- 空间复杂度：O(1)
- 优点：空间最优
- 缺点：理解稍复杂
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 含 0：仍可正确处理（无需除法）
2. 全为负数：乘积结果依然正确
3. 数组长度为 2：互为对方
*/

static void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i + 1 < nums.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution_Optimized solution;

    // 测试用例 1
    vector<int> nums1 = {1, 2, 3, 4};
    vector<int> result1 = solution.productExceptSelf(nums1);
    cout << "测试用例 1 - 输出: ";
    printVector(result1);
    cout << " (期望: [24, 12, 8, 6])" << endl;

    // 测试用例 2
    vector<int> nums2 = {-1, 1, 0, -3, 3};
    vector<int> result2 = solution.productExceptSelf(nums2);
    cout << "测试用例 2 - 输出: ";
    printVector(result2);
    cout << " (期望: [0, 0, 9, 0, 0])" << endl;

    return 0;
}
