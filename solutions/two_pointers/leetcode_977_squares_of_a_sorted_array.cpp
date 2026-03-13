/*
LeetCode 977. 有序数组的平方 (Squares of a Sorted Array)

题目概述 (Problem Summary)
-------------------------
给定一个按非递减顺序排序的整数数组 nums，返回每个元素平方后的新数组，
并要求结果同样按非递减顺序排序。

关键约束 (Key Constraints)
-------------------------
- 1 <= nums.length <= 10^4
- -10^4 <= nums[i] <= 10^4
- nums 已按非递减顺序排序

示例 (Example)
-------------
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后为 [16,1,0,9,100]，排序后得到结果

算法思路 (Algorithm Thinking)
----------------------------
这道题本质在解决什么问题？
- 有序数组平方后会破坏顺序，需要重新得到有序结果

关键观察：
1. 最大平方值一定来自数组两端（绝对值最大）
2. 可以用双指针从两端向中间收缩
3. 从结果数组末尾向前填入最大平方

根据这些观察，可以得到两种典型解法：
1. 双指针（最优）
2. 直接平方后排序（更简单但更慢）
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
方法一：我的原始解法 (Approach 1: My Original Solution)

核心思想
--------
使用双指针分别指向数组两端，
比较两端平方的大小，将较大者放到结果数组的末尾。

算法流程：
1. left 指向起点，right 指向终点
2. 比较 nums[left]^2 与 nums[right]^2
3. 将较大值放到 result[pos]，并移动对应指针
4. pos 从末尾向前移动

复杂度分析
---------
时间复杂度：O(n)
空间复杂度：O(n)
*/
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> result(n, 0);
        int left = 0;
        int right = n - 1;
        int pos = n - 1;

        while (left <= right) {
            int leftVal = nums[left] * nums[left];
            int rightVal = nums[right] * nums[right];

            if (leftVal > rightVal) {
                result[pos--] = leftVal;
                left++;
            } else {
                result[pos--] = rightVal;
                right--;
            }
        }

        return result;
    }
};

/*
方法二：优化解法 (Approach 2: Optimized Solution - Sort After Square)

优化思路
--------
先对每个元素平方，再整体排序。
实现简单但复杂度更高。

为什么可行：
- 排序保证最终结果有序

复杂度分析
---------
时间复杂度：O(n log n)
空间复杂度：O(1)（忽略排序实现的额外空间）
*/
class Solution_Optimized {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        for (int& x : nums) {
            x = x * x;
        }
        sort(nums.begin(), nums.end());
        return nums;
    }
};

/*
示例推演 (Example Walkthrough)
-----------------------------
nums = [-4,-1,0,3,10]

left=-4, right=10 -> 比较 16 和 100，放 100
left=-4, right=3  -> 比较 16 和 9，放 16
left=-1, right=3  -> 比较 1 和 9，放 9
left=-1, right=0  -> 比较 1 和 0，放 1
left=0, right=0   -> 放 0
结果：[0,1,9,16,100]
*/

/*
复杂度对比 (Complexity Comparison)
---------------------------------
方法一：双指针
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：最优时间复杂度
- 缺点：需要额外结果数组

方法二：平方后排序
- 时间复杂度：O(n log n)
- 空间复杂度：O(1)
- 优点：实现简单
- 缺点：性能较差
*/

/*
特殊情况 (Edge Cases)
--------------------
1. 全负数：依旧可用双指针
2. 全非负数：结果与原数组平方一致
3. 含 0：正常处理
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
    Solution solution;

    // 测试用例 1
    vector<int> nums1 = {-4, -1, 0, 3, 10};
    vector<int> result1 = solution.sortedSquares(nums1);
    cout << "测试用例 1 - 输出: ";
    printVector(result1);
    cout << " (期望: [0, 1, 9, 16, 100])" << endl;

    // 测试用例 2
    vector<int> nums2 = {-7, -3, 2, 3, 11};
    vector<int> result2 = solution.sortedSquares(nums2);
    cout << "测试用例 2 - 输出: ";
    printVector(result2);
    cout << " (期望: [4, 9, 9, 49, 121])" << endl;

    return 0;
}
